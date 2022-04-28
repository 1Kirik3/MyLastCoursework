#pragma once
#include <vector>
#define PI 3.141592653589793238463

class Calc
{
public:
	Calc();
	~Calc();
protected:
	CPoint center;
	double scale = 10;
	bool checkLog;
	double step = 1;
	bool checkCalculation = false;
	double from = 1;
	double to = 15;
public:
	std::vector<CPoint> points;

public:
	CPoint ScalingPoint(CPoint dot, double scale);
	CPoint ToRectCenter(const CRect & place);
	double GetScale(double sc) { return scale = sc; }
	void SetStep(double s) { step = s;}
	void SetLog(bool b) { checkLog = b; }
	void IsCalculated() { checkCalculation = true; }
	virtual const std::vector<CPoint>& get_points();

protected:
	virtual void calculate();
	
};


class RealSignal : public Calc 
{
protected:
	double f_ = 0.2 ;
	double m = 0.5;
	double Fm = 0.3 ;
	double a = 1;

public:
	std::vector<double> data;
	

protected:
	

public:
	double f(double x);
	const std::vector<double>& get_data();
	virtual void calculate();

};


class DFTSignal : public RealSignal 
{
public:
	std::vector <CPoint> DFTGraph;
};

