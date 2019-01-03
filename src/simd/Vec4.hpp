//
// Created by kurono267 on 2019-01-03.
//

#pragma once

#include <x86intrin.h>

namespace simd {

class Vec4 {
	public:
		Vec4();
		Vec4(const Vec4& v);
		explicit Vec4(float v);
		Vec4(float x, float y, float z, float w);
		explicit Vec4(const float* data);
		explicit Vec4(const __m128& _simd);

		union {
			struct {
				float x; float y; float z; float w;
			};
			float data[4];
			__m128 simd;
		};
};

Vec4 operator+(const Vec4& a, const Vec4& b);
Vec4 operator+(const Vec4& a, float b);

Vec4 operator-(const Vec4& a, const Vec4& b);
Vec4 operator-(const Vec4& a, float b);

Vec4 operator*(const Vec4& a, const Vec4& b);
Vec4 operator*(const Vec4& a, float b);

Vec4 operator/(const Vec4& a, const Vec4& b);
Vec4 operator/(const Vec4& a, float b);

}
