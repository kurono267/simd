//
// Created by kurono267 on 2019-01-03.
//

#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "portability-simd-intrinsics"

#include <immintrin.h>
#include <functional>
#include <stack>

namespace simd {

	class Bool16 {
	public:
		Bool16() : simd(_mm512_int2mask(0)) {}
		Bool16(const bool v) : simd(v?_mm512_int2mask(0xFFFFFFFF):_mm512_int2mask(0)) {}
		Bool16(const __mmask16& data) : simd(data) {}
		Bool16(const Bool16& b) : simd(b.simd) {}

		inline bool operator[](const int id) const {
			return static_cast<bool>((_mm512_mask2int(simd) >> id) & 1);
		}

		__mmask16 simd;
	};

	inline bool any(const Bool16& a){
		return _mm512_mask2int(a.simd) != 0;
	}

	inline bool all(const Bool16& a){
		return _mm512_mask2int(a.simd) == 0xFFFF;
	}

	inline bool none(const Bool16& a){
		return _mm512_mask2int(a.simd) == 0;
	}

	inline Bool16 operator!(const Bool16& a){
		return _mm512_knot(a.simd);
	}

	inline Bool16 operator&(const Bool16& a, const Bool16& b){
		return _mm512_kand(a.simd,b.simd);
	}

	inline Bool16 operator|(const Bool16& a, const Bool16& b){
		return _mm512_kor(a.simd,b.simd);
	}

	inline Bool16 operator^(const Bool16& a, const Bool16& b){
		return _mm512_kxor(a.simd,b.simd);
	}

	thread_local static std::stack<Bool16>* __stack16;

	inline std::stack<Bool16>& stack16(){
		if(!__stack16) {
			__stack16 = new std::stack<Bool16>();
			__stack16->push(Bool16(true));
		}
		return *__stack16;
	}

	constexpr size_t Float16_Size = 16;

	class Float16 {
	public:
		Float16() : simd(_mm512_setzero_ps()) {}

		Float16(const Float16 &v){
			//auto r = blend(*this,v,mask4());
			simd = v.simd;
		}

		Float16(float v) {
			simd = _mm512_set1_ps(v);
		}

		Float16(float _0, float _1, float _2, float _3,
				float _4, float _5, float _6, float _7,
				float _8, float _9, float _10, float _11,
				float _12, float _13, float _14, float _15) {
			simd = _mm512_set_ps(_15,_14,_13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1,_0);
		}

		Float16(const float *_data) {
			simd = _mm512_loadu_ps(_data);
		}

		Float16(const __m512 &_simd) : simd(_simd) {}

		inline Float16 &operator=(const Float16 &b) {
			auto mask16 = stack16().top();
			if(all(mask16))simd = b.simd;
			else simd = _mm512_mask_blend_ps(mask16.simd,simd,b.simd);
			return *this;
		}

		inline Float16 &operator+=(const Float16 &b) {
			auto mask16 = stack16().top();
			simd = _mm512_mask_add_ps(simd,mask16.simd,simd,b.simd);
			return *this;
		}

		inline Float16 &operator+=(float b) {
			auto mask16 = stack16().top();
			simd = _mm512_mask_add_ps(simd,mask16.simd,simd,_mm512_set1_ps(b));
			return *this;
		}

		inline Float16 &operator-=(const Float16 &b) {
			auto mask16 = stack16().top();
			simd = _mm512_mask_sub_ps(simd,mask16.simd,simd,b.simd);
			return *this;
		}

		inline Float16 &operator-=(float b) {
			auto mask16 = stack16().top();
			simd = _mm512_mask_sub_ps(simd,mask16.simd,simd,_mm512_set1_ps(b));
			return *this;
		}

		inline Float16 &operator*=(const Float16 &b) {
			auto mask16 = stack16().top();
			simd = _mm512_mask_mul_ps(simd,mask16.simd,simd,b.simd);
			return *this;
		}

		inline Float16 &operator*=(float b) {
			auto mask16 = stack16().top();
			simd = _mm512_mask_mul_ps(simd,mask16.simd,simd,_mm512_set1_ps(b));
			return *this;
		}

