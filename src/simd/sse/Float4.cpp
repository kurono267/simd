#pragma clang diagnostic push
#pragma ide diagnostic ignored "portability-simd-intrinsics"
//
// Created by kurono267 on 2019-01-03.
//

#include <cstring>
#include "Float4.hpp"

namespace simd {

Float4::Float4() : Float4(0.f) {}

Float4::Float4(const Float4 &v){
	simd = v.simd;
}

Float4::Float4(float v) {
	simd = _mm_set1_ps(v);
}

Float4::Float4(float _x, float _y, float _z, float _w) {
	simd = _mm_set_ps(_w,_z,_y,_x);
}

Float4::Float4(const float *_data) {
	simd = _mm_load_ps(_data);
}

Float4::Float4(const __m128 &_simd) : simd(_simd) {}

Float4 &Float4::operator+=(const Float4 &b) {
	simd = _mm_add_ps(simd,b.simd);
	return *this;
}

Float4 &Float4::operator+=(float b) {
	simd = _mm_add_ps(simd,_mm_set1_ps(b));
	return *this;
}

Float4 &Float4::operator-=(const Float4 &b) {
	simd = _mm_sub_ps(simd,b.simd);
	return *this;
}

Float4 &Float4::operator-=(float b) {
	simd = _mm_sub_ps(simd,_mm_set1_ps(b));
	return *this;
}

Float4 &Float4::operator*=(const Float4 &b) {
	simd = _mm_mul_ps(simd,b.simd);
	return *this;
}

Float4 &Float4::operator*=(float b) {
	simd = _mm_mul_ps(simd,_mm_set1_ps(b));
	return *this;
}

Float4 &Float4::operator/=(const Float4 &b) {
	simd = _mm_div_ps(simd,b.simd);
	return *this;
}

Float4 &Float4::operator/=(float b) {
	simd = _mm_div_ps(simd,_mm_set1_ps(b));
	return *this;
}

Float4 operator+(const Float4 &a, const Float4 &b) {
	return Float4(_mm_add_ps(a.simd,b.simd));
}

Float4 operator+(const Float4 &a, float b) {
	return Float4(_mm_add_ps(a.simd,_mm_set1_ps(b)));
}

Float4 operator-(const Float4 &a, const Float4 &b) {
	return Float4(_mm_sub_ps(a.simd,b.simd));
}

Float4 operator-(const Float4 &a, float b) {
	return Float4(_mm_sub_ps(a.simd,_mm_set1_ps(b)));
}

Float4 operator*(const Float4 &a, const Float4 &b) {
	return Float4(_mm_mul_ps(a.simd,b.simd));
}

Float4 operator*(const Float4 &a, float b) {
	return Float4(_mm_mul_ps(a.simd,_mm_set1_ps(b)));
}

Float4 operator/(const Float4 &a, const Float4 &b) {
	return Float4(_mm_div_ps(a.simd,b.simd));
}

Float4 operator/(const Float4 &a, float b) {
	return Float4(_mm_div_ps(a.simd,_mm_set1_ps(b)));
}

}

#pragma clang diagnostic pop