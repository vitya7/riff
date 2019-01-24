#pragma once

#include "riff_stream.hpp"

namespace riff
{
    class header_iterator
    {
    public :
        using value_type        = header;
        using pointer	        = value_type const*;
        using reference	        = value_type const&;
        using difference_type   = void;
        using iterator_category	= std::input_iterator_tag;

        using stream_type = riff_stream;

        header_iterator () = default;

        explicit
        header_iterator (stream_type & stream);

        bool operator == (header_iterator const& it) const;

        bool operator != (header_iterator const& it) const;

        bool end_of_stream () const;

        reference operator * () const;

        pointer operator -> () const;

        header_iterator & operator ++ ();

        header_iterator   operator ++ (int);

        constexpr static value_type DEFAULT_HEADER = { .id = make_fourcc( "DFLT" ), .size = 0 };

    private :

        void update_proxy_object ();

        value_type m_header = DEFAULT_HEADER;

        stream_type *p_stream = nullptr;
    };
}
