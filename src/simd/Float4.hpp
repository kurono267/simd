//
// Created by kurono267 on 2019-01-03.
//

#pragma once

#include <x86intrin.h>

namespace simd {

class Float4 {
	public:
		Float4();
		Float4(const Float4& v);
		explicit Float4(float v);
		Float4(float x, float y, float z, float w);
		explicit Float4(const float* data);
		explicit Float4(const __m128& _simd);

		Float4& operator+=(const Float4& b);
		Float4& operator+=(float b);
		Float4& operator-=(const Float4& b);
		Float4& operator-=(float b);
		Float4& operator*=(const Float4& b);
		Float4& operator*=(float b);
		Float4& operator/=(const Float4& b);
		Float4& operator/=(float b);

		union {
			struct {
				float x; float y; float z; float w;
			};
			float data[4];
			__m128 simd;
		};
};

Float4 operator+(const Float4& a, const Float4& b);
Float4 operator+(const Float4& a, float b);

Float4 operator-(const Float4& a, const Float4& b);
Float4 operator-(const Float4& a, float b);

Float4 operator*(const Float4& a, const Float4& b);
Float4 operator*(const Float4& a, float b);

Float4 operator/(const Float4& a, const Float4& b);
Float4 operator/(const Float4& a, float b);

}
