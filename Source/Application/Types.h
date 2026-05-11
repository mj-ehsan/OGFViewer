#ifndef __TYPES_H__
#define __TYPES_H__

#include <cstdint>

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using usize = size_t;

struct _vector3f 
{
    float x, y, z;
};
using Vector3f = _vector3f;

struct _bbox 
{
    float x1, y1, z1;
    float x2, y2, z2;
};
using BBox = _bbox;

struct _bsphere 
{
    Vector3f center;
    float radius;
};
using BSphere = _bsphere;

#endif
