// COPYRIGHT Dassault Systemes 2014
//===================================================================
//
// TSTCallingEKLWithBR.h
//
//===================================================================

#ifndef TSTCallingEKLWithBR_H
#define TSTCallingEKLWithBR_H


//-----------------------------------------------------------------------
class TSTCallingEKLWithBR
{

public:
   TSTCallingEKLWithBR ();
   ~TSTCallingEKLWithBR ();
   HRESULT Test ();

private:
   TSTCallingEKLWithBR (TSTCallingEKLWithBR &);
   TSTCallingEKLWithBR& operator=(TSTCallingEKLWithBR&);
};
//-----------------------------------------------------------------------
#endif

