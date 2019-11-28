################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DR_EXTINT.c \
../src/DR_GPIO.c \
../src/DR_PINSEL.c \
../src/DR_PLL.c \
../src/DR_Salidas.c \
../src/DR_SysTick.c \
../src/DR_Timers.c \
../src/DR_UART1.c \
../src/Microondas.c \
../src/PR_Display.c \
../src/PR_Maq_Recibo.c \
../src/PR_Teclado.c \
../src/PR_Timers.c \
../src/PR_UART1.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/main.c 

OBJS += \
./src/DR_EXTINT.o \
./src/DR_GPIO.o \
./src/DR_PINSEL.o \
./src/DR_PLL.o \
./src/DR_Salidas.o \
./src/DR_SysTick.o \
./src/DR_Timers.o \
./src/DR_UART1.o \
./src/Microondas.o \
./src/PR_Display.o \
./src/PR_Maq_Recibo.o \
./src/PR_Teclado.o \
./src/PR_Timers.o \
./src/PR_UART1.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/main.o 

C_DEPS += \
./src/DR_EXTINT.d \
./src/DR_GPIO.d \
./src/DR_PINSEL.d \
./src/DR_PLL.d \
./src/DR_Salidas.d \
./src/DR_SysTick.d \
./src/DR_Timers.d \
./src/DR_UART1.d \
./src/Microondas.d \
./src/PR_Display.d \
./src/PR_Maq_Recibo.d \
./src/PR_Teclado.d \
./src/PR_Timers.d \
./src/PR_UART1.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\GCRIS\Documents\MCUXpressoIDE_11.0.1_2563\workspace\Microondas\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


