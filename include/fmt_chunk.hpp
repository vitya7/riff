#pragma once

#include "riff_stream.hpp"

namespace riff
{
    struct fmt_chunk;

    fmt_chunk read_fmt_chunk (riff_stream &);

    struct fmt_chunk
    {
        header  head;
        word_t  compression_code;
        word_t  num_of_channels;
        dword_t sample_rate;
        dword_t avg_bytes_per_sec;
        word_t  block_align;
        word_t  bits_per_sample;
    };
}
