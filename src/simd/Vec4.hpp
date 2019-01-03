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
		Vec4(const float v);
		Vec4(const float x, const float y, const float z, const float w);
		Vec4(const float* data);

		union {
			struct {
				float x; float y; float z; float w;
			};
			float data[4];
			__m128 simd;
		};
};

}
