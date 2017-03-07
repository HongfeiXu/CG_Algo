/*

��������2D����εĽ��㡣
���ж���εĶ�������Ϊ Point��

��Ϊ��������

1. ���������߶εĽ�������  GetCrossPoint2D()
2. ������������εĽ�������  PolygonCrossPoint2D()

*/

#include <vector>
#include <cstdio>
#include <algorithm>

class Point
{
public:
	float x;
	float y;

	Point() { x = y = 0.0f; }
	Point(float x_, float y_) : x(x_), y(y_) { }
};

bool operator== (const Point &lhs, const Point &rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!= (const Point &lhs, const Point &rhs)
{
	return lhs == rhs;
}

bool operator< (const Point &lhs, const Point &rhs)
{
	if(lhs.x < rhs.x)
	{
		return true;
	}
	else if(lhs.x == rhs.x)
	{
		if(lhs.y < rhs.y)
			return true;
		else
			return false;
	}
	else
	{
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////
// ���������߶εĽ�������
//////////////////////////////////////////////////////////////////////////

float min(float x, float y)
{
	return x < y ? x : y;
}

float max(float x, float y)
{
	return x > y ? x : y;
}

// �ų�ʵ��
// �����߶� P1P2 Ϊ�Խ��ߵľ���Ϊ R�������߶� Q1Q2 Ϊ�Խ��ߵľ���Ϊ T����� R �� T ���ཻ�������߶β��ཻ��
bool IsRectCross(const Point &p1, const Point &p2, const Point &q1, const Point &q2)
{
	return (min(p1.x, p2.x) <= max(q1.x, q2.x) &&
		min(q1.x, q2.x) <= max(p1.x, p2.x) &&
		min(p1.y, p2.y) <= max(q1.y, q2.y) &&
		min(q1.y, q2.y) <= max(p1.y, p2.y));
}

// �����ж�
// ������߶��ཻ�������߶α�Ȼ�໥�����Է���
// 1. ��Q1Q2����P1P2����ʸ��(Q1-P1)��(Q2-P1)λ��ʸ��(P2-P1)�����࣬��( Q1 - P1 ) �� ( P2 - P1 ) * ( Q2 - P1 ) �� ( P2 - P1 ) <= 0��
// 2. ��P1P2����Q1Q2����ʸ��(P1-Q1)��(P2-Q1)λ��ʸ��(Q2-Q1)�����࣬��( P1 - Q1 ) �� ( Q2 - Q1 ) * ( P2 - Q1 ) �� ( Q2 - Q1 ) <= 0��
bool IsLineSegmentCross(const Point &p1, const Point &p2, const Point &q1, const Point &q2)
{
	if(((q1.x - p1.x) * (p2.y - p1.y) - (q1.y - p1.y) * (p2.x - p1.x)) * ((q2.x - p1.x) * (p2.y - p1.y) - (q2.y - p1.y) * (p2.x - p1.x)) <= 0 &&
		((p1.x - q1.x) * (q2.y - q1.y) - (p1.y - q1.y) * (q2.x - q1.x)) * ((p2.x - q1.x) * (q2.y - q1.y) - (p2.y - q1.y) * (q2.x - q1.x)) <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// ���߶� P1P2 �� Q1Q2 �Ľ��㡣
// �Ƚ��п����ų�ʵ��Ϳ���ʵ��ȷ���н����ڽ��м��㡣
// ���� crossPoint ʹ�����÷��ء�
bool GetCrossPoint2D(const Point &p1, const Point &p2, const Point &q1, const Point &q2, Point &crossPoint)
{
	if(IsRectCross(p1, p2, q1, q2) && IsLineSegmentCross(p1, p2, q1, q2))
	{
		float tempLeft, tempRight;
		tempLeft = (p2.y - p1.y) * (q2.x - q1.x) - (p2.x - p1.x) * (q2.y - q1.y);
		tempRight = (q1.y - p1.y) * (p2.x - p1.x) * (q2.x - q1.x) + p1.x * (p2.y - p1.y) * (q2.x - q1.x) - q1.x * (p2.x - p1.x) * (q2.y - q1.y);
		crossPoint.x = tempRight / tempLeft;
		tempLeft = (p2.x - p1.x) * (q2.y - q1.y) - (p2.y - p1.y) * (q2.x - q1.x);
		tempRight = (q1.x - p1.x) * (p2.y - p1.y) * (q2.y - q1.y) + p1.y * (p2.x - p1.x) * (q2.y - q1.y) - q1.y * (p2.y - p1.y) * (q2.x - q1.x);
		crossPoint.y = tempRight / tempLeft;
		return true;
	}
	else
	{
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////
// ������������εĽ�������
//////////////////////////////////////////////////////////////////////////

void PolygonCrossPoint2D(const std::vector<Point> &ptList_1, const std::vector<Point> &ptList_2, std::vector<Point> &crossPointList)
{
	Point p1, p2, q1, q2;
	Point crossPoint;

	for(int i = 0; i != ptList_1.size(); i++)
	{
		p1 = ptList_1[i];
		p2 = ptList_1[(i + 1) % ptList_1.size()];
		for(int j = 0; j != ptList_2.size(); j++)
		{
			q1 = ptList_2[j];
			q2 = ptList_2[(j + 1) % ptList_2.size()];
			if(GetCrossPoint2D(p1, p2, q1, q2, crossPoint))
			{
				crossPointList.push_back(crossPoint);
			}
		}
	}

	// �����ͬ�Ķ���
	sort(crossPointList.begin(), crossPointList.end());
	auto end_unique = unique(crossPointList.begin(), crossPointList.end());
	crossPointList.erase(end_unique, crossPointList.end());

	return;
}