//
//
//      uti
//      type_traits.hpp
//

#pragma once

#ifndef UTI_STD_VER
#       if __cplusplus <= 201103L
#              define UTI_STD_VER 11
#       elif __cplusplus <= 201402L
#               define UTI_STD_VER 14
#       elif __cplusplus <= 201703L
#               define UTI_STD_VER 17
#       elif __cplusplus <= 202002L
#               define UTI_STD_VER 20
#       else
#               define UTI_STD_VER 23
#       endif
#endif

#ifndef UTI_MOVE
#define UTI_MOVE(...) \
        static_cast< typename ::uti::remove_reference_t< decltype(__VA_ARGS__)>&&>(__VA_ARGS__)
#endif

#ifndef UTI_FWD
#define UTI_FWD(...) \
        static_cast< decltype(__VA_ARGS__)&&>(__VA_ARGS__)
#endif


#if !__has_builtin(__is_final)                   || \
    !__has_builtin(__is_empty)                   || \
    !__has_builtin(__is_enum)                    || \
    !__has_builtin(__is_union)                   || \
    !__has_builtin(__underlying_type)            || \
    !__has_builtin(__is_trivially_constructible) || \
    !__has_builtin(__is_trivially_copyable)      || \
    ( !__has_builtin(__is_trivially_destructible)  || !__has_builtin(__has_trivial_destructor) )
#       ifdef UTI_HAS_STL
//              use c++ standard library implementations
#               include <type_traits>
#       else
//              oh boi
#       endif
#else
//      use compiler intrinsics
#endif


namespace uti
{


////////////////////////////////////////////////////////////////////////////////
///     typedefs
////////////////////////////////////////////////////////////////////////////////

using  i8_t =           char ;
using  u8_t = unsigned  char ;
using i16_t =          short ;
using u16_t = unsigned short ;
using i32_t =            int ;
using u32_t = unsigned   int ;
using i64_t =           long ;
using u64_t = unsigned  long ;

static_assert( sizeof(  i8_t ) == 1 ) ;
static_assert( sizeof(  u8_t ) == 1 ) ;
static_assert( sizeof( i16_t ) == 2 ) ;
static_assert( sizeof( u16_t ) == 2 ) ;
static_assert( sizeof( i32_t ) == 4 ) ;
static_assert( sizeof( u32_t ) == 4 ) ;
static_assert( sizeof( i64_t ) == 8 ) ;
static_assert( sizeof( u64_t ) == 8 ) ;

using  size_t = u64_t ;
using ssize_t = i64_t ;

////////////////////////////////////////////////////////////////////////////////
///     consteval
////////////////////////////////////////////////////////////////////////////////

constexpr bool is_constant_evaluated () noexcept
{
#if UTI_STD_VER >= 23
        if consteval
        {
                return true;
        }
        return false;
#elif __has_builtin( __builtin_is_constant_evaluated )
        return __builtin_is_constant_evaluated();
#elif defined( UTI_HAS_STL )
        return std::is_constant_evaluated();
#else
#       error "uti: no implementation for 'is_constant_evaluated' available"
#endif
}

////////////////////////////////////////////////////////////////////////////////
///     identity
////////////////////////////////////////////////////////////////////////////////

template< typename... >
struct void_t
{
        using type = void ;
};

template< auto Val >
struct value_identity
{
        static constexpr auto value { Val } ;
};

template< auto Val >
inline constexpr auto value_identity_v = value_identity< Val >::value ;

template< typename T >
struct type_identity
{
        using type = T ;
};

template< typename T >
using type_identity_t = typename type_identity< T >::type ;

struct identity
{
        template< typename T >
        [[ nodiscard ]] constexpr T && operator() ( T && t ) const noexcept
        {
                return UTI_FWD( t );
        }
        using is_transparent = void ;
};

template< typename... > struct print_types ;

////////////////////////////////////////////////////////////////////////////////
///     constants
////////////////////////////////////////////////////////////////////////////////

template< auto Val >
struct integral_constant
{
        using value_type =          decltype( Val ) ;
        using       type = integral_constant< Val > ;

        static constexpr value_type value { Val } ;

        constexpr integral_constant () noexcept = default ;

        template< template< auto Val1 > typename U >
        constexpr integral_constant ( U< Val > ) noexcept {}

