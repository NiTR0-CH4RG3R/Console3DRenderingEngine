#ifndef _MAT4X4_H_
#define _MAT4X4_H_

#include "Matrix.h"

namespace Math {
	template <typename T> using Mat4x4_generic = Matrix_generic<T, 4, 4>;

	/// <summary>
	/// Mat4x4_generic templated on float
	/// </summary>
	typedef Mat4x4_generic<float>	Mat4x4;

	/// <summary>
	/// Mat4x4_generic templated on double
	/// </summary>
	typedef Mat4x4_generic<double>	Mat4x4d;

	/// <summary>
	/// Mat4x4_generic templated on int
	/// </summary>
	typedef Mat4x4_generic<int>		Mat4x4i;
}

#endif // !_MAT4X4_H_
