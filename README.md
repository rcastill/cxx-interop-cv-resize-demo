# CXX Rust Iterop Demo

[cxx](https://github.com/dtolnay/cxx) is a great Rust library to achieve safer interop with C++. This repository is a PoC (a non-trivial example) demonstrating its capabilities. The library repo has an included demo following the tutorial found at [cxx.rs](https://cxx.rs/). This repo is based on that.

## What it does?

Inside `cvresize/` there is pure C++ code for resizing an image using opencv 4. Relevant code is in `cvresize.cpp/h` and an entrypoint in `resize.cpp`.

To test it:

```
cd cvresize
make -j2
./resize <w> <h> <image> >output.jpg
```

Meanwhile, `src/main.rs` is analogous to `resize.cpp` and uses `cvresize.cpp` to actually resize the image:

```
cargo build --release
./target/release/cxx-interop-cv-resize -w <w> -h <h> <image> >output.jpg
```

## Bonus

`bench.sh` is included in the root of the project. It runs `n` times both programs (C++ vs. Rust). Surprisingly, rust implementation is faster. This does not mean that Rust is inherently faster than C++, it only means that it is effortless to write safer/faster code in Rust.

Usage:

```
./bench.sh <n> <image>
```