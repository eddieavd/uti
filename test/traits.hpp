//
//
//      uti
//      test/traits.hpp
//

#include <type_traits>

#include <traits/traits.hpp>


constexpr int test_traits () noexcept ;

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

constexpr int test_traits () noexcept
{
        static_assert( uti::is_v    < uti:: true_type > ) ;
        static_assert( uti::is_not_v< uti::false_type > ) ;

        static_assert( std::is_convertible_v< std:: true_type, uti:: true_type > ) ;
        static_assert( std::is_convertible_v< std::false_type, uti::false_type > ) ;

        static_assert( std::is_convertible_v< uti:: true_type, std:: true_type > ) ;
        static_assert( std::is_convertible_v< uti::false_type, std::false_type > ) ;

        static_assert( uti::is_convertible_v< std:: true_type, uti:: true_type > ) ;
        static_assert( uti::is_convertible_v< std::false_type, uti::false_type > ) ;

        static_assert( uti::is_convertible_v< uti:: true_type, std:: true_type > ) ;
        static_assert( uti::is_convertible_v< uti::false_type, std::false_type > ) ;

        ////////////////////////////////////////////////////////////////////////////////

        static_assert( uti::is_same_v    < int,   int > ) ;
        static_assert( uti::is_not_same_v< int, float > ) ;

        static_assert( uti::is_same_raw_v< int, int const > ) ;
        static_assert( uti::is_not_same_v< int, int const > ) ;

        ////////////////////////////////////////////////////////////////////////////////

        static_assert( uti::is_v    < uti::is_const< int const > > ) ;
        static_assert( uti::is_not_v< uti::is_const< int       > > ) ;

        static_assert( uti::is_v    < uti::is_volatile< int volatile > > ) ;
        static_assert( uti::is_not_v< uti::is_volatile< int          > > ) ;

        static_assert( uti::is_same_v< int    const, uti::add_const_t   < int > > ) ;
        static_assert( uti::is_same_v< int volatile, uti::add_volatile_t< int > > ) ;

        static_assert( uti::is_same_v< int, uti::remove_const_t   < int    const > > ) ;
        static_assert( uti::is_same_v< int, uti::remove_volatile_t< int volatile > > ) ;

        ////////////////////////////////////////////////////////////////////////////////

        static_assert( uti::is_same_v< int, uti::remove_reference_t< int    > > ) ;
        static_assert( uti::is_same_v< int, uti::remove_reference_t< int &  > > ) ;
        static_assert( uti::is_same_v< int, uti::remove_reference_t< int && > > ) ;

        static_assert( uti::is_same_v< int, uti::remove_cv_t< int                > > ) ;
        static_assert( uti::is_same_v< int, uti::remove_cv_t< int const          > > ) ;
        static_assert( uti::is_same_v< int, uti::remove_cv_t< int       volatile > > ) ;
        static_assert( uti::is_same_v< int, uti::remove_cv_t< int const volatile > > ) ;

        static_assert( uti::is_same_v< int, uti::remove_cvref_t< int                & > > ) ;
        static_assert( uti::is_same_v< int, uti::remove_cvref_t< int const          & > > ) ;
        static_assert( uti::is_same_v< int, uti::remove_cvref_t< int       volatile & > > ) ;
        static_assert( uti::is_same_v< int, uti::remove_cvref_t< int const volatile & > > ) ;

        ////////////////////////////////////////////////////////////////////////////////

        static_assert( uti::is_same_v< int, uti::enable_if_t< true, int > > ) ;

        ////////////////////////////////////////////////////////////////////////////////

        static_assert( uti::is_not_v< uti::is_one_of< int > > ) ;

        static_assert( uti::is_v< uti::is_one_of< int, int              > > ) ;
        static_assert( uti::is_v< uti::is_one_of< int, int, float       > > ) ;
        static_assert( uti::is_v< uti::is_one_of< int, int, float, char > > ) ;

        static_assert( uti::is_v< uti::is_one_of< int, float, int, double > > ) ;

        static_assert( uti::is_not_v< uti::is_one_of< int, float, char, double > > ) ;

        ////////////////////////////////////////////////////////////////////////////////

        static_assert( uti::is_same_v<   int, uti::conditional_t<  true, int, float > > ) ;
        static_assert( uti::is_same_v< float, uti::conditional_t< false, int, float > > ) ;

        static_assert( uti::is_not_v< uti::disjunction<> > ) ;

        static_assert( uti::is_v    < uti::disjunction< uti:: true_type > > ) ;
        static_assert( uti::is_not_v< uti::disjunction< uti::false_type > > ) ;

        static_assert( uti::is_v    < uti::disjunction< uti:: true_type, uti:: true_type > > ) ;
        static_assert( uti::is_v    < uti::disjunction< uti:: true_type, uti::false_type > > ) ;
        static_assert( uti::is_v    < uti::disjunction< uti::false_type, uti:: true_type > > ) ;
        static_assert( uti::is_not_v< uti::disjunction< uti::false_type, uti::false_type > > ) ;

        static_assert( uti::is_v< uti::conjunction<> > ) ;

        static_assert( uti::is_v    < uti::conjunction< uti:: true_type > > ) ;
        static_assert( uti::is_not_v< uti::conjunction< uti::false_type > > ) ;

        static_assert( uti::is_v    < uti::conjunction< uti:: true_type, uti:: true_type > > ) ;
        static_assert( uti::is_not_v< uti::conjunction< uti:: true_type, uti::false_type > > ) ;
        static_assert( uti::is_not_v< uti::conjunction< uti::false_type, uti:: true_type > > ) ;
        static_assert( uti::is_not_v< uti::conjunction< uti::false_type, uti::false_type > > ) ;

        ////////////////////////////////////////////////////////////////////////////////

        static_assert( uti::is_v    < uti::is_referenceable<  int > > ) ;
        static_assert( uti::is_not_v< uti::is_referenceable< void > > ) ;

        static_assert( uti::is_same_v< int & , uti::add_lvalue_reference_t< int > > ) ;
        static_assert( uti::is_same_v< int &&, uti::add_rvalue_reference_t< int > > ) ;

        ////////////////////////////////////////////////////////////////////////////////

        static_assert( std::is_same_v< ptrdiff_t, std::ptrdiff_t > ) ;

        ////////////////////////////////////////////////////////////////////////////////

        static_assert( uti::is_same_v< int, uti::remove_all_extents< int[] >::type > ) ;

        ////////////////////////////////////////////////////////////////////////////////

//      static_assert( uti::is_copy_assignable_v< int > ) ;
//      static_assert( uti::is_move_assignable_v< int > ) ;
//      static_assert( uti::is_nothrow_copy_assignable_v< int > ) ;
//      static_assert( uti::is_nothrow_move_assignable_v< int > ) ;

        static_assert(  uti::is_copy_assignable_v< throwcopythrowassign > ) ;
        static_assert(  uti::is_copy_assignable_v<   noexcopynoexassign > ) ;
        static_assert( !uti::is_copy_assignable_v<       nocopynoassign > ) ;

        static_assert(  uti::is_move_assignable_v< throwcopythrowassign > ) ;
        static_assert(  uti::is_move_assignable_v<   noexcopynoexassign > ) ;
        static_assert( !uti::is_move_assignable_v<       nocopynoassign > ) ;

        static_assert( !uti::is_nothrow_copy_assignable_v< throwcopythrowassign > ) ;
        static_assert(  uti::is_nothrow_copy_assignable_v<   noexcopynoexassign > ) ;
        static_assert( !uti::is_nothrow_copy_assignable_v<       nocopynoassign > ) ;

        static_assert( !uti::is_nothrow_move_assignable_v< throwcopythrowassign > ) ;
        static_assert(  uti::is_nothrow_move_assignable_v<   noexcopynoexassign > ) ;
        static_assert( !uti::is_nothrow_move_assignable_v<       nocopynoassign > ) ;

        ////////////////////////////////////////////////////////////////////////////////

        static_assert( uti::is_copy_constructible_v< int > ) ;
        static_assert( uti::is_move_constructible_v< int > ) ;
        static_assert( uti::is_nothrow_copy_constructible_v< int > ) ;
        static_assert( uti::is_nothrow_move_constructible_v< int > ) ;

        static_assert(  uti::is_copy_constructible_v< throwcopythrowassign > ) ;
        static_assert(  uti::is_copy_constructible_v<   noexcopynoexassign > ) ;
        static_assert( !uti::is_copy_constructible_v<       nocopynoassign > ) ;

        static_assert(  uti::is_move_constructible_v< throwcopythrowassign > ) ;
        static_assert(  uti::is_move_constructible_v<   noexcopynoexassign > ) ;
        static_assert( !uti::is_move_constructible_v<       nocopynoassign > ) ;

        static_assert( !uti::is_nothrow_copy_constructible_v< throwcopythrowassign > ) ;
        static_assert(  uti::is_nothrow_copy_constructible_v<   noexcopynoexassign > ) ;
        static_assert( !uti::is_nothrow_copy_constructible_v<       nocopynoassign > ) ;

        static_assert( !uti::is_nothrow_move_constructible_v< throwcopythrowassign > ) ;
        static_assert(  uti::is_nothrow_move_constructible_v<   noexcopynoexassign > ) ;
        static_assert( !uti::is_nothrow_move_constructible_v<       nocopynoassign > ) ;

        ////////////////////////////////////////////////////////////////////////////////

        return 0;
}
