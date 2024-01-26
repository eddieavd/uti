//
//
//      uti
//      traits.hpp
//

#pragma once

#include <util/config.hpp>


#ifndef UTI_MOVE
#define UTI_MOVE(...) \
        static_cast< typename ::uti::remove_reference_t< decltype(__VA_ARGS__)>&&>(__VA_ARGS__)
#endif

#ifndef UTI_FWD
#define UTI_FWD(...) \
        static_cast< decltype(__VA_ARGS__)&&>(__VA_ARGS__)
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

UTI_NORETURN inline void unreachable ()
{
        UTI_UNREACHABLE;
}

////////////////////////////////////////////////////////////////////////////////
///     declval
////////////////////////////////////////////////////////////////////////////////

template< typename T, typename U = T&& > U _declval (  int ) ;
template< typename T                   > T _declval ( long ) ;

template< typename T > auto declval () noexcept -> decltype( _declval< T >( 0 ) ) ;

using nullptr_t = decltype( nullptr ) ;
using ptrdiff_t = decltype( uti::declval< int * >() - uti::declval< int * >() ) ;

#ifdef UTI_HAS_STL
static_assert( std::is_same_v< nullptr_t, std::nullptr_t > ) ;
static_assert( std::is_same_v< ptrdiff_t, std::ptrdiff_t > ) ;
#endif

////////////////////////////////////////////////////////////////////////////////
///     identity
////////////////////////////////////////////////////////////////////////////////

template< typename... >
using void_t = void ;

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
struct add_const : type_identity< T const > {} ;

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
struct add_volatile : type_identity< T volatile > {} ;

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


template< typename T, typename = void >
struct is_referenceable : false_type {} ;

template< typename T >
struct is_referenceable< T, void_t< decltype( uti::declval< T & >() ) > > : true_type {} ;

template< typename T >
inline constexpr bool is_referenceable_v = is_referenceable< T >::value ;


template< typename T, bool = is_referenceable_v< T > >
struct _add_lvalue_reference_impl : type_identity< T > {} ;

template< typename T >
struct _add_lvalue_reference_impl< T, true > : type_identity< T & > {} ;

template< typename T >
struct add_lvalue_reference : _add_lvalue_reference_impl< T > {} ;

template< typename T >
using add_lvalue_reference_t = typename add_lvalue_reference< T >::type ;


template< typename T, bool = is_referenceable_v< T > >
struct _add_rvalue_reference_impl : type_identity< T > {} ;

template< typename T >
struct _add_rvalue_reference_impl< T, true > : type_identity< T && > {} ;

template< typename T >
struct add_rvalue_reference : _add_rvalue_reference_impl< T > {} ;

template< typename T >
using add_rvalue_reference_t = typename add_rvalue_reference< T >::type ;

////////////////////////////////////////////////////////////////////////////////
///     cvref stuff
////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct remove_cv : remove_const< remove_volatile_t< T > > {} ;

template< typename T >
using remove_cv_t = typename remove_cv< T >::type ;

template< typename From, typename To > struct copy_cv                            : type_identity< To                > {} ;
template< typename From, typename To > struct copy_cv< From const         , To > : type_identity< To const          > {} ;
template< typename From, typename To > struct copy_cv< From       volatile, To > : type_identity< To       volatile > {} ;
template< typename From, typename To > struct copy_cv< From const volatile, To > : type_identity< To const volatile > {} ;

template< typename From, typename To > using copy_cv_t = typename copy_cv< From, To >::type ;

template< typename T >
struct remove_cvref : remove_cv< remove_reference_t< T > > {} ;

template< typename T >
using remove_cvref_t = typename remove_cvref< T >::type ;

template< typename From, typename To > struct copy_cvref                :                       copy_cv  < From, To >   {} ;
template< typename From, typename To > struct copy_cvref< From & , To > : add_lvalue_reference< copy_cv_t< From, To > > {} ;
template< typename From, typename To > struct copy_cvref< From &&, To > : add_rvalue_reference< copy_cv_t< From, To > > {} ;

template< typename From, typename To > using copy_cvref_t = typename copy_cvref< From, To >::type ;

////////////////////////////////////////////////////////////////////////////////
///     enable if
////////////////////////////////////////////////////////////////////////////////

template< bool, typename T = void >
struct enable_if {} ;

template< typename T >
struct enable_if< true, T > : type_identity< T > {} ;

template< bool C, typename T = void >
using enable_if_t = typename enable_if< C, T >::type ;

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
struct conditional : type_identity< Then > {} ;

