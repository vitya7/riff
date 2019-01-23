#include "header_iterator.hpp"

namespace riff
{
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
    operator * ()
    {
        return m_header;
    }

    header_iterator &
    header_iterator::
    operator ++ ()
    {
        if( p_stream )
        {
            p_stream->m_stream.seekg( m_header.size, stream_type::wrapped_stream_type::cur );

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
            header_iterator tmp = *this;

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
            p_stream->read( m_header );
        }
    }
}
