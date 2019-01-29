#pragma once

#include "header.hpp"
#include "riff_const.hpp"

#include <fstream>

namespace riff
{
    class riff_stream;

    template <class T>
    void read (riff_stream &, T &);

    template <class T>
    struct read_detail;
}

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


        friend class header_iterator;

        template <class Sample>
        friend class wave_data_iterator;

        template <class T>
        friend struct read_detail;

    private :

        template <class T>
        void read (T &);

        void read (void*, std::streamsize);

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
        read( &x, sizeof( x ));
    }


    template <class T>
    void read (riff_stream & stream, T & x)
    {
        read_detail <T> {} ( stream, x );
    }


    template <class T>
    struct read_detail
    {
        inline
        void operator () (riff_stream & stream, T & x) const
        {
            stream.read( x );
        }
    };
}
