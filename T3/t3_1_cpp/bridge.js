import Module from './build/release.cjs'

const wasm = await Module();
const fun = wasm.cwrap('mancalaBoard', 'number', ['number', 'array', 'number']);

export const mancalaBoard = (flag, seq, size) => {
    let u8arr = new Uint8Array((new Int32Array(seq)).buffer);
    let ptr = fun(flag, u8arr, size);
    return wasm.HEAP32.subarray(ptr / 4, ptr / 4 + 15);
}
