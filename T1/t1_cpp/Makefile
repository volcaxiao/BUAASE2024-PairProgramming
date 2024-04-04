CC = emcc
FG = --no-entry -s ALLOW_TABLE_GROWTH=1
SRC = BocchiShutUp.cpp
EPT = -s EXPORTED_FUNCTIONS="['_bocchiShutUp', '_allocArray', '_freeArray']"

release: ${SRC} build
	${CC} ${SRC} -O3 -o build/release.wasm ${FG} ${EPT}

debug: ${SRC} build
	${CC} ${SRC} -o build/release.wasm ${FG} ${EPT}

build:
	mkdir -p build
