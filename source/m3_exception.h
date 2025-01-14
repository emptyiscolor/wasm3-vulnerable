//
//  m3_exception.h
//
//  Created by Steven Massey on 7/5/19.
//  Copyright © 2019 Steven Massey. All rights reserved.
//
//  some macros to emulate try/catch

#ifndef m3_exception_h
#define m3_exception_h

#include "m3_config.h"

# if d_m3EnableExceptionBreakpoint

// a central function you can be breakpoint:
static void ExceptionBreakpoint (cstr_t i_exception, cstr_t i_message)
{
    printf ("\nexception: '%s' @ %s\n", i_exception, i_message);
    return;
}

#   define EXCEPTION_PRINT(ERROR) ExceptionBreakpoint (ERROR, (__FILE__ ":" M3_STR(__LINE__)))

# else
#   define EXCEPTION_PRINT(...)
# endif


#define _try
#define _(TRY)                            { result = TRY; if (result) { EXCEPTION_PRINT (result); goto _catch; } }
#define _throw(ERROR)                     { result = ERROR; EXCEPTION_PRINT (result); goto _catch; }
#define _throwif(ERROR, COND)             if (UNLIKELY(COND)) \
                                          { result = ERROR; EXCEPTION_PRINT (result); goto _catch; }

#define _throwifnull(PTR)                   _throwif (m3Err_mallocFailed, !(PTR))

#endif // m3_exception_h
