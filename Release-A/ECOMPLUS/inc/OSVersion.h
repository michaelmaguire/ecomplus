/**
*
* Copyright (c) 2007 Blue Whale Systems Ltd.
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

#ifndef __OS_VERSION_H__
#define __OS_VERSION_H__

#include <e32def.h>

const TInt KUidW960iValue = 0x20002e6a;
const TInt KUidZ10Value = 0x1027400c;
const TInt KUidN96Value = 0x20002D82;
const TInt KUidN97Value = 0x20014DDD;

/**
 * Usage notes:
 *
 * In your code, DO NOT #ifdef directly against the MACRO defines in the mmp files such as __DONT_USE_IN_CODE__MMP_ONLY__S60_V1_FP2__, 
 * __DONT_USE_IN_CODE__MMP_ONLY__S60_V2_FP2__, etc.
 * That will be liable to break as new, greater, versions come out from Symbian, Nokia, Sony-Ericsson, etc.
 *
 * e.g. if you write #ifdef( __DONT_USE_IN_CODE__MMP_ONLY__S60_V3_FP0__ ) around some new feature
 * that only came out in Symbian OS 9.1, your code probably won't be reached anymore when it is
 * recompiled in 3 months Symbian OS 9.2.
 *
 *
 * Instead, use >, >= (only 'greater' or 'greater than or equal to') comparisons between __S60_VERSION__ or __UIQ_VERSION__ and 
 * the ..._VERSION_NUMBER__ constants defined below.
 * 
 * e.g. 
 *
 *     #if (__S60_VERSION__ >= __S60_V3_FP0_VERSION_NUMBER__) || (__UIQ_VERSION__ >= __UIQ_V3_FP_0_VERSION_NUMBER__)
 *			// Do stuff for any SDK from current forward.
 *			[...]
 *     #elseif (__S60_VERSION__ >= __S60_V2_FP2_VERSION_NUMBER__) || (__UIQ_VERSION__ >= __UIQ_V2_FP_1_VERSION_NUMBER__)
 *			// Do stuff for older SDK.
 *			[...]
 *     #else // retro.
 *			// Do stuff for really old SDK.
 *			[...]
 *     #endif 
 *
 *
 * Note: Be sure to structure your #if statements so that you only used 'greater' or 'greater than or equal to'
 * so that checks such as #if (__S60_VERSION__ >= __S60_3_FP0_VERSION_NUMBER__) || (__UIQ_VERSION__ >= __UIQ_V3_FP_0_VERSION_NUMBER__)
 * will work as intended when __UIQ_VERSION__ is 0.
 *
 *
 *
 * Note also: If you find you're having trouble getting your conditional statements to behave as you would expect,
 * double check that you've spelled the constant correctly -- one small mistake e.g. _2_FP3_ instead of _V2_FP3 
 * and your statement will be missed.  Quick way to double check -- do a Find in Files on the constant you're
 * checking against and make sure it shows up everywhere, including here in OSVersion.h.
 *
 * Note also: Make sure this file (OSVersion.h) is in the include path for every file where you try to
 * make use of these checks.
 */


// Some handy common version numbers to use in checks.


/**
 * Used Symbian OS 6.1 -- e.g. phones such as Nokia nGage mark 1.
 */
#define __S60_V1_FP2_VERSION_NUMBER__ 10200

/**
 * Used Symbian OS 7.0s -- e.g. phones such as Nokia 6600.
 */
#define __S60_V2_FP0_VERSION_NUMBER__ 20000

/**
 * Used Symbian OS 7.0s -- e.g. phones such as Nokia 7610, 6670, 6260, 3230.
 */
#define __S60_V2_FP1_VERSION_NUMBER__ 20100

/**
 * Used Symbian OS 8.0a -- e.g. phones such as Nokia 6630, 6680.
 */
#define __S60_V2_FP2_VERSION_NUMBER__ 20200

/**
 * Used Symbian OS 8.1a -- e.g. phones such as Nokia N70.
 */
#define __S60_V2_FP3_VERSION_NUMBER__ 20300

/**
 * Used Symbian OS 9.1 -- e.g. phones such as Nokia E50, E61, N73.
 */
#define __S60_V3_FP0_VERSION_NUMBER__ 30000   

/**
 * Used Symbian OS 9.2 -- e.g. phones such as Nokia N95.
 */
#define __S60_V3_FP1_VERSION_NUMBER__ 30100   

/**
 * Used Symbian OS 7.0 -- e.g. phones such as Sony-Ericsson p900, Motorola A9000.
 */
#define __UIQ_V2_FP1_VERSION_NUMBER__ 20100   

/**
 * Used Symbian OS 9.1 -- e.g. phones such as Sony-Ericsson m600i, p990i, w950i.
 */
#define __UIQ_V3_FP0_VERSION_NUMBER__ 30000   



#if defined(__DONT_USE_IN_CODE__MMP_ONLY__S60_V1_FP2__)

#define __S60_VERSION__ 			__S60_V1_FP2_VERSION_NUMBER__
#define __UIQ_VERSION_NUMBER__ 			0

#else 

#if defined( __DONT_USE_IN_CODE__MMP_ONLY__S60_V2_FP0__ )

#define __S60_VERSION__ 			__S60_V2_FP0_VERSION_NUMBER__
#define __UIQ_VERSION_NUMBER__ 			0

#else 

#if defined( __DONT_USE_IN_CODE__MMP_ONLY__S60_V2_FP1__ )

#define __S60_VERSION__ 			__S60_V2_FP1_VERSION_NUMBER__
#define __UIQ_VERSION_NUMBER__ 			0

#else 

#if defined( __DONT_USE_IN_CODE__MMP_ONLY__S60_V2_FP2__ )

#define __S60_VERSION__ 			__S60_V2_FP2_VERSION_NUMBER__
#define __UIQ_VERSION_NUMBER__ 			0

#else 

#if defined( __DONT_USE_IN_CODE__MMP_ONLY__S60_V2_FP3__ )

#define __S60_VERSION__ 			__S60_V2_FP3_VERSION_NUMBER__
#define __UIQ_VERSION_NUMBER__ 			0

#else 

#if defined( __DONT_USE_IN_CODE__MMP_ONLY__S60_V3_FP0__ )
#define __S60_VERSION__ 			__S60_V3_FP0_VERSION_NUMBER__
#define __UIQ_VERSION_NUMBER__ 			0

#else 

#if defined( __DONT_USE_IN_CODE__MMP_ONLY__S60_V3_FP1__ )

#define __S60_VERSION__ 			__S60_V3_FP1_VERSION_NUMBER__
#define __UIQ_VERSION_NUMBER__ 			0

#else 

#if defined( __DONT_USE_IN_CODE__MMP_ONLY__UIQ_V2_FP1__ )

#define __S60_VERSION__ 			0
#define __UIQ_VERSION_NUMBER__ 			__UIQ_V2_FP1_VERSION_NUMBER__

#else 

#if defined( __DONT_USE_IN_CODE__MMP_ONLY__UIQ_V3_FP0__ )

#define __S60_VERSION__ 			0
#define __UIQ_VERSION_NUMBER__ 			__UIQ_V3_FP0_VERSION_NUMBER__

#else 

#error You must define a __DONT_USE_IN_CODE__MMP_ONLY__... type of macro in your mmp file.

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif



#endif /* __OS_VERSION_H__ */
