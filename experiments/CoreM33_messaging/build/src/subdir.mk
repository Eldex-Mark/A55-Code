################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/MainTask_entry.c \
../src/blinky_thread_entry.c \
../src/hal_entry.c \
../src/mbed_printf_implementation.c \
../src/pin_data.c \
../src/platform_info.c \
../src/rpmsg_demo.c \
../src/rsc_table.c \
../src/rzg2_rproc.c \
../src/serial.c \
../src/sys_init.c 

LST += \
MainTask_entry.lst \
blinky_thread_entry.lst \
hal_entry.lst \
mbed_printf_implementation.lst \
pin_data.lst \
platform_info.lst \
rpmsg_demo.lst \
rsc_table.lst \
rzg2_rproc.lst \
serial.lst \
sys_init.lst 

C_DEPS += \
./src/MainTask_entry.d \
./src/blinky_thread_entry.d \
./src/hal_entry.d \
./src/mbed_printf_implementation.d \
./src/pin_data.d \
./src/platform_info.d \
./src/rpmsg_demo.d \
./src/rsc_table.d \
./src/rzg2_rproc.d \
./src/serial.d \
./src/sys_init.d 

OBJS += \
./src/MainTask_entry.o \
./src/blinky_thread_entry.o \
./src/hal_entry.o \
./src/mbed_printf_implementation.o \
./src/pin_data.o \
./src/platform_info.o \
./src/rpmsg_demo.o \
./src/rsc_table.o \
./src/rzg2_rproc.o \
./src/serial.o \
./src/sys_init.o 

MAP += \
rzg2l_cm33_rpmsg_demo.map 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mthumb -mcpu=cortex-m33+nodsp+nofp -fdiagnostics-parseable-fixits -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wnull-dereference -g -gdwarf-4 -D_RENESAS_RZG_ -I"../generate" -I"../src" -I"../rzg/arm/CMSIS_5/CMSIS/Core/Include" -I"../rzg/fsp/src/rm_freertos_port" -I"../rzg/aws/amazon-freertos/freertos_kernel/include" -I"../src" -I"../rzg/fsp/inc" -I"../rzg/fsp/inc/api" -I"../rzg/fsp/inc/instances" -I"../rzg/fsp/src/bsp/mcu/rzg2l" -I"../rzg_gen" -I"../rzg_cfg/fsp_cfg/bsp" -I"../rzg_cfg/fsp_cfg" -I"../rzg_cfg/aws" -I"../rzg/linaro/open-amp/lib/include" -I"../rzg/linaro/libmetal/include" -std=c99 -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@echo $< && arm-none-eabi-gcc @"$@.in"

