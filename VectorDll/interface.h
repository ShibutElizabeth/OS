#pragma once
#include <objbase.h>

typedef int* pMyInt;
typedef int(*pMyFunc)();

interface Vect {
	virtual void init(double startX, double startY, double endX, double endY) PURE;
	virtual double getX() PURE;
	virtual double getY() PURE;
	virtual double getFi_coord() PURE;
	virtual double getR_coord() PURE;
	virtual void destroy() PURE;
};

typedef int(*pCreateObject)(Vect*&);