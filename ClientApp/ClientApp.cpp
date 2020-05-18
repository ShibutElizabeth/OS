// ClientApp.cpp : Defines the entry point for the console application.
//
#define WIN32_LEAN_AND_MEAN	
#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "..\VectorDll\interface.h"

int main()
{
	pMyInt pN;
	pMyFunc pFn;
	pCreateObject pCrObj;
	std::cout << "Starting..." << std::endl;

	HMODULE hmod =:: LoadLibrary("VectorDll.dll");
	if (!hmod) {
		std::cout << "Error: " << GetLastError() << std::endl;
		system("pause");
		return 1;
	}

	pN = (pMyInt)GetProcAddress(hmod,"?nADLL@@3HA");
	pN = (pMyInt)GetProcAddress(hmod, "init");
	if (pN)
		std::cout << "pN=" << *pN << std::endl;
	else
		std::cout << "Error variable!" << std::endl;

	pFn = (pMyFunc)GetProcAddress(hmod, "fnADLL");
	if (pFn)
		std::cout << "pFn=" << pFn() << std::endl;
	else
		std::cout << "Error Function Call!" << std::endl;
		
	//pCreateObject pCrObj;

	pCrObj = (pCreateObject)GetProcAddress(hmod, "CreateObject");
	if (pCrObj)
	{
		Vect* pIMyObject;
		double d;
		int iRet = pCrObj(pIMyObject);
		std::cout << "CreateObject Return Value!=" << iRet << std::endl;
		std::cout << "CreateObject Parameter Value!=" << pIMyObject << std::endl;

		//		if (iRet)
		//		{
		pIMyObject->init(13.5, 17, 100, 28);
		//		std::cout << "d =" << d << std::endl;
		double y = pIMyObject->getR_coord();
		std::cout << "R = " << y << std::endl;
		std::cout << "Fi = " << pIMyObject->getFi_coord() << std::endl;
		pIMyObject->destroy();
		//First Case
		FreeLibrary(hmod);         //Second Case

								 //		}
								 //		else
								 //			std::cout << "Error Function CreateObject Return Value!" << std::endl;

	}
	else
		std::cout << "Error Function CreateObject Call!" << std::endl;
	std::cout << "Finishing..." << std::endl;


	system("pause");
    return 0;
}

