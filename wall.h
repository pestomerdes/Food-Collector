#ifndef wall_h
#define wall_h

#include "cell.h"

class Wall : public Cell{
 public:
	Wall(int, int);
    int type();
};
#endif