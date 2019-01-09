//
// Created by kurono267 on 2019-01-03.
//

#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "portability-simd-intrinsics"

#include <x86intrin.h>
#include <functional>

namespace simd {

class Bool4 {
public:
	Bool4() : simd(_mm_setzero_ps()) {}
	Bool4(const bool v) : simd(v?_mm_set1_epi32(0xFFFFFFFF):_mm_setzero_ps()) {}
	explicit Bool4(const __m128& data) : simd(data) {}
	Bool4(const Bool4& b) : simd(b.simd) {}

	inline bool operator[](const int id) const {
		return static_cast<bool>((_mm_movemask_ps(simd) >> id) & 1);
	}

	__m128 simd;
};

inline Bool4 operator!(const Bool4& a){
	return Bool4(_mm_xor_ps(a.simd,_mm_set1_epi32(0xFFFFFFFF)));
}

inline Bool4 operator&(const Bool4& a, const Bool4& b){
	return Bool4(_mm_and_ps(a.simd,b.simd));
}

inline Bool4 operator|(const Bool4& a, const Bool4& b){
	return Bool4(_mm_or_ps(a.simd,b.simd));
}

inline Bool4 operator^(const Bool4& a, const Bool4& b){
	return Bool4(_mm_xor_ps(a.simd,b.simd));
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

class Float4 {
	public:
		Float4() : simd(_mm_setzero_ps()) {}

		Float4(const Float4 &v){
			//auto r = blend(*this,v,mask4());
			simd = v.simd;
		}

		Float4(float v) {
			simd = _mm_set1_ps(v);
		}

		Float4(float _x, float _y, float _z, float _w) {
			simd = _mm_set_ps(_w,_z,_y,_x);
		}

		Float4(const float *_data) {
			simd = _mm_load_ps(_data);
		}

		Float4(const __m128 &_simd) : simd(_simd) {}

		Float4 &operator=(const Float4 &b) {
			auto r = _mm_blendv_ps(simd,b.simd,mask4().simd);
			simd = r;
			return *this;
		}

		Float4 &operator+=(const Float4 &b) {
			simd = _mm_add_ps(simd,b.simd);
			return *this;
		}

		Float4 &operator+=(float b) {
			simd = _mm_add_ps(simd,_mm_set1_ps(b));
			return *this;
		}

		Float4 &operator-=(const Float4 &b) {
			simd = _mm_sub_ps(simd,b.simd);
			return *this;
		}

		Float4 &operator-=(float b) {
			simd = _mm_sub_ps(simd,_mm_set1_ps(b));
			return *this;
		}

		Float4 &operator*=(const Float4 &b) {
			simd = _mm_mul_ps(simd,b.simd);
			return *this;
		}

		Float4 &operator*=(float b) {
			simd = _mm_mul_ps(simd,_mm_set1_ps(b));
			return *this;
		}

		Float4 &operator/=(const Float4 &b) {
			simd = _mm_div_ps(simd,b.simd);
			return *this;
		}

		Float4 &operator/=(float b) {
			simd = _mm_div_ps(simd,_mm_set1_ps(b));
			return *this;
		}

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

class Result4 {
	public:
		Result4(const Bool4& mask) : _mask(mask) {} // In init compute false mask

		template <typename T>
			Result4& ElseIf(const Bool4& mask, const T& func) {
			_elseMask = !_mask;
			auto elseIfMask = _elseMask&mask;
			mask4() = elseIfMask;
			func();
			// For else block
			_elseMask = _elseMask&(!elseIfMask);
			mask4() = _mask;
			return *this;
		}

		template <typename T>
		void Else(const T& func){
			mask4() = _elseMask;
			func();
			mask4() = _mask;
		}
	private:
		Bool4 _mask;
		Bool4 _elseMask;
};

template<typename T>
Result4 If(const Bool4& mask, const T& func){
	auto prevMask = mask4();
	mask4() = mask;
	func();
	mask4() = prevMask;
	return Result4(mask);
}

}

#pragma clang diagnostic pop
