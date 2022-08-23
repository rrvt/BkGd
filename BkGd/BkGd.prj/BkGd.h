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

  afx_msg void OnFilePrintSetup();
  afx_msg void OnAppAbout();
  afx_msg void OnHelp();
  };


extern BkGd theApp;

inline void             invalidate() {theApp.invalidate();}
inline BkGdDoc*  doc()        {return theApp.doc();}
inline BkGdView* view()       {return theApp.view();}
inline MainFrame*       mainFrm()    {return theApp.mainFrm();}
inline ToolBar&         getToolBar() {return mainFrm()->getToolBar();}

