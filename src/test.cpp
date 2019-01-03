#include <iostream>
#include "simd/Vec4.hpp"

#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE SimdTests
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Vec4)

BOOST_AUTO_TEST_CASE(Vec4Init)
{
	simd::Vec4 v0;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v0.data[i],0.f);
	}
	simd::Vec4 v1(0.5f);
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v1.data[i],0.5f);
	}
	float data[4] = {1.f,2.f,3.f,4.f};
	simd::Vec4 v2(data[0],data[1],data[2],data[3]);
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v2.data[i],data[i]);
	}
	simd::Vec4 v3(data);
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v3.data[i],data[i]);
	}
}

BOOST_AUTO_TEST_CASE(Vec4Arithmetic){
	simd::Vec4 a(1.f,2.f,3.f,4.f);
	simd::Vec4 b(2.f,4.f,8.f,16.f);
	float c = 3.f;
	simd::Vec4 v0 = a+b;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v0.data[i],a.data[i]+b.data[i]);
	}
	simd::Vec4 v1 = a+c;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v1.data[i],a.data[i]+c);
	}
	simd::Vec4 v2 = a-b;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v2.data[i],a.data[i]-b.data[i]);
	}
	simd::Vec4 v3 = a-c;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v3.data[i],a.data[i]-c);
	}
	simd::Vec4 v4 = a*b;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v4.data[i],a.data[i]*b.data[i]);
	}
	simd::Vec4 v5 = a*c;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v5.data[i],a.data[i]*c);
	}
	simd::Vec4 v6 = a/b;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v6.data[i],a.data[i]/b.data[i]);
	}
	simd::Vec4 v7 = a/c;
	for(int i = 0;i<4;++i){
		BOOST_CHECK_EQUAL(v7.data[i],a.data[i]/c);
	}
}

BOOST_AUTO_TEST_SUITE_END();