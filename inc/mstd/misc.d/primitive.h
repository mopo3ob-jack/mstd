#ifndef MSTD_PRIMITIVE_H
#define MSTD_PRIMITIVE_H

// Character types
#ifdef __cplusplus

#include <cstdint>
#include <cstddef>
#include <cuchar>

namespace mstd {

#else

#include <stdint.h>
#include <stddef.h>
#include <uchar.h>

#endif

typedef char        C8;
typedef char16_t    C16;
typedef char32_t    C32;

// Signed integer types
typedef int8_t      I8;
typedef int16_t     I16;
typedef int32_t     I32;
typedef int64_t     I64;

// Unsigned integer types
typedef uint8_t     U8;
typedef uint16_t    U16;
typedef uint32_t    U32;
typedef uint64_t    U64;
typedef size_t      Size;
typedef size_t      Status;

// Floating point types
typedef float       F32;
typedef double      F64;

// Boolean type
typedef bool        Bool;

#ifdef __cplusplus
#ifndef MSTD_SUPRESS_PRIMITIVE_SIZE_GURANTEE
static_assert(sizeof(C8) == 1);
static_assert(sizeof(C16) >= 2);
static_assert(sizeof(C32) >= 4);

static_assert(sizeof(I8) == 1);
static_assert(sizeof(I16) == 2);
static_assert(sizeof(I32) == 4);
static_assert(sizeof(I64) == 8);

static_assert(sizeof(U8) == 1);
static_assert(sizeof(U16) == 2);
static_assert(sizeof(U32) == 4);
static_assert(sizeof(U64) == 8);

static_assert(sizeof(F32) == 4);
static_assert(sizeof(F64) == 8);
#endif

}
#endif

#endif
