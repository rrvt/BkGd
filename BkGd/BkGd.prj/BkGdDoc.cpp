 // BkGdDoc.cpp : implementation of the BkGdDoc class


#include "stdafx.h"
#include "BkGdDoc.h"
#include "BkGd.h"
#include "BkGdView.h"
#include "ClipBoard.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "IntervalDlg.h"
#include "NotePad.h"
#include "ResourceExtra.h"
#include "MyToolBar.h"


static TCchar* BkGdTitle    = _T("BkGdEx -- MessageHandler");
       TCchar* Section      = _T("Global");
static TCchar* WallPaperKey = _T("WallPaperPath");
static TCchar* IntervalKey  = _T("Interval");
       TCchar* EnabledKey   = _T("Enabled");
static TCchar* ModeKey      = _T("Mode");

static TCchar* IndexKey     = _T("Index");
static TCchar* CurrentKey   = _T("CurrentPath");
static TCchar* LastKey      = _T("LastPath");
static TCchar* CountKey     = _T("Count");
static TCchar* MaxHitsKey   = _T("MaxHits");


// BkGdDoc

IMPLEMENT_DYNCREATE(BkGdDoc, CDoc)

BEGIN_MESSAGE_MAP(BkGdDoc, CDoc)

  ON_COMMAND(ID_GetCurrent,     &onGetCurrent)
  ON_COMMAND(ID_Next,           &onNext)
  ON_COMMAND(ID_SelectRootPath, &onSelectRootPath)
  ON_COMMAND(ID_SetInterval,    &onSetInterval)
  ON_COMMAND(ID_SetMode,        &onSetMode)
  ON_COMMAND(ID_StopWallPaper,  &onStopWallPaper)
  ON_COMMAND(ID_EnableBkGdEx,   &OnEnableBkGdEx)
  ON_COMMAND(ID_DisableBkGdEx,  &onDisableBkGdEx)
  ON_COMMAND(ID_EDIT_COPY,      &onEditCopy)

END_MESSAGE_MAP()


// BkGdDoc construction/destruction

BkGdDoc::BkGdDoc() noexcept : bkGdEx(0), dataSource(NotePadSrc) {
  enabled = iniFile.readInt(Section, EnabledKey, 0);
  }


BkGdDoc::~BkGdDoc() { }


void BkGdDoc::onGetCurrent() {notePad.clear();   showCurrent();   display();}


void BkGdDoc::onNext() {notePad.clear();   sendCommand(IDM_Next);  showCurrent();   display();}


void BkGdDoc::onSelectRootPath() {

  getRootPath(path);

  if (getDirPathDlg(_T("Wallpaper Root Path"), path)) {iniFile.writeString(Section, WallPaperKey, path);}

  notePad.clear();   sendCommand(IDM_Initialize);   showCurrent();   display();
  }


void BkGdDoc::onSetInterval() {
int         interval;
IntervalDlg dlg;
uint        pos;

  interval = getInterval();

  dlg.interval = interval;

  if (dlg.DoModal() != IDOK) return;

  interval = dlg.interval.stoi(pos);

  iniFile.writeInt(Section, IntervalKey, interval);

  notePad.clear();   sendCommand(IDM_Next);   showCurrent();   display();
  }


void BkGdDoc::onSetMode() {
bool mode = getMode();

  mode = mode ? false : true;

  iniFile.writeInt(Section, ModeKey, mode);

  notePad.clear();   sendCommand(IDM_Mode);   showCurrent();   display();
  }


void BkGdDoc::sendCommand(int cmd) {
HWND hwnd = findBkGdEx();  if (!hwnd) return;
int  lastErr;

  if (!enabled) notePad << _T("Wallpaper changer is not enabled") << nCrlf;

  if (PostMessage(hwnd, WM_COMMAND, cmd, 0)) return;

  lastErr = GetLastError();   notePad << _T("Last Error = ") << lastErr << nCrlf;
  }


void BkGdDoc::showCurrent() {
String pth;
int    intvl;

  getRootPath(pth);   showRootPath(pth);

  intvl = getInterval();  notePad << _T("Change interval is ") << getInterval() << _T(" Min") << nCrlf;

  showMode(getMode());

  if (!enabled) notePad << _T("Wallpaper changer is not enabled") << nCrlf;

  getCurrent();
  }


void BkGdDoc::getRootPath(String& path) {iniFile.readString(Section, WallPaperKey, path);}


void BkGdDoc::showRootPath(TCchar* path) {
int count;

  notePad << _T("Wallpaper Files Root Path:  ") << path << nCrlf;

  iniFile.read(Section, CountKey, count);
  notePad << _T("Number of Wallpaper Files = ") << count << nCrlf;
  }


