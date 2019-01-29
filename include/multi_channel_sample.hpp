#pragma once

#include "fmt_chunk.hpp"

#include <vector>

namespace riff
{
    template <class T = int16_t>
    class multi_channel_sample
    {
    public :

        using value_type = T;
        using data_type = std::vector <value_type>;

        multi_channel_sample () = default;

        explicit
        multi_channel_sample (word_t num_of_channels, word_t bits_per_sample)
            : m_num_of_channels ( num_of_channels )
            , m_bits_per_sample ( bits_per_sample )
            , m_data            ( num_of_channels )
        {}

        explicit
        multi_channel_sample (fmt_chunk const& fmt)
            : multi_channel_sample ( fmt.num_of_channels, fmt.bits_per_sample )
        {}

        word_t num_of_channels () const { return m_num_of_channels; }

        word_t bits_per_sample () const { return m_bits_per_sample; }

        word_t bytes_per_sample () const { return m_bits_per_sample / 8 + (m_bits_per_sample % 8 != 0); }

        data_type const& data () const& { return m_data; }

    private :

        word_t m_num_of_channels = 0;

        word_t m_bits_per_sample = 0;

        data_type m_data;
    };

    template <class T>
    struct read_detail < multi_channel_sample <T> >
    {
        inline
        void operator () (riff_stream & stream, multi_channel_sample <T> & sample) const
        {
            const auto sz = sample.bytes_per_sample();

            for(auto & cx : sample.data())
            {
                auto & x = const_cast < typename multi_channel_sample <T>::value_type & > (cx);

                stream.read( &x, sz );
            }
        }
    };

}