		inline Float16 &operator/=(const Float16 &b) {
			auto mask16 = stack16().top();
			simd = _mm512_mask_div_ps(simd,mask16.simd,simd,b.simd);
			return *this;
		}

		inline Float16 &operator/=(float b) {
			auto mask16 = stack16().top();
			simd = _mm512_mask_div_ps(simd,mask16.simd,simd,_mm512_set1_ps(b));
			return *this;
		}

		inline float& operator[](int id){
			return data[id];
		}

		inline const float& operator[](int id) const {
			return data[id];
		}

		union {
			float data[16];
			__m512 simd;
		};
	};

	inline Float16 operator+(const Float16 &a, const Float16 &b) {
		return _mm512_add_ps(a.simd,b.simd);
	}

	inline Float16 operator+(const Float16 &a, float b) {
		return _mm512_add_ps(a.simd,_mm512_set1_ps(b));
	}

	inline Float16 operator-(const Float16 &a, const Float16 &b) {
		return _mm512_sub_ps(a.simd,b.simd);
	}

	inline Float16 operator-(const Float16 &a, float b) {
		return _mm512_sub_ps(a.simd,_mm512_set1_ps(b));
	}

	inline Float16 operator*(const Float16 &a, const Float16 &b) {
		return _mm512_mul_ps(a.simd,b.simd);
	}

	inline Float16 operator*(const Float16 &a, float b) {
		return _mm512_mul_ps(a.simd,_mm512_set1_ps(b));
	}

	inline Float16 operator/(const Float16 &a, const Float16 &b) {
		return _mm512_div_ps(a.simd,b.simd);
	}

	inline Float16 operator/(const Float16 &a, float b) {
		return _mm512_div_ps(a.simd,_mm512_set1_ps(b));
	}

	inline Bool16 operator<(const Float16& a, const Float16& b) {
		return _mm512_cmp_ps_mask(a.simd,b.simd,_CMP_LT_OS);
	}

	inline Bool16 operator<=(const Float16& a, const Float16& b) {
		return _mm512_cmp_ps_mask(a.simd,b.simd,_CMP_LE_OS);
	}

	inline Bool16 operator>(const Float16& a, const Float16& b) {
		return _mm512_cmp_ps_mask(a.simd,b.simd,_CMP_GT_OS);
	}

	inline Bool16 operator>=(const Float16& a, const Float16& b) {
		return _mm512_cmp_ps_mask(a.simd,b.simd,_CMP_GE_OS);
	}

	inline Bool16 operator==(const Float16& a, const Float16& b) {
		return _mm512_cmpeq_ps_mask(a.simd,b.simd);
	}

	inline Bool16 operator!=(const Float16& a, const Float16& b) {
		return _mm512_cmpneq_ps_mask(a.simd,b.simd);
	}

	inline Float16 blend(const Float16& a, const Float16& b, const Bool16& m){
		return _mm512_mask_blend_ps(m.simd,a.simd,b.simd);
	}

	class Result16 {
	public:
		Result16(const Bool16& mask) : _else(!mask) {} // In init compute false mask

		template <typename T>
		Result16& ElseIf(const Bool16& mask, const T& func) {
			auto elseIfMask = _else&mask;
			_else = _else&(!mask);
			if(none(elseIfMask))return *this;
			stack16().push(elseIfMask);
			func();
			stack16().pop();
			return *this;
		}

		template <typename T>
		void Else(const T& func){
			if(none(_else))return;
			stack16().push(_else);
			func();
			stack16().pop();
		}
	private:
		Bool16 _else;
	};

	template<typename T>
	Result16 If(const Bool16& mask, const T& func){
		auto topMask = stack16().top();
		auto ifMask = topMask&mask;
		if(none(ifMask))return Result16(ifMask);
		stack16().push(ifMask);
		func();
		stack16().pop();
		return Result16(ifMask);
	}

	inline Float16 max(const Float16& a, const Float16& b){
		return _mm512_max_ps(a.simd,b.simd);
	}

	inline Float16 min(const Float16& a, const Float16& b){
		return _mm512_min_ps(a.simd,b.simd);
	}

	inline Float16 abs(const Float16& a){
		return _mm512_abs_ps(a.simd);
	}
}

#pragma clang diagnostic pop
