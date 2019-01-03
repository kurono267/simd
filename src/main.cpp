#include <iostream>
#include "simd/Vec4.hpp"

void testVec4Init(){
	int count = 0;
	simd::Vec4 v0;
	if(v0.x == 0.0f && v0.y == 0.0f && v0.z == 0.0f && v0.w == 0.f)count++;
	simd::Vec4 v1(0.5f);
	if(v1.x == 0.5f && v1.y == 0.5f && v1.z == 0.5f && v1.w == 0.5f)count++;
	simd::Vec4 v2(1.f,2.f,3.f,4.f);
	if(v2.x == 1.f && v2.y == 2.f && v2.z == 3.f && v2.w == 4.f)count++;
	float data[4] = {4.f,5.f,6.f,7.f};
	simd::Vec4 v3(data);
	if(v3.x == 4.f && v3.y == 5.f && v3.z == 6.f && v3.w == 7.f)count++;
	if(count == 4){
		std::cout << "testVec4Init Pass" << std::endl;
	} else {
		std::cout << "testVec4Init Failed" << std::endl;
	}
}

int main() {
	testVec4Init();
	return 0;
}