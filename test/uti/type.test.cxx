//
//
//      uti
//      gtest_traits.cpp
//

#include <snitch/snitch.hpp>

#include "uti.test.hxx"

#include <uti/type/traits.hxx>
#include <uti/meta/algo.hxx>


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

using all_test_types_const    = uti::meta::unpack_t< uti::meta::transform< uti::meta::to_const    >, all_test_types       > ;
using all_test_types_volatile = uti::meta::unpack_t< uti::meta::transform< uti::meta::to_volatile >, all_test_types       > ;
using all_test_types_cv       = uti::meta::unpack_t< uti::meta::transform< uti::meta::to_volatile >, all_test_types_const > ;

using traits_test_types = join::fn< all_test_types, all_test_types_const, all_test_types_volatile, all_test_types_cv > ;


TEMPLATE_LIST_TEST_CASE( "traits::identity", "[traits][identity]", all_test_types )
{
        CONSTEVAL_CHECK( uti::is_v    < uti:: true_type > ) ;
        CONSTEVAL_CHECK( uti::is_not_v< uti::false_type > ) ;

        CONSTEVAL_CHECK( std::is_convertible_v< std:: true_type, uti:: true_type > ) ;
        CONSTEVAL_CHECK( std::is_convertible_v< std::false_type, uti::false_type > ) ;

        CONSTEVAL_CHECK( std::is_convertible_v< uti:: true_type, std:: true_type > ) ;
        CONSTEVAL_CHECK( std::is_convertible_v< uti::false_type, std::false_type > ) ;

        CONSTEVAL_CHECK( uti::is_convertible_v< std:: true_type, uti:: true_type > ) ;
        CONSTEVAL_CHECK( uti::is_convertible_v< std::false_type, uti::false_type > ) ;

        CONSTEVAL_CHECK( uti::is_convertible_v< uti:: true_type, std:: true_type > ) ;
        CONSTEVAL_CHECK( uti::is_convertible_v< uti::false_type, std::false_type > ) ;

        CONSTEVAL_CHECK( uti::is_same_v    < TestType, TestType > ) ;
        CONSTEVAL_CHECK( uti::is_not_same_v< TestType,    float > ) ;

        CONSTEVAL_CHECK( uti::is_same_raw_v< TestType, TestType const > ) ;
        CONSTEVAL_CHECK( uti::is_not_same_v< TestType, TestType const > ) ;

        CONSTEVAL_CHECK( uti::is_same_v< TestType, uti::enable_if_t< true, TestType > > ) ;

        CONSTEVAL_CHECK( uti::is_not_v< uti::is_one_of< TestType > > ) ;

        CONSTEVAL_CHECK( uti::is_v< uti::is_one_of< TestType, TestType              > > ) ;
        CONSTEVAL_CHECK( uti::is_v< uti::is_one_of< TestType, TestType, float       > > ) ;
        CONSTEVAL_CHECK( uti::is_v< uti::is_one_of< TestType, TestType, float, char > > ) ;

        CONSTEVAL_CHECK( uti::is_v< uti::is_one_of< TestType, float, TestType, double > > ) ;

        CONSTEVAL_CHECK( uti::is_not_v< uti::is_one_of< int, float, char, double > > ) ;

        CONSTEVAL_CHECK( uti::is_v    < uti::is_referenceable< TestType > > ) ;
        CONSTEVAL_CHECK( uti::is_not_v< uti::is_referenceable<     void > > ) ;

        CONSTEVAL_CHECK( uti::is_same_v< TestType & , uti::add_lvalue_reference_t< TestType > > ) ;
        CONSTEVAL_CHECK( uti::is_same_v< TestType &&, uti::add_rvalue_reference_t< TestType > > ) ;

        CONSTEVAL_CHECK( std::is_same_v< uti::ptrdiff_t, std::ptrdiff_t > ) ;

        CONSTEVAL_CHECK( uti::is_same_v< int, uti::remove_all_extents< int[] >::type > ) ;
}

