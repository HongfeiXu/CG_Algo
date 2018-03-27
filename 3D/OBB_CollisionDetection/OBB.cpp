#include "OBB.h"
#include <cmath>  // abs()

bool OBBCollisionWithOBB(const OBB &lhs, const OBB &rhs)
{
	// CSA refer to candidate_seperate_axis
	Vector3f CSA[15] =
	{
		Vector3f(lhs.localX),
		Vector3f(lhs.localY),
		Vector3f(lhs.localZ),
		Vector3f(rhs.localX),
		Vector3f(rhs.localY),
		Vector3f(rhs.localZ)
	};
	for (int i = 0; i < 3; ++i)
	{
		CSA[6 + i * 3 + 0] = cross3D_OBB(CSA[i], CSA[0]);
		CSA[6 + i * 3 + 1] = cross3D_OBB(CSA[i], CSA[1]);
		CSA[6 + i * 3 + 2] = cross3D_OBB(CSA[i], CSA[2]);
	}
	for (int i = 0; i < 15; i++)
	{
		normalize(CSA[i]);
		if (!OverlapOnAxis(lhs, rhs, CSA[i]))
			return false;  // Seperating axis found
	}
	return true;  // Seperating axis not found
}

bool OverlapOnAxis(const OBB& lhs, const OBB& rhs, const Vector3f& csa)
{
	float w0 = lhs.halfSize[0];
	float h0 = lhs.halfSize[1];
	float d0 = lhs.halfSize[2];

	float w1 = rhs.halfSize[0];
	float h1 = rhs.halfSize[1];
	float d1 = rhs.halfSize[2];

	Vector3f T = rhs.cenPt - lhs.cenPt;
	
	float T_axis_projection = abs(T DOT csa);
	float half_lhs_axis_projection = abs(w0 * lhs.localX DOT csa) + abs(h0 * lhs.localY DOT csa) + abs(d0 * lhs.localZ DOT csa);
	float half_rhs_axis_projection = abs(w1 * rhs.localX DOT csa) + abs(h1 * rhs.localY DOT csa) + abs(d1 * rhs.localZ DOT csa);

	if (T_axis_projection > half_lhs_axis_projection + half_rhs_axis_projection)  // sep_axis is the seperate axis
		return false;
	else
		return true;
}

float CorrectDegrees(float degrees)
{
	while (degrees > 360.0f)
	{
		degrees -= 360.0f;
	}
	while (degrees < -360.0f)
	{
		degrees += 360.0f;
	}
	return degrees;
}

float RAD2DEG(float radians)
{
	float degrees = radians * 57.295754f;
	degrees = CorrectDegrees(degrees);
	return degrees;
}

float DEG2RAD(float degrees)
{
	degrees = CorrectDegrees(degrees);
	float radians = degrees * 0.0174533f;
	return radians;
}

Vector3f cross3D_OBB(const Vector3f &lhs, const Vector3f &rhs)
{
	Vector3f ret;
	ret[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
	ret[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
	ret[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
	return ret;
}

Vector3d rotate3D_OBB(const Vector3d &inVec, const Vector3d &axis, const double angle)
{
	double c, s;
	Vector3d outVec;
	double mat[9];
	Vector3d myAxis;

	// form the rotation matrix
	c = std::cos(angle);
	s = std::sin(angle);

	myAxis = axis;
	normalize(myAxis);

	auto n1 = myAxis[0];
	auto n2 = myAxis[1];
	auto n3 = myAxis[2];

	mat[0] = c + n1*n1*(1 - c);
	mat[1] = n1*n2*(1 - c) - s*n3;
	mat[2] = n3*n1*(1 - c) + s*n2;

	mat[3] = n1*n2*(1 - c) + s*n3;
	mat[4] = c + n2*n2*(1 - c);
	mat[5] = n3*n2*(1 - c) - s*n1;

	mat[6] = n3*n1*(1 - c) - s*n2;
	mat[7] = n3*n2*(1 - c) + s*n1;
	mat[8] = c + n3*n3*(1 - c);

	Vector3d v1 = { mat[0], mat[1], mat[2] };
	Vector3d v2 = { mat[3], mat[4], mat[5] };
	Vector3d v3 = { mat[6], mat[7], mat[8] };

	// perform rotation
	outVec[0] = v1 DOT inVec;
	outVec[1] = v2 DOT inVec;
	outVec[2] = v3 DOT inVec;

	return outVec;
}
