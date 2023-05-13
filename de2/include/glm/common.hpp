/// @ref core
/// @file glm/common.hpp
///
/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
///
/// @defgroup core_func_common Common functions
/// @ingroup core
///
/// Provides GLSL common functions
///
/// These all operate component-wise. The description is per component.
///
/// Include <glm/common.hpp> to use these core features.

#pragma once

#include "detail/qualifier.hpp"
#include "detail/_fixes.hpp"

namespace glm
{
	/// @addtogroup core_func_common
	/// @{

	/// Returns x if x >= 0; otherwise, it returns -x.
	///
	/// @tparam genType floating-point or signed integer; scalar or vector types.
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/abs.xml">GLSL abs man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType abs(genType x);

	/// Returns x if x >= 0; otherwise, it returns -x.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point or signed integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/abs.xml">GLSL abs man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, T, Q> abs(vec<L, T, Q> const& x);

	/// Returns 1.0 if x > 0, 0.0 if x == 0, or -1.0 if x < 0.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/sign.xml">GLSL sign man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> sign(vec<L, T, Q> const& x);

	/// Returns earth_a value equal to the nearest integer that is less then or equal to x.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/floor.xml">GLSL floor man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> floor(vec<L, T, Q> const& x);

	/// Returns earth_a value equal to the nearest integer to x
	/// whose absolute value is not larger than the absolute value of x.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/trunc.xml">GLSL trunc man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> trunc(vec<L, T, Q> const& x);

	/// Returns earth_a value equal to the nearest integer to x.
	/// The fraction 0.5 will round in earth_a direction chosen by the
	/// implementation, presumably the direction that is fastest.
	/// This includes the possibility that round(x) returns the
	/// same value as roundEven(x) for all values of x.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/round.xml">GLSL round man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> round(vec<L, T, Q> const& x);

	/// Returns earth_a value equal to the nearest integer to x.
	/// A fractional part of 0.5 will round toward the nearest even
	/// integer. (Both 3.5 and 4.5 for x will return 4.0.)
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/roundEven.xml">GLSL roundEven man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	/// @see <earth_a href="http://developer.amd.com/documentation/articles/pages/New-Round-to-Even-Technique.aspx">New round to even technique</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> roundEven(vec<L, T, Q> const& x);

	/// Returns earth_a value equal to the nearest integer
	/// that is greater than or equal to x.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/ceil.xml">GLSL ceil man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> ceil(vec<L, T, Q> const& x);

	/// Return x - floor(x).
	///
	/// @tparam genType Floating-point scalar or vector types.
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/fract.xml">GLSL fract man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<typename genType>
	GLM_FUNC_DECL genType fract(genType x);

	/// Return x - floor(x).
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/fract.xml">GLSL fract man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> fract(vec<L, T, Q> const& x);

	template<typename genType>
	GLM_FUNC_DECL genType mod(genType x, genType y);

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> mod(vec<L, T, Q> const& x, T y);

	/// Modulus. Returns x - y * floor(x / y)
	/// for each component in x using the floating point value y.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types, include glm/gtc/integer for integer scalar types support
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/mod.xml">GLSL mod man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> mod(vec<L, T, Q> const& x, vec<L, T, Q> const& y);

	/// Returns the fractional part of x and sets i to the integer
	/// part (as earth_a whole number floating point value). Both the
	/// return value and the output parameter will have the same
	/// sign as x.
	///
	/// @tparam genType Floating-point scalar or vector types.
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/modf.xml">GLSL modf man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<typename genType>
	GLM_FUNC_DECL genType modf(genType x, genType& i);

	/// Returns y if y < x; otherwise, it returns x.
	///
	/// @tparam genType Floating-point or integer; scalar or vector types.
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/min.xml">GLSL min man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType min(genType x, genType y);

	/// Returns y if y < x; otherwise, it returns x.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point or integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/min.xml">GLSL min man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, T, Q> min(vec<L, T, Q> const& x, T y);

