################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rzg/fsp/src/bsp/mcu/all/bsp_clocks.c \
../rzg/fsp/src/bsp/mcu/all/bsp_common.c \
../rzg/fsp/src/bsp/mcu/all/bsp_delay.c \
../rzg/fsp/src/bsp/mcu/all/bsp_group_irq.c \
../rzg/fsp/src/bsp/mcu/all/bsp_guard.c \
../rzg/fsp/src/bsp/mcu/all/bsp_io.c \
../rzg/fsp/src/bsp/mcu/all/bsp_irq.c \
../rzg/fsp/src/bsp/mcu/all/bsp_irqs.c \
../rzg/fsp/src/bsp/mcu/all/bsp_sbrk.c \
../rzg/fsp/src/bsp/mcu/all/bsp_security.c 

LST += \
bsp_clocks.lst \
bsp_common.lst \
bsp_delay.lst \
bsp_group_irq.lst \
bsp_guard.lst \
bsp_io.lst \
bsp_irq.lst \
bsp_irqs.lst \
bsp_sbrk.lst \
bsp_security.lst 

C_DEPS += \
./rzg/fsp/src/bsp/mcu/all/bsp_clocks.d \
./rzg/fsp/src/bsp/mcu/all/bsp_common.d \
./rzg/fsp/src/bsp/mcu/all/bsp_delay.d \
./rzg/fsp/src/bsp/mcu/all/bsp_group_irq.d \
./rzg/fsp/src/bsp/mcu/all/bsp_guard.d \
./rzg/fsp/src/bsp/mcu/all/bsp_io.d \
./rzg/fsp/src/bsp/mcu/all/bsp_irq.d \
./rzg/fsp/src/bsp/mcu/all/bsp_irqs.d \
./rzg/fsp/src/bsp/mcu/all/bsp_sbrk.d \
./rzg/fsp/src/bsp/mcu/all/bsp_security.d 

OBJS += \
./rzg/fsp/src/bsp/mcu/all/bsp_clocks.o \
./rzg/fsp/src/bsp/mcu/all/bsp_common.o \
./rzg/fsp/src/bsp/mcu/all/bsp_delay.o \
./rzg/fsp/src/bsp/mcu/all/bsp_group_irq.o \
./rzg/fsp/src/bsp/mcu/all/bsp_guard.o \
./rzg/fsp/src/bsp/mcu/all/bsp_io.o \
./rzg/fsp/src/bsp/mcu/all/bsp_irq.o \
./rzg/fsp/src/bsp/mcu/all/bsp_irqs.o \
./rzg/fsp/src/bsp/mcu/all/bsp_sbrk.o \
./rzg/fsp/src/bsp/mcu/all/bsp_security.o 

MAP += \
rzg2l_cm33_rpmsg_demo.map 


# Each subdirectory must supply rules for building sources it contributes
rzg/fsp/src/bsp/mcu/all/%.o: ../rzg/fsp/src/bsp/mcu/all/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mthumb -mcpu=cortex-m33+nodsp+nofp -fdiagnostics-parseable-fixits -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wnull-dereference -g -gdwarf-4 -D_RENESAS_RZG_ -I"../generate" -I"../src" -I"../rzg/arm/CMSIS_5/CMSIS/Core/Include" -I"../rzg/fsp/src/rm_freertos_port" -I"../rzg/aws/amazon-freertos/freertos_kernel/include" -I"../src" -I"../rzg/fsp/inc" -I"../rzg/fsp/inc/api" -I"../rzg/fsp/inc/instances" -I"../rzg/fsp/src/bsp/mcu/rzg2l" -I"../rzg_gen" -I"../rzg_cfg/fsp_cfg/bsp" -I"../rzg_cfg/fsp_cfg" -I"../rzg_cfg/aws" -I"../rzg/linaro/open-amp/lib/include" -I"../rzg/linaro/libmetal/include" -std=c99 -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@echo $< && arm-none-eabi-gcc @"$@.in"

