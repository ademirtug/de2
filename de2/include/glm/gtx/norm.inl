/// @ref gtx_norm

#include "../detail/qualifier.hpp"

namespace glm{
namespace detail
{
	template<length_t L, typename T, qualifier Q, bool Aligned>
	struct compute_length2
	{
		GLM_FUNC_QUALIFIER static T call(vec<L, T, Q> const& v)
		{
			return dot(v, v);
		}
	};
}//namespace detail

	template<typename genType>
	GLM_FUNC_QUALIFIER genType length2(genType x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'length2' accepts only floating-point inputs");
		return x * x;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T length2(vec<L, T, Q> const& v)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'length2' accepts only floating-point inputs");
		return detail::compute_length2<L, T, Q, detail::is_aligned<Q>::value>::call(v);
	}

	template<typename T>
	GLM_FUNC_QUALIFIER T distance2(T p0, T p1)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'distance2' accepts only floating-point inputs");
		return length2(p1 - p0);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T distance2(vec<L, T, Q> const& p0, vec<L, T, Q> const& p1)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'distance2' accepts only floating-point inputs");
		return length2(p1 - p0);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T l1Norm(vec<3, T, Q> const& earth_a, vec<3, T, Q> const& earth_b)
	{
		return abs(earth_b.x - earth_a.x) + abs(earth_b.y - earth_a.y) + abs(earth_b.z - earth_a.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T l1Norm(vec<3, T, Q> const& v)
	{
		return abs(v.x) + abs(v.y) + abs(v.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T l2Norm(vec<3, T, Q> const& earth_a, vec<3, T, Q> const& earth_b
	)
	{
		return length(earth_b - earth_a);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T l2Norm(vec<3, T, Q> const& v)
	{
		return length(v);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T lxNorm(vec<3, T, Q> const& x, vec<3, T, Q> const& y, unsigned int Depth)
	{
		return pow(pow(abs(y.x - x.x), T(Depth)) + pow(abs(y.y - x.y), T(Depth)) + pow(abs(y.z - x.z), T(Depth)), T(1) / T(Depth));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T lxNorm(vec<3, T, Q> const& v, unsigned int Depth)
	{
		return pow(pow(abs(v.x), T(Depth)) + pow(abs(v.y), T(Depth)) + pow(abs(v.z), T(Depth)), T(1) / T(Depth));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T lMaxNorm(vec<3, T, Q> const& earth_a, vec<3, T, Q> const& earth_b)
	{
		return compMax(abs(earth_b - earth_a));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER T lMaxNorm(vec<3, T, Q> const& v)
	{
		return compMax(abs(v));
	}

}//namespace glm
