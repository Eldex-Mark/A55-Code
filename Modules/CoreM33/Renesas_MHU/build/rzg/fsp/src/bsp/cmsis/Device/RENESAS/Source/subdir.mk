################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rzg/fsp/src/bsp/cmsis/Device/RENESAS/Source/startup.c \
../rzg/fsp/src/bsp/cmsis/Device/RENESAS/Source/startups.c \
../rzg/fsp/src/bsp/cmsis/Device/RENESAS/Source/system.c \
../rzg/fsp/src/bsp/cmsis/Device/RENESAS/Source/systems.c 

LST += \
startup.lst \
startups.lst \
system.lst \
systems.lst 

C_DEPS += \
./rzg/fsp/src/bsp/cmsis/Device/RENESAS/Source/startup.d \
./rzg/fsp/src/bsp/cmsis/Device/RENESAS/Source/startups.d \
./rzg/fsp/src/bsp/cmsis/Device/RENESAS/Source/system.d \
./rzg/fsp/src/bsp/cmsis/Device/RENESAS/Source/systems.d 

OBJS += \
./rzg/fsp/src/bsp/cmsis/Device/RENESAS/Source/startup.o \
./rzg/fsp/src/bsp/cmsis/Device/RENESAS/Source/startups.o \
./rzg/fsp/src/bsp/cmsis/Device/RENESAS/Source/system.o \
./rzg/fsp/src/bsp/cmsis/Device/RENESAS/Source/systems.o 

MAP += \
rzg2l_cm33_rpmsg_demo.map 


# Each subdirectory must supply rules for building sources it contributes
rzg/fsp/src/bsp/cmsis/Device/RENESAS/Source/%.o: ../rzg/fsp/src/bsp/cmsis/Device/RENESAS/Source/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mthumb -mcpu=cortex-m33+nodsp+nofp -fdiagnostics-parseable-fixits -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wnull-dereference -g -gdwarf-4 -D_RENESAS_RZG_ -I"../generate" -I"../src" -I"../rzg/arm/CMSIS_5/CMSIS/Core/Include" -I"../rzg/fsp/src/rm_freertos_port" -I"../rzg/aws/amazon-freertos/freertos_kernel/include" -I"../src" -I"../rzg/fsp/inc" -I"../rzg/fsp/inc/api" -I"../rzg/fsp/inc/instances" -I"../rzg/fsp/src/bsp/mcu/rzg2l" -I"../rzg_gen" -I"../rzg_cfg/fsp_cfg/bsp" -I"../rzg_cfg/fsp_cfg" -I"../rzg_cfg/aws" -I"../rzg/linaro/open-amp/lib/include" -I"../rzg/linaro/libmetal/include" -std=c99 -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@echo $< && arm-none-eabi-gcc @"$@.in"

