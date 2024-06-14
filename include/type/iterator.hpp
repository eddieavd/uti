//
//
//      uti
//      iterator.hpp
//

#pragma once

#include <type/traits.hpp>
#include <meta/concepts.hpp>


namespace uti
{


////////////////////////////////////////////////////////////////////////////////

struct default_sentinel_t {} ;

inline constexpr default_sentinel_t default_sentinel {} ;

////////////////////////////////////////////////////////////////////////////////

struct         input_iterator_tag ;
struct        output_iterator_tag ;
struct       forward_iterator_tag ;
struct bidirectional_iterator_tag ;
struct random_access_iterator_tag ;
struct    contiguous_iterator_tag ;

template< typename Iter >                              struct iterator_traits           ;
template< typename Iter > requires is_object_v< Iter > struct iterator_traits< Iter * > ;

template< typename Iter, typename > struct _iterator_traits ;


namespace _detail
{

template< typename T > using _with_ref = T & ;

template< typename T > concept _can_reference   = requires { typename _with_ref< T > ; } ;
template< typename T > concept _dereferenceable = requires( T & t )
{
        { *t } -> _can_reference ;
} ;

} // namespace _detail


template< _detail::_dereferenceable T >
using iter_reference_t = decltype( *declval< T & >() ) ;

////////////////////////////////////////////////////////////////////////////////

namespace _detail::_imove
{


void iter_move () ;

template< typename T >
concept _adl_imove = ( is_class_v< remove_reference_t< T > >
                    || is_enum_v < remove_reference_t< T > >
                    || is_union_v< remove_reference_t< T > > )
                    && requires( T&& t ) { iter_move( static_cast< T&& >( t ) ) ; } ;

struct _imove
{
private:
        template< typename T >
        struct _result
        { using type = iter_reference_t< T > ; } ;

        template< typename T >
                requires _adl_imove< T >
        struct _result< T >
        { using type = decltype( iter_move( declval< T >() ) ) ; } ;

        template< typename T >
                requires( !_adl_imove< T > )
                && is_lvalue_reference_v< iter_reference_t< T > >
        struct _result< T >
        { using type = remove_reference_t< iter_reference_t< T > > && ; } ;

        template< typename T >
        static constexpr bool _s_noexcept ()
        {
                if constexpr( _adl_imove< T > )
                        return noexcept( iter_move( declval< T >() ) ) ;
                else
                        return noexcept( *declval< T >() ) ;
        }
public:
        template< _detail::_dereferenceable T >
        using _type = typename _result< T >::type ;

