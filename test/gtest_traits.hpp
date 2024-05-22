//
//
//      uti
//      gtest_traits.hpp
//

#pragma once

#include "gtest_uti.hpp"


struct nocopynoassign
{
        nocopynoassign             ( nocopynoassign const & ) = delete ;
        nocopynoassign & operator= ( nocopynoassign const & ) = delete ;

        nocopynoassign             ( nocopynoassign && ) = delete ;
        nocopynoassign & operator= ( nocopynoassign && ) = delete ;
};

struct throwcopythrowassign
{
        throwcopythrowassign             ( throwcopythrowassign const & ) ;
        throwcopythrowassign & operator= ( throwcopythrowassign const & ) ;

        throwcopythrowassign             ( throwcopythrowassign && ) ;
        throwcopythrowassign & operator= ( throwcopythrowassign && ) ;
};

struct noexcopynoexassign
{
        noexcopynoexassign             ( noexcopynoexassign const & ) noexcept ;
        noexcopynoexassign & operator= ( noexcopynoexassign const & ) noexcept ;

        noexcopynoexassign             ( noexcopynoexassign && ) noexcept ;
        noexcopynoexassign & operator= ( noexcopynoexassign && ) noexcept ;
};

class A     {} ;
class B : A {} ;
class C : B {} ;
class D     {} ;
union E     {} ;
using I = int  ;
