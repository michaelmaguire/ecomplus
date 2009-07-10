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

#ifndef __ECOMPLUS_REF_COUNTED_BASE_H__
#define __ECOMPLUS_REF_COUNTED_BASE_H__

#include "RefCountedBase.h"
#include "TracksOwnDestructorKey.h"
#include "EcomPlus.h"

/**
 * An OPTIONAL inline base class which implements MUnknown, MTracksOwnDestructorKey 
 * and reference counting.
 *
 *
 * Note: This class' implementation of its destructor relies on REComPlusSession::DestroyedImplementation
 * so you must link to ECOMPLUS.dll in any code which uses this class.
 */
class CEComPlusRefCountedBase : public CRefCountedBase, public MTracksOwnDestructorKey
{
public:
	virtual MUnknown * QueryInterfaceL( TInt aInterfaceId )
	{
		if( KIID_MTracksOwnDestructorKey == aInterfaceId )
		{
			AddRef(); // Remember to do this in your subclasses for every QI.
			return static_cast<MTracksOwnDestructorKey*>( this );
		}
		else
		{
			return CRefCountedBase::QueryInterfaceL(aInterfaceId);
		}
	}

	virtual void AddRef() {CRefCountedBase::AddRef();}

	virtual void Release() {CRefCountedBase::Release();}

	virtual void SetDestructorKey( TUid aDtorIDKey /* IN */ )
	{
		iDtorIDKey = aDtorIDKey;
	}

protected:
	CEComPlusRefCountedBase( TAny * aConstructionParameters )
		: CRefCountedBase(aConstructionParameters)
	{
	}

	void ConstructL()
	{
		CRefCountedBase::ConstructL();
	}

	virtual ~CEComPlusRefCountedBase() 
	{
		REComPlusSession::DestroyedImplementation(iDtorIDKey);
	}

private:
	TUid iDtorIDKey;	
};


#endif /* __ECOMPLUS_REF_COUNTED_BASE_H__ */

