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

#ifndef __TEST_INTERFACE_H__
#define __TEST_INTERFACE_H__

#include "unknown.h"

/**
 * The implementation id of a default component which implements the MtestInterface interface.
 */
const TInt KCID_MTestInterface = 0x10200DE9;
const TUid KImplUid_MTestInterface = {KCID_MTestInterface};



const TInt KIID_MTestInterface = 0x59384912;

class MTestInterface : public MUnknown
{
public:
	virtual TInt foo(TInt aArgument1, TInt aArgument2) = 0;

protected:
	virtual ~MTestInterface() {}
};




const TInt KIID_MTestInterface2 = 0x59384933;

class MTestInterface2 : public MUnknown
{
public:
	virtual TInt bar(TInt aArgument1, TInt aArgument2) = 0;

protected:
	virtual ~MTestInterface2() {}
};




#endif /* __TEST_INTERFACE_H__ */
