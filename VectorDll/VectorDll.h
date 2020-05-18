#ifdef VECTORDLL_EXPORTS
#define VECTORDLL_API __declspec(dllexport) 
#else
#define VECTORDLL_API __declspec(dllimport) 
#endif
#include "interface.h"

namespace Math {
	class Vector : Vect {
	private:
		double X;
		double Y;
	public:

		VECTORDLL_API Vector();
		VECTORDLL_API Vector(double startX, double startY, double endX, double endY);

		void VECTORDLL_API init(double startX, double startY, double endX, double endY);

		double VECTORDLL_API getX();

		double VECTORDLL_API getY();

		double VECTORDLL_API getR_coord();

		double VECTORDLL_API getFi_coord();

		void VECTORDLL_API destroy();
	};
}

extern "C" VECTORDLL_API int CreateObject(Vect*&);