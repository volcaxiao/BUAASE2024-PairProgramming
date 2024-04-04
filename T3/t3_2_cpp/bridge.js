import Module from './build/release.cjs'

const wasm = await Module();
const fun = wasm.cwrap('mancalaOperator', 'number', ['array']);

export const mancalaOperator = (flag, status) => {
    let u8arr = new Uint8Array(status) + new Uint8Array([flag]);
    return fun(u8arr);
}
