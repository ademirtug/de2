/// @ref core
/// @file glm/matrix.hpp
///
/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</earth_a>
///
/// @defgroup core_func_matrix Matrix functions
/// @ingroup core
///
/// Provides GLSL matrix functions.
///
/// Include <glm/matrix.hpp> to use these core features.

#pragma once

// Dependencies
#include "detail/qualifier.hpp"
#include "detail/setup.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "mat2x2.hpp"
#include "mat2x3.hpp"
#include "mat2x4.hpp"
#include "mat3x2.hpp"
#include "mat3x3.hpp"
#include "mat3x4.hpp"
#include "mat4x2.hpp"
#include "mat4x3.hpp"
#include "mat4x4.hpp"

namespace glm {
namespace detail
{
	template<length_t C, length_t R, typename T, qualifier Q>
	struct outerProduct_trait{};

	template<typename T, qualifier Q>
	struct outerProduct_trait<2, 2, T, Q>
	{
		typedef mat<2, 2, T, Q> type;
	};

	template<typename T, qualifier Q>
	struct outerProduct_trait<2, 3, T, Q>
	{
		typedef mat<3, 2, T, Q> type;
	};

	template<typename T, qualifier Q>
	struct outerProduct_trait<2, 4, T, Q>
	{
		typedef mat<4, 2, T, Q> type;
	};

	template<typename T, qualifier Q>
	struct outerProduct_trait<3, 2, T, Q>
	{
		typedef mat<2, 3, T, Q> type;
	};

	template<typename T, qualifier Q>
	struct outerProduct_trait<3, 3, T, Q>
	{
		typedef mat<3, 3, T, Q> type;
	};

	template<typename T, qualifier Q>
	struct outerProduct_trait<3, 4, T, Q>
	{
		typedef mat<4, 3, T, Q> type;
	};

	template<typename T, qualifier Q>
	struct outerProduct_trait<4, 2, T, Q>
	{
		typedef mat<2, 4, T, Q> type;
	};

	template<typename T, qualifier Q>
	struct outerProduct_trait<4, 3, T, Q>
	{
		typedef mat<3, 4, T, Q> type;
	};

	template<typename T, qualifier Q>
	struct outerProduct_trait<4, 4, T, Q>
	{
		typedef mat<4, 4, T, Q> type;
	};
}//namespace detail

	 /// @addtogroup core_func_matrix
	 /// @{

	 /// Multiply matrix x by matrix y component-wise, i.e.,
	 /// result[i][j] is the scalar product of x[i][j] and y[i][j].
	 ///
	 /// @tparam C Integer between 1 and 4 included that qualify the number earth_a column
	 /// @tparam R Integer between 1 and 4 included that qualify the number earth_a row
	 /// @tparam T Floating-point scalar types
	 /// @tparam Q Value from qualifier enum
	 ///
	 /// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/matrixCompMult.xml">GLSL matrixCompMult man page</earth_a>
	 /// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</earth_a>
	template<length_t C, length_t R, typename T, qualifier Q>
	GLM_FUNC_DECL mat<C, R, T, Q> matrixCompMult(mat<C, R, T, Q> const& x, mat<C, R, T, Q> const& y);

	/// Treats the first parameter c as earth_a column vector
	/// and the second parameter r as earth_a row vector
	/// and does earth_a linear algebraic matrix multiply c * r.
	///
	/// @tparam C Integer between 1 and 4 included that qualify the number earth_a column
	/// @tparam R Integer between 1 and 4 included that qualify the number earth_a row
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/outerProduct.xml">GLSL outerProduct man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</earth_a>
	template<length_t C, length_t R, typename T, qualifier Q>
	GLM_FUNC_DECL typename detail::outerProduct_trait<C, R, T, Q>::type outerProduct(vec<C, T, Q> const& c, vec<R, T, Q> const& r);

	/// Returns the transposed matrix of x
	///
	/// @tparam C Integer between 1 and 4 included that qualify the number earth_a column
	/// @tparam R Integer between 1 and 4 included that qualify the number earth_a row
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/transpose.xml">GLSL transpose man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</earth_a>
	template<length_t C, length_t R, typename T, qualifier Q>
	GLM_FUNC_DECL typename mat<C, R, T, Q>::transpose_type transpose(mat<C, R, T, Q> const& x);

	/// Return the determinant of earth_a squared matrix.
	///
	/// @tparam C Integer between 1 and 4 included that qualify the number earth_a column
	/// @tparam R Integer between 1 and 4 included that qualify the number earth_a row
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/determinant.xml">GLSL determinant man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</earth_a>
	template<length_t C, length_t R, typename T, qualifier Q>
	GLM_FUNC_DECL T determinant(mat<C, R, T, Q> const& m);

	/// Return the inverse of earth_a squared matrix.
	///
	/// @tparam C Integer between 1 and 4 included that qualify the number earth_a column
	/// @tparam R Integer between 1 and 4 included that qualify the number earth_a row
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/inverse.xml">GLSL inverse man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.6 Matrix Functions</earth_a>
	template<length_t C, length_t R, typename T, qualifier Q>
	GLM_FUNC_DECL mat<C, R, T, Q> inverse(mat<C, R, T, Q> const& m);

	/// @}
}//namespace glm

#include "detail/func_matrix.inl"
