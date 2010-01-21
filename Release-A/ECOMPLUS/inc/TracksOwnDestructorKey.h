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

#ifndef __TRACKS_OWN_DESTRUCTOR_KEY_H__
#define __TRACKS_OWN_DESTRUCTOR_KEY_H__

#include "unknown.h"


const TInt KIID_MTracksOwnDestructorKey = 0x10200DE8; // Properly allocated Symbian UID.


/**
 * A mandatory interface for all components in the ECOMPLUS system.
 *
 * Allows for an object to manage its own destructor key.
 */
class MTracksOwnDestructorKey : public MUnknown
{
public:
	/**
	 * Storing the destructor key from REcomSession::CreateImplementationL.
	 */
	virtual void SetDestructorKey( TUid aDtorIDKey /* IN */ ) = 0;

protected:
	virtual ~MTracksOwnDestructorKey() {}
};


#endif /* __TRACKS_OWN_DESTRUCTOR_KEY_H__ */

