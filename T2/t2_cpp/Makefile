CC = emcc
METHODS = -s EXPORTED_FUNCTIONS='["_mancalaResult"]' -s EXPORTED_RUNTIME_METHODS='["cwrap"]'
FLAGS = -s WASM=1 -s MODULARIZE=1 -s ALLOW_MEMORY_GROWTH=1 -s NODEJS_CATCH_EXIT=0 -s NODEJS_CATCH_REJECTION=0 
SRC = MancalaResult.cpp

release: ${SRC} build
	${CC} ${SRC} -o build/release.cjs -O3 ${METHODS} ${FLAGS}

debug: ${SRC} build
	${CC} ${SRC} -o build/debug.cjs -O0 ${METHODS} ${FLAGS}

test: ${SRC} build
	g++ ${SRC} -o build/test -O3
	./build/test

build:
	mkdir -p build
