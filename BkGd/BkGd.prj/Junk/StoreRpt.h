// Store Report -- Template for such a report


#pragma once
#include "ReportBase.h"


class StoreRpt : public ReportBase {

public:

  StoreRpt(NotePad& notePad) : ReportBase(notePad) { }
 ~StoreRpt() { }

//  void StoreRpt::display(CScrView& vw);
  void print(CScrView& vw);

//  void detWraps(  CScrView& vw);               // Wrap each entity in the report body

//  void detNoPages(CScrView& vw);               // Performs a dummy printer output to determine the
                                                  // number of pages that will be produced
  void footer(Device& dev, int pageNo);          // Output page Footer to NotePad

private:

  StoreRpt() : ReportBase(*(NotePad*)0) { }

  void create(CScrView& vw);
  int  header(NotePad& np, bool printing);
  };

