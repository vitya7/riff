#include "riff_stream.hpp"

namespace riff
{
    riff_stream::
    riff_stream (std::string const& path)
    {
        open( path );
    }

    bool
    riff_stream::
    is_open () const
    {
        return m_stream.is_open();
    }
    bool
    riff_stream::
    eof () const
    {
        return m_stream.eof();
    }

    void
    riff_stream::
    open (std::string const& path)
    {
        m_path = path;

        m_stream.open( path, wrapped_stream_type::binary );

        init();
    }

    void
    riff_stream::
    close ()
    {
        m_stream.close();
    }

    void
    riff_stream::
    reopen ()
    {
        close();
        open( m_path );
    }

    std::string const&
    riff_stream::
    get_path () const&
    {
        return m_path;
    }

    riff_stream::wrapped_stream_type const&
    riff_stream::
    get_ifstream () const&
    {
        return m_stream;
    }

    header const&
    riff_stream::
    get_header () const&
    {
        return m_header;
    }

    fourcc const&
    riff_stream::
    get_format () const&
    {
        return m_format;
    }

    void
    riff_stream::
    init ()
    {
        read( m_header );
        read( m_format );

        if( m_header.id != RIFF_ID )
        {
            throw std::logic_error{ "open failure : 'RIFF' chunk not found in file " + m_path };
        }
    }
}
