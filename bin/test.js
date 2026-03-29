/**
 * Requires: npm install koffi  (from this directory or repo root)
 * Run: node test.js
 */
const path = require("path");
const koffi = require("koffi");

const dllPath = path.join(__dirname, "lib.dll");
let lib;
try {
  lib = koffi.load(dllPath);
} catch (e) {
  console.error("LoadLibrary failed:", e.message);
  process.exit(1);
}

const hello = lib.func("void hello(void)");
const printNumber = lib.func("void printNumber(int)");

hello();
printNumber(23);
