// Define shared memory structure
#define MHU_SHARED_MEM ((volatile struct shared_data *)0x62F01000)

struct shared_data {
    volatile uint32_t data_ready;  // Flag for synchronization
    volatile uint32_t value;       // Actual data
    // Add other variables as needed
};

// In A55 core:
void write_shared_data(uint32_t new_value) {
    MHU_SHARED_MEM->value = new_value;
    // Memory barrier to ensure write is complete
    __DSB();
    // Set flag to indicate new data
    MHU_SHARED_MEM->data_ready = 1;
}

// In M33 core:
uint32_t read_shared_data(void) {
    while(!MHU_SHARED_MEM->data_ready) {
        // Optional: Add small delay if needed
        __NOP();
    }
    // Memory barrier to ensure fresh read
    __DSB();
    uint32_t value = MHU_SHARED_MEM->value;
    MHU_SHARED_MEM->data_ready = 0;  // Clear flag
    return value;
}
