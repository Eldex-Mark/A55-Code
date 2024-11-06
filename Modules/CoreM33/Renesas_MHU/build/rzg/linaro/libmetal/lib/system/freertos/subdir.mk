################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rzg/linaro/libmetal/lib/system/freertos/condition.c \
../rzg/linaro/libmetal/lib/system/freertos/device.c \
../rzg/linaro/libmetal/lib/system/freertos/init.c \
../rzg/linaro/libmetal/lib/system/freertos/io.c \
../rzg/linaro/libmetal/lib/system/freertos/irq.c \
../rzg/linaro/libmetal/lib/system/freertos/shmem.c \
../rzg/linaro/libmetal/lib/system/freertos/time.c 

LST += \
condition.lst \
device.lst \
init.lst \
io.lst \
irq.lst \
shmem.lst \
time.lst 

C_DEPS += \
./rzg/linaro/libmetal/lib/system/freertos/condition.d \
./rzg/linaro/libmetal/lib/system/freertos/device.d \
./rzg/linaro/libmetal/lib/system/freertos/init.d \
./rzg/linaro/libmetal/lib/system/freertos/io.d \
./rzg/linaro/libmetal/lib/system/freertos/irq.d \
./rzg/linaro/libmetal/lib/system/freertos/shmem.d \
./rzg/linaro/libmetal/lib/system/freertos/time.d 

OBJS += \
./rzg/linaro/libmetal/lib/system/freertos/condition.o \
./rzg/linaro/libmetal/lib/system/freertos/device.o \
./rzg/linaro/libmetal/lib/system/freertos/init.o \
./rzg/linaro/libmetal/lib/system/freertos/io.o \
./rzg/linaro/libmetal/lib/system/freertos/irq.o \
./rzg/linaro/libmetal/lib/system/freertos/shmem.o \
./rzg/linaro/libmetal/lib/system/freertos/time.o 

MAP += \
rzg2l_cm33_rpmsg_demo.map 


# Each subdirectory must supply rules for building sources it contributes
rzg/linaro/libmetal/lib/system/freertos/%.o: ../rzg/linaro/libmetal/lib/system/freertos/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mthumb -mcpu=cortex-m33+nodsp+nofp -fdiagnostics-parseable-fixits -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wnull-dereference -g -gdwarf-4 -D_RENESAS_RZG_ -I"../generate" -I"../src" -I"../rzg/arm/CMSIS_5/CMSIS/Core/Include" -I"../rzg/fsp/src/rm_freertos_port" -I"../rzg/aws/amazon-freertos/freertos_kernel/include" -I"../src" -I"../rzg/fsp/inc" -I"../rzg/fsp/inc/api" -I"../rzg/fsp/inc/instances" -I"../rzg/fsp/src/bsp/mcu/rzg2l" -I"../rzg_gen" -I"../rzg_cfg/fsp_cfg/bsp" -I"../rzg_cfg/fsp_cfg" -I"../rzg_cfg/aws" -I"../rzg/linaro/open-amp/lib/include" -I"../rzg/linaro/libmetal/include" -std=c99 -mcmse -w -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@echo $< && arm-none-eabi-gcc @"$@.in"

