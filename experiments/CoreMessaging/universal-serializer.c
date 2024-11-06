#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <arpa/inet.h>  // for network byte order functions

// Type identifiers for our serialization system
typedef enum {
    TYPE_INT8 = 1,
    TYPE_INT16 = 2,
    TYPE_INT32 = 3,
    TYPE_INT64 = 4,
    TYPE_UINT8 = 5,
    TYPE_UINT16 = 6,
    TYPE_UINT32 = 7,
    TYPE_UINT64 = 8,
    TYPE_FLOAT = 9,
    TYPE_DOUBLE = 10,
    TYPE_STRING = 11,
    TYPE_STRUCT_START = 12,
    TYPE_STRUCT_END = 13
} SerialType;

// Metadata for each field
typedef struct {
    const char* name;
    SerialType type;
    size_t offset;
    size_t size;
} FieldInfo;

// Serialization context
typedef struct {
    uint8_t* buffer;
    size_t capacity;
    size_t position;
} SerializationContext;

// Function to swap endianness if needed
static void swap_bytes(void* data, size_t size) {
    uint8_t* bytes = (uint8_t*)data;
    for (size_t i = 0; i < size / 2; i++) {
        uint8_t temp = bytes[i];
        bytes[i] = bytes[size - 1 - i];
        bytes[size - 1 - i] = temp;
    }
}

// Write a value to the buffer with proper endianness handling
static bool write_value(SerializationContext* ctx, const void* value, SerialType type, size_t size) {
    // Check if we have enough space
    if (ctx->position + size + sizeof(SerialType) > ctx->capacity) {
        return false;
    }

    // Write type identifier
    ctx->buffer[ctx->position++] = (uint8_t)type;

    // Handle endianness for numeric types
    if (type != TYPE_STRING && type != TYPE_STRUCT_START && type != TYPE_STRUCT_END) {
        uint8_t temp[sizeof(uint64_t)];  // Maximum size buffer
        memcpy(temp, value, size);
        
        // Convert to network byte order (big-endian)
        if (size > 1) {
            swap_bytes(temp, size);
        }
        
        memcpy(ctx->buffer + ctx->position, temp, size);
        ctx->position += size;
    } else if (type == TYPE_STRING) {
        // For strings, write length first
        size_t len = strlen((const char*)value) + 1;
        uint32_t network_len = htonl((uint32_t)len);
        memcpy(ctx->buffer + ctx->position, &network_len, sizeof(uint32_t));
        ctx->position += sizeof(uint32_t);
        
        // Then write string data
        memcpy(ctx->buffer + ctx->position, value, len);
        ctx->position += len;
    }
    
    return true;
}

// Read a value from the buffer with proper endianness handling
static bool read_value(SerializationContext* ctx, void* value, SerialType expected_type, size_t size) {
    // Check if we have enough data
    if (ctx->position + 1 > ctx->capacity) {
        return false;
    }

    // Read and verify type
    SerialType type = (SerialType)ctx->buffer[ctx->position++];
    if (type != expected_type) {
        return false;
    }

    // Handle endianness for numeric types
    if (type != TYPE_STRING && type != TYPE_STRUCT_START && type != TYPE_STRUCT_END) {
        if (ctx->position + size > ctx->capacity) {
            return false;
        }
        
        memcpy(value, ctx->buffer + ctx->position, size);
        
        // Convert from network byte order (big-endian)
        if (size > 1) {
            swap_bytes(value, size);
        }
        
        ctx->position += size;
    } else if (type == TYPE_STRING) {
        // Read string length
        uint32_t network_len;
        memcpy(&network_len, ctx->buffer + ctx->position, sizeof(uint32_t));
        uint32_t len = ntohl(network_len);
        ctx->position += sizeof(uint32_t);
        
        if (ctx->position + len > ctx->capacity) {
            return false;
        }
        
        // Read string data
        memcpy(value, ctx->buffer + ctx->position, len);
        ctx->position += len;
    }
    
    return true;
}

