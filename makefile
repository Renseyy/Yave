COMPILE = g++ -std=c++20 -lglad -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

OBJ := $(patsubst %.cpp,%.o,$(wildcard *.cpp src/*.cpp))
OF = yave #output file 

%.o : %.c
	$(COMPILE) $< -o $@
$(OF): $(OBJ)
	$(COMPILE) -o $@ $^

all: build _chmod
build: $(OBJ) $(OF)
_chmod:
	@chmod +x yave
_run:
	./yave
run: build chmod _run