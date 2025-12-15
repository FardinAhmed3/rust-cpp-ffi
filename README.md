# rust-cpp-ffi
Foreign Function Interfacing

## How to run

```
rustc -O --crate-type staticlib arithmetic.rs -o mathlib.a
g++ -O3 rust_bridge.cpp mathlib.a -o ffi_interop.out
./ffi_interop.out
```

