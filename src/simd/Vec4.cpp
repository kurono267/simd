//
// Created by kurono267 on 2019-01-03.
//

#include <cstring>
#include "Vec4.hpp"

namespace simd {

Vec4::Vec4() : Vec4(0.f) {}

Vec4::Vec4(const Vec4 &v) {

}

Vec4::Vec4(const float v) {
	simd = _mm_set1_ps(v);
}

Vec4::Vec4(const float _x, const float _y, const float _z, const float _w) {
	simd = _mm_set_ps(_w,_z,_y,_x);
}

Vec4::Vec4(const float *_data) {
	simd = _mm_load_ps(_data);
}

}
