#pragma clang diagnostic push
#pragma ide diagnostic ignored "portability-simd-intrinsics"
//
// Created by kurono267 on 2019-01-03.
//

#include <cstring>
#include "Vec4.hpp"

namespace simd {

Vec4::Vec4() : Vec4(0.f) {}

Vec4::Vec4(const Vec4 &v){
	simd = v.simd;
}

Vec4::Vec4(float v) {
	simd = _mm_set1_ps(v);
}

Vec4::Vec4(float _x, float _y, float _z, float _w) {
	simd = _mm_set_ps(_w,_z,_y,_x);
}

Vec4::Vec4(const float *_data) {
	simd = _mm_load_ps(_data);
}

Vec4::Vec4(const __m128 &_simd) : simd(_simd) {}

Vec4 &Vec4::operator+=(const Vec4 &b) {
	simd = _mm_add_ps(simd,b.simd);
	return *this;
}

Vec4 &Vec4::operator+=(float b) {
	simd = _mm_add_ps(simd,_mm_set1_ps(b));
	return *this;
}

Vec4 &Vec4::operator-=(const Vec4 &b) {
	simd = _mm_sub_ps(simd,b.simd);
	return *this;
}

Vec4 &Vec4::operator-=(float b) {
	simd = _mm_sub_ps(simd,_mm_set1_ps(b));
	return *this;
}

Vec4 &Vec4::operator*=(const Vec4 &b) {
	simd = _mm_mul_ps(simd,b.simd);
	return *this;
}

Vec4 &Vec4::operator*=(float b) {
	simd = _mm_mul_ps(simd,_mm_set1_ps(b));
	return *this;
}

Vec4 &Vec4::operator/=(const Vec4 &b) {
	simd = _mm_div_ps(simd,b.simd);
	return *this;
}

Vec4 &Vec4::operator/=(float b) {
	simd = _mm_div_ps(simd,_mm_set1_ps(b));
	return *this;
}

Vec4 operator+(const Vec4 &a, const Vec4 &b) {
	return Vec4(_mm_add_ps(a.simd,b.simd));
}

Vec4 operator+(const Vec4 &a, float b) {
	return Vec4(_mm_add_ps(a.simd,_mm_set1_ps(b)));
}

Vec4 operator-(const Vec4 &a, const Vec4 &b) {
	return Vec4(_mm_sub_ps(a.simd,b.simd));
}

Vec4 operator-(const Vec4 &a, float b) {
	return Vec4(_mm_sub_ps(a.simd,_mm_set1_ps(b)));
}

Vec4 operator*(const Vec4 &a, const Vec4 &b) {
	return Vec4(_mm_mul_ps(a.simd,b.simd));
}

Vec4 operator*(const Vec4 &a, float b) {
	return Vec4(_mm_mul_ps(a.simd,_mm_set1_ps(b)));
}

Vec4 operator/(const Vec4 &a, const Vec4 &b) {
	return Vec4(_mm_div_ps(a.simd,b.simd));
}

Vec4 operator/(const Vec4 &a, float b) {
	return Vec4(_mm_div_ps(a.simd,_mm_set1_ps(b)));
}

}

#pragma clang diagnostic pop