template< typename Then, typename Else >
struct conditional< false, Then, Else > : type_identity< Else > {} ;

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

template< typename... Args >
struct disjunction< false_type, Args... > : disjunction< Args... > {} ;

template< typename... Args >
inline constexpr bool disjunction_v = disjunction< Args... >::value ;

////////////////////////////////////////////////////////////////////////////////
///     primary
////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct remove_extent : type_identity< T > {} ;

template< typename T >
struct remove_extent< T[] > : type_identity< T > {} ;

template< typename T, size_t N >
struct remove_extent< T[ N ] > : type_identity< T > {} ;

template< typename T >
using remove_extent_t = typename remove_extent< T >::type ;


template< typename T >
struct remove_all_extents : type_identity< T > {} ;

template< typename T >
struct remove_all_extents< T[] > : remove_all_extents< T > {} ;

template< typename T, size_t N >
struct remove_all_extents< T[ N ] > : remove_all_extents< T > {} ;

template< typename T >
using remove_all_extents_t = typename remove_all_extents< T >::type ;

////////////////////////////////////////////////////////////////////////////////

#if __has_builtin( __is_empty )

template< typename T >
struct is_empty : integral_constant< __is_empty( T ) > {} ;

#elif defined( UTI_HAS_STL )

template< typename T >
struct is_empty : std::is_empty< T > {} ;

#else
template< typename T > struct is_empty UTI_DEFAULT_FOR_MISSING ;
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
template< typename T > struct is_final UTI_DEFAULT_FOR_MISSING ;
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


template< typename T >
struct remove_pointer : type_identity< T > {} ;

template< typename T >
struct remove_pointer< T * > : type_identity< T > {} ;

template< typename T >
using remove_pointer_t = typename remove_pointer< T >::type ;


template< typename T >
struct add_pointer : type_identity< T * > {} ;

template< typename T >
using add_pointer_t = typename add_pointer< T >::type ;

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
template< typename T > struct is_enum UTI_DEFAULT_FOR_MISSING ;
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
template< typename T > struct is_union UTI_DEFAULT_FOR_MISSING ;
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

template< typename T, bool = is_arithmetic_v< T > >
struct _is_signed_impl : false_type {} ;

template< typename T >
struct _is_signed_impl< T, true > : integral_constant< T( -1 ) < T( 0 ) > {} ;

template< typename T >
using is_signed = _is_signed_impl< T > ;

template< typename T >
inline constexpr bool is_signed_v = is_signed< T >::value ;

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

namespace _detail
{


template< typename B >  true_type _test_ptr_conv (    B const volatile * ) ;
template< typename   > false_type _test_ptr_conv ( void const volatile * ) ;

template< typename B, typename D > auto _test_is_base_of ( int ) -> decltype( _test_ptr_conv< B >( static_cast< D * >( nullptr ) ) ) ;
template< typename  , typename   > auto _test_is_base_of ( ... ) -> true_type ; // private or ambiguous base


} // namespace _detail


template< typename Base, typename Derived >
struct is_base_of : integral_constant< is_class_v< Base    > &&
                                       is_class_v< Derived > &&
                                       decltype( _detail::_test_is_base_of< Base, Derived >( 0 ) )::value
                                     > {} ;

template< typename Base, typename Derived >
inline constexpr bool is_base_of_v = is_base_of< Base, Derived >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
struct is_object : integral_constant< is_scalar_v< T >
                                   || is_array_v< T >
                                   || is_union_v< T >
                                   || is_class_v< T > > {} ;

template< typename T >
inline constexpr bool is_object_v = is_object< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T >
using alignment_of = integral_constant< alignof( T ) > ;

template< typename T >
inline constexpr auto alignment_of_v = alignment_of< T >::value ;

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
using is_convertible
        = integral_constant
          <
                ( decltype( _test_returnable< To >( 0 ) )::value &&
                  decltype( _test_implicitly_convertible< From, To >( 0 ) )::value ) ||
                ( is_void_v< From > && is_void_v< To > )
          > ;

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

////////////////////////////////////////////////////////////////////////////////
///     unary
////////////////////////////////////////////////////////////////////////////////

template< typename T >
using is = integral_constant< is_convertible_v< T, true_type > > ;

template< typename T >
inline constexpr bool is_v = is< T >::value ;


template< typename T >
using is_not = integral_constant< is_convertible_v< T, false_type > > ;

