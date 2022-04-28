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
		myBackDC.FillSolidRect(&rc, RGB(0, 100, 0));
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
		myBackDC.SelectObject(old);
		myBgrOk = true;
	}
	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &myBackDC, 0, 0, NOTSRCCOPY);

	CRgn rgn;
	CRect rgc(rc);
	rgc.DeflateRect(1000, 1000, 1000, 1000);
	rgn.CreateRectRgn(rgc.left, rgc.top, rgc.right, rgc.bottom);
	dc.SelectClipRgn(&rgn);
	CPen penG(PS_SOLID, 2, RGB(0, 206, 209));
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

