#include <iostream>
#include "OBB.h"
#include "vec.h"
#include <sys/timeb.h>  // ¼ÆÊ±
using namespace std;

int main()
{
	// OBB OBB collision detection test
	OBB obb0(Vector3f(0, 0, 0), Vector3f(1, 1, 1));
	Vector3f rotAxis(0, 0, 1);
	float rotAngle = 40;
	obb0.Rotate(rotAxis, rotAngle);

	OBB obb1(Vector3f(2.574f, 0, 0), Vector3f(1, 1, 1));
	rotAxis = Vector3f(0, 1, 0);
	rotAngle = 60.0f;
	obb1.Rotate(rotAxis, rotAngle);

	bool isColl = obb0.CollisionWithOBB(obb1);
	if (isColl)
		cout << "\nCollision detected!" << endl;
	else
		cout << "\nNo Collision!" << endl;


	return 0;
}