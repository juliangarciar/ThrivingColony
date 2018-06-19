# Makefile for Thriving colony
# Created by Mario Gonzalez and Julian Garcia

# Name of the executable created
TARGET = ThrivingColony.exe
# Project root
PROJECTROOT = .
# Path for the executable
BINPATH = $(PROJECTROOT)
# Path for the .o files
BUILDPATH = $(PROJECTROOT)/obj
#Directories
SOURCEPATHS = $(PROJECTROOT)/src
#C++ compiler
CXX = clang++
#C++ debugger
DBG = lldb

####
# FLAGS
####
# Include paths
CPPFLAGS = -I/mingw64/include -I/mingw64/include/eigen3 -I$(PROJECTROOT)/include -I$(PROJECTROOT)/include/nanovg
# Compiler params
CPPFLAGS += -g -O3 -std=c++11 -m64 -ffast-math -Wall -Wno-macro-redefined -Wno-unused-value -Wno-delete-non-virtual-dtor -Wno-unknown-pragmas -DUSE_VIDEO -DUSE_GLAD -DGLFW_DLL -DGLFW_INCLUDE_NONE -DNANOGUI_GLAD -DNANOGUI_SHARED
# Lib paths
LDFLAGS = -L/mingw64/lib -L/mingw64/lib/x86_64-linux-gnu -L/mingw64/lib/X11 -L/mingw64/local/lib -L$(PROJECTROOT)/lib -Wl,-R -Wl,$(PROJECTROOT)/lib
# Libs
LIBS = -lglad -lglfw3 -lopengl32 -lglu32 -lgdi32 -lpthread -lnanogui -lfmod64 -lfmodstudio64 -lterterrain -laabbtree -lavformat -lavcodec -lavutil -lswresample -lswscale

######## DON'T EDIT ANYTHING BELOW THIS LINE
EXECUTABLE := $(BINPATH)/$(TARGET)

rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

SRC_DIRS := $(foreach DIR,$(SOURCEPATHS),$(shell find $(DIR) -type d))
OBJ_DIRS := $(foreach DIR,$(SOURCEPATHS),$(patsubst %, $(BUILDPATH)/%,$(shell find $(DIR) -type d ! -path .)))

SRC_FILES := $(foreach DIR,$(SRC_DIRS),$(wildcard $(DIR)/*.cpp))
OBJ_FILES := $(foreach FILE,$(SRC_FILES),$(patsubst %.cpp, $(BUILDPATH)/%.o, $(FILE)))

INCLUDE_DIRS := $(foreach DIR,$(SOURCEPATHS),$(patsubst %, -I%, $(DIR)))
CPPFLAGS += $(INCLUDE_DIRS)

#MAKE OPTIONS
.PHONY: all run debug clean cleanfolder

all: $(BUILDPATH) $(OBJ_FILES)
	$(info =================================)
	$(info Creando el ejecutable $(Target)...)
	$(info =================================)
	@$(CXX) $(CPPFLAGS) $(OBJ_FILES) -o $(EXECUTABLE) $(LDFLAGS) $(LIBS)
    
$(BUILDPATH)/%.o: %.cpp
	$(info Creando el binario para el archivo $<...)
	@$(CXX) $(CPPFLAGS) -c $< -o $@

$(BUILDPATH):
	$(info =================================)
	$(info Creando la estructura de carpetas...)
	$(info =================================)
	@mkdir -p $(OBJ_DIRS)
	@mkdir -p $(BINPATH)

clean:
	$(info =================================)
	$(info Limpiando todo el proyecto...)
	$(info =================================)
	@$(RM) $(EXECUTABLE)
	@$(RM) -r $(OBJ_DIRS)
	@$(RM) -r $(BUILDPATH)

cleanfolder:
	$(info =================================)
	$(info Limpiando la carpeta $(FOLDER)...)
	$(info =================================)
	@$(RM) $(EXECUTABLE)
	@$(RM) -r $(BUILDPATH)/$(FOLDER)

run: all
	$(info =================================)
	$(info Ejecutando...)
	$(info =================================)
	@$(EXECUTABLE)

debug: all
	$(info =================================)
	$(info Ejecutando...)
	$(info =================================)
	@$(DBG) $(EXECUTABLE)
