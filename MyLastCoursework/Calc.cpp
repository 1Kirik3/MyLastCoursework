#include "pch.h"
#include "Calc.h"
#include <cmath>

Calc::Calc() 
{

}

Calc::~Calc()
{

}

CPoint Calc::ScalingPoint(CPoint dot, double scale)
{
	CPoint ptOut;
	ptOut.x = dot.x * scale;
	ptOut.y = dot.y * scale;	
	return ptOut;
}

CPoint Calc::ToRectCenter(const CRect& place)
{
	center = place.CenterPoint();
	return center;
}

const std::vector<CPoint>& Calc::get_points()
{
	if (!checkCalculation) {
		calculate();
	}
	return points;
}

void Calc::calculate()
{
	double start = from;
	double end = to;
	points.resize(ceil((end - start) / step));
	for (size_t i = 0; i < points.size(); i++)
	{
		CPoint myPoint;
		myPoint.x = start + step * i;
		double x = myPoint.x;
		myPoint.y = 0;

		if (checkLog) {
			myPoint.y = log10(abs(myPoint.y));
		}
		myPoint = ScalingPoint(myPoint, scale);
		points.push_back(myPoint);
	}
	IsCalculated();
}

double RealSignal::f(double x)
{
	return (scale * a *(1+m*sin(2*PI*Fm*(x/scale)))*sin(2*PI*f_*(x/scale)));
}

const std::vector<double>& RealSignal::get_data()
{
	if (!checkCalculation) {
		calculate();
	}
	return data;
}

void RealSignal::calculate()
{
	double start = from;
	double end = to;
	points.resize(ceil((end - start) / step));
	data.resize(points.size());
	for (size_t i = 0; i < points.size(); i++)
	{
		CPoint myPoint;
		myPoint.x = start + step * i;
		double x = myPoint.x;
		myPoint.y = f(x);
		data[i] = myPoint.y;
		if (checkLog) {
			myPoint.y = log10(abs(myPoint.y));
		}
		myPoint = ScalingPoint(myPoint, scale);
		points.push_back(myPoint);
	}
	IsCalculated();
}
