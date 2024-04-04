import Module from "./function.js";

var RealModule = await Module()

var callOp = RealModule.cwrap("mancalaOperator", "number", ["number", "number"]);

export function mancalaOperator(flag, status) {
    const bytesPerElement = Int32Array.BYTES_PER_ELEMENT;
    const numBytes = 14 * bytesPerElement;
    const ptr = RealModule._malloc(numBytes);
    
    let heapView = new Int32Array(RealModule.HEAP32.buffer, ptr, 14);
    heapView.set(status);
    
    const result = callOp(flag, ptr);
    return result;
}