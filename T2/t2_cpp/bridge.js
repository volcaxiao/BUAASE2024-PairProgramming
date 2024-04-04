import Module from './build/release.cjs'

const wasm = await Module();
const fun = wasm.cwrap('mancalaResult', 'number', ['number', 'array', 'number']);

export const mancalaResult = (flag, seq, size) => {
    let u8arr = new Uint8Array((new Int32Array(seq)).buffer);
    return fun(flag, u8arr, size);
}