// BkGdView.h : interface of the BkGdView class


#pragma once
#include "CScrView.h"
#include "NotePadRpt.h"


class BkGdDoc;


class BkGdView : public CScrView {

NotePadRpt dspNote;
NotePadRpt prtNote;

CMenu      menu;
CMenu      sub;

protected: // create from serialization only

  BkGdView() noexcept;

  DECLARE_DYNCREATE(BkGdView)

public:

  virtual ~BkGdView() { }

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void onPrepareOutput(bool printing);

  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void printFooter(Device& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  BkGdDoc* GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:

  DECLARE_MESSAGE_MAP()

  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnLButtonDown(  UINT nFlags, CPoint point);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

  afx_msg void OnContextMenu(CWnd* , CPoint point);
  afx_msg void onCopy();
  };


#ifndef _DEBUG  // debug version in BkGdView.cpp
inline BkGdDoc* BkGdView::GetDocument() const
   { return reinterpret_cast<BkGdDoc*>(m_pDocument); }
#endif




#ifdef Examples
#include "StoreRpt.h"
#endif
#ifdef Examples
StoreRpt   dspStore;
StoreRpt   prtStore;
#endif

