// Wall Paper (Find them, Randomize them, Return them


#pragma once
#include "Expandable.h"
#include "IniFile.h"
#include "Random.h"


extern TCchar* Section;
extern TCchar* WallPaperKey;
extern TCchar* ModeKey;
extern TCchar* IndexKey;
extern TCchar* DebugKey;


struct Item {
String s;
bool   hit;

  Item() : hit(false) { }
 ~Item() { }
  };


class WallPaper {

String                 path;
Random                 rand;
int                    index;
bool                   mode;             // true for random, false is linear
Expandable<Item, 1024> data;

public:

          WallPaper() : rand(), index(0), mode(false) { }
         ~WallPaper() { }

  void    initialize();

  bool    findAll(TCchar* path) {data.clear(); find(path);  return nData() > 0;}

  void    set();

  void    getMode() {mode  = iniFile.readInt(Section, ModeKey, 0) != 0;}

private:

  void    find(TCchar* path);
  void    add(TCchar* path);
  void*   pick();

  // returns either a pointer to datum at index i in array or zero

  Item*   datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}

  int     nData()      {return data.end();}                       // returns number of data items in array

  void    removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

#if 0
  void    debug(int v)    {iniFile.write(Section, DebugKey, v);}
  void    debug(double v) {iniFile.write(Section, DebugKey, v);}
#endif
  };


extern WallPaper wallPaper;