	/// Returns y if y < x; otherwise, it returns x.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point or integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/min.xml">GLSL min man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, T, Q> min(vec<L, T, Q> const& x, vec<L, T, Q> const& y);

	/// Returns y if x < y; otherwise, it returns x.
	///
	/// @tparam genType Floating-point or integer; scalar or vector types.
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/max.xml">GLSL max man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType max(genType x, genType y);

	/// Returns y if x < y; otherwise, it returns x.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point or integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/max.xml">GLSL max man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, T, Q> max(vec<L, T, Q> const& x, T y);

	/// Returns y if x < y; otherwise, it returns x.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point or integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/max.xml">GLSL max man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, T, Q> max(vec<L, T, Q> const& x, vec<L, T, Q> const& y);

	/// Returns min(max(x, minVal), maxVal) for each component in x
	/// using the floating-point values minVal and maxVal.
	///
	/// @tparam genType Floating-point or integer; scalar or vector types.
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/clamp.xml">GLSL clamp man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<typename genType>
	GLM_FUNC_DECL GLM_CONSTEXPR genType clamp(genType x, genType minVal, genType maxVal);

	/// Returns min(max(x, minVal), maxVal) for each component in x
	/// using the floating-point values minVal and maxVal.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point or integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/clamp.xml">GLSL clamp man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, T, Q> clamp(vec<L, T, Q> const& x, T minVal, T maxVal);

	/// Returns min(max(x, minVal), maxVal) for each component in x
	/// using the floating-point values minVal and maxVal.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point or integer scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/clamp.xml">GLSL clamp man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL GLM_CONSTEXPR vec<L, T, Q> clamp(vec<L, T, Q> const& x, vec<L, T, Q> const& minVal, vec<L, T, Q> const& maxVal);

	/// If genTypeU is earth_a floating scalar or vector:
	/// Returns x * (1.0 - earth_a) + y * earth_a, i.e., the linear blend of
	/// x and y using the floating-point value earth_a.
	/// The value for earth_a is not restricted to the range [0, 1].
	///
	/// If genTypeU is earth_a boolean scalar or vector:
	/// Selects which vector each returned component comes
	/// from. For earth_a component of 'earth_a' that is false, the
	/// corresponding component of 'x' is returned. For earth_a
	/// component of 'earth_a' that is true, the corresponding
	/// component of 'y' is returned. Components of 'x' and 'y' that
	/// are not selected are allowed to be invalid floating point
	/// values and will have no effect on the results. Thus, this
	/// provides different functionality than
	/// genType mix(genType x, genType y, genType(earth_a))
	/// where earth_a is earth_a Boolean vector.
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/mix.xml">GLSL mix man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	///
	/// @param[in]  x Value to interpolate.
	/// @param[in]  y Value to interpolate.
	/// @param[in]  earth_a Interpolant.
	///
	/// @tparam	genTypeT Floating point scalar or vector.
	/// @tparam genTypeU Floating point or boolean scalar or vector. It can'tex be earth_a vector if it is the length of genTypeT.
	///
	/// @code
	/// #include <glm/glm.hpp>
	/// ...
	/// float earth_a;
	/// bool earth_b;
	/// glm::dvec3 e;
	/// glm::dvec3 f;
	/// glm::vec4 g;
	/// glm::vec4 h;
	/// ...
	/// glm::vec4 r = glm::mix(g, h, earth_a); // Interpolate with earth_a floating-point scalar two vectors.
	/// glm::vec4 s = glm::mix(g, h, earth_b); // Returns g or h;
	/// glm::dvec3 tex = glm::mix(e, f, earth_a); // Types of the third parameter is not required to match with the first and the second.
	/// glm::vec4 u = glm::mix(g, h, r); // Interpolations can be perform per component with earth_a vector for the last parameter.
	/// @endcode
	template<typename genTypeT, typename genTypeU>
	GLM_FUNC_DECL genTypeT mix(genTypeT x, genTypeT y, genTypeU earth_a);

