#include "header_iterator.hpp"

#include <algorithm>

namespace riff
{
    std::optional <header>
    find_header (riff_stream & stream, fourcc const& id)
    {
        header_iterator first { stream };
        header_iterator last {};

        auto result = std::find( first, last, header {.id = id} );

        return result == last ? std::nullopt : std::make_optional( *result );
    }


    header_iterator::
    header_iterator (stream_type & stream)
        : p_stream { &stream }
    {}

    bool
    header_iterator::
    operator == (header_iterator const& it) const
    {
        return ( end_of_stream() && it.end_of_stream() ) || ( p_stream == it.p_stream );
    }

    bool
    header_iterator::
    operator != (header_iterator const& it) const
    {
        return !( *this == it );
    }

    bool
    header_iterator::
    end_of_stream () const
    {
        return p_stream ? p_stream->eof() : true;
    }

    header_iterator::reference
    header_iterator::
    operator * () const
    {
        return m_header;
    }

    header_iterator::pointer
    header_iterator::
    operator -> () const
    {
        return &m_header;
    }

    header_iterator &
    header_iterator::
    operator ++ ()
    {
        if( p_stream )
        {
            p_stream->m_stream.seekg( m_header.size + m_header.size % 2, stream_type::wrapped_stream_type::cur );

            update_proxy_object();
        }
        return *this;
    }

    header_iterator
    header_iterator::
    operator ++ (int)
    {
        if( p_stream )
        {
            auto tmp = *this;

            ++(*this);

            return tmp;
        }
        else
        {
            return *this;
        }
    }

    void
    header_iterator::
    update_proxy_object ()
    {
        if( p_stream )
        {
            read( *p_stream, m_header );
        }
    }
}
