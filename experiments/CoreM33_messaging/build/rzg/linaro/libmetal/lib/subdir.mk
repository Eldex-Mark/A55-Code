################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rzg/linaro/libmetal/lib/device.c \
../rzg/linaro/libmetal/lib/dma.c \
../rzg/linaro/libmetal/lib/init.c \
../rzg/linaro/libmetal/lib/io.c \
../rzg/linaro/libmetal/lib/log.c \
../rzg/linaro/libmetal/lib/shmem.c \
../rzg/linaro/libmetal/lib/version.c 

LST += \
device.lst \
dma.lst \
init.lst \
io.lst \
log.lst \
shmem.lst \
version.lst 

C_DEPS += \
./rzg/linaro/libmetal/lib/device.d \
./rzg/linaro/libmetal/lib/dma.d \
./rzg/linaro/libmetal/lib/init.d \
./rzg/linaro/libmetal/lib/io.d \
./rzg/linaro/libmetal/lib/log.d \
./rzg/linaro/libmetal/lib/shmem.d \
./rzg/linaro/libmetal/lib/version.d 

OBJS += \
./rzg/linaro/libmetal/lib/device.o \
./rzg/linaro/libmetal/lib/dma.o \
./rzg/linaro/libmetal/lib/init.o \
./rzg/linaro/libmetal/lib/io.o \
./rzg/linaro/libmetal/lib/log.o \
./rzg/linaro/libmetal/lib/shmem.o \
./rzg/linaro/libmetal/lib/version.o 

MAP += \
rzg2l_cm33_rpmsg_demo.map 


# Each subdirectory must supply rules for building sources it contributes
rzg/linaro/libmetal/lib/%.o: ../rzg/linaro/libmetal/lib/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mthumb -mcpu=cortex-m33+nodsp+nofp -fdiagnostics-parseable-fixits -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wnull-dereference -g -gdwarf-4 -D_RENESAS_RZG_ -I"../generate" -I"../src" -I"../rzg/arm/CMSIS_5/CMSIS/Core/Include" -I"../rzg/fsp/src/rm_freertos_port" -I"../rzg/aws/amazon-freertos/freertos_kernel/include" -I"../src" -I"../rzg/fsp/inc" -I"../rzg/fsp/inc/api" -I"../rzg/fsp/inc/instances" -I"../rzg/fsp/src/bsp/mcu/rzg2l" -I"../rzg_gen" -I"../rzg_cfg/fsp_cfg/bsp" -I"../rzg_cfg/fsp_cfg" -I"../rzg_cfg/aws" -I"../rzg/linaro/open-amp/lib/include" -I"../rzg/linaro/libmetal/include" -std=c99 -mcmse -w -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@echo $< && arm-none-eabi-gcc @"$@.in"

