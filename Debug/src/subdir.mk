################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Age.cpp \
../src/Human.cpp \
../src/Location.cpp \
../src/Occupation.cpp \
../src/innerClass5.cpp 

OBJS += \
./src/Age.o \
./src/Human.o \
./src/Location.o \
./src/Occupation.o \
./src/innerClass5.o 

CPP_DEPS += \
./src/Age.d \
./src/Human.d \
./src/Location.d \
./src/Occupation.d \
./src/innerClass5.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


