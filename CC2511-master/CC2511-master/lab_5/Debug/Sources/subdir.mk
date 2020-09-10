################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Events.c \
../Sources/main.c 

OBJS += \
./Sources/Events.o \
./Sources/main.o 

C_DEPS += \
./Sources/Events.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"D:/Desktop/JCU folder/Second Year 2020/Second semester/CC2511/Workspace/lab_5.1/Static_Code/PDD" -I"D:/Desktop/JCU folder/Second Year 2020/Second semester/CC2511/Workspace/lab_5.1/Static_Code/IO_Map" -I"D:/Desktop/JCU folder/Second Year 2020/Second semester/CC2511/Workspace/lab_5.1/Sources" -I"D:/Desktop/JCU folder/Second Year 2020/Second semester/CC2511/Workspace/lab_5.1/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