template< typename T >
inline constexpr bool is_not_v = is_not< T >::value ;

////////////////////////////////////////////////////////////////////////////////
///     detector
////////////////////////////////////////////////////////////////////////////////

struct notype ;

template< typename Default, typename Void,
          template< typename... > typename Fn,
          typename... Args >
struct _detector
{
        using type    = Default    ;
        using value_t = false_type ;
};

template< typename Default,
          template< typename... > typename Fn,
          typename... Args >
struct _detector< Default, void_t< Fn< Args... > >, Fn, Args... >
{
        using type    = Fn< Args... > ;
        using value_t = true_type     ;
};

template< template< typename... > typename Fn, typename... Args >
using is_detected = typename _detector< notype, void, Fn, Args... >::value_t ;

template< template< typename... > typename Fn, typename... Args >
inline constexpr bool is_detected_v = is_detected< Fn, Args... >::value ;

template< template< typename... > typename Fn, typename... Args >
using detected_t = typename _detector< notype, void, Fn, Args... >::type ;

template< typename Default, template< typename... > typename Fn, typename... Args >
using detected_or = _detector< Default, void, Fn, Args... > ;

template< typename Default, template< typename... > typename Fn, typename... Args >
using detected_or_t = typename detected_or< Default, Fn, Args... >::type ;

template< typename Expected, template< typename... > typename Fn, typename... Args >
using is_detected_exact = is_same< Expected, detected_t< Fn, Args... > > ;

template< typename Expected, template< typename... > typename Fn, typename... Args >
inline constexpr bool is_detected_exact_v = is_detected_exact< Expected, Fn, Args... >::value ;

template< typename To, template< typename... > typename Fn, typename... Args >
using is_detected_convertible = is_convertible< detected_t< Fn, Args... >, To > ;

template< typename To, template< typename... > typename Fn, typename... Args >
inline constexpr bool is_detected_convertible_v = is_detected_convertible< To, Fn, Args... >::value ;

////////////////////////////////////////////////////////////////////////////////
///     assignability
////////////////////////////////////////////////////////////////////////////////

template< typename T, typename U > using assign_t = decltype( uti::declval< T >() = uti::declval< U >() ) ;

template< typename T > using copy_assign_t = assign_t< add_lvalue_reference_t< T >, add_lvalue_reference_t< add_const_t< T > > > ;
template< typename T > using move_assign_t = assign_t< add_lvalue_reference_t< T >, add_rvalue_reference_t<              T   > > ;

template< typename T, typename U > using      is_assignable = integral_constant< is_detected_v<      assign_t, T, U > > ;
template< typename T             > using is_copy_assignable = integral_constant< is_detected_v< copy_assign_t, T    > > ;
template< typename T             > using is_move_assignable = integral_constant< is_detected_v< move_assign_t, T    > > ;

template< typename T, typename U > inline constexpr bool      is_assignable_v =      is_assignable< T, U >::value ;
template< typename T             > inline constexpr bool is_copy_assignable_v = is_copy_assignable< T    >::value ;
template< typename T             > inline constexpr bool is_move_assignable_v = is_move_assignable< T    >::value ;

template< typename T, typename U > using nothrow_assign = integral_constant< noexcept( uti::declval< T >() = uti::declval< U >() ) > ;

template< bool, typename T, typename U > struct _is_nothrow_assignable_impl               : false_type             {} ;
template<       typename T, typename U > struct _is_nothrow_assignable_impl< true, T, U > : nothrow_assign< T, U > {} ;

template< typename T, typename U > using is_nothrow_assignable = _is_nothrow_assignable_impl< is_assignable_v< T, U >, T, U > ;

template< typename T > using is_nothrow_copy_assignable = is_nothrow_assignable< add_lvalue_reference_t< T >, add_lvalue_reference_t< add_const_t< T > > > ;
template< typename T > using is_nothrow_move_assignable = is_nothrow_assignable< add_lvalue_reference_t< T >, add_rvalue_reference_t<              T   > > ;

template< typename T, typename U > inline constexpr bool      is_nothrow_assignable_v =      is_nothrow_assignable< T, U >::value ;
template< typename T             > inline constexpr bool is_nothrow_copy_assignable_v = is_nothrow_copy_assignable< T    >::value ;
template< typename T             > inline constexpr bool is_nothrow_move_assignable_v = is_nothrow_move_assignable< T    >::value ;

#if __has_builtin( __is_trivially_assignable )

