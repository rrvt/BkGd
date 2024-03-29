// BkGd.cpp : Defines the class behaviors for the application.


#include "stdafx.h"
#include "BkGd.h"
#include "AboutDlg.h"
#include "BkGdDoc.h"
#include "BkGdView.h"
#include "FileName.h"
#include "IniFile.h"
#include "MainFrame.h"
#include "NotePad.h"
#include "ResourceExtra.h"


BkGd    theApp;                         // The one and only BkGd object
IniFile iniFile;


// BkGd

BEGIN_MESSAGE_MAP(BkGd, CWinAppEx)
  ON_COMMAND(ID_Help,      &onHelp)
  ON_COMMAND(ID_App_About, &onAppAbout)
END_MESSAGE_MAP()


// BkGd initialization

BOOL BkGd::InitInstance() {

  CWinAppEx::InitInstance();

  myPath = getPath(m_pszHelpFilePath);

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  notePad.clear();

  SetRegistryKey(appID);

  LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

  // Register the application's document templates.  Document templates
  // serve as the connection between documents, frame windows and views

  CSingleDocTemplate* pDocTemplate;

  pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,
    RUNTIME_CLASS(BkGdDoc),
    RUNTIME_CLASS(MainFrame),       // main SDI frame window
    RUNTIME_CLASS(BkGdView));

  if (!pDocTemplate) return FALSE;

  AddDocTemplate(pDocTemplate);

//  EnableShellOpen(); RegisterShellFileTypes(TRUE);       // Enable DDE Execute open

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo;   ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  setAppName(_T("Back Ground")); setTitle(_T("Main"));

  view()->setFont(_T("Arial"), 12.0);

  doc()->onGetCurrent();

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }



int BkGd::ExitInstance() {

#ifdef DebugMemoryLeaks
  _CrtDumpMemoryLeaks();
#endif

  return CApp::ExitInstance();
  }


void BkGd::onHelp() {
String topic = m_pszHelpFilePath; topic += _T(">Introduction");

  ::HtmlHelp(m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 0);
  }


void BkGd::onAppAbout() {AboutDlg aboutDlg; aboutDlg.DoModal();}

