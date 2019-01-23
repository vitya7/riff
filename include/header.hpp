#pragma once

#include "riff_types.hpp"

namespace riff
{
    struct header
    {
        fourcc  id;

        dword_t size;

        bool operator == (header const& h) const;

        bool operator != (header const& h) const;
    };
}
