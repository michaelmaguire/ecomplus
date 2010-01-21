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

#ifndef __REF_COUNTED_BASE_H__
#define __REF_COUNTED_BASE_H__

#include <e32base.h>
#include "unknown.h"


/**
 * An OPTIONAL inline base class which implements MUnknown and reference counting
 * and delegation.
 *
 * Note: It is not aware of ECOM and simply deletes itself when ref count goes to 0.
 * For ECOM aware class, see subclass of this in ECOMRefCountedBase.h.
 */
class CRefCountedBase : public CBase, public MUnknown
{
public:
	virtual MUnknown * QueryInterfaceL( TInt aInterfaceId )
	{
		if( KIID_MUnknown == aInterfaceId )
		{
			AddRef(); // Remember to do this in your subclasses for every QI.
			return static_cast<MUnknown*>( this );
		}
		else
		{
			User::Leave(KErrNotSupported);
			return 0;
		}
	}

	virtual void AddRef()
	{
		++iRefCount;
	}

	virtual void Release()
	{
		--iRefCount;
		if( 0 == iRefCount )
		{
			delete this;
		}
	}

protected:
	CRefCountedBase( TAny * /* aConstructionParameters */ )
		: iRefCount(0)
	{
	}

	void ConstructL()
	{
	}

	virtual ~CRefCountedBase()
	{
	}

private:	
	TInt iRefCount;
};


#endif /* __REF_COUNTED_BASE_H__ */

