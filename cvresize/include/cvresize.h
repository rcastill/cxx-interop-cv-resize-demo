#pragma once

#ifndef DISABLE_RUST_SUPPORT
#include "src/main.rs.h"
#endif
#include <cstdint>
#include <vector>

std::vector<unsigned char> resize_raw(std::vector<unsigned char> const& buf, unsigned int w, unsigned int h);

#ifndef DISABLE_RUST_SUPPORT
rust::Vec<uint8_t> resize_raw(rust::Slice<uint8_t const> buf, size_t w, size_t h);
#endif