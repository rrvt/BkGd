



#include "framework.h"
#include "WallPaper.h"
#include "FileName.h"
#include "FileSrch.h"


TCchar* Section      = _T("Global");
TCchar* WallPaperKey = _T("WallPaperPath");
TCchar* IntervalKey  = _T("Interval");
TCchar* CurrentKey   = _T("CurrentPath");
TCchar* ModeKey      = _T("Mode");
TCchar* IndexKey     = _T("Index");


IniFile   iniFile;
WallPaper wallPaper;


WallPaper::WallPaper() {
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

  if (ext.lowerCase() == _T("png"))  {String s = path; data += s; return;}
  if (ext.lowerCase() == _T("jpg"))  {String s = path; data += s; return;}
  if (ext.lowerCase() == _T("jpeg")) {String s = path; data += s; return;}
  if (ext.lowerCase() == _T("bmp"))  {String s = path; data += s; return;}
  if (ext.lowerCase() == _T("tif"))  {String s = path; data += s; return;}

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

  index = mode ? int(rand.next() * float(nData())) : (index + 1) % nData();
  tc = data[index];

  iniFile.writeString(Section, CurrentKey, tc);

  if (!mode) iniFile.writeInt(   Section, IndexKey,   index);

  return (void*) tc;
  }

