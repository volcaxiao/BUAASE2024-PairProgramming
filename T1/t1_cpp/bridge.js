import { readFileSync } from "fs";

const wasmMemory = new WebAssembly.Memory({ initial: 10 });
const wasmBuffer = new Uint8Array(wasmMemory.buffer);

const wasmSource = new Uint8Array(readFileSync("t1_cpp/build/release.wasm"));
const wasmModule = new WebAssembly.Module(wasmSource);
const wasmInstance = new WebAssembly.Instance(wasmModule, {
    env: {
        memory: wasmMemory,
        __memory_base: 0,
    }
});

export const bocchiShutUp = (flag, seq, size) => {
    const ptr = wasmInstance.exports.allocArray(size);
    new Int32Array(wasmInstance.exports.memory.buffer).set(seq, ptr >> 2);
    const result = wasmInstance.exports.bocchiShutUp(flag, ptr, size);
    wasmInstance.exports.freeArray(ptr);
    return result;
};
