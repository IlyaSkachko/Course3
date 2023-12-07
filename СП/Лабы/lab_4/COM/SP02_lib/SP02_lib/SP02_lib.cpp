// SP02_lib.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "framework.h"

#include "SP02_LIB.h"
#include <stdexcept>
#include <iostream>



SP2HANDLE OS12::Init()
{
    IUnknown* pIUnknown = nullptr;
    try {
        if (!SUCCEEDED(CoInitialize(nullptr)))
            throw std::runtime_error("Error initialize OLE32");

        if (!SUCCEEDED(CoCreateInstance(CLSID_SP, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pIUnknown)))
            throw std::runtime_error("Error create instance CLSID");

        return pIUnknown;
    }
    catch (std::runtime_error error) {
        IRES("Init: ", error.what());
        return nullptr;
    }
}

double OS12::Adder::Add(SP2HANDLE h, double x, double y)
{
    try {
        if (!SUCCEEDED(((IUnknown*)h)->QueryInterface(IID_Adder, (void**)&h)))
            throw std::runtime_error("Error get interface IID_Adder");

        double result = 0.0;
        if (!SUCCEEDED((( IAdder*)h)->Add(x, y, result)))
            throw std::runtime_error("Error IAdder::Add");
        return result;
    }
    catch (std::runtime_error error) {
        IRES("Add: ", error.what());
    }

}

double OS12::Adder::Sub(SP2HANDLE h, double x, double y)
{
    try {
        if (!SUCCEEDED(((IUnknown*)h)->QueryInterface(IID_Adder, (void**)&h)))
            throw std::runtime_error("Error get interface IID_Adder");

        double result = 0.0;
        if (!SUCCEEDED((( IAdder*)h)->Sub(x, y, result)))
            throw std::runtime_error("Error IAdder::Sub");
        return result;
    }
    catch (std::runtime_error error) {
        IRES("Sub: ", error.what());
    }
}

double OS12::Multiplier::Mul(SP2HANDLE h, double x, double y)
{
    try {
        if (!SUCCEEDED(((IUnknown*)h)->QueryInterface(IID_Multiplier, (void**)&h)))
            throw std::runtime_error("Error get interface IID_Multiplier");

        double result = 0.0;
        if (!SUCCEEDED(((IMultiplier*)h)->Mul(x, y, result)))
            throw std::runtime_error("Error Multiplier::Mul");
        return result;
    }
    catch (std::runtime_error error) {
        IRES("Mul: ", error.what());
    }
}

double OS12::Multiplier::Div(SP2HANDLE h, double x, double y)
{
    try {
        if (!SUCCEEDED(((IUnknown*)h)->QueryInterface(IID_Multiplier, (void**)&h)))
            throw std::runtime_error("Error get interface IID_Multiplier");

        if (y == 0)
            throw std::runtime_error("Param of second equals to zero (x/0)");

        double result = 0.0;
        if (!SUCCEEDED(((IMultiplier*)h)->Div(x, y, result)))
            throw std::runtime_error("Error Multiplier::Div");
        return result;
    }
    catch (std::runtime_error error) {
        IRES("Div: ", error.what());
    }
}

void OS12::Dispose(SP2HANDLE h) {
    ((IUnknown*)h)->Release();
    CoFreeUnusedLibraries();
}