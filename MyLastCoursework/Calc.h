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
	double signalScale = 10;
	double DFTscale=10;
public:
	std::vector<CPoint> points;

public:
	CPoint ScalingPoint(CPoint dot, double scale);
	CPoint ToRectCenter(const CRect & place);
	
};


class RealSignal : public Calc 
{
protected:
	
	double m_f;
	double m_m;
	double m_Fm;
	double m_a=1;

public:
	bool checkLog;
	bool checkXScale;
	bool checkYScale;
	std::vector<double> data;
	

protected:
	

public:
	void SetSignalScale(double sc) { signalScale = sc; }
	void SetParametrs(float m, float Fm, float f) { m_f = f; m_m = m; m_Fm = Fm;}
	double f(double x);
	double f_no_scale(double x);

};


class DFTSignal : public RealSignal 
{
public:
	std::vector <CPoint> DFTGraph;

public: 
	void SetDFTScale(double sc) { DFTscale = sc; }
	double f_DFT(double x);
	size_t n;
};

