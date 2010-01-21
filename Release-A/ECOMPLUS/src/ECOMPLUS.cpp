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

#include "ECOMPLUS.h"
#include <ecom\ecom.h>
#include "TracksOwnDestructorKey.h"
#include <OSVersion.h>


EXPORT_C MUnknown * REComPlusSession::CreateImplementationL(TUid aImplementationUid, TUid aInterfaceUid, TAny* aConstructionParameters)
{
	TUid dtorIDKey;
	TAny * object = REComSession::CreateImplementationL(aImplementationUid, dtorIDKey, aConstructionParameters);
	// Object's reference count should now be 1.

	// Our convention requires that the ECOMPLUS-aware object returns
	// a pointer to an MUnknown (sub)interface from CreateImplementationL.
	// If they don't, we'll probably get an AV in the call to QueryInterfaceL
	// below, but I'm not sure what can be done about that.
	// TODO: Perhaps we can use one of the resolver-aware REComSession methods
	// to select only implementations which are registered to support KIID_MUnknown
	// which would give us an added level of security.
	MUnknown * createdUnknown = reinterpret_cast<MUnknown*>(object);
	CleanupReleasePushL(*createdUnknown);

	MTracksOwnDestructorKey * tracksOwnDestructorKey = 0;
	TRAPD( queryError, tracksOwnDestructorKey = QiL( createdUnknown, MTracksOwnDestructorKey ) )
	if( KErrNone != queryError )
	{
		// It doesn't look like its one of ours, or perhaps someone just
		// forgot to implement MTracksOwnDestructorKey.
		// Note: If it's really not one of ours, I'm not sure 
		// if Release() will work at all -- it will probably 
		// cause an access violation.  But there's nothing we
		// can do about that as we have no other way of deleting.

		CleanupStack::PopAndDestroy(createdUnknown);
		// Object's reference count should now be 0.

		DestroyedImplementation(dtorIDKey);
		User::Leave(queryError);
		return 0;
	}
	else
	{
		// Object's reference count should now be 2.
		CleanupReleasePushL(*tracksOwnDestructorKey);
		
		tracksOwnDestructorKey->SetDestructorKey(dtorIDKey);

		CleanupStack::PopAndDestroy(tracksOwnDestructorKey);
		// Object's reference count should now be 1.

		MUnknown * expectedCastUnknown = createdUnknown->QueryInterfaceL(aInterfaceUid.iUid);
		// Object's reference count should now be 2.

		CleanupStack::PopAndDestroy(createdUnknown);
		// Object's reference count should now be 1.

		return expectedCastUnknown;
	}
}

EXPORT_C void REComPlusSession::DestroyedImplementation(TUid aDtorIDKey)
{
	/**
	 * Check to make sure we have a non-zero aDtorIDKey,
	 * in case some classes which aren't being served out
	 * through EcomPlus (or Ecom at all) are using 
	 * the CEcomPlusRefCountedBase and it's calling us 
	 * in the destructor without a aDtorIDKey being set.
	 */
	if( aDtorIDKey.iUid )
	{
		REComSession::DestroyedImplementation(aDtorIDKey);
	}
}


#if (__S60_VERSION__ >= __S60_V3_FP0_VERSION_NUMBER__) || (__UIQ_VERSION_NUMBER__ >= __UIQ_V3_FP0_VERSION_NUMBER__)
GLDEF_C TInt E32Dll()
#else // older SDK's
GLDEF_C TInt E32Dll( TDllReason aReason )
#endif
{
	return(KErrNone);
}