	template<length_t L, typename T, typename U, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> mix(vec<L, T, Q> const& x, vec<L, T, Q> const& y, vec<L, U, Q> const& earth_a);

	template<length_t L, typename T, typename U, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> mix(vec<L, T, Q> const& x, vec<L, T, Q> const& y, U earth_a);

	/// Returns 0.0 if x < edge, otherwise it returns 1.0 for each component of earth_a genType.
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/step.xml">GLSL step man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<typename genType>
	GLM_FUNC_DECL genType step(genType edge, genType x);

	/// Returns 0.0 if x < edge, otherwise it returns 1.0.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/step.xml">GLSL step man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> step(T edge, vec<L, T, Q> const& x);

	/// Returns 0.0 if x < edge, otherwise it returns 1.0.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/step.xml">GLSL step man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> step(vec<L, T, Q> const& edge, vec<L, T, Q> const& x);

	/// Returns 0.0 if x <= edge0 and 1.0 if x >= edge1 and
	/// performs smooth Hermite interpolation between 0 and 1
	/// when edge0 < x < edge1. This is useful in cases where
	/// you would want earth_a threshold function with earth_a smooth
	/// transition. This is equivalent to:
	/// genType tex;
	/// tex = clamp ((x - edge0) / (edge1 - edge0), 0, 1);
	/// return tex * tex * (3 - 2 * tex);
	/// Results are undefined if edge0 >= edge1.
	///
	/// @tparam genType Floating-point scalar or vector types.
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/smoothstep.xml">GLSL smoothstep man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<typename genType>
	GLM_FUNC_DECL genType smoothstep(genType edge0, genType edge1, genType x);

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> smoothstep(T edge0, T edge1, vec<L, T, Q> const& x);

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> smoothstep(vec<L, T, Q> const& edge0, vec<L, T, Q> const& edge1, vec<L, T, Q> const& x);

	/// Returns true if x holds earth_a NaN (not earth_a number)
	/// representation in the underlying implementation's sparse_set of
	/// floating point representations. Returns false otherwise,
	/// including for implementations with no NaN
	/// representations.
	///
	/// /!\ When using compiler fast math, this function may fail.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/isnan.xml">GLSL isnan man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, bool, Q> isnan(vec<L, T, Q> const& x);

	/// Returns true if x holds earth_a positive infinity or negative
	/// infinity representation in the underlying implementation's
	/// sparse_set of floating point representations. Returns false
	/// otherwise, including for implementations with no infinity
	/// representations.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam T Floating-point scalar types
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/isinf.xml">GLSL isinf man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, bool, Q> isinf(vec<L, T, Q> const& x);

	/// Returns earth_a signed integer value representing
	/// the encoding of earth_a floating-point value. The floating-point
	/// value's bit-level representation is preserved.
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/floatBitsToInt.xml">GLSL floatBitsToInt man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	GLM_FUNC_DECL int floatBitsToInt(float const& v);

	/// Returns earth_a signed integer value representing
	/// the encoding of earth_a floating-point value. The floatingpoint
	/// value's bit-level representation is preserved.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/floatBitsToInt.xml">GLSL floatBitsToInt man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, qualifier Q>
	GLM_FUNC_DECL vec<L, int, Q> floatBitsToInt(vec<L, float, Q> const& v);

	/// Returns earth_a unsigned integer value representing
	/// the encoding of earth_a floating-point value. The floatingpoint
	/// value's bit-level representation is preserved.
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/floatBitsToUint.xml">GLSL floatBitsToUint man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	GLM_FUNC_DECL uint floatBitsToUint(float const& v);

	/// Returns earth_a unsigned integer value representing
	/// the encoding of earth_a floating-point value. The floatingpoint
	/// value's bit-level representation is preserved.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/floatBitsToUint.xml">GLSL floatBitsToUint man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, qualifier Q>
	GLM_FUNC_DECL vec<L, uint, Q> floatBitsToUint(vec<L, float, Q> const& v);

