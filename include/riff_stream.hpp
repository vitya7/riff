#pragma once

#include "header.hpp"
#include "riff_const.hpp"

#include <fstream>

namespace riff
{
    class riff_stream
    {
    public :

        using wrapped_stream_type = std::ifstream;

        riff_stream () = default;

        ~riff_stream () = default;

        explicit
        riff_stream (std::string const&);

        bool is_open () const;

        bool eof () const;

        void open (std::string const&);

        void close ();

        void reopen ();

        std::string const& get_path () const&;

        wrapped_stream_type const& get_ifstream () const&;

        header const& get_header () const&;

        fourcc const& get_format () const&;

        template <class T>
        void read (T &);

        friend class header_iterator;

        template <class Sample>
        friend class wave_data_iterator;

    private :

        void init ();

        std::string m_path;

        wrapped_stream_type m_stream;

        header m_header;

        fourcc m_format;
    };

    template <class T>
    void
    riff_stream::
    read (T & x)
    {
        m_stream.read( reinterpret_cast <wrapped_stream_type::char_type*> ( &x ), sizeof( x ) );
    }
}
