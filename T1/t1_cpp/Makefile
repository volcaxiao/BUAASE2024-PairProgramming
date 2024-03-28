
all: BocchiShutUp.cpp
	emcc BocchiShutUp.cpp -o build/release.wasm --no-entry -s EXPORTED_FUNCTIONS="['_bocchiShutUp', '_malloc', '_free']" -s ALLOW_TABLE_GROWTH=1
