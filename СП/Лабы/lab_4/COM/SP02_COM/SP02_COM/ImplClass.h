#pragma once
//#include"Interface.h"
//#include<iostream>
//
//
extern long g_lObjs;
extern long g_lLocks;
//
//class ImplClass :public IAdder, public IMultiplier {
//private:
//	volatile ULONG m_lRef;
//public:
//	ImplClass();
//	~ImplClass();
//
//	STDMETHOD(QueryInterface(REFIID riid, void** ppv));
//	STDMETHOD_(ULONG, AddRef(void));
//	STDMETHOD_(ULONG, Release(void));
//
//	HRESULT _stdcall Add(const double x, const double y, double& z);
//	HRESULT _stdcall Sub(const double x, const double y, double& z);
//	HRESULT _stdcall Mul(const double x, const double y, double& z);
//	HRESULT _stdcall Div(const double x, const double y, double& z);
//};

#pragma once
#include <objbase.h>
#include <Unknwn.h>
#include "Interface.h"




class ImplClass : public IAdder, public IMultiplier {
private:
	ULONG counter;
public:
	ImplClass();
	~ImplClass();
	HRESULT __stdcall QueryInterface(const IID& iid, void** ppv);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	HRESULT __stdcall Add(const double, const double, double&);
	HRESULT __stdcall Sub(const double, const double, double&);
	HRESULT __stdcall Mul(const double, const double, double&);
	HRESULT __stdcall Div(const double, const double, double&);
};

