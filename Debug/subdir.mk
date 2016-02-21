################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SDL_Sound.cpp \
../graphics.cpp \
../sdlmain.cpp 

OBJS += \
./SDL_Sound.o \
./graphics.o \
./sdlmain.o 

CPP_DEPS += \
./SDL_Sound.d \
./graphics.d \
./sdlmain.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"C:\Users\motey\Downloads\SDL2-devel-2.0.3-VC\SDL2-2.0.3\include" -I"C:\Users\motey\Documents\Visual Studio 2015\Projects\Project1\Project1\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


