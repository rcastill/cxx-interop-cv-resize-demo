#include <cvresize.h>
#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>

std::vector<unsigned char> read_file(char const* filename)
{
    // open the file:
    std::ifstream file(filename, std::ios::binary);

    // Stop eating new lines in binary mode!!!
    file.unsetf(std::ios::skipws);

    // get its size:
    std::streampos fileSize;

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // reserve capacity
    std::vector<unsigned char> vec;
    vec.reserve(fileSize);

    // read the data:
    vec.insert(vec.begin(),
        std::istream_iterator<unsigned char>(file),
        std::istream_iterator<unsigned char>());

    return vec;
}

int main(int argc, char const** argv)
{
    if (argc != 4) {
        std::cerr << "Usage: " << std::string(*argv) << " image w h" << std::endl;
        return 1;
    }
    std::string image_path = argv[1];
    std::string w_s = argv[2];
    std::string h_s = argv[3];
    size_t idx;
    int w = std::stoi(w_s, &idx);
    if (idx != w_s.size() || w <= 0) {
        std::cerr << "w must be a positive number" << std::endl;
        return 1;
    }
    int h = std::stoi(h_s, &idx);
    if (idx != h_s.size() || h <= 0) {
        std::cerr << "h must be a positive number" << std::endl;
        return 1;
    }
    std::vector<unsigned char> buf = read_file(image_path.c_str());
    std::vector<unsigned char> resized_buf = resize_raw(buf, w, h);
    size_t max_chunk_size = 64;
    for (size_t i = 0; i < resized_buf.size(); i += max_chunk_size) {
        size_t remaining = resized_buf.size() - i;
        size_t chunk_size = (max_chunk_size < remaining) ? max_chunk_size : remaining;
        std::fwrite((void*)(resized_buf.data() + i), 1, chunk_size, stdout);
    }
}