template< typename T, typename U >
struct _is_trivially_assignable_impl : integral_constant< __is_trivially_assignable( T, U ) > {} ;

#elif defined( UTI_HAS_STL )

template< typename T, typename U >
struct _is_trivially_assignable_impl : std::is_trivially_assignable< T, U > {} ;

#else
template< typename T, typename U > struct _is_trivially_assignable_impl UTI_DEFAULT_FOR_MISSING ;
#endif

template< typename T, typename U > using      is_trivially_assignable = _is_trivially_assignable_impl< T, U > ;
template< typename T             > using is_trivially_copy_assignable =  is_trivially_assignable< T, add_lvalue_reference_t< add_const_t< T > > > ;
template< typename T             > using is_trivially_move_assignable =  is_trivially_assignable< T, add_rvalue_reference_t<              T   > > ;

template< typename T, typename U > inline constexpr bool      is_trivially_assignable_v =      is_trivially_assignable< T, U >::value ;
template< typename T             > inline constexpr bool is_trivially_copy_assignable_v = is_trivially_copy_assignable< T    >::value ;
template< typename T             > inline constexpr bool is_trivially_move_assignable_v = is_trivially_move_assignable< T    >::value ;

////////////////////////////////////////////////////////////////////////////////
///     constructibility
////////////////////////////////////////////////////////////////////////////////

template< typename T, typename... Args > using construct_t = decltype( T( uti::declval< Args >()... ) ) ;

template< typename T > using default_construct_t = construct_t< T                                             > ;
template< typename T > using    copy_construct_t = construct_t< T, add_lvalue_reference_t< add_const_t< T > > > ;
template< typename T > using    move_construct_t = construct_t< T, add_rvalue_reference_t<              T   > > ;

template< typename T, typename... Args > using         is_constructible = integral_constant< is_detected_v<         construct_t, T, Args... > > ;
template< typename T                   > using is_default_constructible = integral_constant< is_detected_v< default_construct_t, T          > > ;
template< typename T                   > using    is_copy_constructible = integral_constant< is_detected_v<    copy_construct_t, T          > > ;
template< typename T                   > using    is_move_constructible = integral_constant< is_detected_v<    move_construct_t, T          > > ;

template< typename T, typename... Args > inline constexpr bool         is_constructible_v =         is_constructible< T, Args... >::value ;
template< typename T                   > inline constexpr bool is_default_constructible_v = is_default_constructible< T          >::value ;
template< typename T                   > inline constexpr bool    is_copy_constructible_v =    is_copy_constructible< T          >::value ;
template< typename T                   > inline constexpr bool    is_move_constructible_v =    is_move_constructible< T          >::value ;

template< typename T, typename... Args > using nothrow_construct = integral_constant< noexcept( T( uti::declval< Args >()... ) ) > ;

template< bool, typename T, typename... Args > struct _is_nothrow_constructible_impl                     : false_type                      {} ;
template<       typename T, typename... Args > struct _is_nothrow_constructible_impl< true, T, Args... > : nothrow_construct< T, Args... > {} ;

template< typename T, typename... Args > using is_nothrow_constructible = _is_nothrow_constructible_impl< is_constructible_v< T, Args... >, T, Args... > ;

template< typename T > using is_nothrow_default_constructible = is_nothrow_constructible< T                                             > ;
template< typename T > using    is_nothrow_copy_constructible = is_nothrow_constructible< T, add_lvalue_reference_t< add_const_t< T > > > ;
template< typename T > using    is_nothrow_move_constructible = is_nothrow_constructible< T, add_rvalue_reference_t<              T   > > ;

template< typename T, typename... Args > inline constexpr bool         is_nothrow_constructible_v =         is_nothrow_constructible< T, Args... >::value ;
template< typename T                   > inline constexpr bool is_nothrow_default_constructible_v = is_nothrow_default_constructible< T          >::value ;
template< typename T                   > inline constexpr bool    is_nothrow_copy_constructible_v =    is_nothrow_copy_constructible< T          >::value ;
template< typename T                   > inline constexpr bool    is_nothrow_move_constructible_v =    is_nothrow_move_constructible< T          >::value ;


template< typename T > using destruct_t = decltype( uti::declval< T >().~T() ) ;

template< typename T > using is_destructible = integral_constant< is_detected_v< destruct_t, T > > ;

template< typename T > inline constexpr bool is_destructible_v = is_destructible< T >::value ;

template< typename T > using nothrow_destruct = integral_constant< noexcept( uti::declval< T >().~T() ) > ;

