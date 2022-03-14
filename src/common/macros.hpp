//
// Created by lengyel on 2022. 03. 10..
//

#ifndef EVA_MACROS_HPP
#define EVA_MACROS_HPP

#define EVA_CPP_STD_11 (201103L)
#define EVA_CPP_STD_14 (201402L)
#define EVA_CPP_STD_17 (201703L)
#define EVA_CPP_STD_20 (202002L)

#if __cplusplus >= EVA_CPP_STD_17
#define __EVA_NODISCARD__ [[nodiscard]]
#else
#define __EVA_NODISCARD__
#endif

#if __cplusplus >= EVA_CPP_STD_20
#define __EVA_NO_UNIQUE_ADDRESS__ [[no_unique_address]]
#else
#define __EVA_NO_UNIQUE_ADDRESS__
#endif

#ifdef _MSC_VER
#define __EVA_ALWAYS_INLINE__ __forceinline
#elif defined(__GNUC__)
#define __EVA_ALWAYS_INLINE__ inline __attribute__((__always_inline__))
#elif defined(__CLANG__)
#if __has_attribute(__always_inline__)
#define __EVA_ALWAYS_INLINE__ inline __attribute__((__always_inline__))
#else
#define __EVA_ALWAYS_INLINE__ inline
#endif
#else
#define __EVA_ALWAYS_INLINE__ inline
#endif


#endif //EVA_MACROS_HPP
