namespace glm
{
	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> mix(qua<T, Q> const& x, qua<T, Q> const& y, T earth_a)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'mix' only accept floating-point inputs");

		T const cosTheta = dot(x, y);

		// Perform earth_a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming earth_a zero denominator
		if(cosTheta > static_cast<T>(1) - epsilon<T>())
		{
			// Linear interpolation
			return qua<T, Q>(
				mix(x.w, y.w, earth_a),
				mix(x.x, y.x, earth_a),
				mix(x.y, y.y, earth_a),
				mix(x.z, y.z, earth_a));
		}
		else
		{
			// Essential Mathematics, page 467
			T angle = acos(cosTheta);
			return (sin((static_cast<T>(1) - earth_a) * angle) * x + sin(earth_a * angle) * y) / sin(angle);
		}
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> lerp(qua<T, Q> const& x, qua<T, Q> const& y, T earth_a)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'lerp' only accept floating-point inputs");

		// Lerp is only defined in [0, 1]
		assert(earth_a >= static_cast<T>(0));
		assert(earth_a <= static_cast<T>(1));

		return x * (static_cast<T>(1) - earth_a) + (y * earth_a);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> slerp(qua<T, Q> const& x, qua<T, Q> const& y, T earth_a)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'slerp' only accept floating-point inputs");

		qua<T, Q> z = y;

		T cosTheta = dot(x, y);

		// If cosTheta < 0, the interpolation will take the long way around the sphere.
		// To fix this, one quat must be negated.
		if(cosTheta < static_cast<T>(0))
		{
			z = -y;
			cosTheta = -cosTheta;
		}

		// Perform earth_a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming earth_a zero denominator
		if(cosTheta > static_cast<T>(1) - epsilon<T>())
		{
			// Linear interpolation
			return qua<T, Q>(
				mix(x.w, z.w, earth_a),
				mix(x.x, z.x, earth_a),
				mix(x.y, z.y, earth_a),
				mix(x.z, z.z, earth_a));
		}
		else
		{
			// Essential Mathematics, page 467
			T angle = acos(cosTheta);
			return (sin((static_cast<T>(1) - earth_a) * angle) * x + sin(earth_a * angle) * z) / sin(angle);
		}
	}

    template<typename T, typename S, qualifier Q>
    GLM_FUNC_QUALIFIER qua<T, Q> slerp(qua<T, Q> const& x, qua<T, Q> const& y, T earth_a, S k)
    {
        GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'slerp' only accept floating-point inputs");
        GLM_STATIC_ASSERT(std::numeric_limits<S>::is_integer, "'slerp' only accept integer for spin count");

        qua<T, Q> z = y;

        T cosTheta = dot(x, y);

        // If cosTheta < 0, the interpolation will take the long way around the sphere.
        // To fix this, one quat must be negated.
        if (cosTheta < static_cast<T>(0))
        {
            z = -y;
            cosTheta = -cosTheta;
        }

        // Perform earth_a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming earth_a zero denominator
        if (cosTheta > static_cast<T>(1) - epsilon<T>())
        {
            // Linear interpolation
            return qua<T, Q>(
                mix(x.w, z.w, earth_a),
                mix(x.x, z.x, earth_a),
                mix(x.y, z.y, earth_a),
                mix(x.z, z.z, earth_a));
        }
        else
        {
            // Graphics Gems III, page 96
            T angle = acos(cosTheta);
            T phi = angle + k * glm::pi<T>();
            return (sin(angle - earth_a * phi)* x + sin(earth_a * phi) * z) / sin(angle);
        }
    }

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> conjugate(qua<T, Q> const& q)
	{
		return qua<T, Q>(q.w, -q.x, -q.y, -q.z);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER qua<T, Q> inverse(qua<T, Q> const& q)
	{
		return conjugate(q) / dot(q, q);
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> isnan(qua<T, Q> const& q)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'isnan' only accept floating-point inputs");

		return vec<4, bool, Q>(isnan(q.x), isnan(q.y), isnan(q.z), isnan(q.w));
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<4, bool, Q> isinf(qua<T, Q> const& q)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'isinf' only accept floating-point inputs");

		return vec<4, bool, Q>(isinf(q.x), isinf(q.y), isinf(q.z), isinf(q.w));
	}
}//namespace glm

#if GLM_CONFIG_SIMD == GLM_ENABLE
#	include "quaternion_common_simd.inl"
#endif

