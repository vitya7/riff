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

        m_stream.open( path, stream_type::binary );

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
    reset ()
    {
        m_stream.seekg( 0 );

        init();
    }

    std::string const&
    riff_stream::
    get_path () const&
    {
        return m_path;
    }

    riff_stream::stream_type const&
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

    template <class T>
    void
    riff_stream::
    read (T & x)
    {
        m_stream.read( reinterpret_cast <stream_type::char_type*> ( &x ), sizeof( x ) );
    }

    void
    riff_stream::
    init ()
    {
        read( m_header );
        read( m_format );

        if( m_header.id != RIFF_ID )
        {
            throw std::logic_error{ "open failure : riff chunk not found in file " + m_path };
        }
    }
}