template< bool, typename T > struct _is_nothrow_destructible_impl            : false_type            {} ;
template<       typename T > struct _is_nothrow_destructible_impl< true, T > : nothrow_destruct< T > {} ;

template< typename T > using                 is_nothrow_destructible   = _is_nothrow_destructible_impl< is_destructible_v< T >, T > ;
template< typename T > inline constexpr bool is_nothrow_destructible_v =  is_nothrow_destructible< T >::value ;

////////////////////////////////////////////////////////////////////////////////

#if __has_builtin( __is_trivially_constructible )

template< typename T, typename... Args >
struct _is_trivially_constructible_impl : integral_constant< __is_trivially_constructible( T, Args... ) > {} ;

#elif defined( UTI_HAS_STL )

template< typename T, typename... Args >
struct _is_trivially_constructible_impl : std::is_trivially_constructible< T, Args... > {} ;

#else
template< typename T, typename... Args > struct _is_trivially_constructible_impl UTI_DEFAULT_FOR_MISSING ;
#endif

template< typename T, typename... Args > using is_trivially_constructible = _is_trivially_constructible_impl< T, Args... > ;

template< typename T > using is_trivially_default_constructible = is_trivially_constructible< T                                             > ;
template< typename T > using    is_trivially_copy_constructible = is_trivially_constructible< T, add_lvalue_reference_t< add_const_t< T > > > ;
template< typename T > using    is_trivially_move_constructible = is_trivially_constructible< T, add_rvalue_reference_t<              T   > > ;

template< typename T, typename... Args > inline constexpr bool         is_trivially_constructible_v =         is_trivially_constructible< T, Args... >::value ;
template< typename T                   > inline constexpr bool is_trivially_default_constructible_v = is_trivially_default_constructible< T          >::value ;
template< typename T                   > inline constexpr bool    is_trivially_copy_constructible_v =    is_trivially_copy_constructible< T          >::value ;
template< typename T                   > inline constexpr bool    is_trivially_move_constructible_v =    is_trivially_move_constructible< T          >::value ;

////////////////////////////////////////////////////////////////////////////////

#if __has_builtin( __is_trivially_destructible )

template< typename T >
using _is_trivially_destructible_impl = integral_constant< __is_trivially_destructible( T ) > ;

#elif __has_builtin( __has_trivial_destructor )

UTI_DIAGS_PUSH()
UTI_DIAGS_CLANG_DISABLE( -Wdeprecated-builtins )

template< typename T >
using _is_trivially_destructible_impl = integral_constant< is_destructible_v< T > && __has_trivial_destructor( T ) > ;

UTI_DIAGS_POP()

#elif defined( UTI_HAS_STL )

template< typename T >
using _is_trivially_destructible_impl = std::is_trivially_destructible< T > ;

#elif UTI_STD_VER <= 11

template< typename T >
using _trivial_destructor_impl = integral_constant< is_scalar_v< T > || is_reference_v< T > > ;

template< typename T >
using _is_trivially_destructible_impl = _trivial_destructor_impl< remove_all_extents_t< T > > ;

template< typename T >
using _is_trivially_destructible_impl< T[] > = false_type ;

#else
template< typename T > struct _is_trivially_destructible_impl UTI_DEFAULT_FOR_MISSING ;
#endif

template< typename T >
using is_trivially_destructible = _is_trivially_destructible_impl< T > ;

template< typename T >
inline constexpr bool is_trivially_destructible_v = is_trivially_destructible< T >::value ;

////////////////////////////////////////////////////////////////////////////////

#if __has_builtin( __is_trivially_copyable )

template< typename T >
using _is_trivially_copyable_impl = integral_constant< __is_trivially_copyable( T ) > ;

#elif defined( UTI_HAS_STL )

template< typename T >
using _is_trivially_copyable_impl = std::is_trivially_copyable< T > ;

#else

// https://en.cppreference.com/w/cpp/language/classes#Trivially_copyable_class
template< typename T >
using _is_trivially_copyable_impl = conjunction< conjunction
                                <
                                        disjunction
                                        <
                                                is_trivially_copy_constructible< T >,
                                                is_not< is_copy_constructible< T > >
                                        >,
                                        disjunction
                                        <
                                                is_trivially_move_constructible< T >,
                                                is_not< is_move_constructible< T > >
                                        >,
                                        disjunction
                                        <
                                                is_trivially_copy_assignable< T >,
                                                is_not< is_copy_assignable< T > >
                                        >,
                                        disjunction
                                        <
                                                is_trivially_move_assignable< T >,
                                                is_not< is_move_assignable< T > >
                                        > >,
                                        is_trivially_destructible< T >
                                > ;