// Macro to help define field information
#define FIELD_INFO(struct_name, field_name, field_type) \
    { #field_name, field_type, offsetof(struct_name, field_name), sizeof(((struct_name*)0)->field_name) }

// Example usage with a test structure
typedef struct {
    int32_t id;
    float value;
    char name[50];
    uint16_t flags;
} TestStruct;

// Define field information for TestStruct
static const FieldInfo test_struct_fields[] = {
    FIELD_INFO(TestStruct, id, TYPE_INT32),
    FIELD_INFO(TestStruct, value, TYPE_FLOAT),
    FIELD_INFO(TestStruct, name, TYPE_STRING),
    FIELD_INFO(TestStruct, flags, TYPE_UINT16)
};

// Serialize a structure
bool serialize_struct(const void* data, const FieldInfo* fields, size_t field_count, 
                     uint8_t* buffer, size_t buffer_size, size_t* bytes_written) {
    SerializationContext ctx = {buffer, buffer_size, 0};
    
    // Write struct start marker
    if (!write_value(&ctx, NULL, TYPE_STRUCT_START, 0)) {
        return false;
    }
    
    // Serialize each field
    for (size_t i = 0; i < field_count; i++) {
        const FieldInfo* field = &fields[i];
        const uint8_t* field_data = (const uint8_t*)data + field->offset;
        
        if (!write_value(&ctx, field_data, field->type, field->size)) {
            return false;
        }
    }
    
    // Write struct end marker
    if (!write_value(&ctx, NULL, TYPE_STRUCT_END, 0)) {
        return false;
    }
    
    *bytes_written = ctx.position;
    return true;
}

// Deserialize a structure
bool deserialize_struct(void* data, const FieldInfo* fields, size_t field_count,
                       const uint8_t* buffer, size_t buffer_size) {
    SerializationContext ctx = {(uint8_t*)buffer, buffer_size, 0};
    
    // Read and verify struct start marker
    SerialType type;
    if (!read_value(&ctx, &type, TYPE_STRUCT_START, 0)) {
        return false;
    }
    
    // Deserialize each field
    for (size_t i = 0; i < field_count; i++) {
        const FieldInfo* field = &fields[i];
        uint8_t* field_data = (uint8_t*)data + field->offset;
        
        if (!read_value(&ctx, field_data, field->type, field->size)) {
            return false;
        }
    }
    
    // Read and verify struct end marker
    if (!read_value(&ctx, &type, TYPE_STRUCT_END, 0)) {
        return false;
    }
    
    return true;
}

// Example usage
int main() {
    // Create test data
    TestStruct original = {
        .id = 12345,
        .value = 3.14159f,
        .name = "Test String",
        .flags = 0xABCD
    };
    
    // Buffer for serialized data
    uint8_t buffer[1024];
    size_t bytes_written;
    
    // Serialize
    if (!serialize_struct(&original, test_struct_fields, 
                         sizeof(test_struct_fields) / sizeof(FieldInfo),
                         buffer, sizeof(buffer), &bytes_written)) {
        printf("Serialization failed!\n");
        return 1;
    }
    
    printf("Serialized %zu bytes\n", bytes_written);
    
    // Create new struct for deserialized data
    TestStruct deserialized = {0};
    
    // Deserialize
    if (!deserialize_struct(&deserialized, test_struct_fields,
                           sizeof(test_struct_fields) / sizeof(FieldInfo),
                           buffer, bytes_written)) {
        printf("Deserialization failed!\n");
        return 1;
    }
    
    // Verify results
    printf("Original: id=%d, value=%f, name=%s, flags=0x%04X\n",
           original.id, original.value, original.name, original.flags);
    printf("Deserialized: id=%d, value=%f, name=%s, flags=0x%04X\n",
           deserialized.id, deserialized.value, deserialized.name, deserialized.flags);
    
    return 0;
}
