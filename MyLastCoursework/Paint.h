#pragma once
#include "Calc.h"
#include <afxwin.h>
class Paint :  public CStatic
{
	DECLARE_DYNAMIC(Paint)

public:
	Paint();
	~Paint();

protected:
	DECLARE_MESSAGE_MAP();
	CBitmap myBitmap;
	CDC myBackDC;
	HGDIOBJ myOldBitmap;

public:
	afx_msg void OnPaint();
	bool myBgrOk;
	std::vector<Calc*> functions;
	bool hist = false;
	bool is_log = false;
	std::vector <CPoint> vec;
	void ToGraph(std::vector <CPoint> vc)
	{
		vec = vc;
	}
};

