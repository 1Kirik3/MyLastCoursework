#include "pch.h"
#include "Calc.h"
#include <cmath>

Calc::Calc() 
{

}

Calc::~Calc()
{

}


CPoint Calc::ToRectCenter(const CRect& place)	
{
	center = place.CenterPoint();
	return center;
}


double RealSignal::f(double x)				//Функция для подсчёта сигнала										
{
	if ((checkYScale == 1) && (checkXScale == 0))		//Проверка на масштабирование по Y
	{
		if (checkLog)									//Проверка на логарифмический масштаб
			return (signalScale * log10(abs((m_a * (1 + m_m * sin(2 * PI * m_Fm * (x))) * sin(2 * PI * m_f * (x))))));
		else
			return (signalScale * (m_a * (1 + m_m * sin(2 * PI * m_Fm * (x))) * sin(2 * PI * m_f * (x))));
	}

	else if ((checkYScale == 0) && (checkXScale == 1))	//Проверка на масштабирование по X
	{
		if (checkLog)									//Проверка на логарифмический масштаб
			return (log10(abs((m_a * (1 + m_m * sin(2 * PI * m_Fm * (x / signalScale))) * sin(2 * PI * m_f * (x / signalScale))))));
		else
			return ((m_a * (1 + m_m * sin(2 * PI * m_Fm * (x / signalScale))) * sin(2 * PI * m_f * (x / signalScale))));
	}
	else if (((checkYScale == 0) && (checkXScale == 0))) // Отсутствие масштабирования 
	{
	if (checkLog)										//Проверка на логарифмический масштаб
			return (log10(abs((m_a * (1 + m_m * sin(2 * PI * m_Fm * (x))) * sin(2 * PI * m_f * (x))))));
		else
			return ((m_a * (1 + m_m * sin(2 * PI * m_Fm * (x))) * sin(2 * PI * m_f * (x))));
	}

	else                                                    // Масштабирование по обеям осям
	{
		if (checkLog)										//Проверка на логарифмический масштаб
			return (signalScale * log10(abs((m_a * (1 + m_m * sin(2 * PI * m_Fm * (x / signalScale))) * sin(2 * PI * m_f * (x / signalScale))))));
		else
			return (signalScale * (m_a * (1 + m_m * sin(2 * PI * m_Fm * (x / signalScale))) * sin(2 * PI * m_f * (x / signalScale))));
	}


}

double RealSignal::f_no_checkBox(double x)						//Для передачи значений в ДПФ 
{
	return (m_a * (1. + m_m * sin(2. * PI * m_Fm * (x))) * sin(2. * PI * m_f * (x)));
}

double DFTSignal::f_DFT(double x)
{	
	size_t m = x;
	size_t N = data.size();
	double re = 0, im = 0;
	for (size_t n = 0; n < N; n++)										//Суммирование вещественной и мнимой части
	{
		if (checkXScale)												//Проверка на масштабирование по X			
		{
			re += data[n] * cos(2. * PI * (m / DFTscale) * n / N);
			im += data[n] * sin(-2. * PI * (m / DFTscale) * n / N);
		}

		else
		{
			re += data[n] * cos(2. * PI * (m ) * n / N);
			im += data[n] * sin(-2. * PI * (m) * n / N);
		}
		
	}

	if (checkYScale)													//Проверка на логарифмический масштаб
	{
	if (checkLog)														//Проверка на логарифмический масштаб
			return (-1. * (DFTscale  * (log10(abs(sqrt(re * re + im * im))))));
		else
			return (-1. * (DFTscale * (sqrt(re * re + im * im))));
	}
	else
	{
	if (checkLog)
			return (-1. * (log10(abs(sqrt(re * re + im * im)))));
		else
			return (-1. * (sqrt(re * re + im * im)));
	}

	
}
