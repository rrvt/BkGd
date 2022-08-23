// IntervalDlg dialog


#pragma once
//#include "afxdialogex.h"


class IntervalDlg : public CDialogEx {

  DECLARE_DYNAMIC(IntervalDlg)

public:
Cstring interval;

           IntervalDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~IntervalDlg();

// Dialog Data

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_Interval };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };
