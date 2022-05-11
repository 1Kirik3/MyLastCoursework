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

	 if (!myBgrOk)
	{
		if (NULL == myBackDC.GetSafeHdc())
		{
			myBackDC.CreateCompatibleDC(&dc);
			myBitmap.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
			myOldBitmap = myBackDC.SelectObject(myBitmap);
		}
		myBackDC.FillSolidRect(&rc, RGB(backUserColor.red, backUserColor.green , backUserColor.blue));
		CPen pen(PS_SOLID, 2, RGB(130, 145, 80));
		HGDIOBJ  old = myBackDC.SelectObject(pen);
		CRect rcd = rc;
		rcd.DeflateRect(8, 8);
		CPoint cP = rcd.CenterPoint();
		//x ax
		myBackDC.MoveTo(rcd.left, cP.y);
		myBackDC.LineTo(rcd.right, cP.y);
		//y ax
		myBackDC.MoveTo(cP.x, rcd.top);
		myBackDC.LineTo(cP.x, rcd.bottom);

		CFont fn;
		fn.CreateFontW(16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Times"));
		HGDIOBJ pof = myBackDC.SelectObject(&fn);
		myBackDC.SetBkMode(TRANSPARENT);
		myBackDC.SetTextAlign(TA_CENTER | TA_TOP);
		myBackDC.SetTextColor(RGB(200, 255, 200));
		
		CPoint axisX;
		axisX.x = 1;
		axisX.y = 0;
		axisX.Offset(rcd.right, rcd.CenterPoint().y);
		myBackDC.MoveTo(axisX);
		axisX.Offset(0, 8);
		myBackDC.LineTo(axisX);
		axisX.Offset(0, -16);
		myBackDC.LineTo(axisX);
		axisX.Offset(0, 8);
		myBackDC.TextOutW(axisX.x, axisX.y, _T("x"));

		CPoint axisY;
		axisY.x = 0;
		axisY.y = 1;
		axisY.Offset(rcd.CenterPoint().x, rcd.top);
		myBackDC.MoveTo(axisY);
		axisY.Offset(-8, 0);
		myBackDC.LineTo(axisY);
		axisY.Offset(16, 0);
		myBackDC.LineTo(axisY);
		axisY.Offset(8, 0);
		myBackDC.TextOutW(axisY.x, axisY.y, _T("y"));


		




		myBackDC.SelectObject(pof);
		myBackDC.SelectObject(old);
		myBgrOk = true;
	}
	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &myBackDC, 0, 0, NOTSRCCOPY);

	CRgn rgn;
	rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);
	dc.SelectClipRgn(&rgn);
	rc.DeflateRect(500, 200, 500, 200);
	
	
	CPen penG(PS_SOLID, 2, RGB(graphUserColor.red, graphUserColor.green, graphUserColor.blue));
	HGDIOBJ  old = dc.SelectObject(penG);
	if (vec.size())
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

