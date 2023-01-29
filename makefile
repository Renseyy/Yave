YAVE_LIB_DIR = src/YAVE
IMGUI_SRC_DIR = src/imgui
IMGUI_LIB_DIR = src/imgui
ASSIMP_FLAGS = -I include/assimp -L lib64 -lassimp 
COMPILE = g++ -std=c++20 -lglad -lglfw -lGL -lm -lX11 -lpthread -lXrandr -lXi -ldl -lstdc++fs

OBJ := $(patsubst %.cpp,%.o,$(wildcard $(IMGUI_SRC_DIR)/imgui*.cpp))
OF = yave #output file 

#rules
default: run # do not change place of this rule

%.o : %.cpp
	$(COMPILE) -c $< -o $@ -I $(IMGUI_LIB_DIR)
$(OF): $(OBJ)
	$(COMPILE) -o $@ $^






all: _build_imgui build _build_imgui _chmod _run#XD


build: 
	g++ main.cpp -o yave \
	$(OBJ) \
	-I $(IMGUI_LIB_DIR) \
	$(YAVE_LIB_DIR)/*.cpp 	\
	-std=c++20 -lglad -lglfw -lGL -lm -lX11 -lpthread -lXrandr -lXi -ldl $(ASSIMP_FLAGS)



run: build _chmod _run

_build_imgui: $(OBJ) 

_chmod:
	@chmod +x yave
_run:
	./yave

_clean_imgui:
	rm $(OBJ)