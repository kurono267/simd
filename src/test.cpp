#include <iostream>
#include "simd/sse/Float4.hpp"

#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE SimdTests
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Float4)

BOOST_AUTO_TEST_CASE(Float4Init)
{
	simd::Float4 v0;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v0.data[i],0.f);
	}
	simd::Float4 v1(0.5f);
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v1.data[i],0.5f);
	}
	float data[4] = {1.f,2.f,3.f,4.f};
	simd::Float4 v2(data[0],data[1],data[2],data[3]);
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v2.data[i],data[i]);
	}
	simd::Float4 v3(data);
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v3.data[i],data[i]);
	}
	simd::Float4 v4 = v3;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v4.data[i],v3.data[i]);
	}
}

BOOST_AUTO_TEST_CASE(Float4Arithmetic){
	simd::Float4 a(1.f,2.f,3.f,4.f);
	simd::Float4 b(2.f,4.f,8.f,16.f);
	float c = 3.f;
	simd::Float4 v0 = a+b;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v0.data[i],a.data[i]+b.data[i]);
	}
	simd::Float4 v1 = a+c;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v1.data[i],a.data[i]+c);
	}
	simd::Float4 v2 = a-b;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v2.data[i],a.data[i]-b.data[i]);
	}
	simd::Float4 v3 = a-c;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v3.data[i],a.data[i]-c);
	}
	simd::Float4 v4 = a*b;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v4.data[i],a.data[i]*b.data[i]);
	}
	simd::Float4 v5 = a*c;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v5.data[i],a.data[i]*c);
	}
	simd::Float4 v6 = a/b;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v6.data[i],a.data[i]/b.data[i]);
	}
	simd::Float4 v7 = a/c;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v7.data[i],a.data[i]/c);
	}
}

BOOST_AUTO_TEST_CASE(Float4ArithmeticAdditional){
	simd::Float4 a(1.f);
	simd::Float4 b(2.f);
	float c = 3.0f;

	simd::Float4 v0 = a;
	v0 += b;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v0.data[i],a.data[i]+b.data[i]);
	}
	simd::Float4 v1 = a;
	v1 += c;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v1.data[i],a.data[i]+c);
	}
	simd::Float4 v2 = a;
	v2 *= b;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v2.data[i],a.data[i]*b.data[i]);
	}
	simd::Float4 v3 = a;
	v3 *= c;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v3.data[i],a.data[i]*c);
	}
	simd::Float4 v4 = a;
	v4 /= b;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v4.data[i],a.data[i]/b.data[i]);
	}
	simd::Float4 v5 = a;
	v5 /= c;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v5.data[i],a.data[i]/c);
	}
	simd::Float4 v6 = a;
	v6 -= b;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v6.data[i],a.data[i]-b.data[i]);
	}
	simd::Float4 v7 = a;
	v7 -= c;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v7.data[i],a.data[i]-c);
	}
}

BOOST_AUTO_TEST_CASE(Vec4Bool){
	simd::Float4 a(1.f,2.f,3.f,4.f);
	simd::Float4 b(1.f,2.f,3.f,4.f);
	simd::Float4 c(2.f,3.f,5.f,6.f);
	auto b0 = a == b;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(b0[i],a[i]==b[i]);
	}
	auto b1 = a != c;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(b1[i],a[i]!=c[i]);
	}
	auto b2 = a < c;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(b2[i],a[i]<c[i]);
	}
	auto b3 = a > c;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(b3[i],a[i]>c[i]);
	}
	auto b4 = a <= c;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(b4[i],a[i]<=c[i]);
	}
	auto b5 = a >= c;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(b5[i],a[i]>=c[i]);
	}
	// Blend test
	simd::Float4 mask = simd::Float4(1.f,1.f,0.f,0.f);
	simd::Float4 b6 = blend(a,c,mask == simd::Float4(1.f));
	for(int i = 0;i<4;++i){
		if(mask[i] == 1.f)BOOST_CHECK_EQUAL(b6[i],a[i]);
		else BOOST_CHECK_EQUAL(b6[i],c[i]);
	}
}

BOOST_AUTO_TEST_SUITE_END();