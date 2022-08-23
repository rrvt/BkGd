// BkGdDoc.h : interface of the BkGdDoc class


#pragma once
#include "CDoc.h"
#include "Resource.h"


enum DataSource {NotePadSrc};


class BkGdDoc : public CDoc {

DECLARE_DYNCREATE(BkGdDoc)

HWND        bkGdEx;
String      path;
int         interval;

PathDlgDsc  pathDlgDsc;

DataSource  dataSource;

protected: // create from serialization only


                     BkGdDoc() noexcept;

public:

  virtual           ~BkGdDoc();

          void       showCurrent();

          DataSource dataSrc() {return dataSource;}
          void       display(DataSource ds);

  virtual void       serialize(Archive& ar);

private:

  void getRootPath(String& path);
  void showRootPath(TCchar* path);

  void getCurrent();

  int  getInterval();

  bool getMode();
  void showMode(bool mode);

  void sendCommand(int cmd = IDM_Initialize);
  HWND findBkGdEx(bool restart = true);
  bool startBkGdEx();

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void onSelectRootPath();
  afx_msg void onSetInterval();
  afx_msg void onGetCurrent();
  afx_msg void onSetMode();
  afx_msg void onStopWallPaper();

  afx_msg void OnOptions();
  };


