// Sample Data Store


#include "stdafx.h"
#include "Store.h"
#include "NotePad.h"
#include "qsort.h"


const int TabVal = 5;


Store store;                                        // Global since all classes need access



void Store::setName(String& s) {name = s; dt.getToday();}


int Store::missionNo() {
  if (!mssnNo) {Date d; d.getToday();   CTimeSpan t = d - dt;  mssnNo = t.GetSeconds() % 60;}

  return mssnNo;
  }


// Load is called from serialize in the Document class
// The basic idea is that the method reads some chunk from the file (Archive is a fileio surrogate)

void Store::load(Archive& ar) {
String s;

  data.clear();

  while (ar.read(s)) add(s);
  }


void Store::store(Archive& ar) {

  }


void Store::add(String& s) {data.nextData().add(s);}




// Parse the data into the record

void Datum::add(String& stg) {
int pos = stg.find('\n');

  s = pos >= 0 ? stg.substr(0, pos) : stg;
  }


void Store::sort() {qsort(&data[0], &data[data.end()-1]);}




int Datum::wrap(Device& dev, CDC* dc) {
int  chWidth = dev.flChWidth();

  dev << dCR << dClrTabs << dSetTab(TabVal) << dTab;    // Return to left margin (dCR), clear Tabs and
                                                        // tab to position desired for wrap
    wrp.initialize(dc, dev.remaining(), dev.maxWidth(), false);

  dev<< dCR << dClrTabs;                                // return to left margin and clear tabs

  return wrp(s);                                        // wrap string
  }



int Datum::display() {
WrapIter  iter(wrp);
WrapData* wd;
int       i;

  notePad << nClrTabs << nSetTab(TabVal) << nTab;       // The tab is set to the same value as in wrap

  for (wd = iter(), i = 0; wd; wd = iter++, i++) {
    if (i) notePad << nTab;

    notePad << wd->line << nCrlf;
    }

  return i;
  }