int BkGdDoc::getInterval() {return iniFile.readInt(Section, IntervalKey, 1);}


bool BkGdDoc::getMode() {return iniFile.readInt(Section, ModeKey,  1) != 0;}


void BkGdDoc::showMode(bool mode) {
  if (mode) notePad << _T("Wallpaper is Randomly Selected");
  else      notePad << _T("Wallpaper is Lineraly Selected");

  notePad << nCrlf;
  }


void BkGdDoc::getCurrent() {
String    r;
String    s;
String    t;
int       index;
int       maxHits;
ClipBoard clipBoard;

  iniFile.readString(Section, CurrentKey, r);
  iniFile.readString(Section, LastKey,    s);

  t = r + _T("\r\n") + s;   clipBoard.load(t);

  notePad << _T("Previous Wallpaper Path (and in the Clip Board):") << nTab << s << nCrlf;
  notePad << _T("Current Wallpaper Path (and in the Clip Board):") << nTab << r << nCrlf;

  iniFile.read(Section, IndexKey, index);
  notePad << _T("Current Index = ") << index << nCrlf;

  iniFile.read(Section, MaxHitsKey, maxHits);
  if (maxHits) {notePad << _T("Max No of Hits = ") << maxHits << nCrlf;}
  }


void BkGdDoc::onEditCopy() {clipLine.load();}


void BkGdDoc::OnEnableBkGdEx()  {setEnabled(true);   findBkGdEx();}
void BkGdDoc::onDisableBkGdEx() {onStopWallPaper();  setEnabled(false);}


void BkGdDoc::onStopWallPaper() {
HWND hwnd = findBkGdEx(false);   if (!hwnd) return;
int  lastErr;

  if (PostMessage(hwnd, WM_COMMAND, IDM_EXIT, 0)) {
    bkGdEx = 0;   notePad << _T("Wallpaper Changer shutting down") << nCrlf;  display();

    return;
    }

  lastErr = GetLastError();   notePad << _T("Last Error = ") << lastErr << nCrlf;   display();
  }


HWND BkGdDoc::findBkGdEx(bool restart) {
Tchar  buf[UNLEN+1];
DWORD  len = noElements(buf);
String title;

  if (!enabled) return 0;

  if (GetUserName(buf, &len)) {title = buf; title += _T(' ');}   title += BkGdTitle;

  for (int i = 0; !bkGdEx && i < 2; i++)
           {bkGdEx = FindWindow(0, title);   if (!bkGdEx && restart && !startBkGdEx()) break;}

  if (!bkGdEx) {notePad << _T("Wallpaper Changer is not running!") << nCrlf;   display();}

  return bkGdEx;
  }


bool BkGdDoc::startBkGdEx() {
String              cmdName = theApp.myPath + _T("BkGdEx.exe");
STARTUPINFO         startupInfo;
PROCESS_INFORMATION processInfo;

  GetStartupInfo(&startupInfo);

  if (!CreateProcess(cmdName, 0, 0, 0, false, NORMAL_PRIORITY_CLASS, 0, 0, &startupInfo, &processInfo))
      {notePad << _T("Unable to create Wallpaper process") << nCrlf; display(); return false;}

  return !WaitForInputIdle(processInfo.hProcess, INFINITE);
  }


void BkGdDoc::display(DataSource ds) {dataSource = ds; invalidate();}


// UglyDoc serialization

void BkGdDoc::serialize(Archive& ar) {

  if (ar.isStoring())
    switch(dataSource) {
      case NotePadSrc : ar << notePad; return;
      default         : return;
      }

  else
    switch(dataSource) {
      case NotePadSrc :
      default         : return;
      }
  }


// BkGdDoc diagnostics

#ifdef _DEBUG
void BkGdDoc::AssertValid()          const {CDocument::AssertValid();}
void BkGdDoc::Dump(CDumpContext& dc) const {CDocument::Dump(dc);}
#endif //_DEBUG





#if 1
#else
  iniFile.readString(Section, WallPaperKey, path);
#endif
#if 1
#else
  notePad << _T("Wallpaper Files Root Path: ") << path << nCrlf;
#endif


#if 0
void BkGdDoc::OnContextMenu(CWnd* , CPoint point) {
CRect  rect;
CMenu* popup;
CWnd*  pWndPopupOwner = this;

  if (point.x == -1 && point.y == -1)
            {GetClientRect(rect);  ClientToScreen(rect);  point = rect.TopLeft();  point.Offset(5, 5);}

  popup = menu.GetSubMenu(0);   if (!popup) return;

  while (pWndPopupOwner->GetStyle() & WS_CHILD) pWndPopupOwner = pWndPopupOwner->GetParent();

  popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
  }
#endif

