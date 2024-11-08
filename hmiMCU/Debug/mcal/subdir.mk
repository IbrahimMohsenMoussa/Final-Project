################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mcal/gpio.c \
../mcal/icu.c \
../mcal/timer_0.c \
../mcal/timer_1.c \
../mcal/timer_2.c \
../mcal/uart.c 

OBJS += \
./mcal/gpio.o \
./mcal/icu.o \
./mcal/timer_0.o \
./mcal/timer_1.o \
./mcal/timer_2.o \
./mcal/uart.o 

C_DEPS += \
./mcal/gpio.d \
./mcal/icu.d \
./mcal/timer_0.d \
./mcal/timer_1.d \
./mcal/timer_2.d \
./mcal/uart.d 


# Each subdirectory must supply rules for building sources it contributes
mcal/%.o: ../mcal/%.c mcal/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


