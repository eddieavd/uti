//
//
//      uti
//      config.hpp
//
//      shamelessly stolen from
//      https://github.com/psiha/build/blob/master/include/psi/build/disable_warnings.hpp

#pragma once


#define UTI_STRINGIZE( x ) #x

#if defined( __GNUC__ ) || defined( __clang__ )

#       define UTI_DIAGS_COMMAND( compiler, command, ... ) \
        _Pragma( UTI_STRINGIZE( compiler diagnostic command __VA_ARGS__ ) )

#       define UTI_DIAGS_PUSH() UTI_DIAGS_COMMAND( UTI_COMPILER, push )
#       define UTI_DIAGS_POP()  UTI_DIAGS_COMMAND( UTI_COMPILER,  pop )

#       ifdef __clang__
#              define UTI_COMPILER clang
#              define UTI_DIAGS_CLANG_DISABLE( x ) UTI_DIAGS_COMMAND( clang, ignored, #x )
#              define UTI_DIAGS_GCC_DISABLE(   x )
#       else
#              define UTI_COMPILER GCC
#              define UTI_DIAGS_GCC_DISABLE(   x ) UTI_DIAGS_COMMAND(   gcc, ignored, #x )
#              define UTI_DIAGS_CLANG_DISABLE( x )
#       endif

#       define UTI_DIAGS_DISABLE( x ) UTI_DIAGS_COMMAND( UTI_COMPILER, ignored, #x )
#else
#       error "uti: unsupported compiler"
#endif
