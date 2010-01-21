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

#ifndef __TEST_COMPONENT_H__
#define __TEST_COMPONENT_H__

#include "TestInterface.h"
#include "EcomPlusRefCountedBase.h"

class CTestComponent : public CEComPlusRefCountedBase, public MTestInterface, public MTestInterface2
{
public:
	static MTestInterface * NewL(TAny * aConstructionParameters );

	virtual TInt foo(TInt aArgument1, TInt aArgument2);
	virtual TInt bar(TInt aArgument1, TInt aArgument2);

	MUnknown * QueryInterfaceL( TInt aInterfaceId);
	void AddRef() { CEComPlusRefCountedBase::AddRef(); }
	void Release() { CEComPlusRefCountedBase::Release(); }

protected:
	CTestComponent(TAny * aConstructionParameters);
	void ConstructL();


};

#endif /* __TEST_COMPONENT_H__ */
