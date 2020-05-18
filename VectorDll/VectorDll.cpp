#include "stdafx.h"
#include "VectorDll.h"
#include "interface.h"
#include <cmath>
#include <iostream>


Math::Vector* pMyObject = NULL;

namespace Math {
	Vector::Vector() {
		
	}

	Vector::Vector(double startX, double startY, double endX, double endY) {
		this->X = endX - startX;
		this->Y = endY - startY;
	}

	void Vector::init(double startX, double startY, double endX, double endY) {
		this->X = endX - startX;
		this->Y = endY - startY;
	}

	double Vector::getX() {
		return X;
	}
	double Vector::getY() {
		return Y;
	}

	double Vector::getR_coord() {
		return sqrt(getX()*getX() + getY()*getY());
	}

	double Vector::getFi_coord() {
		return atan2(getY(), getX()) * 180 / 3.14;
	}

	void Vector::destroy() {
		this->~Vector();
		std::cout << "destroy()" << std::endl;
	}
}

VECTORDLL_API int CreateObject(Vect*& MyObject)
{
	if (pMyObject != NULL)
	{
		MyObject = (Vect*)pMyObject;
		std::cout << "CreateMyObject::Exists" << std::endl;
		return 0;
	}
	else
	{
		pMyObject = new Math::Vector;
		MyObject = (Vect*)pMyObject;
		std::cout << "CreateMyObject::New" << std::endl;
		return 1;
	}
}