#include <algorithm>
#include <vector>
#include "GetCrossPoint.h"

int main()
{
	// Test GetCrossPoint2D function
	//Point a1(0, 0), a2(2, 2);
	//Point b1(1, 1), b2(3, 1);

	//Point crossPoint;
	//if(GetCrossPoint2D(a1, a2, b1, b2, crossPoint))
	//{
	//	printf("crossPoint (%f, %f)\n", crossPoint.x, crossPoint.y);
	//}
	//else
	//{
	//	printf("No cross point!!\n");
	//}

	std::vector<Point> ptList_1;
	std::vector<Point> ptList_2;

	Point p1(0, 0);
	Point p2(2, 0);
	Point p3(2, 2);

	Point q1(1, 1);
	Point q2(3, 1);
	Point q3(3, 3);
	Point q4(1, 3);

	ptList_1.push_back(p1);
	ptList_1.push_back(p2);
	ptList_1.push_back(p3);

	ptList_2.push_back(q1);
	ptList_2.push_back(q2);
	ptList_2.push_back(q3);
	ptList_2.push_back(q4);

	std::vector<Point> crossPointList;

	PolygonCrossPoint2D(ptList_1, ptList_2, crossPointList);

	printf("There are %d cross points which are \n", crossPointList.size());
	for(const auto &p : crossPointList)
	{
		printf("(%f, %f)\n", p.x, p.y);
	}

	return 0;
}