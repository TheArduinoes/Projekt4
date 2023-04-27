
SOURCES = sonar.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
DEPS=$(SOURCES:.cpp=.d)
EXE=parts
CXXFLAGS= -Wall -I.

ARCH?=x86-64

ifeq (${ARCH},x86-64)
CXX = g++
BUILD_DIR=build/x86-64
EXE_DIR=bin/x86-64            #added bin for executable
endif

#Making for archietecture

# > make ARCH=arm

ifeq (${ARCH},arm)
CXX=arm-rpizw-g++
BUILD_DIR=build/arm
EXE_DIR=bin/arm            #added bin for executable
endif

ALL: dir $(EXE)                    #added all 

dir:                            #add folders bin and build
    mkdir -p $(BUILD_DIR)
    mkdir -p $(EXE_DIR)

$(EXE): $(addprefix $(BUILD_DIR)/,$(DEPS)) $(addprefix $(BUILD_DIR)/,$(OBJECTS))
    $(CXX) $(CXXFLAGS) -o $@ $(addprefix $(BUILD_DIR)/,$(OBJECTS))
    mv ${EXE} ${EXE_DIR}                        #move exe to bin folder.

${BUILD_DIR}/%.o: %.cpp $(BUILD_DIR)/%.d            #builds .o files to build_dir
    $(CXX) -o $@ -c $< $(CXXFLAGS)

$(BUILD_DIR)/%.d: %.cpp
    $(CXX) -MT $@ -MM $(CXXFLAGS) $< > $@
    $(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >> $@

#clean command

clean: 

    echo "Cleaning" 
    rm -rf $(BUILD_DIR) $(EXE_DIR)
    rmdir build bin

ifneq ($(MAKEGMDGOALS),clean)

-include $(DEPS)

endif