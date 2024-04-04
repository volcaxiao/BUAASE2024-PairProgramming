CC = emcc
METHODS = -s EXPORTED_FUNCTIONS='["_mancalaResult"]' -s EXPORTED_RUNTIME_METHODS='["cwrap"]'
FLAGS = -s WASM=1 -s MODULARIZE=1 -s ALLOW_MEMORY_GROWTH=1 -s NODEJS_CATCH_EXIT=0 -s NODEJS_CATCH_REJECTION=0 
SRC = MancalaResult.cpp

release: ${SRC}
	${CC} ${SRC} -o build/release.cjs -O3 ${METHODS} ${FLAGS}

debug: ${SRC}
	${CC} ${SRC} -O0 build/debug.cjs ${METHODS} ${FLAGS}

test: ${SRC}
	g++ ${SRC} -o build/test -O3
	./build/test