        template< _detail::_dereferenceable T >
        UTI_NODISCARD
        constexpr _type< T >
        operator() ( T && e ) const noexcept( _s_noexcept< T >() )
        {
                if constexpr( _adl_imove< T > )
                        return iter_move( static_cast< T && >( e ) ) ;
                else if constexpr( is_lvalue_reference_v< iter_reference_t< T > > )
                        return static_cast< _type< T > >( *e ) ;
                else
                        return *e ;
        }
} ;


} // namespace _detail::_imove


template< _detail::_dereferenceable T >
        requires _detail::_can_reference< _detail::_imove::_imove::_type< T & > >
using iter_rvalue_reference_t = _detail::_imove::_imove::_type< T & > ;

////////////////////////////////////////////////////////////////////////////////

template< typename Iter > struct incrementable_traits {} ;

template< typename Iter > requires is_object_v< Iter >
struct incrementable_traits< Iter * >
{
        using difference_type = ptrdiff_t ;
} ;

template< typename Iter >
struct incrementable_traits< Iter const > : incrementable_traits< Iter > {} ;

template< typename Iter >
        requires requires { typename Iter::difference_type ; }
struct incrementable_traits< Iter >
{
        using difference_type = typename Iter::difference_type ;
} ;

template< typename Iter >
        requires( !requires { typename Iter::difference_type ; } ) &&
        requires( Iter const & a, Iter const & b ) { { a - b } -> integral ; }
struct incrementable_traits< Iter >
{
        using difference_type = make_signed_t< decltype( declval< Iter >() - declval< Iter >() ) > ;
} ;

////////////////////////////////////////////////////////////////////////////////

namespace _detail
{


template< typename Iter >
concept _primary_iter_traits = is_base_of_v< _iterator_traits< Iter, void >, iterator_traits< Iter > > ;

template< typename Iter, typename T >
struct _iter_traits_impl : type_identity< iterator_traits< Iter > > {} ;

template< typename Iter, typename T > requires _primary_iter_traits< Iter >
struct _iter_traits_impl< Iter, T > : type_identity< T > {} ;

template< typename Iter, typename T = Iter >
using _iter_traits = typename _iter_traits_impl< Iter, T >::type ;

template< typename T >
using _iter_diff_t = typename _iter_traits< T, incrementable_traits< T > >::difference_type ;


} // namespace _detail


template< typename T >
using iter_difference_t = _detail::_iter_diff_t< remove_cvref_t< T > > ;

////////////////////////////////////////////////////////////////////////////////

namespace _detail
{


template< typename > struct _cond_value_type {} ;

template< typename T > requires is_object_v< T >
struct _cond_value_type< T >
{
        using value_type = remove_cv_t< T > ;
} ;

template< typename T >
concept _has_member_value_type = requires { typename T::value_type ; } ;

template< typename T >
concept _has_member_element_type = requires { typename T::element_type ; } ;


} // namespace _detail

////////////////////////////////////////////////////////////////////////////////

template< typename Iter > struct indirectly_readable_traits {} ;

template< typename T >
struct indirectly_readable_traits< T * > : _detail::_cond_value_type< T > {} ;

template< typename Iter > requires is_array_v< Iter >
struct indirectly_readable_traits< Iter >
{
        using value_type = remove_cv_t< remove_extent_t< Iter > > ;
} ;

template< typename Iter >
struct indirectly_readable_traits< Iter const > : indirectly_readable_traits< Iter > {} ;

template< _detail::_has_member_value_type T >
struct indirectly_readable_traits< T > : _detail::_cond_value_type< typename T::value_type > {} ;

template< _detail::_has_member_element_type T >
struct indirectly_readable_traits< T > : _detail::_cond_value_type< typename T::element_type > {} ;

template< _detail::_has_member_value_type T >
        requires _detail::_has_member_element_type< T >
        && same_as< remove_cv_t< typename T::element_type >,
                    remove_cv_t< typename T::  value_type > >
struct indirectly_readable_traits< T > : _detail::_cond_value_type< typename T::value_type > {} ;

template< _detail::_has_member_value_type T >
        requires _detail::_has_member_element_type< T >
struct indirectly_readable_traits< T > {} ;


namespace _detail
{


template< typename T >
using _iter_value_t = typename _iter_traits< T, indirectly_readable_traits< T > >::value_type ;


} // namespace _detail


template< typename T >
using iter_value_t = _detail::_iter_value_t< remove_cvref_t< T > > ;

////////////////////////////////////////////////////////////////////////////////

namespace _detail
{


template< typename Iter >
concept _cpp17_iterator = requires( Iter iter )
{
        {  *iter   } -> _can_reference     ;
        { ++iter   } ->  same_as< Iter & > ;
        {  *iter++ } -> _can_reference     ;
} && copyable< Iter > ;

template< typename Iter >
concept _cpp17_input_iterator = _cpp17_iterator< Iter >
        && equality_comparable< Iter >
        && requires( Iter iter )
{
        typename incrementable_traits< Iter >:: difference_type ;
        typename indirectly_readable_traits< Iter >::value_type ;
        typename common_reference_t< iter_reference_t< Iter >&&,
                 typename indirectly_readable_traits< Iter >::value_type & > ;
        typename common_reference_t< decltype( *iter++ )&&,
                 typename indirectly_readable_traits< Iter >::value_type & > ;
        requires signed_integral<
                typename incrementable_traits< Iter >::difference_type > ;
} ;

template< typename Iter >
concept _cpp17_fwd_iterator = _cpp17_input_iterator< Iter >
        && constructible_from< Iter >
        && is_lvalue_reference_v< iter_reference_t< Iter > >
        && same_as< remove_cvref_t< iter_reference_t< Iter > >,
                typename indirectly_readable_traits< Iter >::value_type >
        && requires( Iter iter )
{
        {  iter++ } -> convertible_to< Iter const & > ;
        { *iter++ } -> same_as< iter_reference_t< Iter > > ;
} ;

template< typename Iter >
concept _cpp17_bidi_iterator = _cpp17_fwd_iterator< Iter >
        && requires( Iter iter )
{
        { --iter   } -> same_as< Iter & > ;
        {   iter-- } -> convertible_to< Iter const & > ;
        {  *iter-- } -> same_as< iter_reference_t< Iter > > ;
} ;

template< typename Iter >
concept _cpp17_randacc_iterator = _cpp17_bidi_iterator< Iter >
        && totally_ordered< Iter >
        && requires( Iter iter, typename incrementable_traits< Iter >::difference_type n )
{
        { iter +=    n } -> same_as< Iter & > ;
        { iter -=    n } -> same_as< Iter & > ;
        { iter +     n } -> same_as< Iter   > ;
        { iter -     n } -> same_as< Iter   > ;
        {    n +  iter } -> same_as< Iter   > ;
        {    n -  iter } -> same_as< Iter   > ;
        { iter -  iter } -> same_as< decltype( n ) > ;
        { iter[ n ]    } -> convertible_to< iter_reference_t< Iter > > ;
} ;

template< typename Iter >
concept _iter_with_nested_types = requires
{
        typename Iter::iterator_category ;
        typename Iter::       value_type ;
        typename Iter::  difference_type ;
        typename Iter::        reference ;
} ;

template< typename Iter >
concept _iter_without_nested_types = !_iter_with_nested_types< Iter > ;

template< typename Iter >
concept _iter_without_category =
        !requires { typename Iter::iterator_category ; } ;


} // namespace _detail


template< typename Iter >
        requires _detail::_iter_with_nested_types< Iter >
struct _iterator_traits< Iter, void >
{
private:
        template< typename Iter_ >
        struct _ptr
        { using type = void ; } ;

