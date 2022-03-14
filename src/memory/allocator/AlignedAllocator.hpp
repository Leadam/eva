//
// Created by lengyel on 2022. 03. 10..
//

#ifndef EVA_ALIGNEDALLOCATOR_HPP
#define EVA_ALIGNEDALLOCATOR_HPP

#include <cstddef>
#include <stdexcept>
#include "../../common/macros.hpp"

namespace eva {
    template<typename T, std::align_val_t ALIGNMENT>
    class AlignedAllocator {
    public:
        using pointer = T *;
        using const_pointer = const T *;
        using reference = T &;
        using const_reference = const T &;
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = ptrdiff_t;
        static constexpr std::align_val_t Alignment = ALIGNMENT;

        T *address(reference r) const;

        const T *address(const_reference s) const;

        __EVA_NODISCARD__
        std::size_t max_size() const;

        template<typename U>
        struct rebind {
            using other = AlignedAllocator<U, Alignment>;
        };

        bool operator!=(const AlignedAllocator &other) const;

        void construct(pointer p, const_reference t) const;

        void destroy(pointer p) const;

        bool operator==(const AlignedAllocator &other) const;

        AlignedAllocator() = default;

        AlignedAllocator(const AlignedAllocator &) = default;

        template<typename U>
        explicit AlignedAllocator(const AlignedAllocator<U, Alignment> &) {};

        ~AlignedAllocator() = default;

        T *allocate(std::size_t n) const;

        void deallocate(pointer p, std::size_t size) const;

        template<typename U>
        T *allocate(std::size_t n, const U * /* const hint */) const;

    private:
        AlignedAllocator &operator=(const AlignedAllocator &) = delete;
    };


    template<typename T, std::align_val_t ALIGNMENT>
    T *AlignedAllocator<T, ALIGNMENT>::address(T &r) const {
        return &r;
    }

    template<typename T, std::align_val_t ALIGNMENT>
    const T *AlignedAllocator<T, ALIGNMENT>::address(const T &s) const {
        return &s;
    }

    template<typename T, std::align_val_t ALIGNMENT>
    std::size_t AlignedAllocator<T, ALIGNMENT>::max_size() const {
        return (static_cast<std::size_t>(0) - static_cast<std::size_t>(1)) / sizeof(T);
    }

    template<typename T, std::align_val_t ALIGNMENT>
    bool AlignedAllocator<T, ALIGNMENT>::operator!=(const AlignedAllocator &other) const {
        return !(*this == other);
    }

    template<typename T, std::align_val_t ALIGNMENT>
    void AlignedAllocator<T, ALIGNMENT>::construct(T *const p, const T &t) const {
        void *const pv = static_cast<void *>(p);
        new(pv) T(t);
    }

    template<typename T, std::align_val_t ALIGNMENT>
    void AlignedAllocator<T, ALIGNMENT>::destroy(T *const p) const {
        p->~T();
    }

    template<typename T, std::align_val_t ALIGNMENT>
    bool AlignedAllocator<T, ALIGNMENT>::operator==(const AlignedAllocator &other) const {
        return true;
    }

    template<typename T, std::align_val_t ALIGNMENT>
    T *AlignedAllocator<T, ALIGNMENT>::allocate(const std::size_t n) const {
        if (n == 0) {
            return nullptr;
        }

        if (n > max_size()) {
            throw std::length_error("AlignedAllocator<T>::allocate() - Integer overflow.");
        }

        void *pv = ::operator new(n * sizeof(T), std::align_val_t(Alignment));

        if (pv == nullptr) {
            throw std::bad_alloc();
        }

        return static_cast<T *>(pv);
    }

    template<typename T, std::align_val_t ALIGNMENT>
    void AlignedAllocator<T, ALIGNMENT>::deallocate(T *const p, std::size_t size) const {
        ::operator delete(p, size, std::align_val_t(Alignment));
    }

    template<typename T, std::align_val_t ALIGNMENT>
    template<typename U>
    T *AlignedAllocator<T, ALIGNMENT>::allocate(const std::size_t n, const U *) const {
        return allocate(n);
    }
}
#endif //EVA_ALIGNEDALLOCATOR_HPP
