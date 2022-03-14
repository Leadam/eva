//
// Created by lengyel on 2022. 03. 10..
//

#ifndef EVA_BLOB_HPP
#define EVA_BLOB_HPP

#include <memory>
#include "../../common/macros.hpp"
#include "../allocator/AlignedAllocator.hpp"

namespace eva {
    template<typename T, typename ALLOCATOR>
    class BaseBlob {
    public:
        using allocator_t = ALLOCATOR;
        using pointer = T *;
        using const_pointer = const T *;
        using reference = T &;
        using const_reference = const T &;
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

    protected:
        pointer _data = nullptr;
        size_t _size = 0;
        __EVA_NO_UNIQUE_ADDRESS__
        allocator_t _allocator;

        BaseBlob(pointer data, size_t size) : _data(data), _size(size) {}

    public:
        explicit BaseBlob(size_t size) : _data(_allocator.allocate(size)), _size(size) {}

        BaseBlob(BaseBlob &&other) : _data(other._data), _size(other._size) {
            other._data = nullptr;
            other._size = 0;
        }

        BaseBlob &operator=(BaseBlob &&other) {
            std::swap(_data, other._data);
            std::swap(_size, other._size);
            return *this;
        }

        T &operator[](uint64_t idx) { return _data[idx]; }

        const T &operator[](uint64_t idx) const { return _data[idx]; }

        size_t size() const { return _size; }

        pointer data() const { return _data; }

        pointer release() {
            pointer tmp = _data;
            _data = nullptr;
            _size = 0;
            return tmp;
        }

        virtual ~BaseBlob() {
            _allocator.deallocate(_data, _size);
        }
    };

    using Blob = BaseBlob<std::byte, AlignedAllocator<std::byte, std::align_val_t(__STDCPP_DEFAULT_NEW_ALIGNMENT__)>>;

}
#endif //EVA_BLOB_HPP
