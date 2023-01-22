all: build chmod
build:
	g++ -std=c++20 main.cpp -lglad -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o yave
chmod:
	@chmod +x yave
_run:
	./yave
run: build chmod _run