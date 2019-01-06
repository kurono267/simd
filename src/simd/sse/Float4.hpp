//
// Created by kurono267 on 2019-01-03.
//

#pragma once

#include <x86intrin.h>
#include <functional>

namespace simd {

class Bool4 {
public:
	Bool4() : simd(_mm_setzero_ps()) {}
	Bool4(const bool v) : simd(_mm_set1_ps(v)) {}
	explicit Bool4(const __m128& data) : simd(data) {}
	Bool4(const Bool4& b) : simd(b.simd) {}

	inline bool operator[](const int id) const {
		return static_cast<bool>((_mm_movemask_ps(simd) >> id) & 1);
	}

	__m128 simd;
};

inline Bool4 operator&(const Bool4& a, const Bool4& b){
	return Bool4(_mm_and_ps(a.simd,b.simd));
}

inline Bool4 operator|(const Bool4& a, const Bool4& b){
	return Bool4(_mm_or_ps(a.simd,b.simd));
}

inline Bool4 operator^(const Bool4& a, const Bool4& b){
	return Bool4(_mm_xor_ps(a.simd,b.simd));
}

class Float4 {
	public:
		Float4();
		Float4(const Float4& v);
		explicit Float4(float v);
		Float4(float x, float y, float z, float w);
		explicit Float4(const float* data);
		explicit Float4(const __m128& _simd);

		Float4& operator=(const Float4& b);

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
	return Float4(_mm_blendv_ps(a.simd,b.simd,m.simd));
}

thread_local static Bool4* __mask4;

inline Bool4& mask4(){
	if(!__mask4){
		__mask4 = new Bool4();
	}
	return *__mask4;
}

inline void clearMask4(){
	mask4() = Bool4();
}

class Result4 {
	public:
		Result4(const Bool4& mask) : _mask(mask^Bool4(true)) {} // In init compute false mask

		template <typename T>
		Result4& ElseIf(const Bool4& mask, const T& func) {
			mask4() = _mask&mask;
			func();
			return *this;
		}

		template <typename T>
		void Else(const T& func){
			mask4() = _mask;
			func();
		}
	private:
		Bool4 _mask;
};

template<typename T>
Result4 If(const Bool4& mask, const T& func){
	mask4() = mask;
	func();
	return Result4(mask);
}

}
