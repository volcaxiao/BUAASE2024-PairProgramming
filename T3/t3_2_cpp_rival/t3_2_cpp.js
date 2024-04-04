import CPPModule from './mancalaOperator.js'
var wasmInstance = await CPPModule();
//这个题的关键就是看看怎么返回一个js数组
function mancalaOperator(flag, status) {
    const cppFuncPtr = wasmInstance.cwrap('mancala_operator', 'number', ['number', 'number']);
    const malloc = wasmInstance.cwrap('malloc', 'number', ['number']);
    const free = wasmInstance.cwrap('free',null,['number']);
    const paramPtr= malloc(20*Uint32Array.BYTES_PER_ELEMENT)
    const memoryView = new Uint32Array(wasmInstance.HEAPU8.buffer,paramPtr,20)
    for(let i=0;i<status.length;i++){
        memoryView[i]=status[i];
    }
    const ans= cppFuncPtr(flag,paramPtr)
    free(paramPtr);
    return ans
}
export {mancalaOperator}