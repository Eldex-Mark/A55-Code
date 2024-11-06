################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rzg/aws/amazon-freertos/freertos_kernel/event_groups.c \
../rzg/aws/amazon-freertos/freertos_kernel/list.c \
../rzg/aws/amazon-freertos/freertos_kernel/queue.c \
../rzg/aws/amazon-freertos/freertos_kernel/stream_buffer.c \
../rzg/aws/amazon-freertos/freertos_kernel/tasks.c \
../rzg/aws/amazon-freertos/freertos_kernel/timers.c 

LST += \
event_groups.lst \
list.lst \
queue.lst \
stream_buffer.lst \
tasks.lst \
timers.lst 

C_DEPS += \
./rzg/aws/amazon-freertos/freertos_kernel/event_groups.d \
./rzg/aws/amazon-freertos/freertos_kernel/list.d \
./rzg/aws/amazon-freertos/freertos_kernel/queue.d \
./rzg/aws/amazon-freertos/freertos_kernel/stream_buffer.d \
./rzg/aws/amazon-freertos/freertos_kernel/tasks.d \
./rzg/aws/amazon-freertos/freertos_kernel/timers.d 

OBJS += \
./rzg/aws/amazon-freertos/freertos_kernel/event_groups.o \
./rzg/aws/amazon-freertos/freertos_kernel/list.o \
./rzg/aws/amazon-freertos/freertos_kernel/queue.o \
./rzg/aws/amazon-freertos/freertos_kernel/stream_buffer.o \
./rzg/aws/amazon-freertos/freertos_kernel/tasks.o \
./rzg/aws/amazon-freertos/freertos_kernel/timers.o 

MAP += \
rzg2l_cm33_rpmsg_demo.map 


# Each subdirectory must supply rules for building sources it contributes
rzg/aws/amazon-freertos/freertos_kernel/%.o: ../rzg/aws/amazon-freertos/freertos_kernel/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mthumb -mcpu=cortex-m33+nodsp+nofp -fdiagnostics-parseable-fixits -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wnull-dereference -g -gdwarf-4 -D_RENESAS_RZG_ -I"../generate" -I"../src" -I"../rzg/arm/CMSIS_5/CMSIS/Core/Include" -I"../rzg/fsp/src/rm_freertos_port" -I"../rzg/aws/amazon-freertos/freertos_kernel/include" -I"../src" -I"../rzg/fsp/inc" -I"../rzg/fsp/inc/api" -I"../rzg/fsp/inc/instances" -I"../rzg/fsp/src/bsp/mcu/rzg2l" -I"../rzg_gen" -I"../rzg_cfg/fsp_cfg/bsp" -I"../rzg_cfg/fsp_cfg" -I"../rzg_cfg/aws" -I"../rzg/linaro/open-amp/lib/include" -I"../rzg/linaro/libmetal/include" -std=c99 -w -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@echo $< && arm-none-eabi-gcc @"$@.in"