        template< template< auto Val1 > typename U >
        constexpr operator U< Val > () const noexcept {}

        ////////////////////////////////////////////////////////////////////////
        // conversions to and from std::integral_constant                     //
        //                                                                    //
        template< template< typename T1, T1 Val1 > typename U >               //
        constexpr integral_constant ( U< value_type, Val > ) noexcept {}      //
        //                                                                    //
        template< template< typename T1, T1 Val1 > typename U >               //
        constexpr operator U< value_type, Val > () const noexcept {}          //
        //                                                                    //
        ////////////////////////////////////////////////////////////////////////

        constexpr   operator value_type () const noexcept { return value; }
        constexpr value_type operator() () const noexcept { return value; }
};

using  true_type = integral_constant<  true > ;
using false_type = integral_constant< false > ;

#ifdef UTI_HAS_STL
static_assert( std::is_convertible_v< uti::true_type, std::true_type > ) ;
static_assert( std::is_convertible_v< std::true_type, uti::true_type > ) ;
#endif

////////////////////////////////////////////////////////////////////////////////
///     const stuff
////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_const : false_type {} ;

template< typename T >
struct is_const< T const > : true_type {} ;

template< typename T >
inline constexpr bool is_const_v = is_const< T >::value ;


template< typename T >
struct add_const { using type = T const ; } ;

template< typename T >
using add_const_t = typename add_const< T >::type ;


template< typename T >
struct remove_const : type_identity< T > {} ;

template< typename T >
struct remove_const< T const > : type_identity< T > {} ;

template< typename T >
using remove_const_t = typename remove_const< T >::type ;

////////////////////////////////////////////////////////////////////////////////
///     volatile stuff
////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_volatile : false_type {} ;

template< typename T >
struct is_volatile< T volatile > : true_type {} ;

template< typename T >
inline constexpr bool is_volatile_v = is_volatile< T >::value ;


template< typename T >
struct add_volatile { using type = T volatile ; } ;

template< typename T >
using add_volatile_t = typename add_volatile< T >::type ;


template< typename T >
struct remove_volatile : type_identity< T > {} ;

template< typename T >
struct remove_volatile< T volatile > : type_identity< T > {} ;

template< typename T >
using remove_volatile_t = typename remove_volatile< T >::type ;

////////////////////////////////////////////////////////////////////////////////
///     reference stuff
////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct remove_reference : type_identity< T > {} ;

template< typename T >
struct remove_reference< T & > : type_identity< T > {} ;

template< typename T >
struct remove_reference< T && > : type_identity< T > {} ;

template< typename T >
using remove_reference_t = typename remove_reference< T >::type ;

////////////////////////////////////////////////////////////////////////////////
///     cvref stuff
////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct remove_cv : remove_const< remove_volatile_t< T > > {} ;

template< typename T >
using remove_cv_t = typename remove_cv< T >::type ;


template< typename T >
struct remove_cvref : remove_reference< remove_cv_t< T > > {} ;

template< typename T >
using remove_cvref_t = typename remove_cvref< T >::type ;

////////////////////////////////////////////////////////////////////////////////
///     enable if
////////////////////////////////////////////////////////////////////////////////

template< bool, typename T = void >
struct enable_if {} ;

template< typename T >
struct enable_if< true, T > { using type = T ; } ;

template< bool C, typename T = void >
using enable_if_t = typename enable_if< C, T >::type ;

////////////////////////////////////////////////////////////////////////////////
///     unary
////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is : false_type {} ;

template<>
struct is< true_type > : true_type {} ;

template< typename T >
inline constexpr bool is_v = is< T >::value ;


template< typename T >
struct is_not : true_type {} ;

template<>
struct is_not< true_type > : false_type {} ;

template< typename T >
inline constexpr bool is_not_v = is_not< T >::value ;

////////////////////////////////////////////////////////////////////////////////
///     binary
////////////////////////////////////////////////////////////////////////////////

template< typename T1, typename T2 >
struct is_same : false_type {} ;

template< typename T >
struct is_same< T, T > : true_type {} ;

template< typename T1, typename T2 >
inline constexpr bool is_same_v = is_same< T1, T2 >::value ;


template< typename T1, typename T2 >
struct is_same_raw : is_same< remove_cv_t< T1 >, remove_cv_t< T2 > > {} ;

template< typename T1, typename T2 >
inline constexpr bool is_same_raw_v = is_same_raw< T1, T2 >::value ;


template< typename T1, typename T2 >
struct is_not_same : true_type {} ;

template< typename T >
struct is_not_same< T, T > : false_type {} ;

template< typename T1, typename T2 >
inline constexpr bool is_not_same_v = is_not_same< T1, T2 >::value ;


template< typename T, typename... Args >
struct is_one_of ;

template< typename T >
struct is_one_of< T > : false_type {} ;

template< typename T, typename... Args >
struct is_one_of< T, T, Args... > : true_type {} ;

template< typename T, typename Arg1, typename... Args >
struct is_one_of< T, Arg1, Args... > : is_one_of< T, Args... > {} ;

template< typename T, typename... Args >
inline constexpr bool is_one_of_v = is_one_of< T, Args... >::value ;

////////////////////////////////////////////////////////////////////////////////
///     conditionals
////////////////////////////////////////////////////////////////////////////////

template< bool Cond, typename Then, typename Else >
struct conditional
{
        using type = Then ;
};

template< typename Then, typename Else >
struct conditional< false, Then, Else >
{
        using type = Else ;
};

template< bool Cond, typename Then, typename Else >
using conditional_t = typename conditional< Cond, Then, Else >::type ;


template< typename... Args > struct conjunction : true_type {} ;

template< typename... Args >
struct conjunction< true_type, Args... > : conjunction< Args... > {} ;

template< typename... Args >
struct conjunction< false_type, Args... > : false_type {} ;

template< typename... Args >
inline constexpr bool conjunction_v = conjunction< Args... >::value ;


template< typename... Args > struct disjunction : false_type {} ;

template< typename... Args >
struct disjunction< true_type, Args... > : true_type {} ;

template< typename T, typename... Args >
struct disjunction< T, Args... > : disjunction< Args... > {} ;

template< typename... Args >
inline constexpr bool disjunction_v = disjunction< Args... >::value ;

////////////////////////////////////////////////////////////////////////////////
///     reference stuff contd.
////////////////////////////////////////////////////////////////////////////////

struct _is_referenceable_impl
{
        template< typename T > static T &        _test( int ) ;
        template< typename T > static false_type _test( ... ) ;
};

template< typename T >
struct is_referenceable : integral_constant< is_not_same_v< decltype( _is_referenceable_impl::_test< T >( 0 ) ), false_type > > {} ;

template< typename T >
inline constexpr bool is_referenceable_v = is_referenceable< T >::value ;


template< typename T, bool = is_referenceable_v< T > >
struct _add_lvalue_reference_impl { using type = T ; } ;

template< typename T >
struct _add_lvalue_reference_impl< T, true > { using type = T & ; } ;

template< typename T >
struct add_lvalue_reference : _add_lvalue_reference_impl< T > {} ;

template< typename T >
using add_lvalue_reference_t = typename add_lvalue_reference< T >::type ;


template< typename T, bool = is_referenceable_v< T > >
struct _add_rvalue_reference_impl { using type = T ; } ;

template< typename T >
struct _add_rvalue_reference_impl< T, true > { using type = T && ; } ;

template< typename T >
struct add_rvalue_reference : _add_rvalue_reference_impl< T > {} ;

template< typename T >
using add_rvalue_reference_t = typename add_rvalue_reference< T >::type ;

////////////////////////////////////////////////////////////////////////////////
///     declval
////////////////////////////////////////////////////////////////////////////////

template< typename T >
constexpr bool always_false = false ;

template< typename T >
add_rvalue_reference_t< T > declval () noexcept
{
        static_assert( always_false< T >, "uti: declval not allowed in evaluated context" );
}

using nullptr_t = decltype( nullptr ) ;
using ptrdiff_t = decltype( uti::declval< int * >() - uti::declval< int * >() ) ;

#ifdef UTI_HAS_STL
static_assert( std::is_same_v< ptrdiff_t, std::ptrdiff_t > ) ;
#endif

////////////////////////////////////////////////////////////////////////////////
///     primary
////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct remove_all_extents { using type = T ; } ;

template< typename T >
struct remove_all_extents< T[] > { using type = typename remove_all_extents< T >::type ; } ;

template< typename T, size_t N >
struct remove_all_extents< T[ N ] > { using type = typename remove_all_extents< T >::type ; } ;

////////////////////////////////////////////////////////////////////////////////

#if __has_builtin( __is_empty )

template< typename T >
struct is_empty : integral_constant< __is_empty( T ) > {} ;

#elif defined( UTI_HAS_STL )

template< typename T >
struct is_empty : std::is_empty< T > {} ;

#else
#error "uti: no implementation for 'is_empty' available"
#endif

template< typename T >
inline constexpr bool is_empty_v = is_empty< T >::value ;

////////////////////////////////////////////////////////////////////////////////

#if __has_builtin( __is_final )

template< typename T >
struct is_final : integral_constant< __is_final( T ) > {} ;

#elif defined( UTI_HAS_STL )

template< typename T >
struct is_final : std::is_final< T > {} ;

#else
#error "uti: no implementation for 'is_final' available"
#endif

template< typename T >
inline constexpr bool is_final_v = is_final< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
using is_void = is_one_of< T
                         , void
                         , void const
                         , void       volatile
                         , void const volatile
                         > ;

template< typename T >
inline constexpr bool is_void_v = is_void< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
using is_null_pointer = is_one_of< T
                                 , nullptr_t
                                 , nullptr_t const
                                 , nullptr_t       volatile
                                 , nullptr_t const volatile
                                 > ;

template< typename T >
inline constexpr bool is_null_pointer_v = is_null_pointer< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename > struct is_integral_base : false_type {} ;

template<> struct is_integral_base <      bool > : true_type {} ;
template<> struct is_integral_base <       int > : true_type {} ;
template<> struct is_integral_base <     short > : true_type {} ;
template<> struct is_integral_base <      char > : true_type {} ;
template<> struct is_integral_base <   wchar_t > : true_type {} ;
template<> struct is_integral_base <  char16_t > : true_type {} ;
template<> struct is_integral_base <  char32_t > : true_type {} ;
template<> struct is_integral_base <      long > : true_type {} ;
template<> struct is_integral_base < long long > : true_type {} ;

template<> struct is_integral_base < unsigned       int > : true_type {} ;
template<> struct is_integral_base < unsigned     short > : true_type {} ;
template<> struct is_integral_base < unsigned      char > : true_type {} ;
template<> struct is_integral_base < unsigned      long > : true_type {} ;
template<> struct is_integral_base < unsigned long long > : true_type {} ;

template< typename T >
struct is_integral : is_integral_base< remove_cv_t< T > > {} ;

template< typename T >
inline constexpr bool is_integral_v = is_integral< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename > struct is_floating_base : false_type {} ;

template<> struct is_floating_base <       float > : true_type {} ;
template<> struct is_floating_base <      double > : true_type {} ;
template<> struct is_floating_base < long double > : true_type {} ;

template< typename T >
struct is_floating_point : is_floating_base< remove_cv_t< T > > {} ;

template< typename T >
inline constexpr bool is_floating_point_v = is_floating_point< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_array : false_type {} ;

template< typename T, size_t N >
struct is_array< T[ N ] > : true_type {} ;

template< typename T >
struct is_array< T[] > : true_type {} ;

template< typename T >
inline constexpr bool is_array_v = is_array< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct _is_pointer_impl : false_type {} ;

template< typename T >
struct _is_pointer_impl< T * > : true_type {} ;

template< typename T >
struct is_pointer : _is_pointer_impl< remove_cv_t< T > > {} ;

template< typename T >
inline constexpr bool is_pointer_v = is_pointer< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_reference : false_type {} ;

template< typename T >
struct is_reference< T & > : true_type {} ;

template< typename T >
struct is_reference< T && > : true_type {} ;

template< typename T >
inline constexpr bool is_reference_v = is_reference< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_lvalue_reference : false_type {} ;

template< typename T >
struct is_lvalue_reference< T & > : true_type {} ;

template< typename T >
inline constexpr bool is_lvalue_reference_v = is_lvalue_reference< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_rvalue_reference : false_type {} ;

template< typename T >
struct is_rvalue_reference< T && > : true_type {} ;

template< typename T >
inline constexpr bool is_rvalue_reference_v = is_rvalue_reference< T >::value ;

////////////////////////////////////////////////////////////////////////////////

#if __has_builtin( __is_enum )

template< typename T >
struct is_enum : integral_constant< __is_enum( T ) > {} ;

#elif defined( UTI_HAS_STL )

template< typename T >
struct is_enum : std::is_enum< T > {} ;

#else
#error "uti: no implementation for 'is_enum' available"
#endif

template< typename T >
inline constexpr bool is_enum_v = is_enum< T >::value ;

////////////////////////////////////////////////////////////////////////////////

#if __has_builtin( __is_union )

template< typename T >
struct is_union : integral_constant< __is_union( T ) > {} ;

#elif defined( UTI_HAS_STL )

template< typename T >
struct is_union : std::is_union< T > {} ;

#else
#error "uti: no implementation for 'is_union' available"
#endif

template< typename T >
inline constexpr bool is_union_v = is_union< T >::value ;

////////////////////////////////////////////////////////////////////////////////

struct _is_class_impl
{
        template< typename T > static integral_constant< !is_union_v< T > > _test ( int T::* ) ;
        template< typename T > static false_type                            _test (      ... ) ;
};

template< typename T >
struct is_class : integral_constant< is_not_same_v< decltype( _is_class_impl::_test< T >( nullptr ) ), false_type > > {} ;

template< typename T >
inline constexpr bool is_class_v = is_class< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_function : integral_constant< !is_const_v< T const > && !is_reference_v< T > > {} ;

template< typename T >
inline constexpr bool is_function_v = is_function< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_member_pointer : false_type {} ;

template< typename T, typename U >
struct is_member_pointer< T U::* > : true_type {} ;

template< typename T >
inline constexpr bool is_member_pointer_v = is_member_pointer< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct _is_member_function_pointer_impl : false_type {} ;

template< typename T, typename U >
struct _is_member_function_pointer_impl< T U::* > : is_function< T > {} ;

template< typename T >
struct is_member_function_pointer : _is_member_function_pointer_impl< remove_cv_t< T > > {} ;

template< typename T >
inline constexpr bool is_member_function_pointer_v = is_member_function_pointer< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_member_object_pointer : integral_constant< is_member_pointer_v< T > && !is_member_function_pointer_v< T > > {} ;

template< typename T >
inline constexpr bool is_member_object_pointer_v = is_member_object_pointer< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_arithmetic : integral_constant< is_integral_v< T > || is_floating_point_v< T > > {} ;

template< typename T >
inline constexpr bool is_arithmetic_v = is_arithmetic< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_scalar : integral_constant< is_arithmetic_v    < T >
                                   || is_enum_v          < T >
                                   || is_pointer_v       < T >
                                   || is_member_pointer_v< T >
                                   || is_null_pointer_v  < T > > {} ;

template< typename T >
inline constexpr bool is_scalar_v = is_scalar< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct alignment_of : integral_constant< alignof( T ) > {} ;

template< typename T >
inline constexpr auto alignment_of_v = alignment_of< T >::value ;

////////////////////////////////////////////////////////////////////////////////
///     assignability
////////////////////////////////////////////////////////////////////////////////

#if __has_builtin( __is_assignable )

template< typename T, typename U >
struct is_assignable : integral_constant< __is_assignable( T, U ) > {} ;

#elif defined( UTI_HAS_STL )

template< typename T, typename U >
struct is_assignable : std::is_assignable< T, U > {} ;

#else

template< typename, typename T >
struct _select_2nd { using type = T ; } ;

template< typename T, typename U >
typename _select_2nd< decltype( ( uti::declval< T >() = uti::declval< U >() ) ), true_type >::type _is_assignable_test ( int ) ;

template< typename, typename > false_type _is_assignable_test ( ... ) ;

template< typename T, typename U, bool = is_void_v< T > || is_void_v< U > >
struct _is_assignable_impl
        : public decltype( ( _is_assignable_test< T, U >( 0 ) ) ) {} ;

template< typename T, typename U >
struct _is_assignable_impl< T, U, true >
        : public false_type {} ;

template< typename T, typename U >
struct is_assignable : public _is_assignable_impl< T, U > {} ;

#endif

template< typename T, typename U >
inline constexpr bool is_assignable_v = is_assignable< T, U >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_copy_assignable : is_assignable< add_lvalue_reference_t< T >, add_lvalue_reference_t< add_const_t< T > > > {} ;

template< typename T >
inline constexpr bool is_copy_assignable_v = is_copy_assignable< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_move_assignable : is_assignable< add_lvalue_reference_t< T >, add_rvalue_reference_t< T > > {} ;

template< typename T >
inline constexpr bool is_move_assignable_v = is_move_assignable< T >::value ;

////////////////////////////////////////////////////////////////////////////////

#if __has_builtin( __is_nothrow_assignable )

template< typename T, typename Arg >
struct is_nothrow_assignable : integral_constant< __is_nothrow_assignable( T, Arg ) > {} ;

#elif defined( UTI_HAS_STL )

template< typename T, typename Arg >
struct is_nothrow_assignable : std::is_nothrow_assignable< T, Arg > {} ;

#else

template< bool, typename T, typename Arg > struct _is_nothrow_assignable_impl ;

template< typename T, typename Arg >
struct _is_nothrow_assignable_impl< false, T, Arg > : public false_type {} ;

template< typename T, typename Arg >
struct _is_nothrow_assignable_impl< true, T, Arg >
        : public integral_constant< noexcept( uti::declval< T >() = uti::declval< Arg >() ) > {} ;

template< typename T, typename Arg >
struct is_nothrow_assignable
        : public _is_nothrow_assignable_impl< is_assignable_v< T, Arg >, T, Arg > {} ;

#endif

template< typename T, typename Arg >
inline constexpr bool is_nothrow_assignable_v = is_nothrow_assignable< T, Arg >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_nothrow_move_assignable : is_nothrow_assignable< T, add_rvalue_reference_t< T > > {} ;

template< typename T >
inline constexpr bool is_nothrow_move_assignable_v = is_nothrow_move_assignable< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_nothrow_copy_assignable : is_nothrow_assignable< T, add_lvalue_reference_t< add_const_t< T > > > {} ;

template< typename T >
inline constexpr bool is_nothrow_copy_assignable_v = is_nothrow_copy_assignable< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct _remove_pointer_impl : type_identity< T > {} ;

template< typename T >
struct _remove_pointer_impl< T * > : type_identity< T > {} ;

template< typename T >
struct remove_pointer : _remove_pointer_impl< remove_cv_t< T > > {} ;

template< typename T >
using remove_pointer_t = typename remove_pointer< T >::type ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct _is_pointer_to_const_impl : false_type {} ;

template< typename T >
struct _is_pointer_to_const_impl< T * > : is_const< T > {} ;

template< typename T >
struct is_pointer_to_const : _is_pointer_to_const_impl< remove_cv_t< T > > {} ;

template< typename T >
inline constexpr bool is_pointer_to_const_v = is_pointer_to_const< T >::value ;

////////////////////////////////////////////////////////////////////////////////
///     constructibility
////////////////////////////////////////////////////////////////////////////////

#if !__has_builtin( __is_constructible )

template< typename T, typename... Args >
struct _is_constructible_impl : integral_constant< __is_constructible( T, Args... ) > {} ;

#elif defined( UTI_HAS_STL )

template< typename T, typename... Args >
struct _is_constructible_impl : std::is_constructible< T, Args... > {} ;

#else

template< typename, typename T, typename... Args >
struct _is_constructible_impl : false_type {} ;

template< typename T, typename... Args >
struct _is_constructible_impl< void_t< decltype( ::new T( uti::declval< Args >()... ) ) >, T, Args... > : true_type {} ;

#endif

template< typename T, typename... Args >
using is_constructible = _is_constructible_impl< /* void_T<>, */ T, Args... > ;

template< typename T, typename... Args >
inline constexpr bool is_constructible_v = is_constructible< T, Args... >::value ;

////////////////////////////////////////////////////////////////////////////////

#if __has_builtin( __is_nothrow_constructible )

template< typename T, typename... Args >
struct is_nothrow_constructible : integral_constant< __is_nothrow_constructible( T, Args... ) > {} ;

#elif defined( UTI_HAS_STL )

template< typename T, typename... Args >
struct is_nothrow_constructible : std::is_nothrow_constructible< T > {} ;

#else

template< bool, bool, typename T, typename... Args > struct _is_nothrow_constructible_impl ;

template< typename T, typename... Args >
struct _is_nothrow_constructible_impl< /* is_constructible */ true, /* is_reference */ false, T, Args... >
        : integral_constant< noexcept( T( uti::declval< Args >()... ) ) > {} ;

template< typename T >
void _implicit_conversion_to ( T ) noexcept {}

template< typename T, typename Arg >
struct _is_nothrow_constructible_impl< true, true, T, Arg >
        : integral_constant< noexcept( _implicit_conversion_to< T >( uti::declval< Arg >() ) ) > {} ;

template< typename T, bool IsReference, typename... Args >
struct _is_nothrow_constructible_impl< false, IsReference, T, Args... >
        : public false_type {} ;

template< typename T, typename... Args >
struct is_nothrow_constructible : _is_nothrow_constructible_impl< is_constructible_v< T, Args... >, is_reference_v< T >, T, Args... > {} ;

template< typename T, size_t N >
struct is_nothrow_constructible< T[ N ] >
        : _is_nothrow_constructible_impl< is_constructible_v< T >, is_reference_v< T >, T > {} ;

#endif

template< typename T, typename... Args >
inline constexpr bool is_nothrow_constructible_v = is_nothrow_constructible< T, Args... >::value ;

////////////////////////////////////////////////////////////////////////////////

#if __has_builtin( __is_trivially_constructible )

template< typename T, typename... Args >
struct _is_trivially_constructible_impl : integral_constant< __is_trivially_constructible( T, Args... ) > {} ;

#elif defined( UTI_HAS_STL )

template< typename T, typename... Args >
struct _is_trivially_constructible_impl : std::is_trivially_constructible< T, Args... > {} ;

#else
#error "uti: no implementation for 'is_trivially_constructible' available"
#endif

template< typename T, typename... Args >
struct is_trivially_constructible : _is_trivially_constructible_impl< T, Args... > {} ;

template< typename T, typename... Args >
inline constexpr bool is_trivially_constructible_v = is_trivially_constructible< T, Args... >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename >
struct _is_destructible_apply
{
        using type = int ;
};

template< typename T >
struct _is_destructor_wellformed
{
        template< typename T1 >
        static true_type _test ( typename _is_destructible_apply< decltype( uti::declval< T1 & >().~T1() ) >::type ) ;

