#pragma once

#include "riff_types.hpp"

namespace riff
{
    constexpr fourcc make_fourcc (const char id[4])
    {
        return { char_t(id[0]), char_t(id[1]), char_t(id[2]), char_t(id[3]) };
    }

    constexpr fourcc RIFF_ID = make_fourcc( "RIFF" );
    constexpr fourcc WAVE_ID = make_fourcc( "WAVE" );
    constexpr fourcc fmt__ID = make_fourcc( "fmt " );
    constexpr fourcc data_ID = make_fourcc( "data" );

}
