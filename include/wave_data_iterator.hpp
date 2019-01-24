#pragma once

#include "header_iterator.hpp"

namespace riff
{
    template <class Sample>
    class wave_data_iterator
    {
    public :
        using value_type        = Sample;
        using pointer	        = value_type const*;
        using reference	        = value_type const&;
        using difference_type   = void;
        using iterator_category	= std::input_iterator_tag;

        using stream_type = riff_stream;
        using pos_type = stream_type::wrapped_stream_type::pos_type;

        wave_data_iterator () = default;

        explicit
        wave_data_iterator (stream_type & stream);

        bool operator == (wave_data_iterator const& it) const;

        bool operator != (wave_data_iterator const& it) const;

        bool end_of_stream () const;

        reference operator * () const;

        pointer operator -> () const;

        wave_data_iterator & operator ++ ();

        wave_data_iterator   operator ++ (int);

        pos_type cur_pos () const;

        pos_type end_pos () const;

    private :

        void update_proxy_object ();

        pos_type m_cur_pos = -1;

        pos_type m_end_pos = -1;

        value_type m_sample;

        stream_type *p_stream = nullptr;

    };
}


#include <algorithm>

namespace riff
{
    template <class Sample>
    wave_data_iterator <Sample>::
    wave_data_iterator (stream_type & stream)
        : p_stream { &stream }
    {
        auto result = find_header( stream, data_ID );

        if( ! result.has_value() )
        {
            throw std::logic_error{ "wave_data_iterator failure : 'data' chunk not found in file " + stream.get_path() };
        }

        m_cur_pos = stream.m_stream.tellg();
        m_end_pos = m_cur_pos + result->size;
    }

    template <class Sample>
    bool
    wave_data_iterator <Sample>::
    operator == (wave_data_iterator const& it) const
    {
        return ( end_of_stream() && it.end_of_stream() ) || ( p_stream == it.p_stream );
    }

    template <class Sample>
    bool
    wave_data_iterator <Sample>::
    operator != (wave_data_iterator const& it) const
    {
        return !( *this == it );
    }

    template <class Sample>
    bool
    wave_data_iterator <Sample>::
    end_of_stream () const
    {
        return p_stream ? ( cur_pos() >= end_pos() ) : true;
    }

    template <class Sample>
    typename wave_data_iterator <Sample>::reference
    wave_data_iterator <Sample>::
    operator * () const
    {
        return m_sample;
    }

    template <class Sample>
    typename wave_data_iterator <Sample>::pointer
    wave_data_iterator <Sample>::
    operator -> () const
    {
        return &m_sample;
    }

    template <class Sample>
    wave_data_iterator <Sample> &
    wave_data_iterator <Sample>::
    operator ++ ()
    {
        if( p_stream )
        {
            update_proxy_object();

            m_cur_pos = p_stream->m_stream.tellg();
        }
        return *this;
    }

    template <class Sample>
    wave_data_iterator <Sample>
    wave_data_iterator <Sample>::
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

    template <class Sample>
    void
    wave_data_iterator <Sample>::
    update_proxy_object ()
    {
        if( p_stream )
        {
            read( *p_stream, m_sample );
        }
    }

    template <class Sample>
    typename wave_data_iterator <Sample>:: pos_type
    wave_data_iterator <Sample>::
    cur_pos () const
    {
        return m_cur_pos;
    }

    template <class Sample>
    typename wave_data_iterator <Sample>:: pos_type
    wave_data_iterator <Sample>::
    end_pos () const
    {
        return m_end_pos;
    }

}
