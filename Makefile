# location of the Python header files
PYTHON_VERSION = 3.6m
PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)
 
# location of the Boost Python include files and library
BOOST_INC = /usr/include
BOOST_LIB = /usr/lib

CXX        := -g++
CXXFLAGS   := -Wall -fPIC
LDFLAGS    := -shared -Wl,--export-dynamic
BUILD      := ./build
OBJ_DIR    := $(BUILD)/objects
APP_DIR    := $(BUILD)/
TARGET     := lac.so
INCLUDE    := -Iinclude/
SRC        := $(wildcard src/*.cpp)

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS) -L$(BOOST_LIB) -lboost_python3 -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION)

.PHONY: all build clean debug release run

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O3
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*

run:
	./$(BUILD)/$(TARGET)