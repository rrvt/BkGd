// BkGdView.cpp : implementation of the BkGdView class


#include "stdafx.h"
#include "BkGdView.h"
#include "BkGd.h"
#include "BkGdDoc.h"
#include "ClipLine.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "Resources.h"


// BkGdView

IMPLEMENT_DYNCREATE(BkGdView, CScrView)

BEGIN_MESSAGE_MAP(BkGdView, CScrView)
  ON_COMMAND(ID_Options, &onOptions)

  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONDBLCLK()

  ON_WM_CONTEXTMENU()
  ON_COMMAND(ID_Pup0, &onCopy)
END_MESSAGE_MAP()


BkGdView::BkGdView() noexcept : dspNote( dMgr.getNotePad()), prtNote( pMgr.getNotePad()) {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);

  sub.LoadMenu(ID_PopupMenu);
  menu.CreatePopupMenu();
  menu.AppendMenu(MF_POPUP, (UINT_PTR) sub.GetSafeHmenu(), _T(""));        //

  sub.Detach();
  }


BOOL BkGdView::PreCreateWindow(CREATESTRUCT& cs) {

  return CScrView::PreCreateWindow(cs);
  }


void BkGdView::onOptions() {
OptionsDlg dlg;

  if (printer.name.isEmpty()) printer.load(0);

  if (dlg.DoModal() == IDOK) pMgr.setFontScale(printer.scale);
  }



// Perpare output (i.e. report) then start the output with the call to SCrView

void BkGdView::onBeginPrinting() {prtNote.onBeginPrinting(*this);}


void BkGdView::onDisplayOutput() {dspNote.display(*this);}


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void BkGdView::printFooter(DevBase& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.prtFooter(dev, pageNo);  break;
    }
  }


void BkGdView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  CScrView::OnEndPrinting(pDC, pInfo);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    }
  }


void BkGdView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    }
  }


void BkGdView::OnLButtonDown(UINT nFlags, CPoint point)
                        {clipLine.set(point);   invalidate();   CScrView::OnLButtonDown(nFlags, point);}


void BkGdView::OnLButtonDblClk(UINT nFlags, CPoint point)
  {clipLine.set(point);   RedrawWindow();   clipLine.load();   CScrView::OnLButtonDblClk(nFlags, point);}


void BkGdView::OnContextMenu(CWnd* /*pWnd*/, CPoint point) {
CRect  rect;
CMenu* popup;
CWnd*  pWndPopupOwner = this;

  if (point.x == -1 && point.y == -1)
            {GetClientRect(rect);  ClientToScreen(rect);  point = rect.TopLeft();  point.Offset(5, 5);}

  popup = menu.GetSubMenu(0);   if (!popup) return;

  while (pWndPopupOwner->GetStyle() & WS_CHILD) pWndPopupOwner = pWndPopupOwner->GetParent();

  popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
  }


void BkGdView::onCopy() {clipLine.load();  invalidate();}


// BkGdView diagnostics

#ifdef _DEBUG

void BkGdView::AssertValid() const {CScrollView::AssertValid();}

void BkGdView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
BkGdDoc* BkGdView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(BkGdDoc))); return (BkGdDoc*)m_pDocument;}

#endif //_DEBUG
