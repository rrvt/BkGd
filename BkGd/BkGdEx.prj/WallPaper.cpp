// Wall Paper (Find them, Randomize them, Return them


#include "framework.h"
#include "WallPaper.h"
#include "FileName.h"
#include "FileSrch.h"


TCchar* Section      = _T("Global");
TCchar* WallPaperKey = _T("WallPaperPath");
TCchar* IntervalKey  = _T("Interval");
TCchar* EnabledKey   = _T("Enabled");

TCchar* CurrentKey   = _T("CurrentPath");
TCchar* LastKey      = _T("LastPath");
TCchar* ModeKey      = _T("Mode");
TCchar* IndexKey     = _T("Index");
TCchar* DebugKey     = _T("Debug");


IniFile   iniFile;
WallPaper wallPaper;


void WallPaper::initialize() {

  if (!iniFile.readString(Section, WallPaperKey, path)) return;

  index = iniFile.readInt(Section, IndexKey, 0);

  getMode();
  }


void WallPaper::find(TCchar* path) {
Expandable<String, 2> subDir;
FileSrch              srch;
String                sub;
String                file;
int                   i;
int                   n;

  if (!path || _tcslen(path) == 0) return;

  if (srch.findAllSubDirs(path)) while (srch.getName(sub)) subDir = sub;

  if (srch.findAllFiles(path)) while (srch.getName(file)) add(file);

  for (i = 0, n = subDir.end(); i < n; i++) find(subDir[i]);

  subDir.clear();
  }


void WallPaper::add(TCchar* path) {
String ext = getExtension(path);

  if (ext.lowerCase() == _T("jpg"))  {Item item; item.s = path; data += item; return;}
  if (ext.lowerCase() == _T("jpeg")) {Item item; item.s = path; data += item; return;}
  if (ext.lowerCase() == _T("bmp"))  {Item item; item.s = path; data += item; return;}
  if (ext.lowerCase() == _T("tif"))  {Item item; item.s = path; data += item; return;}

  if (ext.lowerCase() == _T("crw"))  return;
  if (ext.lowerCase() == _T("thm"))  return;
  if (ext.lowerCase() == _T("pdf"))  return;
  if (ext.lowerCase() == _T("thm"))  return;
  if (ext.lowerCase() == _T("avi"))  return;
  if (ext.lowerCase() == _T("info")) return;
  if (ext.lowerCase() == _T("jbf"))  return;
  if (ext.lowerCase() == _T("mp4"))  return;
  if (ext.lowerCase() == _T("doc"))  return;
  if (ext.lowerCase() == _T("db"))   return;

  ToAnsi pth(path);   cout << pth() << endl;
  }


void WallPaper::set() {SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, pick(), SPIF_UPDATEINIFILE);}



void* WallPaper::pick() {
TCchar* tc;
int     n = nData();
double  x = rand.next() * double(n) + 0.5;
int     i = int(x);
String  s;

  index = mode ? i : index + 1;

  index %=  n;

  for (i = 0; data[index].hit && i < n; i++)
    index = (index + 1) % n;

  if (i >= n)
    for (i = 0; i < n; i++) data[i].hit = false;

  Item& item = data[index];

  iniFile.readString(Section, CurrentKey, s);    iniFile.writeString(Section, LastKey, s);

  tc = item.s;   item.hit = true;   iniFile.writeString(Section, CurrentKey, tc);

  if (!mode) iniFile.writeInt(   Section, IndexKey,   index);

  return (void*) tc;
  }



