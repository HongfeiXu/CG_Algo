#ifndef OBB_H
#define OBB_H

#include "vec.h"
#include <iostream>

typedef Vec<3, double> Vector3d;
class OBB;

// help function declaration
float RAD2DEG(float radians);
float DEG2RAD(float degrees);
float CorrectDegrees(float degrees);
Vector3f cross3D_OBB(const Vector3f &lhs, const Vector3f &rhs);
Vector3d rotate3D_OBB(const Vector3d &inOutVec, const Vector3d &axis, const double angle);

// key function
bool OBBCollisionWithOBB(const OBB &lhs, const OBB &rhs);  // use SAT algorithm
bool OverlapOnAxis(const OBB &lhs, const OBB &rhs, const Vector3f& csa);  // csa refer to candidate seperate axis

// class for Oriented Bounding Box
class OBB {
public:
	OBB(): 
		cenPt(Vector3f()), 
		halfSize(Vector3f()), 
		rotAxis(Vector3f()), 
		rotAngle(0),
		localX(Vector3f(1,0,0)),
		localY(Vector3f(0,1,0)),
		localZ(Vector3f(0,0,1))
	{ }
	OBB(Vector3f cenPt_, Vector3f halfSize_):
		cenPt(cenPt_),
		halfSize(halfSize_),
		rotAxis(Vector3f()),
		rotAngle(0),
		localX(Vector3f(1, 0, 0)),
		localY(Vector3f(0, 1, 0)),
		localZ(Vector3f(0, 0, 1))
	{ }
	OBB(const OBB &rhs):
		cenPt(rhs.cenPt),
		halfSize(rhs.halfSize),
		rotAxis(rhs.rotAxis),
		rotAngle(rhs.rotAngle),
		localX(rhs.localX),
		localY(rhs.localY),
		localZ(rhs.localZ)
	{ }
	OBB & operator = (const OBB &rhs)
	{
		cenPt = rhs.cenPt;
		halfSize = rhs.halfSize;
		rotAxis = rhs.rotAxis;
		rotAngle = rhs.rotAngle;
		localX = rhs.localX;
		localY = rhs.localY;
		localZ = rhs.localZ;
	}
	void Rotate(Vector3f rotAxis_, float rotAngle_)
	{
		std::cout << "rotate " << rotAngle_ << " along axis: " << rotAxis_ << std::endl;
		rotAxis = rotAxis_;
		rotAngle = rotAngle_;
		ComputeLocalAxis();
	}
	bool CollisionWithOBB(const OBB &rhs)
	{
		return OBBCollisionWithOBB(*this, rhs);
	}
	// TODO...
	float VolumeOfIntersection(const OBB &rhs)
	{
		if (!CollisionWithOBB(rhs))
			return 0;



		return 0.0f;
	}
private:
	void ComputeLocalAxis()
	{
		Vector3d localX_ = { static_cast<double>(localX.x), static_cast<double>(localX.y), static_cast<double>(localX.z) };
		Vector3d localY_ = { static_cast<double>(localY.x), static_cast<double>(localY.y), static_cast<double>(localY.z) };
		Vector3d localZ_ = { static_cast<double>(localZ.x), static_cast<double>(localZ.y), static_cast<double>(localZ.z) };
		Vector3d rotAxis_ = { static_cast<double>(rotAxis.x), static_cast<double>(rotAxis.y), static_cast<double>(rotAxis.z) };
		double rotAngle_ = static_cast<double>(DEG2RAD(rotAngle));  // degree to radius

		localX_ = rotate3D_OBB(localX_, rotAxis_, rotAngle_);
		localY_ = rotate3D_OBB(localY_, rotAxis_, rotAngle_);
		localZ_ = rotate3D_OBB(localZ_, rotAxis_, rotAngle_);

		localX = Vector3f(static_cast<float>(localX_[0]), static_cast<float>(localX_[1]), static_cast<float>(localX_[2]));
		localY = Vector3f(static_cast<float>(localY_[0]), static_cast<float>(localY_[1]), static_cast<float>(localY_[2]));
		localZ = Vector3f(static_cast<float>(localZ_[0]), static_cast<float>(localZ_[1]), static_cast<float>(localZ_[2]));
	}

public:
	// Data
	Vector3f cenPt;     // Center Point
	Vector3f halfSize;  // HALF SIZE! length along local x-axis, y-axis, z-axis

	Vector3f localX;  // unit vector representing the local x-axis of this OBB
	Vector3f localY;  // unit vector representing the local y-axis of this OBB
	Vector3f localZ;  // unit vector representing the local z-axis of this OBB
private:
	// add rotate
	Vector3f rotAxis;
	float rotAngle;  // unit: Degree
};


#endif // !OBB_H
