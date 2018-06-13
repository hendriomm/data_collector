################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/Controller.cc \
../src/Engine.cc \
../src/MotorController.cc \
../src/MotorDriver.cc \
../src/Sensoring.cc \
../src/TemperatureSensor.cc \
../src/Top.cc \
../src/TopControllers.cc \
../src/TopMain.cc 

CC_DEPS += \
./src/Controller.d \
./src/Engine.d \
./src/MotorController.d \
./src/MotorDriver.d \
./src/Sensoring.d \
./src/TemperatureSensor.d \
./src/Top.d \
./src/TopControllers.d \
./src/TopMain.d 

OBJS += \
./src/Controller.o \
./src/Engine.o \
./src/MotorController.o \
./src/MotorDriver.o \
./src/Sensoring.o \
./src/TemperatureSensor.o \
./src/Top.o \
./src/TopControllers.o \
./src/TopMain.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	armv8-rpi3-linux-gnueabihf-g++ -I/home/hendrio/Downloads/Papyrus-RT/plugins/org.eclipse.papyrusrt.rts_1.0.0.201707181457/umlrts/include -I"/home/hendrio/x-tools/armv8-rpi3-linux-gnueabihf//include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


