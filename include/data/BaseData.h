#pragma once

template<typename T>
struct TPoint2D
{
	TPoint2D() : x(0), y(0) {}
	TPoint2D(T xx, T yy) : x(xx), y(yy) {}
	T x;
	T y;
};

typedef TPoint2D<double> Point2D;

template<typename T>
struct TPoint3D
{
	TPoint3D() : x(0), y(0), z(0) {}
	TPoint3D(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
	T x;
	T y;
	T z;
};

typedef TPoint3D<double> Point3D;

inline bool Point3DCompare(const Point3D& pt1, const Point3D& pt2)
{
	return pt1.z < pt2.z;
}