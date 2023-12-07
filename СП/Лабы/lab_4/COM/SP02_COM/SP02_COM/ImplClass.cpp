#include"pch.h"
//#include"Interface.h"
#include"ImplClass.h"
//
//long g_lObjs = 0;
//long g_lLocks = 0;
//
//ImplClass::ImplClass()
//{
//	m_lRef = 1;
//	InterlockedIncrement(&g_lObjs);
//};
//
//ImplClass::~ImplClass()
//{
//	InterlockedDecrement(&g_lObjs);
//}
//
//HRESULT STDMETHODCALLTYPE ImplClass::QueryInterface(REFIID riid, void** ppv)
//{
//	HRESULT rc = S_OK;
//	if (riid == IID_IUnknown || riid == IID_Adder)
//		*ppv = (IAdder*)this;
//	else if (riid == IID_Multiplier)
//		*ppv = (IMultiplier*)this;
//	else
//		rc = E_NOINTERFACE;
//
//	if (rc==S_OK)
//		AddRef();
//	return rc;
//};
//
//STDMETHODIMP_(ULONG) ImplClass::AddRef()
//{
//	InterlockedIncrement(&m_lRef);
//	return m_lRef;
//};
//
//STDMETHODIMP_(ULONG) ImplClass::Release()
//{
//	InterlockedDecrement(&m_lRef);
//	if (m_lRef == 0)
//	{
//		delete this;
//		return 0;
//	}
//	else
//		return m_lRef;
//};
//
//HRESULT _stdcall ImplClass::Add(const double x, const double y, double& z) {
//	z = x + y;
//	return S_OK;
//}
//
//HRESULT _stdcall ImplClass::Sub(const double x, const double y, double& z) {
//	z = x - y;
//	return S_OK;
//}
//
//HRESULT _stdcall ImplClass::Mul(const double x, const double y, double& z) {
//	z = x * y;
//	return S_OK;
//}
//
//HRESULT _stdcall ImplClass::Div(const double x, const double y, double& z) {
//	z = x / y;
//	return S_OK;
//}
#include "pch.h"

ImplClass::ImplClass() : counter(1) {}

ImplClass::~ImplClass() {}

HRESULT __stdcall ImplClass::QueryInterface(const IID& iid, void** ppv) {
    if (iid == IID_Adder) {
        *ppv = (IAdder*)this;
    }
    else if (iid == IID_Multiplier) {
        *ppv = (IMultiplier*)this;
    }
    else {
        *ppv = this;
    }

    this->AddRef();
    return S_OK;
}

ULONG __stdcall ImplClass::AddRef() {
    InterlockedIncrement(&counter);
    return counter;
}

ULONG __stdcall ImplClass::Release() {
    InterlockedDecrement(&counter);

    if (counter == 0) {
        delete this;
        return 0;
    }

    return counter;
}

HRESULT __stdcall ImplClass::Add(const double x, const double y, double& c) {
    c = x + y;
    return S_OK;
}

HRESULT __stdcall ImplClass::Sub(const double x, const double y, double& c) {
    c = x - y;
    return S_OK;
}

HRESULT __stdcall ImplClass::Mul(const double x, const double y, double& c) {
    c = x * y;
    return S_OK;
}

HRESULT __stdcall ImplClass::Div(const double x, const double y, double& c) {
    c = x / y;
    return S_OK;
}