#endif

template< typename T >
using is_trivially_copyable = _is_trivially_copyable_impl< T > ;

template< typename T >
inline constexpr bool is_trivially_copyable_v = is_trivially_copyable< T >::value ;


template< typename T >
using is_trivially_relocatable = integral_constant< UTI_IS_TRIVIALLY_RELOCATABLE( T ) > ;

template< typename T >
inline constexpr bool is_trivially_relocatable_v = is_trivially_relocatable< T >::value ;


// https://en.cppreference.com/w/cpp/language/classes#Trivial_class
template< typename T >
using is_trivial = conjunction< is_trivially_copyable< T >, is_trivially_default_constructible< T > > ;

template< typename T >
inline constexpr bool is_trivial_v = is_trivial< T >::value ;

////////////////////////////////////////////////////////////////////////////////

template< typename T, bool >
struct _decay : remove_cv_t< T > {} ;

template< typename T >
struct _decay< T, true > : conditional
                        <
                                is_array_v< T >,
                                remove_extent_t< T >*,
                                conditional_t
                                <
                                        is_function_v< T >,
                                        add_pointer_t< T >,
                                        remove_cv_t< T >
                                >
                        > {} ;

template< typename T, bool B >
using _decay_t = typename _decay< T, B >::type ;

template< typename T >
struct decay
{
private:
        using U = remove_reference_t< T > ;
public:
        using type = _decay_t< U, is_referenceable_v< U > > ;
};

template< typename T >
using decay_t = typename decay< T >::type ;

////////////////////////////////////////////////////////////////////////////////
///     swappability
////////////////////////////////////////////////////////////////////////////////

template< typename T > struct _is_swappable         ;
template< typename T > struct _is_nothrow_swappable ;

template< typename... Ts > struct tuple ;

template< typename >       struct _is_tuple_like_impl                   : false_type {} ;
template< typename... Ts > struct _is_tuple_like_impl< tuple< Ts... > > :  true_type {} ;

template< typename T > struct _is_tuple_like : public _is_tuple_like_impl< remove_cvref_t< T > >::type {} ;

template< typename T >
inline constexpr
enable_if_t
<
        conjunction_v
        <
                is_not< _is_tuple_like< T > >,
                is_move_constructible< T >,
                is_move_assignable< T >
        >
>
swap ( T &, T & )
        noexcept( is_nothrow_move_constructible_v< T > && is_nothrow_move_assignable_v< T > ) ;

template< typename T, ssize_t N >
inline constexpr
enable_if_t< _is_swappable< T >::value >
swap ( T ( & a )[ N ], T ( & b )[ N ] ) noexcept( _is_nothrow_swappable< T >::value ) ;

namespace _swappable
{


using uti::swap ;

struct _do_is_swappable_impl
{
        template< typename T, typename = decltype( swap( uti::declval< T & >(), uti::declval< T & >() ) ) > static  true_type _test ( int ) ;
        template< typename                                                                                > static false_type _test ( ... ) ;
};

struct _do_is_nothrow_swappable_impl
{
        template< typename T > static integral_constant< noexcept( swap( uti::declval< T & >(), uti::declval< T & >() ) ) > _test ( int ) ;
        template< typename   > static false_type                                                                            _test ( ... ) ;
};


} // namespace _swappable


template< typename T >
struct _is_swappable_impl : public _swappable::_do_is_swappable_impl { using type = decltype( _test< T >( 0 ) ) ; } ;

template< typename T >
struct _is_nothrow_swappable_impl : public _swappable::_do_is_nothrow_swappable_impl { using type = decltype( _test< T >( 0 ) ) ; } ;

template< typename T > struct _is_swappable         : public _is_swappable_impl        < T >::type {} ;
template< typename T > struct _is_nothrow_swappable : public _is_nothrow_swappable_impl< T >::type {} ;

template< typename T > using is_swappable         = _is_swappable        < T > ;
template< typename T > using is_nothrow_swappable = _is_nothrow_swappable< T > ;

template< typename T > inline constexpr bool is_swappable_v         = is_swappable        < T >::value ;
template< typename T > inline constexpr bool is_nothrow_swappable_v = is_nothrow_swappable< T >::value ;


} // namespace uti