TEMPLATE_LIST_TEST_CASE( "traits::cvref", "[traits][cvref]", all_test_types )
{
        CONSTEVAL_CHECK( uti::is_v    < uti::is_const< TestType const > > ) ;
        CONSTEVAL_CHECK( uti::is_not_v< uti::is_const< TestType       > > ) ;

        CONSTEVAL_CHECK( uti::is_v    < uti::is_volatile< TestType volatile > > ) ;
        CONSTEVAL_CHECK( uti::is_not_v< uti::is_volatile< TestType          > > ) ;

        CONSTEVAL_CHECK( uti::is_same_v< TestType    const, uti::add_const_t   < TestType > > ) ;
        CONSTEVAL_CHECK( uti::is_same_v< TestType volatile, uti::add_volatile_t< TestType > > ) ;

        CONSTEVAL_CHECK( uti::is_same_v< TestType, uti::remove_const_t   < TestType    const > > ) ;
        CONSTEVAL_CHECK( uti::is_same_v< TestType, uti::remove_volatile_t< TestType volatile > > ) ;

        CONSTEVAL_CHECK( uti::is_same_v< TestType, uti::remove_reference_t< TestType    > > ) ;
        CONSTEVAL_CHECK( uti::is_same_v< TestType, uti::remove_reference_t< TestType &  > > ) ;
        CONSTEVAL_CHECK( uti::is_same_v< TestType, uti::remove_reference_t< TestType && > > ) ;

        CONSTEVAL_CHECK( uti::is_same_v< TestType, uti::remove_cv_t< TestType                > > ) ;
        CONSTEVAL_CHECK( uti::is_same_v< TestType, uti::remove_cv_t< TestType const          > > ) ;
        CONSTEVAL_CHECK( uti::is_same_v< TestType, uti::remove_cv_t< TestType       volatile > > ) ;
        CONSTEVAL_CHECK( uti::is_same_v< TestType, uti::remove_cv_t< TestType const volatile > > ) ;

        CONSTEVAL_CHECK( uti::is_same_v< TestType, uti::remove_cvref_t< TestType                & > > ) ;
        CONSTEVAL_CHECK( uti::is_same_v< TestType, uti::remove_cvref_t< TestType const          & > > ) ;
        CONSTEVAL_CHECK( uti::is_same_v< TestType, uti::remove_cvref_t< TestType       volatile & > > ) ;
        CONSTEVAL_CHECK( uti::is_same_v< TestType, uti::remove_cvref_t< TestType const volatile & > > ) ;
}

TEMPLATE_LIST_TEST_CASE( "traits::conditionals", "[traits][conditionals]", all_test_types )
{
        CONSTEVAL_CHECK( uti::is_same_v< TestType, uti::conditional_t<  true, TestType, float > > ) ;
        CONSTEVAL_CHECK( uti::is_same_v<    float, uti::conditional_t< false, TestType, float > > ) ;

        CONSTEVAL_CHECK( uti::is_not_v< uti::disjunction<> > ) ;

        CONSTEVAL_CHECK( uti::is_v    < uti::disjunction< uti:: true_type > > ) ;
        CONSTEVAL_CHECK( uti::is_not_v< uti::disjunction< uti::false_type > > ) ;

        CONSTEVAL_CHECK( uti::is_v    < uti::disjunction< uti:: true_type, uti:: true_type > > ) ;
        CONSTEVAL_CHECK( uti::is_v    < uti::disjunction< uti:: true_type, uti::false_type > > ) ;
        CONSTEVAL_CHECK( uti::is_v    < uti::disjunction< uti::false_type, uti:: true_type > > ) ;
        CONSTEVAL_CHECK( uti::is_not_v< uti::disjunction< uti::false_type, uti::false_type > > ) ;

        CONSTEVAL_CHECK( uti::is_v< uti::conjunction<> > ) ;

        CONSTEVAL_CHECK( uti::is_v    < uti::conjunction< uti:: true_type > > ) ;
        CONSTEVAL_CHECK( uti::is_not_v< uti::conjunction< uti::false_type > > ) ;

        CONSTEVAL_CHECK( uti::is_v    < uti::conjunction< uti:: true_type, uti:: true_type > > ) ;
        CONSTEVAL_CHECK( uti::is_not_v< uti::conjunction< uti:: true_type, uti::false_type > > ) ;
        CONSTEVAL_CHECK( uti::is_not_v< uti::conjunction< uti::false_type, uti:: true_type > > ) ;
        CONSTEVAL_CHECK( uti::is_not_v< uti::conjunction< uti::false_type, uti::false_type > > ) ;
}

