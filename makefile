.DEFAULT_GOAL:= build
fileName := sampleapp
files := "./src/*.cpp"
CC = g++

LINKER_FLAGS  = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
BUILD_DIR := ./bin


build:
	@echo "Build started"
	@echo "Creating Build Directory"
	rm -rf ${BUILD_DIR} || true
	mkdir ${BUILD_DIR}
	@echo "Compiling code"
	g++ -o ${BUILD_DIR}/${fileName} ${files} -I. ${LINKER_FLAGS}
	@echo "Build completed"

clean:
	@echo "Cleaning up"
	rm -rf ${BUILD_DIR} || true