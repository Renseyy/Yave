COMPILE = g++ -std=c++20 -lglad -lglfw -lGL -lm -lX11 -lpthread -lXrandr -lXi -ldl

OBJ := $(patsubst %.cpp,%.o,$(wildcard *.cpp */*.cpp))
OF = yave #output file 
YAVE_LIB_DIR = src/yave
IMGUI_SRC_DIR = src/imgui
IMGUI_LIB_DIR = src/imgui

%.o : %.c
	$(COMPILE) $< -o $@
$(OF): $(OBJ)
	$(COMPILE) -o $@ $^

all: clean build _chmod clean #XD
build: $(OBJ) $(OF)

build2: 
	g++ main.cpp -o yave \
	$(IMGUI_SRC_DIR)/imgui*.cpp  \
	$(YAVE_LIB_DIR)/*.cpp 	\
	-I $(IMGUI_LIB_DIR) \
	-std=c++20 -lglad -lglfw -lGL -lm -lX11 -lpthread -lXrandr -lXi -ldl
_chmod:
	@chmod +x yave
_run:
	./yave
run: build chmod _run

clean:
	rm $(OBJ)