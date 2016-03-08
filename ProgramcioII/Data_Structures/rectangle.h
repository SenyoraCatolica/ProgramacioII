
#ifndef __R_H__
#define __R_H__

#include "p2Defs.h"



class rectangle
{
public:

	rectangle(uint x, uint y, uint w, uint h) : w(w), h(h)
	{
		position.x = x;
		position.y = y;
	}

	uint Area()
	{
		return w * h;
	}

	bool Intersection(const rectangle& r2);



private:
	uint w, h;

public:
	p2Point<uint> position;

};



#endif