TEMPLATE_LIST_TEST_CASE( "traits::assignability", "[traits][assignability]", all_test_types )
{
//      CONSTEVAL_CHECK( !uti::is_assignable_v<    TestType  , TestType > ) ;
        CONSTEVAL_CHECK(  uti::is_assignable_v<    TestType &, TestType > ) ;
        CONSTEVAL_CHECK(  uti::is_assignable_v< std::string  ,   double > ) ;

        CONSTEVAL_CHECK( uti::is_nothrow_assignable_v< int &, double > ) ;

        CONSTEVAL_CHECK( uti::is_copy_assignable_v< TestType > ) ;
        CONSTEVAL_CHECK( uti::is_move_assignable_v< TestType > ) ;
        CONSTEVAL_CHECK( uti::is_nothrow_copy_assignable_v<      int > ) ;
        CONSTEVAL_CHECK( uti::is_nothrow_move_assignable_v< TestType > ) ;

        CONSTEVAL_CHECK(  uti::is_copy_assignable_v< throwcopythrowassign > ) ;
        CONSTEVAL_CHECK(  uti::is_copy_assignable_v<   noexcopynoexassign > ) ;
        CONSTEVAL_CHECK( !uti::is_copy_assignable_v<       nocopynoassign > ) ;

        CONSTEVAL_CHECK(  uti::is_move_assignable_v< throwcopythrowassign > ) ;
        CONSTEVAL_CHECK(  uti::is_move_assignable_v<   noexcopynoexassign > ) ;
        CONSTEVAL_CHECK( !uti::is_move_assignable_v<       nocopynoassign > ) ;

        CONSTEVAL_CHECK( !uti::is_nothrow_copy_assignable_v< throwcopythrowassign > ) ;
        CONSTEVAL_CHECK(  uti::is_nothrow_copy_assignable_v<   noexcopynoexassign > ) ;
        CONSTEVAL_CHECK( !uti::is_nothrow_copy_assignable_v<       nocopynoassign > ) ;

        CONSTEVAL_CHECK( !uti::is_nothrow_move_assignable_v< throwcopythrowassign > ) ;
        CONSTEVAL_CHECK(  uti::is_nothrow_move_assignable_v<   noexcopynoexassign > ) ;
        CONSTEVAL_CHECK( !uti::is_nothrow_move_assignable_v<       nocopynoassign > ) ;
}

TEMPLATE_LIST_TEST_CASE( "traits::constructibility", "[traits][constructibility]", all_test_types )
{
        CONSTEVAL_CHECK( uti::is_copy_constructible_v< TestType > ) ;
        CONSTEVAL_CHECK( uti::is_move_constructible_v< TestType > ) ;
        CONSTEVAL_CHECK( uti::is_nothrow_copy_constructible_v< int > ) ;
        CONSTEVAL_CHECK( uti::is_nothrow_move_constructible_v< int > ) ;

        CONSTEVAL_CHECK(  uti::is_copy_constructible_v< throwcopythrowassign > ) ;
        CONSTEVAL_CHECK(  uti::is_copy_constructible_v<   noexcopynoexassign > ) ;
        CONSTEVAL_CHECK( !uti::is_copy_constructible_v<       nocopynoassign > ) ;

        CONSTEVAL_CHECK(  uti::is_move_constructible_v< throwcopythrowassign > ) ;
        CONSTEVAL_CHECK(  uti::is_move_constructible_v<   noexcopynoexassign > ) ;
        CONSTEVAL_CHECK( !uti::is_move_constructible_v<       nocopynoassign > ) ;

        CONSTEVAL_CHECK( !uti::is_nothrow_copy_constructible_v< throwcopythrowassign > ) ;
        CONSTEVAL_CHECK(  uti::is_nothrow_copy_constructible_v<   noexcopynoexassign > ) ;
        CONSTEVAL_CHECK( !uti::is_nothrow_copy_constructible_v<       nocopynoassign > ) ;

        CONSTEVAL_CHECK( !uti::is_nothrow_move_constructible_v< throwcopythrowassign > ) ;
        CONSTEVAL_CHECK(  uti::is_nothrow_move_constructible_v<   noexcopynoexassign > ) ;
        CONSTEVAL_CHECK( !uti::is_nothrow_move_constructible_v<       nocopynoassign > ) ;
}

TEMPLATE_LIST_TEST_CASE( "traits::swappability", "[traits][swappability]", all_test_types )
{
        CONSTEVAL_CHECK(  uti::meta::swappable_with< TestType       &, TestType       & > ) ;
        CONSTEVAL_CHECK( !uti::meta::swappable_with< TestType const &, TestType const & > ) ;
}

TEST_CASE( "traits::inherit", "[traits][inherit]" )
{
        CONSTEVAL_CHECK
        (
                uti::is_base_of_v<A, A> == true &&
                uti::is_base_of_v<A, B> == true &&
                uti::is_base_of_v<A, C> == true &&
                uti::is_base_of_v<A, D> != true &&
                uti::is_base_of_v<B, A> != true &&
                uti::is_base_of_v<E, E> != true &&
                uti::is_base_of_v<I, I> != true
        );
}
