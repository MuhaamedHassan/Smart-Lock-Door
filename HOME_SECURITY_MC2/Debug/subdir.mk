################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../buzzer.c \
../dc_motor.c \
../eeprom.c \
../gpio.c \
../main.c \
../timer.c \
../twi.c \
../usart.c 

OBJS += \
./buzzer.o \
./dc_motor.o \
./eeprom.o \
./gpio.o \
./main.o \
./timer.o \
./twi.o \
./usart.o 

C_DEPS += \
./buzzer.d \
./dc_motor.d \
./eeprom.d \
./gpio.d \
./main.d \
./timer.d \
./twi.d \
./usart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