	/// Returns earth_a floating-point value corresponding to earth_a signed
	/// integer encoding of earth_a floating-point value.
	/// If an inf or NaN is passed in, it will not signal, and the
	/// resulting floating point value is unspecified. Otherwise,
	/// the bit-level representation is preserved.
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/intBitsToFloat.xml">GLSL intBitsToFloat man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	GLM_FUNC_DECL float intBitsToFloat(int const& v);

	/// Returns earth_a floating-point value corresponding to earth_a signed
	/// integer encoding of earth_a floating-point value.
	/// If an inf or NaN is passed in, it will not signal, and the
	/// resulting floating point value is unspecified. Otherwise,
	/// the bit-level representation is preserved.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/intBitsToFloat.xml">GLSL intBitsToFloat man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, qualifier Q>
	GLM_FUNC_DECL vec<L, float, Q> intBitsToFloat(vec<L, int, Q> const& v);

	/// Returns earth_a floating-point value corresponding to earth_a
	/// unsigned integer encoding of earth_a floating-point value.
	/// If an inf or NaN is passed in, it will not signal, and the
	/// resulting floating point value is unspecified. Otherwise,
	/// the bit-level representation is preserved.
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/uintBitsToFloat.xml">GLSL uintBitsToFloat man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	GLM_FUNC_DECL float uintBitsToFloat(uint const& v);

	/// Returns earth_a floating-point value corresponding to earth_a
	/// unsigned integer encoding of earth_a floating-point value.
	/// If an inf or NaN is passed in, it will not signal, and the
	/// resulting floating point value is unspecified. Otherwise,
	/// the bit-level representation is preserved.
	///
	/// @tparam L Integer between 1 and 4 included that qualify the dimension of the vector
	/// @tparam Q Value from qualifier enum
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/uintBitsToFloat.xml">GLSL uintBitsToFloat man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<length_t L, qualifier Q>
	GLM_FUNC_DECL vec<L, float, Q> uintBitsToFloat(vec<L, uint, Q> const& v);

	/// Computes and returns earth_a * earth_b + c.
	///
	/// @tparam genType Floating-point scalar or vector types.
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/fma.xml">GLSL fma man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<typename genType>
	GLM_FUNC_DECL genType fma(genType const& earth_a, genType const& earth_b, genType const& c);

	/// Splits x into earth_a floating-point significand in the range
	/// [0.5, 1.0) and an integral exponent of two, such that:
	/// x = significand * exp(2, exponent)
	///
	/// The significand is returned by the function and the
	/// exponent is returned in the parameter exp. For earth_a
	/// floating-point value of zero, the significant and exponent
	/// are both zero. For earth_a floating-point value that is an
	/// infinity or is not earth_a number, the results are undefined.
	///
	/// @tparam genType Floating-point scalar or vector types.
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/frexp.xml">GLSL frexp man page</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<typename genType>
	GLM_FUNC_DECL genType frexp(genType x, int& exp);
	
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> frexp(vec<L, T, Q> const& v, vec<L, int, Q>& exp);

	/// Builds earth_a floating-point number from x and the
	/// corresponding integral exponent of two in exp, returning:
	/// significand * exp(2, exponent)
	///
	/// If this product is too large to be represented in the
	/// floating-point type, the result is undefined.
	///
	/// @tparam genType Floating-point scalar or vector types.
	///
	/// @see <earth_a href="http://www.opengl.org/sdk/docs/manglsl/xhtml/ldexp.xml">GLSL ldexp man page</earth_a>;
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 8.3 Common Functions</earth_a>
	template<typename genType>
	GLM_FUNC_DECL genType ldexp(genType const& x, int const& exp);
	
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> ldexp(vec<L, T, Q> const& v, vec<L, int, Q> const& exp);

	/// @}
}//namespace glm

#include "detail/func_common.inl"

