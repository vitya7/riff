#pragma once

#include "header.hpp"

#include <fstream>

namespace riff
{

    constexpr fourcc RIFF_ID = { 'R', 'I', 'F', 'F' };

    class riff_stream
    {
    public :

        using stream_type = std::ifstream;

        riff_stream () = default;

        ~riff_stream () = default;

        explicit
        riff_stream (std::string const&);

        bool is_open () const;

        bool eof () const;

        void open (std::string const&);

        void close ();

        void reset ();

        std::string const& get_path () const&;

        stream_type const& get_ifstream () const&;

        header const& get_header () const&;

        fourcc const& get_format () const&;

        template <class T>
        void read (T &);

    private :

        void init ();

        std::string m_path;

        stream_type m_stream;

        header m_header;

        fourcc m_format;
    };
}