        template< typename T1 >
        static false_type _test ( ... ) ;

        static const bool value = decltype( _test< T >( 8372 ) )::value ;
};

template< typename, bool >
struct _destructible_impl ;

template< typename T >
struct _destructible_impl< T, false >
        : public integral_constant< _is_destructor_wellformed< typename remove_all_extents< T >::type >::value > {} ;

template< typename T >
struct _destructible_impl< T, true >
        : public true_type {} ;

template< typename T, bool >
struct _destructible_false ;

template< typename T >
struct _destructible_false< T, false > : public _destructible_impl< T, is_reference_v< T > > {} ;

template< typename T >
struct _destructible_false< T, true > : public false_type {} ;

template< typename T >
struct is_destructible : public _destructible_false< T, is_function_v< T > > {} ;

template< typename T >
struct is_destructible< T[] > : public false_type {} ;

template<>
struct is_destructible< void > : public false_type {} ;

template< typename T >
inline constexpr bool is_destructible_v = is_destructible< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< bool, typename T >
struct _is_nothrow_destructible_impl ;

template< typename T >
struct _is_nothrow_destructible_impl< false, T > : public false_type {} ;

template< typename T >
struct _is_nothrow_destructible_impl< true, T > : public integral_constant< noexcept( uti::declval< T >().~T() ) > {} ;

template< typename T >
struct is_nothrow_destructible : public _is_nothrow_destructible_impl< is_destructible_v< T >, T > {} ;

template< typename T >
inline constexpr bool is_nothrow_destructible_v = is_nothrow_destructible< T >::value ;

////////////////////////////////////////////////////////////////////////////////

#if __has_builtin( __is_trivially_destructible )

template< typename T >
struct is_trivially_destructible : integral_constant< __is_trivially_destructible( T ) > {} ;

#elif __has_builtin( __has_trivial_destructor )

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-builtins"

template< typename T >
struct is_trivially_destructible : integral_constant< __has_trivial_destructor( T ) > {} ;

#pragma GCC diagnostic pop

#elif defined( UTI_HAS_STL )

template< typename T >
struct is_trivially_destructible : std::is_trivially_destructible< T > {} ;

#elif UTI_STD_VER <= 11

template< typename T >
struct _trivial_destructor_impl : public integral_constant< is_scalar_v< T > || is_reference_v< T > > {} ;

template< typename T >
struct is_trivially_destructible : _trivial_destructor_impl< typename remove_all_extents< T >::type > {} ;

template< typename T >
struct is_trivially_destructible< T[] > : public false_type {} ;

#else
#error "uti: no implementation for 'is_trivially_destructible' available"
#endif

template< typename T >
inline constexpr bool is_trivially_destructible_v = is_trivially_destructible< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_copy_constructible : is_constructible
                                <
                                        T,
                                        add_lvalue_reference_t< add_const_t< T > >
                                > {} ;

template< typename T >
inline constexpr bool is_copy_constructible_v = is_copy_constructible< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_move_constructible : is_constructible
                                <
                                        T,
                                        add_rvalue_reference_t< T >
                                > {} ;

template< typename T >
inline constexpr bool is_move_constructible_v = is_move_constructible< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_trivially_copy_constructible : is_trivially_constructible< T, add_lvalue_reference_t< add_const_t< T > > > {} ;

template< typename T >
inline constexpr bool is_trivially_copy_constructible_v = is_trivially_copy_constructible< T >::value ;

////////////////////////////////////////////////////////////////////////////////

#if __has_builtin( __is_trivially_copyable )

template< typename T >
struct is_trivially_copyable : integral_constant< __is_trivially_copyable( T ) > {} ;

#elif defined( UTI_HAS_STL )

template< typename T >
struct is_trivially_copyable : std::is_trivially_copyable< T > {} ;

#else
#error "uti: no implementation for 'is_trivially_copyable' available"
#endif

template< typename T >
inline constexpr bool is_trivially_copyable_v = is_trivially_copyable< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_trivially_move_constructible : is_trivially_constructible< T, add_rvalue_reference_t< T > > {} ;

template< typename T >
inline constexpr bool is_trivially_move_constructible_v = is_trivially_move_constructible< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_nothrow_default_constructible : is_nothrow_constructible< T > {} ;

template< typename T >
inline constexpr bool is_nothrow_default_constructible_v = is_nothrow_default_constructible< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_nothrow_copy_constructible : is_nothrow_constructible< T, add_lvalue_reference_t< add_const_t< T > > > {} ;

template< typename T >
inline constexpr bool is_nothrow_copy_constructible_v = is_nothrow_copy_constructible< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_nothrow_move_constructible : is_nothrow_constructible< T, add_rvalue_reference_t< T > > {} ;

template< typename T >
inline constexpr bool is_nothrow_move_constructible_v = is_nothrow_move_constructible< T >::value ;

////////////////////////////////////////////////////////////////////////////////
///     convertibility
////////////////////////////////////////////////////////////////////////////////

template< typename T >
auto _test_returnable ( int ) -> decltype( void( static_cast< T( * )() >( nullptr ) ), true_type {} ) ;

template< typename >
auto _test_returnable ( ... ) -> false_type ;

template< typename From, typename To >
auto _test_implicitly_convertible ( int ) -> decltype( void( uti::declval< void( & )( To ) >()( uti::declval< From >() ) ), true_type {} ) ;

template< typename, typename >
auto _test_implicitly_convertible ( ... ) -> false_type ;


template< typename From, typename To >
struct is_convertible
        : integral_constant
          <
                ( decltype( _test_returnable< To >( 0 ) )::value &&
                  decltype( _test_implicitly_convertible< From, To >( 0 ) )::value ) ||
                ( is_void_v< From > && is_void_v< To > )
          > {} ;

template< typename From, typename To >
inline constexpr bool is_convertible_v = is_convertible< From, To >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename To >
void_t< To() > convert_to ( To ) noexcept ;

template< typename From, typename To, typename = void >
struct _is_nothrow_convertible_impl : false_type {} ;

template< typename From, typename To >
struct _is_nothrow_convertible_impl< From, To, enable_if_t< noexcept( convert_to< To >( uti::declval< From >() ) ) > > : true_type {} ;

template< typename From, typename To >
struct is_nothrow_convertible : conditional_t
                                <
                                        is_void_v< From >,
                                        is_void< To >,
                                        _is_nothrow_convertible_impl< From, To >
                                > {} ;

template< typename From, typename To >
inline constexpr bool is_nothrow_convertible_v = is_nothrow_convertible< From, To >::value ;


} // namespace uti
