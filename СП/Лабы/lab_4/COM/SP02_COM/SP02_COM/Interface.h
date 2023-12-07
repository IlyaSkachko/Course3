#pragma once
#include"COM.h"

#define FNAME L"Smw.CA.COM"
#define VINDX L"Smw.CA.1"
#define PRGID L"Smw.CA"


// {6D58DB86-B4FB-4BF2-8E25-A1ADB0FB9301}
static const GUID CLSID_SP =
{ 0x6d58db86, 0xb4fb, 0x4bf2, { 0x8e, 0x25, 0xa1, 0xad, 0xb0, 0xfb, 0x93, 0x1 } };



// {2C299B46-A0A0-4A2E-A10E-23D03ADC79D7}
static const GUID IID_Adder =
{ 0x2c299b46, 0xa0a0, 0x4a2e, { 0xa1, 0xe, 0x23, 0xd0, 0x3a, 0xdc, 0x79, 0xd7 } };


struct IAdder : IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE Add(const double x, const double y, double& z) = 0;
    virtual HRESULT STDMETHODCALLTYPE Sub(const double x, const double y, double& z) = 0;
};



// {68DAA552-5037-46A2-9918-4E0BB23BDA05}
static const GUID IID_Multiplier =
{ 0x68daa552, 0x5037, 0x46a2, { 0x99, 0x18, 0x4e, 0xb, 0xb2, 0x3b, 0xda, 0x5 } };


struct IMultiplier : IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE Mul(const double x, const double y, double& z) = 0;
    virtual HRESULT STDMETHODCALLTYPE Div(const double x, const double y, double& z) = 0;
};
