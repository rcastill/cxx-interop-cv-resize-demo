#include <cvresize.h>
#include <opencv2/opencv.hpp>

std::vector<unsigned char> resize_raw(std::vector<unsigned char> const& raw, unsigned int w, unsigned int h)
{
    cv::Mat im = cv::imdecode(raw, cv::IMREAD_COLOR);
    cv::Mat dst;
    cv::resize(im, dst, cv::Size(w, h), 0., 0., cv::INTER_LINEAR);
    std::vector<unsigned char> out;
    cv::imencode(".jpg", dst, out);
    return out;
}

#ifndef DISABLE_RUST_SUPPORT
rust::Vec<uint8_t> resize_raw(rust::Slice<uint8_t const> buf, size_t w, size_t h)
{
    std::vector<uint8_t> raw(buf.begin(), buf.end());
    std::vector<unsigned char> buf_resized = resize_raw(raw, w, h);
    rust::Vec<uint8_t> out;
    out.reserve(buf_resized.size());
    for (unsigned char b : buf_resized)
        out.push_back(b);
    return out;
}
#endif