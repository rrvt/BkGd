// IntervalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IntervalDlg.h"
#include "Resource.h"


BEGIN_MESSAGE_MAP(IntervalDlg, CDialogEx)
END_MESSAGE_MAP()


// IntervalDlg dialog

IMPLEMENT_DYNAMIC(IntervalDlg, CDialogEx)

IntervalDlg::IntervalDlg(CWnd* pParent) : CDialogEx(IDD_Interval, pParent), interval(_T("")) { }


IntervalDlg::~IntervalDlg() { }


void IntervalDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_Interval, interval);
  }
