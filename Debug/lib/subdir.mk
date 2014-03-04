################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/lcd-routines.c \
../lib/sensors.c \
../lib/sleepcontrol.c \
../lib/util.c 

OBJS += \
./lib/lcd-routines.o \
./lib/sensors.o \
./lib/sleepcontrol.o \
./lib/util.o 

C_DEPS += \
./lib/lcd-routines.d \
./lib/sensors.d \
./lib/sleepcontrol.d \
./lib/util.d 


# Each subdirectory must supply rules for building sources it contributes
lib/%.o: ../lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


