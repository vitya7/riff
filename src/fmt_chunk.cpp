#include "fmt_chunk.hpp"

#include "header_iterator.hpp"

namespace riff
{
    void read_fmt_chunk (riff_stream & stream, fmt_chunk & chunk)
    {
        auto fmt_head = find_header( stream, fmt__ID );

        if( ! fmt_head.has_value() )
        {
            throw std::logic_error{ "read_fmt_chunk failure : 'fmt ' chunk not found in file " + stream.get_path() };
        }

        chunk.head = *fmt_head;

        read( stream, chunk.compression_code  );
        read( stream, chunk.num_of_channels   );
        read( stream, chunk.sample_rate       );
        read( stream, chunk.avg_bytes_per_sec );
        read( stream, chunk.block_align       );
        read( stream, chunk.bits_per_sample   );
    }
}