        template< typename Iter_ > requires requires { typename Iter_::pointer ; }
        struct _ptr< Iter_ >
        { using type = typename Iter_::pointer ; } ;

public:
        using iterator_category = typename       Iter  ::iterator_category ;
        using        value_type = typename       Iter  ::       value_type ;
        using   difference_type = typename       Iter  ::  difference_type ;
        using           pointer = typename _ptr< Iter >::             type ;
        using         reference = typename       Iter  ::        reference ;
} ;

template< typename Iter >
        requires _detail::_iter_without_nested_types< Iter >
              && _detail::_cpp17_input_iterator     < Iter >
struct _iterator_traits< Iter, void >
{
private:
        template< typename Iter_ >
        struct _cat
        { using type = input_iterator_tag ; } ;

        template< typename Iter_ >
                requires requires { typename Iter_::iterator_category ; }
        struct _cat< Iter_ >
        { using type = typename Iter_::iterator_category ; } ;

        template< typename Iter_ >
                requires _detail::_iter_without_category < Iter_ >
                      && _detail::_cpp17_randacc_iterator< Iter_ >
        struct _cat< Iter_ >
        { using type = random_access_iterator_tag ; } ;

        template< typename Iter_ >
                requires _detail::_iter_without_category< Iter_ >
                      && _detail::_cpp17_bidi_iterator  < Iter_ >
        struct _cat< Iter_ >
        { using type = bidirectional_iterator_tag ; } ;

        template< typename Iter_ >
                requires _detail::_iter_without_category< Iter_ >
                      && _detail::_cpp17_fwd_iterator   < Iter_ >
        struct _cat< Iter_ >
        { using type = forward_iterator_tag ; } ;

        template< typename Iter_ >
        struct _ptr
        { using type = void ; } ;

        template< typename Iter_ > requires requires { typename Iter_::pointer ; }
        struct _ptr< Iter_ >
        { using type = typename Iter_::pointer ; } ;

        template< typename Iter_ >
                requires ( !requires { typename Iter_::point ; }
                      &&    requires( Iter_ & iter ) { iter.operator->() ; } )
        struct _ptr< Iter_ >
        { using type = decltype( declval< Iter_ & >().operator->() ) ; } ;

        template< typename Iter_ >
        struct _ref
        { using type = iter_reference_t< Iter_ > ; } ;

        template< typename Iter_ > requires requires { typename Iter_::reference ; }
        struct _ref< Iter_ >
        { using type = typename Iter_::reference ; } ;
public:
        using iterator_category = typename                       _cat< Iter >::           type ;
        using        value_type = typename indirectly_readable_traits< Iter >::     value_type ;
        using   difference_type = typename       incrementable_traits< Iter >::difference_type ;
        using           pointer = typename                       _ptr< Iter >::           type ;
        using         reference = typename                       _ref< Iter >::           type ;
} ;

template< typename Iter >
        requires _detail::_iter_without_nested_types< Iter >
              && _detail::_cpp17_iterator< Iter >
struct _iterator_traits< Iter, void >
{
private:
        template< typename Iter_ >
        struct _diff
        { using type = void ; } ;

