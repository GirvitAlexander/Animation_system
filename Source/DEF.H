/* FILE NAME: DEF.H
 * PROGRAMMER: AG6
 * DATE: 07.01.2019
 * PURPORSE: .
 */

#ifndef __DEF_H_
#define __DEF_H_

/* Debug memory allocation support */
#ifndef NDEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
     _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
       _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else /* _DEBUG */
#  define SetDbgMemHooks() ((void)0)
#endif /* _DEBUG */
#include <stdlib.h>

//#include <commondf.h>

#ifdef WIN32
#pragma warning(disable : 4200 4244 4013 4018 4115 4761 4127 4305)
#pragma warning(error : 4016 4027 4701)
#include <windows.h>
#endif /* WIN32 */

#include <stdio.h>

#include "mth.h"

#endif /* __DEF_H_ */

/* END OF 'DEF.H' FILE */


