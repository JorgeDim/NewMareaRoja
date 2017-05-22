################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FuncionesOpenGL.cpp \
../src/Main.cpp \
../src/glui-jsm.cpp \
../src/grid3D.cpp 

O_SRCS += \
../src/Main.o 

OBJS += \
./src/FuncionesOpenGL.o \
./src/Main.o \
./src/glui-jsm.o \
./src/grid3D.o 

CPP_DEPS += \
./src/FuncionesOpenGL.d \
./src/Main.d \
./src/glui-jsm.d \
./src/grid3D.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -w -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


