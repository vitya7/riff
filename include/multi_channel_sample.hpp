#pragma once

#include "fmt_chunk.hpp"

#include <vector>

namespace riff
{

    class multi_channel_sample
    {
    public :

        using buffer_type = std::vector <uint8_t>;

        multi_channel_sample () = default;

        explicit
        multi_channel_sample (word_t num_of_channels_, word_t bits_per_sample_);

        explicit
        multi_channel_sample (fmt_chunk const& fmt);

        word_t num_of_channels () const;

        word_t bits_per_sample () const;

        word_t bytes_per_sample () const;

        void const* get_ptr (size_t pos) const&;

        template <class T>
        T const& get (size_t pos) const&;

    private :

        word_t m_num_of_channels = 0;

        word_t m_bits_per_sample = 0;

        buffer_type m_buffer;
    };

    template <class T>
    T const&
    multi_channel_sample::
    get (size_t pos) const&
    {
        return *reinterpret_cast <T const*> ( get_ptr( pos ) );
    }

    template <>
    struct read_detail <multi_channel_sample>
    {
        inline
        void operator () (riff_stream & stream, multi_channel_sample & sample) const
        {
            for(size_t pos = 0, size = sample.num_of_channels(); pos != size; pos++ )
            {
                auto ptr = const_cast <void *> ( sample.get_ptr( pos ) );

                stream.read( ptr, sample.bytes_per_sample() );
            }
        }
    };

}
