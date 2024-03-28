import { readFileSync } from "fs";

const wasmSource = new Uint8Array(readFileSync("t1_cpp/build/release.wasm"));
const wasmModule = new WebAssembly.Module(wasmSource);
const wasmInstance = new WebAssembly.Instance(wasmModule, {
    env: {}
});

console.log(wasmInstance.exports.memory);

function transferToHeap(arr) {
    // const heapSpace = wasmInstance.exports.malloc(arr.length * Int32Array.BYTES_PER_ELEMENT); // 1
    // const heap = new Int32Array(wasmInstance.exports.memory.buffer);
    // wasmInstance.exports.memory.(arr, heapSpace);
    // for (let i = 0; i < arr.length; i++)
    //     heap[i] = arr[i];
    return heapSpace;
}

const _bocchiShutUp = wasmInstance.exports.bocchiShutUp;

export const bocchiShutUp = (flag, arr, size) => {
    const savedStack = wasmInstance.exports.stackSave();
    const ptr = wasmInstance.exports.stackAlloc(arr.length * 4);
    const start = ptr >> 2;
    const heap = new Uint32Array(wasmInstance.exports.memory.buffer);
    
    for (let i = 0; i < arr.length; ++i) {
        heap[start + i] = arr[i];
    }
    const result = _bocchiShutUp(flag, ptr, size);
    wasmInstance.exports.stackRestore(savedStack);
    return result;
};

console.log(bocchiShutUp(2, [13, 14, 13, 11, 21, 13, 21, 22], 8));
console.log(bocchiShutUp(1, [13, 14, 13, 11, 21, 13, 21, 22], 8));
