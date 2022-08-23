// Wall Paper (Find them, Randomize them, Return them


#pragma once
#include "Expandable.h"
//#include "IterT.h"
#include "IniFile.h"
#include "Random.h"


extern TCchar* Section;
extern TCchar* WallPaperKey;
extern TCchar* ModeKey;
extern TCchar* IndexKey;


class WallPaper {

String                path;
Random                rand;
int                   index;
bool                  mode;             // true for random, false is linear
Expandable<String, 2> data;

public:

          WallPaper();
         ~WallPaper() { }

  bool    findAll(TCchar* path) {data.clear(); find(path);  return nData() > 0;}

  void    set();

  void    getMode() {mode  = iniFile.readInt(Section, ModeKey,  1) != 0;}

private:

  void    find(TCchar* path);
  void    add(TCchar* path);
  void*   pick();

  // returns either a pointer to datum at index i in array or zero

  String* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}

  int     nData()      {return data.end();}                       // returns number of data items in array

  void    removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

//  friend typename WpIter;
  };


extern WallPaper wallPaper;
