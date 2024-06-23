#pragma once

#include <vector>
#include <cassert>

#include "base_exception.h"
#include "data/BaseData.h"


using namespace std;

class InterpolaterException : public BaseException {
public:
    InterpolaterException(string message) throw(): BaseException(message) {}
    InterpolaterException(string message, string location) throw(): BaseException(message, location) {}
};


template<class ForwardIterator>
class TInterpolater {
public:
    virtual ~TInterpolater() {}
    virtual double GetInterpolatedZ(double xpos, double ypos, ForwardIterator first, ForwardIterator last)
    throw(InterpolaterException) = 0;
};

//typedef TInterpolater<Point3D*> Interpolater;
typedef TInterpolater<vector<Point3D>::iterator> Interpolater;


