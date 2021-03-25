use std::{
    fs::File,
    io::{stdout, BufWriter, Read, Write},
    path::PathBuf,
};

use structopt::StructOpt;

#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("cvresize/include/cvresize.h");

        fn resize_raw(buf: &[u8], w: usize, h: usize) -> Vec<u8>;
    }
}

#[derive(StructOpt)]
struct Opt {
    #[structopt(short)]
    w: usize,
    #[structopt(short)]
    h: usize,
    image_path: PathBuf,
}

fn main() {
    let opt = Opt::from_args();
    let mut f = File::open(&opt.image_path).expect("Could not open file");
    let mut buf = vec![];
    f.read_to_end(&mut buf).expect("Could not load buffer");
    let resized_buf = ffi::resize_raw(&buf, opt.w, opt.h);
    let mut writer = BufWriter::new(stdout());
    writer.write_all(&resized_buf).unwrap();
}
