#pragma once

#include <cstdint>
#include <array>

namespace riff
{
    using char_t = uint8_t;

    using word_t = uint16_t;

    using dword_t = uint32_t;

    using fourcc = std::array <char_t, 4>;
}
