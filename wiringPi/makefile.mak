lib=wirePiLib.a
CXXFLAG=-I.

SourceFiles= ads1115.c bmp180.c drcSerial.c ds18b20.c htu21d.c max31855.c max5322.c mcp23008.c mcp23016.c mcp23017.c mcp23s08.c mcp23s17.c mcp3002.c mcp3004.c mcp3422.c mcp4802.c pcf8574.c pcf8591.c piHiPri.c piThread.c pseudoPins.c rht03.c sn3218.c softPwm.c softServo.c softTone.c sr595.c wiringPi.c wiringPiI2C.c wiringPiSPI.c wiringSerial.c wiringShift.c wpiExtensions.c

ObjectFiles= $(addprefix $(BUILD_DIR)/,$(SourceFiles:.c=.o))

DEPS=$(addprefix $(BUILD_DIR)/,$(SourceFiles:.c=.d))

ARCH?=x86-64

ifeq (${ARCH},x86-64)
CXX=gcc 
BUILD_DIR=build/x86-64
BIN_DIR=bin/x86-64
endif

ifeq (${ARCH},arm)
CXX= arm-rpizw-gcc 
BUILD_DIR=build/arm
BIN_DIR=bin/arm
endif

$(BUILD_DIR)/$(lib): $(ObjectFiles)
    @echo "Building static library.."
    mkdir -p $(BUILD_DIR)
    ar rcs $@ $(ObjectFiles)

$(BUILD_DIR)/%.o: %.c 
    @echo "Compiling.."
    mkdir -p $(BUILD_DIR)
    $(CXX) $(CXXFLAG) -c $< -o $@

$(BUILD_DIR)/%.d: %.c
    mkdir -p $(BUILD_DIR)
    $(CXX) -MT$@ -MM $(CXXFLAG) $< > $@
    $(CXX) -MT$(@:.d=.o) -MM $(CXXFLAG) $< >> $@

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif

clean:
    rm -rf $(BUILD_DIR) $(BIN_DIR)

help:
    @echo $(ObjectFiles) , clean , help $(lib)