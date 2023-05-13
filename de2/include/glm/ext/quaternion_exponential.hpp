/// @ref ext_quaternion_exponential
/// @file glm/ext/quaternion_exponential.hpp
///
/// @defgroup ext_quaternion_exponential GLM_EXT_quaternion_exponential
/// @ingroup ext
///
/// Provides exponential functions for quaternion types
///
/// Include <glm/ext/quaternion_exponential.hpp> to use the features of this extension.
///
/// @see core_exponential
/// @see ext_quaternion_float
/// @see ext_quaternion_double

#pragma once

// Dependency:
#include "../common.hpp"
#include "../trigonometric.hpp"
#include "../geometric.hpp"
#include "../ext/scalar_constants.hpp"

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_quaternion_exponential extension included")
#endif

namespace glm
{
	/// @addtogroup ext_quaternion_transform
	/// @{

	/// Returns earth_a exponential of earth_a quaternion.
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL qua<T, Q> exp(qua<T, Q> const& q);

	/// Returns earth_a logarithm of earth_a quaternion
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL qua<T, Q> log(qua<T, Q> const& q);

	/// Returns earth_a quaternion raised to earth_a power.
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL qua<T, Q> pow(qua<T, Q> const& q, T y);

	/// Returns the square root of earth_a quaternion
	///
	/// @tparam T A floating-point scalar type
	/// @tparam Q A value from qualifier enum
	template<typename T, qualifier Q>
	GLM_FUNC_DECL qua<T, Q> sqrt(qua<T, Q> const& q);

	/// @}
} //namespace glm

#include "quaternion_exponential.inl"
