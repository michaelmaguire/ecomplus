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

#ifndef __ECOMPLUS_H__
#define __ECOMPLUS_H__

#include <e32std.h>
#include "unknown.h"

typedef MUnknown * (*TDelegate)(TUid aImplementationUid, TUid aInterfaceUid, TAny* aConstructionParameters);

class REComPlusSession  : public RSessionBase
{
public:
	/**
	 * To create an ECOMPLUS object, the minimum you must specify is the implementation 
	 * (also known as component) Uid, as well as the interface Uid.
	 *
	 * If you would like to pay the cost of finding the object once and then
	 * cast for supported interfaces at your leisure, then ask for KIID_MUnknown 
	 * (which should always succeed if the object exists) and then perform
	 * your QueryInterfaceL's.
	 */
	IMPORT_C static MUnknown * REComPlusSession::CreateImplementationL(TUid aImplementationUid, TUid aInterfaceUid, TAny* aConstructionParameters = 0);
	
	/**
	 * Not for users of ECOMPLUS components, but rather for 
	 * implementors of ECOMPLUS components.
	 *
	 * ECOMPLUS removes the need for users of components to worry about
	 * ECOM's destructor key, but component _implementors_ must still
	 * know about it, implement MTracksOwnDestructorKey, and pass the key
	 * to ECOMPLUS on destruction.
	 *
	 * This method does absolutely nothing but pass through to the REComSession version
	 * but providing this and using it in our classes e.g. EcomPlusRefCountedBase.h
	 * allows us to do nice things to provide ECOMPLUS functionality on
	 * earlier platforms that don't have ECOM.
	 */
	IMPORT_C static void DestroyedImplementation(TUid aDtorIDKey);
#ifdef __WINS__	
	IMPORT_C static void SetDelegate(TDelegate aDelegate);
private:
	static TDelegate iDelegate;
#endif
};





/**
 * Macros can often be evil, but the following macro is entirely optional
 * and provides for type safety as well more concise code.
 *
 * This macro works for where there may be more than one component
 * implementing the same interface, and you can't use the component implementation Id
 * naming convention mentioned below.  It uses the interface Id
 * naming convention of KIID_MSomeInterface.
 *
 * e.g. 
 *		MSomeInterface * someInterface = CiL( KCID_MSomeSpecialPlugin, MSomeInterface ); 
 */
#define CiL( COMPONENT_ID, INTERFACE )	reinterpret_cast<INTERFACE*>( REComPlusSession::CreateImplementationL( TUid::Uid(COMPONENT_ID), TUid::Uid(KIID_##INTERFACE) ) )


/**
 * This macro is meant for cases where you usually have a single, *default*
 * implementation of a given interface.
 *
 * It works provided you follow the convention of naming your interface Id's
 * as TInt KIID_MSomeInterface and the default implementation Id of the component
 * implementing your interface with TInt KCID_MSomeInterface, where 
 * MSomeInterface is the name of your interface.
 *
 * e.g.
 *		MSomeInterface * someInterface = DiL( MSomeInterface );
 */
#define DiL( INTERFACE )	CiL( KCID_##INTERFACE, INTERFACE )




#endif  /* __ECOMPLUS_H__ */
