use cxx_build::CFG;

fn main() {
    CFG.include_prefix = "";
    let opencv = pkg_config::probe_library("opencv4").unwrap();
    cxx_build::bridge("src/main.rs")
        .file("cvresize/src/cvresize/cvresize.cpp")
        .flag_if_supported("-std=c++11")
        .include("cvresize/include")
        .includes(opencv.include_paths)
        .compile("demo");
    for link_path in opencv.link_paths {
        println!("cargo:rustc-link-search={}", link_path.to_str().unwrap());
    }
    for lib in opencv.libs {
        println!("cargo:rustc-link-lib={}", lib);
    }
}