        template< typename Iter_ >
                requires requires
                { typename incrementable_traits< Iter_ >::difference_type ; }
        struct _diff< Iter_ >
        { using type = typename incrementable_traits< Iter_ >::difference_type ; } ;
public:
        using iterator_category = output_iterator_tag ;
        using        value_type = void ;
        using   difference_type = typename _diff< Iter >::type ;
        using           pointer = void ;
        using         reference = void ;
} ;


namespace _detail
{


template< typename Iter >
struct _iter_concept_impl ;

template< typename Iter >
        requires requires { typename _iter_traits< Iter >::iterator_concept ; }
struct _iter_concept_impl< Iter >
{ using type = typename _iter_traits< Iter >::iterator_concept ; } ;

template< typename Iter >
        requires ( !requires { typename _iter_traits< Iter >::iterator_concept ; }
              &&   !requires { typename _iter_traits< Iter >::iterator_category ; }
              &&   _primary_iter_traits< Iter > )
struct _iter_concept_impl< Iter >
{ using type = random_access_iterator_tag ; } ;

template< typename Iter >
struct _iter_concept_impl {} ;

template< typename Iter >
using _iter_concept = typename _iter_concept_impl< Iter >::type ;

template< typename In >
concept _indirectly_readable_impl = requires
{
        typename iter_value_t< In > ;
        typename iter_reference_t< In > ;
        typename iter_rvalue_reference_t< In > ;
        requires same_as< iter_reference_t< In const >,
                          iter_reference_t< In       > > ;
        requires same_as< iter_rvalue_reference_t< In const >,
                          iter_rvalue_reference_t< In       > > ;
} && common_reference_with< iter_reference_t< In >&&, iter_value_t< In >& >
  && common_reference_with< iter_reference_t< In >&&,
                            iter_rvalue_reference_t< In >&& >
  && common_reference_with< iter_rvalue_reference_t< In >&&,
                            iter_value_t< In > const & > ;


} // namespace _detail


template< typename In >
concept indirectly_readable = _detail::_indirectly_readable_impl< remove_cvref_t< In > > ;

template< indirectly_readable T >
using iter_common_reference_t = common_reference_t< iter_reference_t< T >, iter_value_t< T > & > ;

template< typename Out, typename T >
concept indirectly_writable = requires( Out && o, T && t )
{
        * o = UTI_FWD( t ) ;
        * UTI_FWD( o ) = UTI_FWD( t ) ;
        const_cast< iter_reference_t< Out > const && >( *o            ) = UTI_FWD( t ) ;
        const_cast< iter_reference_t< Out > const && >( *UTI_FWD( o ) ) = UTI_FWD( t ) ;
} ;


namespace _detail
{


class _max_diff_type ;
class _max_size_type ;

template< typename T >
concept _is_signed_int128
#if __SIZEOF_INT128__
        = same_as< T, __int128 > ;
#else
        = false ;
#endif

template< typename T >
concept _is_unsigned_int128
#if __SIZEOF_INT128__
        = same_as< T, unsigned __int128 > ;
#else
        = false ;
#endif

template< typename T >
concept _cv_bool = same_as< T const volatile, bool const volatile > ;

template< typename T >
concept _integral_nonbool = integral< T > && !_cv_bool< T > ;

template< typename T >
concept _is_int128 = _is_signed_int128< T > || _is_unsigned_int128< T > ;

template< typename T >
concept _is_integer_like = _integral_nonbool< T >
                        || _is_int128< T >
                        || same_as< T, _max_diff_type >
                        || same_as< T, _max_size_type > ;

template< typename T >
concept _is_signed_integer_like = signed_integral< T >
                               || _is_signed_int128< T >
                               || same_as< T, _max_diff_type > ;


} // namespace _detail


template< typename Iter >
concept weakly_incrementable = movable< Iter >
        && requires( Iter iter )
{
        typename iter_difference_t< Iter > ;
        requires _detail::_is_signed_integer_like< iter_difference_t< Iter > > ;
        { ++iter } -> same_as< Iter & > ;
        iter++ ;
} ;

template< typename Iter >
concept incrementable = regular< Iter > && weakly_incrementable< Iter >
        && requires( Iter iter )
{
        { iter++ } -> same_as< Iter > ;
} ;

template< typename Iter >
concept input_or_output_iterator =
        requires( Iter iter )
        { { *iter } -> _detail::_can_reference ; }
        && weakly_incrementable< Iter > ;

template< typename Sent, typename Iter >
concept sentinel_for = semiregular< Sent >
                    && input_or_output_iterator< Iter >
                    && _weakly_eq_comparable_with< Sent, Iter > ;

template< typename Sent, typename Iter >
inline constexpr bool disable_sized_sentinel_for = false ;

template< typename Sent, typename Iter >
concept sized_sentinel_for = sentinel_for< Sent, Iter >
                          && !disable_sized_sentinel_for< remove_cv_t< Sent >, remove_cv_t< Iter > >
                          && requires( Iter const & iter, Sent const & sent )
{
        { sent - iter } -> same_as< iter_difference_t< Iter > > ;
        { iter - sent } -> same_as< iter_difference_t< Iter > > ;
} ;

template< typename Iter >
concept input_iterator = input_or_output_iterator< Iter >
                      && indirectly_readable< Iter >
                      && requires { typename _detail::_iter_concept< Iter > ; }
                      && derived_from< _detail::_iter_concept< Iter >, input_iterator_tag > ;

template< typename Iter, typename T >
concept output_iterator = input_or_output_iterator< Iter >
                       && indirectly_writable< Iter, T >
                       && requires( Iter it, T && t ) { *it++ = UTI_FWD( t ) ; } ;

template< typename Iter >
concept forward_iterator = input_iterator< Iter >
                        && derived_from< _detail::_iter_concept< Iter >, forward_iterator_tag >
                        && incrementable< Iter > && sentinel_for< Iter, Iter > ;

template< typename Iter >
concept bidirectional_iterator = forward_iterator< Iter >
                              && derived_from< _detail::_iter_concept< Iter >, bidirectional_iterator_tag >
                              && requires( Iter it )
{
        { --it } -> same_as< Iter & > ;
        { it-- } -> same_as< Iter   > ;
} ;

template< typename Iter >
concept random_access_iterator = bidirectional_iterator< Iter >
                              && derived_from< _detail::_iter_concept< Iter >, random_access_iterator_tag >
                              && totally_ordered< Iter > && sized_sentinel_for< Iter, Iter >
                              && requires( Iter i, Iter const j, iter_difference_t< Iter > const n )
{
        { i += n } -> same_as< Iter & > ;
        { j +  n } -> same_as< Iter   > ;
        { n +  j } -> same_as< Iter   > ;
        { i -= j } -> same_as< Iter & > ;
        { j -  n } -> same_as< Iter   > ;
        { j[ n ] } -> same_as< iter_reference_t< Iter > > ;
} ;

template< typename Iter >
concept contiguous_iterator = random_access_iterator< Iter >
                           && derived_from< _detail::_iter_concept< Iter >, contiguous_iterator_tag >
                           && is_lvalue_reference_v< iter_reference_t< Iter > >
                           && same_as< iter_value_t< Iter >, remove_cvref_t< iter_reference_t< Iter > > >
                           && requires( Iter const & iter )
{
        { to_address( iter ) } -> same_as< add_pointer_t< iter_reference_t< Iter > > > ;
} ;

////////////////////////////////////////////////////////////////////////////////

struct         input_iterator_tag                                     {} ;
struct        output_iterator_tag                                     {} ;
struct       forward_iterator_tag : public         input_iterator_tag {} ;
struct bidirectional_iterator_tag : public       forward_iterator_tag {} ;
struct random_access_iterator_tag : public bidirectional_iterator_tag {} ;
struct    contiguous_iterator_tag : public random_access_iterator_tag {} ;

template< typename Iter                      > struct  iterator_traits    ;
template< typename Iter, typename = void_t<> > struct _iterator_traits {} ;

template< typename Iter > struct iterator_traits : public _iterator_traits< Iter > {} ;

template< typename T > requires is_object_v< T >
struct iterator_traits< T * >
{
        using  iterator_concept =    contiguous_iterator_tag ;
        using iterator_category = random_access_iterator_tag ;
        using        value_type = remove_cv_t< T > ;
        using   difference_type = ptrdiff_t ;
        using           pointer = T * ;
        using         reference = T & ;
} ;


} // namespace uti
































