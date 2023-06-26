// Store Report -- Template for such a report


#include "stdafx.h"
#include "StoreRpt.h"
#include "CScrView.h"
#include "Store.h"


void StoreRpt::print(CScrView& vw) {

  printing = true;

  maxLines = vw.noLinesPrPg();

  vw.disableWrap(printing);

  detNoPages(vw);

  create(vw);
  }


void StoreRpt::create(CScrView& vw) {
DSIter iter(store);
Datum* datum;
int    i;

  np.clear();   noLines = BigNmbr;                      // Skip first header

  for (i = 0, datum = iter(); datum; i++, datum = iter++) {

    if (noLines + 1 > maxLines) {

      if (i) np << nEndPage;

      noLines = header(np, printing);  np << nClrTabs << nSetTab(10);
      }

    np << datum->get() << nCrlf;   noLines += 1;
    }
  }


int StoreRpt::header(NotePad& np, bool printing) {
String s = store.date() + _T(" ") + store.time();

  np << store.name << nRight << s << nCrlf << nCrlf;   return 2;
  }


void StoreRpt::footer(Device& dev, int pageN) {

  if (pageN > maxPages) maxPages = pageN;

  dev << dRight << pageN << _T(" of ") << maxPages << dFlushFtr;
  }


