// BkGd.h : main header file for the BkGd application

#pragma once
#include "CApp.h"
#include "MainFrame.h"


class BkGdDoc;
class BkGdView;


// BkGd:
// See BkGd.cpp for the implementation of this class

class BkGd : public CApp {

public:
String myPath;

               BkGd() noexcept : CApp(this) { }

  virtual BOOL InitInstance();
  virtual int  ExitInstance();

          BkGdDoc*  doc()  {return (BkGdDoc*)  CApp::getDoc();}
          BkGdView* view() {return (BkGdView*) CApp::getView();}
          MainFrame*       mainFrm() {return (MainFrame*) m_pMainWnd;}

  DECLARE_MESSAGE_MAP()

  afx_msg void onAppAbout();
  afx_msg void onHelp();
  };


extern BkGd theApp;

inline void       invalidate() {theApp.invalidate();}
inline BkGdDoc*   doc()        {return theApp.doc();}
inline BkGdView*  view()       {return theApp.view();}
inline MainFrame* mainFrm()    {return theApp.mainFrm();}
inline MyToolBar& getToolBar() {return mainFrm()->getToolBar();}

