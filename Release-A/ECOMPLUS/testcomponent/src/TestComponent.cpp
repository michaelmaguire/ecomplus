/**
*
* Copyright © 2004 Michael Maguire.
* 
* You are hereby granted free use of the software in this file,
* provided you maintain this entire copyright notice at the top.
*
* This software is provided "as is," and the copyright holder 
* makes no representations or warranties, express or implied,
* including but not limited to warranties of merchantability or 
* fitness for any particular purpose or that the use of this software
* or documentation will not infringe any third party patents, 
* copyrights, trademarks or other rights.
*
* The copyright holder will not be liable for any direct, indirect
* special or consequential damages arising out of any use of this
* software or documentation.
*
*/

#include "TestComponent.h"
#include <e32svr.h>


MTestInterface * CTestComponent::NewL(TAny * aConstructionParameters )
{
	CTestComponent * self = new (ELeave) CTestComponent(aConstructionParameters );
	CleanupStack::PushL(self);
	self->ConstructL();
	
	MTestInterface * testInterface = QiL( self, MTestInterface);

	CleanupStack::Pop(self);
	return self;
}


CTestComponent::CTestComponent(TAny * aConstructionParameters)
	: CEComPlusRefCountedBase(aConstructionParameters)
{
	RDebug::Print(_L("%08x"), aConstructionParameters);
}

void CTestComponent::ConstructL()
{


}

TInt CTestComponent::foo(TInt arg1, TInt arg2)
{
	return arg1 + arg2;
}


TInt CTestComponent::bar(TInt arg1, TInt arg2)
{
	return arg1 * arg2;
}


MUnknown * CTestComponent::QueryInterfaceL(TInt aInterfaceId )
{
	if( KIID_MTestInterface == aInterfaceId )
	{
		AddRef(); // Remember to do this in your subclasses for every QI.
		return static_cast<MTestInterface*>(this);
	}
	else if( KIID_MTestInterface2 == aInterfaceId )
	{
		AddRef(); // Remember to do this in your subclasses for every QI.
		return static_cast<MTestInterface2*>(this);
	}
	else
	{
		//Handy to test for not leaking if component forgets to implement this interface.
		//User::Leave(KErrNotSupported);
		//return 0;
		return CEComPlusRefCountedBase::QueryInterfaceL(aInterfaceId);
	}
}