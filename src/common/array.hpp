//
// Created by lengyel on 2022. 03. 12..
//

#ifndef EVA_COMMON_HPP
#define EVA_COMMON_HPP

#include <utility>
#include <array>
#include <tuple>

namespace eva {
    namespace details {
        template<typename T, std::size_t IDX, typename TUPLE>
        T _make_item(TUPLE &tuple) {
            return std::make_from_tuple<T>(tuple);
        }

        template<typename T, typename TUPLE, std::size_t SIZE, int... N>
        std::array<T, SIZE> _make_array_from(TUPLE &tuple, std::index_sequence<N...>) {
            return {
                    _make_item<T, N>(tuple)...
            };
        }
    }

    template<typename T, std::size_t SIZE, typename... ARGS>
    std::array<T, SIZE> make_array_from(ARGS... args) {
        using TUPLE = std::tuple<ARGS...>;
        return details::_make_array_from<T, TUPLE>(std::make_tuple(args...), std::make_index_sequence<SIZE>());
    }

}
#endif //EVA_COMMON_HPP
