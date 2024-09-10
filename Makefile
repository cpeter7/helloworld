all: prepare

dependency:
	cd build && cmake .. --graphviz=graph.dot && dot -Tpng graph.dot -o graph.png
	
all: prepare

install:
	sudo apt-get install gcc g++ cmake make doxygen git llvm pkg-config curl zip unzip tar python3-dev clang-format clang-tidy

prepare:
	rm -rf build
	mkdir build
