import Module from './build/release.cjs'

const wasm = await Module();
const fun = wasm.cwrap('mancalaOperator', 'number', ['array']);

export const mancalaOperator = (flag, status) => {
    let arr = [];
    arr.push(...status, flag);
    let u8arr = new Uint8Array(arr);
    return fun(u8arr);
}
