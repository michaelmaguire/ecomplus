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

#ifndef __UNKNOWN_H__
#define __UNKNOWN_H__

#include <e32base.h>


const TInt KIID_MUnknown = 0x10200DE6; // Properly allocated Symbian UID.


/**
 * A base interface for all components.
 *
 * Allows for interface discovery and object lifetime management.
 */
class MUnknown
{
public:
	/**
	 * Interface discovery.
	 *
	 * Pass in the interface ID (32 bits on Symbian to work with ECOM) 
	 * you desire and it will return a pointer to the interface.
	 *
	 * This method will Leave with KErrNotSupported if the object
	 * doesn't support the requested interface.
	 *
	 * On return of the desired interface, AddRef will have been 
	 * called for you on that interface already.  You should Release
	 * on that interface when you are finished with the interface.
	 * 
	 * e.g.:
	 *
	 *		MSomeDesiredInterface * someDesiredInterface = reinterpret_cast<MSomeDesiredInterface *>( unknown->QueryInterface( KIID_MSomeDesiredInterface ) );
	 *		CleanupReleasePushL(*someDesiredInterface);
	 *
	 *		[Do stuff with someDesiredInterface.]
	 *
	 *		CleanupStack::PopAndDestroy(someDesiredInterface);
	 *
	 *
	 * Note: At one point in the past this method accepted a pointer to 
	 * a pointer as this paradigm is implemented on some other platforms,
	 * but this proved to be cumbersome to use and unnecessary on Symbian
	 * because of the CleanupStack.
	 *
	 */
	virtual MUnknown * QueryInterfaceL( TInt aInterfaceId /* IN */ ) = 0;

	/**
	 * Lifetime management -- increase the reference count.
	 */
	virtual void AddRef() = 0;

	/**
	 * Lifetime management -- decrease the reference count.
	 *
	 * If reference count goes to 0, the object will take care of deleting itself.
	 */
	virtual void Release() = 0;

protected:
	/**
	 * Destructor virtual and protected (and should be on all sub-interfaces)
	 * to ensure that Release is the only way the object can be destroyed.
	 * This ensures that no single client of the object can unilaterally 
	 * destroy it (by e.g. an accidental attempt to delete)
	 */
	virtual ~MUnknown() {}
};





/**
 * Macros can often be evil, but the following macro is entirely optional
 * and provides for type safety as well more concise code.
 *
 * It works provided you follow the convention of naming your interface Id's
 * as KIID_MSomeInterface, where MSomeInterface is the name of your interface.
 *
 * e.g.
 *		MSomeInterface * someInterface = QiL( unknown, MSomeInterface );
 */
#define QiL( UNKNOWN, INTERFACE )	reinterpret_cast<INTERFACE*>( (UNKNOWN)->QueryInterfaceL(KIID_##INTERFACE ) )


#endif /*  __UNKNOWN_H__ */

