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


double RealSignal::f(double x)
{
	if ((checkYScale == 1) && (checkXScale == 0))
	{
		if (checkLog)
			return (signalScale * log10(abs((m_a * (1 + m_m * sin(2 * PI * m_Fm * (x))) * sin(2 * PI * m_f * (x))))));
		else
			return (signalScale * (m_a * (1 + m_m * sin(2 * PI * m_Fm * (x))) * sin(2 * PI * m_f * (x))));
	}

	else if ((checkYScale == 0) && (checkXScale == 1))
	{
		if (checkLog)
			return (log10(abs((m_a * (1 + m_m * sin(2 * PI * m_Fm * (x / signalScale))) * sin(2 * PI * m_f * (x / signalScale))))));
		else
			return ((m_a * (1 + m_m * sin(2 * PI * m_Fm * (x / signalScale))) * sin(2 * PI * m_f * (x / signalScale))));
	}
	else
	{
	if (checkLog)
			return (signalScale * log10(abs((m_a * (1 + m_m * sin(2 * PI * m_Fm * (x / signalScale))) * sin(2 * PI * m_f * (x / signalScale))))));
		else
			return (signalScale * (m_a * (1 + m_m * sin(2 * PI * m_Fm * (x / signalScale))) * sin(2 * PI * m_f * (x / signalScale))));
	}
	

}

double RealSignal::f_no_scale(double x)
{
	//if (checkLog)
		//return (log10(abs((m_a * (1 + m_m * sin(2 * PI * m_Fm * (x))) * sin(2 * PI * m_f * (x))))));
	//else
		return (m_a * (1 + m_m * sin(2 * PI * m_Fm * (x))) * sin(2 * PI * m_f * (x)));
}

double DFTSignal::f_DFT(double x)
{	
	size_t m = x;
	size_t N = data.size();
	double re = 0, im = 0;
	for (n = 0; n < N; n++)
	{
		if (checkXScale)
		{
			re += data[n] * cos(2 * PI * (m / DFTscale) * n / N);
			im += data[n] * sin(-2 * PI * (m / DFTscale) * n / N);
		}

		else
		{
			re += data[n] * cos(2 * PI * (m ) * n / N);
			im += data[n] * sin(-2 * PI * (m) * n / N);
		}
		
	}

	if (checkYScale)
	{
	if (checkLog)
			return (-1 *(DFTscale  * (log10(abs(sqrt(re * re + im * im))))));
		else
			return (-1 * (DFTscale * (sqrt(re * re + im * im))));
	}
	else
	{
	if (checkLog)
			return (-1 * (log10(abs(sqrt(re * re + im * im)))));
		else
			return (-1 * (sqrt(re * re + im * im)));
	}

	
}
