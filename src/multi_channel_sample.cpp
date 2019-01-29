#include "multi_channel_sample.hpp"

namespace riff
{
    multi_channel_sample::
    multi_channel_sample (word_t num_of_channels_, word_t bits_per_sample_)
        : m_num_of_channels ( num_of_channels_ )
        , m_bits_per_sample ( bits_per_sample_ )
        , m_buffer          ( num_of_channels() * bytes_per_sample() )
    {}

    multi_channel_sample::
    multi_channel_sample (fmt_chunk const& fmt)
        : multi_channel_sample ( fmt.num_of_channels, fmt.bits_per_sample )
    {}

    word_t
    multi_channel_sample::
    num_of_channels () const
    {
        return m_num_of_channels;
    }

    word_t
    multi_channel_sample::
    bits_per_sample () const
    {
        return m_bits_per_sample;
    }

    word_t
    multi_channel_sample::
    bytes_per_sample () const
    {
        return m_bits_per_sample / 8 + (m_bits_per_sample % 8 != 0);
    }

    void const*
    multi_channel_sample::
    get_ptr (size_t pos) const&
    {
        return std::next( m_buffer.data(), pos * bytes_per_sample() );
    }
}
