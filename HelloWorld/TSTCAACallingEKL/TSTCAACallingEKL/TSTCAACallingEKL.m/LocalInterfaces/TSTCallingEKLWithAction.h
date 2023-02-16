//===================================================================
//
// TSTCallingEKLWithAction.h
//
//===================================================================

#ifndef TSTCallingEKLWithAction_H
#define TSTCallingEKLWithAction_H

//-----------------------------------------------------------------------
class TSTCallingEKLWithAction
{
public:
   TSTCallingEKLWithAction ();
   virtual ~TSTCallingEKLWithAction ();
   HRESULT Test();
private:

   TSTCallingEKLWithAction (TSTCallingEKLWithAction &);
   TSTCallingEKLWithAction& operator=(TSTCallingEKLWithAction&);
};
//-----------------------------------------------------------------------
#endif

