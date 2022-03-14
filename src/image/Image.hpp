//
// Created by lengyel on 2022. 03. 12..
//

#ifndef EVA_IMAGE_HPP
#define EVA_IMAGE_HPP

#include "Pixel.hpp"
#include "../memory/blob/Blob.hpp"

namespace eva {

    template<typename PIXEL_FORMAT>
    class Image {
    public:
        using PixelFormat = PIXEL_FORMAT;
        using PlaneArray = typename PixelFormat::PlaneArray;
        using LinestepArray = std::array<std::size_t, PixelFormat::plane_number>;
        using Pixel = typename PixelFormat::Struct;
        using Cursor = typename PixelFormat::Cursor;

    private:
        /***
         * Plane array generator helper function
         * @param width
         * @param height
         * @return
         */
        inline
        static PlaneArray _make_planes(std::size_t width, std::size_t height){
            return PixelFormat::template make_planes<Blob>(width, height);
        }

        /***
         * Line step array generator helper function
         * @param width
         * @param height
         * @return
         */
        inline
        static LinestepArray _make_linesteps(std::size_t width, std::size_t height){
            return PixelFormat::make_linesteps(width, height);
        }

    public:
        Image(std::size_t width, std::size_t height) :
                _planes(_make_planes(width, height)),
                _linesteps(_make_linesteps(width, height)),
                _width(width),
                _height(height) {}

        Image(Image &&other) noexcept = default;

        std::size_t width() const noexcept{
            return _width;
        }

        std::size_t height() const noexcept{
            return _height;
        }

        std::size_t pixelSize()const noexcept{
            return PixelFormat::size;
        }

        std::size_t channels()const noexcept{
            return PixelFormat::channels;
        }

        std::size_t linestep(std::size_t index = 0)const noexcept{
            return _linesteps[index];
        }

        template<std::size_t INDEX = 0>
        std::size_t linestep()const noexcept{
            return _linesteps[INDEX];
        }

        Cursor getPixel(std::size_t x, std::size_t y){
            return Cursor(_planes);
        }
    private:
        PlaneArray _planes;
        LinestepArray _linesteps;
        std::size_t _width;
        std::size_t _height;
    };
}

#endif //EVA_IMAGE_HPP
