#include "header.hpp"

namespace riff
{
    bool
    header::
    operator == (header const& h) const
    {
        return id == h.id;
    }

    bool
    header::
    operator != (header const& h) const
    {
        return id != h.id;
    }
}
