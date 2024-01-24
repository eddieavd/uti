//
//
//      uti
//      ref_wrap.hpp
//

#pragma once

#include <meta/traits.hpp>
#include <meta/invoke.hpp>


namespace uti
{


template< typename T >
T * addressof ( T const & t ) noexcept ;


template< typename T >
class reference_wrapper // : public _weak_result_type< T >
{
public:
        using type = T ;
private:
        type * f_ ;

        static void _fn ( T &  ) noexcept ;
        static void _fn ( T && ) = delete ;
public:
        template< typename U, typename = enable_if_t< !is_same_v< remove_cvref_t< U >, reference_wrapper >, decltype( _fn( uti::declval< U >() ) ) > >
        constexpr reference_wrapper ( U && _u_ ) noexcept( noexcept( _fn( uti::declval< U >() ) ) )
        {
                type & f = static_cast< U && >( _u_ );
                f_ = uti::addressof( f );
        }

        /// access
        constexpr operator type& () const noexcept { return *f_; }

        /// invoke
#ifdef UTI_HAS_STL
        template< typename... Args >
        constexpr typename std::__invoke_of< type&, Args... >::type
        operator() ( Args&&... _args_ ) const
        {
                return std::invoke( std::get(), UTI_FWD( _args_ )... );
        }
#endif
};


template< typename T >
reference_wrapper ( T & ) -> reference_wrapper< T > ;


template< typename T >
inline constexpr reference_wrapper< T >
ref ( T & _t_ ) noexcept
{
        return reference_wrapper< T >( _t_ );
}

template< typename T >
inline constexpr reference_wrapper< T >
ref ( reference_wrapper< T > _t_ ) noexcept
{
        return _t_;
}

template< typename T >
inline constexpr reference_wrapper< T const >
cref ( T const & _t_ ) noexcept
{
        return reference_wrapper< T const >( _t_ );
}

template< typename T >
inline constexpr reference_wrapper< T const >
cref ( reference_wrapper< T > _t_ ) noexcept
{
        return _t_;
}

template< typename T > void  ref (T const && ) = delete ;
template< typename T > void cref (T const && ) = delete ;


template< typename T >
struct _unwrap_reference : type_identity< T > {} ;

template< typename T >
struct _unwrap_reference< reference_wrapper< T > > : type_identity< T & > {} ;

template< typename T >
struct unwrap_reference : _unwrap_reference< T > {} ;

template< typename T >
using unwrap_reference_t = typename unwrap_reference< T >::type ;

template< typename T >
struct unwrap_ref_decay : unwrap_reference< typename decay< T >::type > {} ;

template< typename T >
using unwrap_ref_decay_t = typename unwrap_ref_decay< T >::type ;


} // namespace uti
