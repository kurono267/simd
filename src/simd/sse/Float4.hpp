//
// Created by kurono267 on 2019-01-03.
//

#pragma once

#include <x86intrin.h>
#include <functional>

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

		inline float& operator[](int id){
			return data[id];
		}

		inline const float& operator[](int id) const {
			return data[id];
		}

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

class Bool4 {
	public:
		Bool4() = default;
		explicit Bool4(const __m128& data) : simd(data) {}

		inline bool operator[](const int id) const {
			return static_cast<bool>((_mm_movemask_ps(simd) >> id) & 1);
		}

		__m128 simd;
};

inline Bool4 operator<(const Float4& a, const Float4& b) {
	return Bool4(_mm_cmplt_ps(a.simd,b.simd));
}

inline Bool4 operator>(const Float4& a, const Float4& b) {
	return Bool4(_mm_cmpgt_ps(a.simd,b.simd));
}

inline Bool4 operator<=(const Float4& a, const Float4& b) {
	return Bool4(_mm_cmple_ps(a.simd,b.simd));
}

inline Bool4 operator>=(const Float4& a, const Float4& b) {
	return Bool4(_mm_cmpge_ps(a.simd,b.simd));
}

inline Bool4 operator==(const Float4& a, const Float4& b) {
	return Bool4(_mm_cmpeq_ps(a.simd,b.simd));
}

inline Bool4 operator!=(const Float4& a, const Float4& b) {
	return Bool4(_mm_cmpneq_ps(a.simd,b.simd));
}

inline Float4 blend(const Float4& a, const Float4& b, const Bool4& m){
	return Float4(_mm_blendv_ps(b.simd,a.simd,m.simd));
}

}
