#include "header.hpp"

namespace riff
{
    bool
    header::
    operator == (header const& h)
    {
        return id == h.id;
    }

    bool
    header::
    operator != (header const& h)
    {
        return id != h.id;
    }
}
