//
// Created by lengyel on 2022. 03. 12..
//

#ifndef EVA_PIXEL_HPP
#define EVA_PIXEL_HPP

#include <cstddef>
#include <array>
#include "../memory/blob/Blob.hpp"

namespace eva {

    template<std::size_t SIZE, std::size_t CHANNEL>
    struct PixelOrder {
        static constexpr std::size_t channel = CHANNEL;
        static constexpr std::size_t size = SIZE;
        static constexpr std::size_t plane_number = 1;

        template<typename T>
        __EVA_ALWAYS_INLINE__
        static std::array<T, plane_number> make_planes(std::size_t width, std::size_t height) {
            return {
                    T(width * height)
            };
        }

        __EVA_ALWAYS_INLINE__
        static std::array<std::size_t, plane_number> make_linesteps(std::size_t width, std::size_t height) {
            return {width * SIZE / 8};
        }
    };


    using RGB24 = PixelOrder<24, 3>;
    using RGBA = PixelOrder<32, 4>;
    using RGBX = PixelOrder<32, 3>;

}

#endif //EVA_PIXEL_HPP
