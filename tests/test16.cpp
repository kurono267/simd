#include <iostream>
#include "../src/simd/Float16.hpp"

#define BOOST_TEST_MODULE SimdTests
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Float16)

	using namespace simd;

	BOOST_AUTO_TEST_CASE(Float16Init) {
		simd::Float16 v0;
		for (int i = 0; i < Float16_Size; ++i) {
			BOOST_CHECK_EQUAL(v0.data[i], 0.f);
		}
		simd::Float16 v1(0.5f);
		for (int i = 0; i < 4; ++i) {
			BOOST_CHECK_EQUAL(v1.data[i], 0.5f);
		}
		float data[16] = {1.f, 2.f, 3.f, 4.f,
						5.f, 6.f, 7.f, 8.f,
						9.f, 10.f, 11.f, 12.f,
						13.f, 14.f, 15.f, 16.f};
		simd::Float16 v2(data[0], data[1], data[2], data[3],
						 data[4], data[5], data[6], data[7],
						 data[8], data[9], data[10], data[11],
						 data[12], data[13], data[14], data[15]);
		for (int i = 0; i < Float16_Size; ++i) {
			BOOST_CHECK_EQUAL(v2.data[i], data[i]);
		}
		simd::Float16 v3(data);
		for (int i = 0; i < Float16_Size; ++i) {
			BOOST_CHECK_EQUAL(v3.data[i], data[i]);
		}
		simd::Float16 v4 = v3;
	}

	BOOST_AUTO_TEST_CASE(Float16Arithmetic){
		simd::Float16 a;
		simd::Float16 b;
		for(int i = 0;i<Float16_Size;++i){
			a[i] = i+1.f;
			b[i] = (i+1.f)*2.f;
		}
		float c = 3.f;
		simd::Float16 v0 = a+b;
		for(int i = 0;i<Float16_Size;++i){
			BOOST_CHECK_EQUAL(v0.data[i],a.data[i]+b.data[i]);
		}
		simd::Float16 v1 = a+c;
		for(int i = 0;i<Float16_Size;++i){
			BOOST_CHECK_EQUAL(v1.data[i],a.data[i]+c);
		}
		simd::Float16 v2 = a-b;
		for(int i = 0;i<Float16_Size;++i){
			BOOST_CHECK_EQUAL(v2.data[i],a.data[i]-b.data[i]);
		}
		simd::Float16 v3 = a-c;
		for(int i = 0;i<Float16_Size;++i){
			BOOST_CHECK_EQUAL(v3.data[i],a.data[i]-c);
		}
		simd::Float16 v4 = a*b;
		for(int i = 0;i<Float16_Size;++i){
			BOOST_CHECK_EQUAL(v4.data[i],a.data[i]*b.data[i]);
		}
		simd::Float16 v5 = a*c;
		for(int i = 0;i<Float16_Size;++i){
			BOOST_CHECK_EQUAL(v5.data[i],a.data[i]*c);
		}
		simd::Float16 v6 = a/b;
		for(int i = 0;i<Float16_Size;++i){
			BOOST_CHECK_EQUAL(v6.data[i],a.data[i]/b.data[i]);
		}
		simd::Float16 v7 = a/c;
		for(int i = 0;i<Float16_Size;++i){
			BOOST_CHECK_EQUAL(v7.data[i],a.data[i]/c);
		}
	}

	BOOST_AUTO_TEST_CASE(Float16ArithmeticAdditional){
		simd::Float16 a(1.f);
		simd::Float16 b(2.f);
		float c = 3.0f;

		simd::Float16 v0 = a;
		v0 += b;
		for(int i = 0;i<4;++i){
			BOOST_CHECK_EQUAL(v0.data[i],a.data[i]+b.data[i]);
		}
		simd::Float16 v1 = a;
		v1 += c;
		for(int i = 0;i<4;++i){
			BOOST_CHECK_EQUAL(v1.data[i],a.data[i]+c);
		}
		simd::Float16 v2 = a;
		v2 *= b;
		for(int i = 0;i<4;++i){
			BOOST_CHECK_EQUAL(v2.data[i],a.data[i]*b.data[i]);
		}
		simd::Float16 v3 = a;
		v3 *= c;
		for(int i = 0;i<4;++i){
			BOOST_CHECK_EQUAL(v3.data[i],a.data[i]*c);
		}
		simd::Float16 v4 = a;
		v4 /= b;
		for(int i = 0;i<4;++i){
			BOOST_CHECK_EQUAL(v4.data[i],a.data[i]/b.data[i]);
		}
		simd::Float16 v5 = a;
		v5 /= c;
		for(int i = 0;i<4;++i){
			BOOST_CHECK_EQUAL(v5.data[i],a.data[i]/c);
		}
		simd::Float16 v6 = a;
		v6 -= b;
		for(int i = 0;i<4;++i){
			BOOST_CHECK_EQUAL(v6.data[i],a.data[i]-b.data[i]);
		}
		simd::Float16 v7 = a;
		v7 -= c;
		for(int i = 0;i<4;++i){
			BOOST_CHECK_EQUAL(v7.data[i],a.data[i]-c);
		}
	}

	BOOST_AUTO_TEST_CASE(Float16Bool){
		simd::Float16 a;
		simd::Float16 b;
		simd::Float16 c;
		for(int i = 0;i<Float16_Size;++i){
			a[i] = i+1.f;
			b[i] = i+1.f;
			c[i] = i+2.f;
		}
		auto b0 = a == b;
		for(int i = 0;i<Float16_Size;++i){
			BOOST_CHECK_EQUAL(b0[i],a[i]==b[i]);
		}
		auto b1 = a != c;
		for(int i = 0;i<Float16_Size;++i){
			BOOST_CHECK_EQUAL(b1[i],a[i]!=c[i]);
		}
		auto b2 = a < c;
		for(int i = 0;i<Float16_Size;++i){
			BOOST_CHECK_EQUAL(b2[i],a[i]<c[i]);
		}
		auto b3 = a > c;
		for(int i = 0;i<Float16_Size;++i){
			BOOST_CHECK_EQUAL(b3[i],a[i]>c[i]);
		}
		auto b4 = a <= c;
		for(int i = 0;i<Float16_Size;++i){
			BOOST_CHECK_EQUAL(b4[i],a[i]<=c[i]);
		}
		auto b5 = a >= c;
		for(int i = 0;i<Float16_Size;++i){
			BOOST_CHECK_EQUAL(b5[i],a[i]>=c[i]);
		}
	}

	BOOST_AUTO_TEST_CASE(Float16Mask){
		simd::Float16 a;
		simd::Float16 c;
		simd::Float16 mask;
		for(int i = 0;i<Float16_Size;++i){
			a[i] = i+1.f;
			c[i] = i+2.f;
			mask[i] = i<Float16_Size/2?1.f:0.f;
		}
		// Blend test
		simd::Float16 b6 = blend(c,a,mask == simd::Float16(1.f)); // if true second value else first value
		for(int i = 0;i<Float16_Size;++i){
			if(mask[i] == 1.f)BOOST_CHECK_EQUAL(b6[i],a[i]);
			else BOOST_CHECK_EQUAL(b6[i],c[i]);
		}
		// Test with thread local mask
		simd::mask16() = mask == simd::Float16(1.f);
		simd::Float16 t(10.f);
		t = c;
		for(int i = 0;i<Float16_Size;++i){
			if(mask[i] == 1.f)BOOST_CHECK_EQUAL(t[i],c[i]);
			else BOOST_CHECK_EQUAL(t[i],10.f);
		}
	}

	BOOST_AUTO_TEST_CASE(Float16Ifs){
		simd::Float16 a(1.f,1.f,2.f,3.f,
						1.f,1.f,2.f,3.f,
						1.f,1.f,2.f,3.f,
						1.f,1.f,2.f,3.f);
		If(a == simd::Float16(1.f),[&](){
			a = simd::Float16(0.5f);
		}).ElseIf(a > simd::Float16(2.f),[&](){
			a = simd::Float16(1.f);
		}).Else([&](){
			a = simd::Float16(0.f);
		});
		for(int i = 0;i<4;++i){
			BOOST_CHECK_EQUAL(a[i*4],0.5f);
			BOOST_CHECK_EQUAL(a[i*4+1],0.5f);
			BOOST_CHECK_EQUAL(a[i*4+2],0.f);
			BOOST_CHECK_EQUAL(a[i*4+3],1.f);
		}

		simd::Float16 b(1.f,2.f,3.f,4.f,
						1.f,2.f,3.f,4.f,
						1.f,2.f,3.f,4.f,
						1.f,2.f,3.f,4.f);
		If((b > 1.f) & (b < 4.f),[&](){
			If(b == 2.f,[&](){
				b = 5.f;
			}).ElseIf(b == 3.f,[&](){
				b = 6.f;
			});
		}).ElseIf(b == 1.f,[&](){
			b = 7.f;
		}).Else([&](){
			b = 8.f;
		});
		for(int i = 0;i<4;++i){
			BOOST_CHECK_EQUAL(b[i*4+0],7.f);
			BOOST_CHECK_EQUAL(b[i*4+1],5.f);
			BOOST_CHECK_EQUAL(b[i*4+2],6.f);
			BOOST_CHECK_EQUAL(b[i*4+3],8.f);
		}
	}

BOOST_AUTO_TEST_SUITE_END();