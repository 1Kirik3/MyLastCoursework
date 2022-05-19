#include "pch.h"
#include "Paint.h"
#include "Calc.h"
#include "MyLastCoursework.h"
#include "MyLastCourseworkDlg.h"
#include "vector"



//Paint


IMPLEMENT_DYNAMIC(Paint, CStatic)


Paint::Paint():myBgrOk(false)
{

}

Paint::~Paint()
{
	myBackDC.SelectObject(myOldBitmap);
}


BEGIN_MESSAGE_MAP(Paint, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void Paint::OnPaint() 
{
	CPaintDC dc(this);
	CRect rc;
	GetClientRect(rc);
	CMyLastCourseworkDlg *pWnd = (CMyLastCourseworkDlg *) AfxGetMainWnd();

	 if (!myBgrOk)																	//Проверка для единаразового отрисовывания фона
	{
		if (NULL == myBackDC.GetSafeHdc())
		{
			myBackDC.CreateCompatibleDC(&dc);
			myBitmap.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
			myOldBitmap = myBackDC.SelectObject(myBitmap);
		}
		myBackDC.FillSolidRect(&rc, RGB(backUserColor.red, backUserColor.green , backUserColor.blue));	//Заливка фона
		CPen pen(PS_SOLID, 2, RGB(255, 255, 255));
		HGDIOBJ  old = myBackDC.SelectObject(pen);														//Выбор ручки для фона
		CRect rcd = rc;																					//Прямоугольник для засечек
		rcd.DeflateRect(8, 8);
		CPoint cP = rcd.CenterPoint();
																										//x axis
		myBackDC.MoveTo(rcd.left, cP.y);
		myBackDC.LineTo(rcd.right, cP.y);
																										//y axis
		myBackDC.MoveTo(rcd.left, rcd.top);
		myBackDC.LineTo(rcd.left, rcd.bottom);

		CFont fn;																						//Шрифт для направления осей
		fn.CreateFontW(16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Times"));
		HGDIOBJ pof = myBackDC.SelectObject(&fn);
		myBackDC.SetBkMode(TRANSPARENT);
		myBackDC.SetTextAlign(TA_CENTER | TA_TOP);
		myBackDC.SetTextColor(RGB(255, 255, 255));
		
		//Ось x
		CPoint axisX;
		axisX.x = 0;
		axisX.y = 0;
		axisX.Offset(rcd.right - 5, rcd.CenterPoint().y + 5);
		myBackDC.MoveTo(axisX.x , rcd.CenterPoint().y + 5);
		axisX.Offset(5, -5);
		myBackDC.LineTo(axisX);
		axisX.Offset(-5, -5);
		myBackDC.LineTo(axisX);
		axisX.Offset(0, 20);
		myBackDC.TextOutW(axisX.x, axisX.y + 10, _T("t"));

		//Ось y
		CPoint axisY;
		axisY.x = 0;
		axisY.y = 0;
		axisY.Offset(rcd.left + 5, rcd.top + 5);
		myBackDC.MoveTo(axisY);
		axisY.Offset(-5, -5);
		myBackDC.LineTo(axisY);
		axisY.Offset(-5, 5);
		myBackDC.LineTo(axisY);
		axisY.Offset(20, 0);
		myBackDC.TextOutW(axisY.x, axisY.y - 10, _T("y"));


		
		myBackDC.SelectObject(pof);
		myBackDC.SelectObject(old);
		myBgrOk = true;
	}

	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &myBackDC, 0, 0, NOTSRCCOPY);

	CRgn rgn;												//Ограничения для графика
	rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);
	dc.SelectClipRgn(&rgn);
	rc.DeflateRect(900, 200);
	
	
	CPen penG(PS_SOLID, 2, RGB(graphUserColor.red, graphUserColor.green, graphUserColor.blue));
	HGDIOBJ  old = dc.SelectObject(penG);
	if (vec.size())											//Рисовании по точкам внутри вектора
	{
		auto it = vec.begin();
		dc.MoveTo(*it);
		for (; it != vec.end(); it++)
		{
			dc.LineTo(*it); 
		}
			
	}
	dc.SelectObject(old);

}

