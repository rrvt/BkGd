// BkGdView.h : interface of the BkGdView class


#pragma once
#include "CScrView.h"
#include "ReportNtPd.h"


class BkGdDoc;


class BkGdView : public CScrView {

CMenu      menu;
CMenu      sub;

protected: // create from serialization only

  BkGdView() noexcept;

  DECLARE_DYNCREATE(BkGdView)

public:

  virtual ~BkGdView() { }

  virtual void       initNoteOrietn() { }
  virtual void       saveNoteOrietn() { }
  virtual void       initRptOrietn()  { };
  virtual void       saveRptOrietn()  { };
  virtual PrtrOrient getOrientation() {return prtNote.prtrOrietn;}

  virtual BOOL       PreCreateWindow(CREATESTRUCT& cs);

  virtual void       onDisplayOutput();
  virtual void       onPreparePrinting(CPrintInfo* info) {prtNote.onPreparePrinting(info);}
  virtual void       onBeginPrinting();

  virtual void       printFooter(DevStream& dev, int pageNo);
  virtual void       OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

          BkGdDoc*   GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:

  DECLARE_MESSAGE_MAP()

  afx_msg void onOptions();
  afx_msg void onRptOrietn();
  afx_msg void OnSetFocus(CWnd* pOldWnd);

  afx_msg void OnLButtonDown(  UINT nFlags, CPoint point);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

  afx_msg void OnContextMenu(CWnd* , CPoint point);
  afx_msg void onCopy();
  };


#ifndef _DEBUG  // debug version in BkGdView.cpp
inline BkGdDoc* BkGdView::GetDocument() const {return reinterpret_cast<BkGdDoc*>(m_pDocument);}
#endif

