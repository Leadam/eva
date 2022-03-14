//
// Created by lengyel on 2022. 03. 14..
//

#ifndef EVA_SIMPLEPIXEL_HPP
#define EVA_SIMPLEPIXEL_HPP

#include <cstddef>
#include <array>
#include "../../memory/blob/Blob.hpp"

namespace eva {
    template<typename FORMAT>
    class Image;

#pragma pack(push, 1)
    struct RGBPixel{
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };

    struct RGBAPixel{
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;
    };

    struct RGBXPixel{
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t _resoved;
    };
#pragma pack(pop)

    template<std::size_t SIZE, std::size_t CHANNEL, typename STRUCT>
    struct SimplePixel {
        static constexpr std::size_t channel = CHANNEL;
        static constexpr std::size_t size = SIZE;
        static constexpr std::size_t plane_number = 1;
        using Struct = STRUCT;
        using self = SimplePixel<SIZE, CHANNEL, STRUCT>;
        using PlaneArray = std::array<Blob, plane_number>;
        using LinestepArray = std::array<std::size_t, plane_number>;

        template<typename T>
        __EVA_ALWAYS_INLINE__
        static std::array<T, plane_number> make_planes(std::size_t width, std::size_t height){
            return {
                    T(width * height)
            };
        }

        __EVA_ALWAYS_INLINE__
        static std::array<std::size_t, plane_number> make_linesteps(std::size_t width, std::size_t height) noexcept{
            return {width * SIZE / 8};
        }

        __EVA_ALWAYS_INLINE__
        static Struct* make_pixel(void* address)noexcept{
            return reinterpret_cast<Struct*>(address);
        }

        class Cursor{
        private:
            std::byte* _base;
            std::byte* _pointer;
            std::size_t _linestep;

            explicit Cursor(const PlaneArray& ptr, const LinestepArray& linestep):
                _base(ptr[0].data()),
                _pointer(ptr[0].data()),
                _linestep(linestep[0]){}

            friend Image<self>;
        public:
            Struct& operator*(){
                return *make_pixel(_pointer);
            }

            const Struct& operator*()const{
                return *make_pixel(_pointer);
            }

            Struct* operator->(){
                return make_pixel(_pointer);
            }

            const Struct* operator->()const{
                return make_pixel(_pointer);
            }

            Cursor operator++(){
                _pointer += size;
            }

            Cursor operator--(){
                _pointer -= size;
            }

        };
    };


    using RGB24 = SimplePixel<24, 3, RGBPixel>;
    using RGBA = SimplePixel<32, 4, RGBAPixel>;
    using RGBX = SimplePixel<32, 3, RGBXPixel>;
    using GRAY8 = SimplePixel<8, 1, uint8_t>;
    using GRAY16 = SimplePixel<16, 1, uint16_t>;

}

#endif //EVA_SIMPLEPIXEL_HPP
