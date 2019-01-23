#pragma once

#include "riff_types.hpp"

namespace riff
{
    struct header
    {
        fourcc  id;

        dword_t size;

        bool operator == (header const& h);

        bool operator != (header const& h);
    };
}
