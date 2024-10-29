//
//
//      uti
//      string.hpp
//

#pragma once

#include <util/assert.hpp>
#include <type/traits.hpp>
#include <allocator/meta.hpp>
#include <allocator/default.hpp>
#include <allocator/resource.hpp>
#include <iterator/meta.hpp>
#include <iterator/base.hpp>
#include <iterator/reverse_iterator.hpp>
#include <meta/concepts.hpp>
#include <container/meta.hpp>
#include <algo/mem.hpp>

#define UTI_SSO_CAP 23


namespace uti
{


template< typename CharType, typename Allocator >
class generic_string ;

using string = generic_string< char, allocator< char, malloc_resource > > ;


template< typename CharType, typename Allocator = allocator< CharType, malloc_resource > >
class generic_string
{
        static_assert( is_trivial_v< CharType >, "uti::string: bruh" ) ;

        static constexpr ssize_t sso_cap { UTI_SSO_CAP } ;

        using allocator_type = Allocator                          ;
        using  _alloc_traits = allocator_traits< allocator_type > ;
        using     block_type = typename _alloc_traits::block_type ;

        struct heap_string
        {
                ssize_t capacity_ ;
                ssize_t     size_ ;
                ssize_t  padding_ ;
        } ;
        struct alignas( heap_string ) stack_string
        {
                CharType data_ [ sso_cap ] ;
                u8_t     size_ ;
        } ;

        static_assert(  sizeof( heap_string ) ==  sizeof( stack_string ) ) ;
        static_assert( alignof( heap_string ) == alignof( stack_string ) ) ;

        union string_rep
        {
                heap_string   heap_ ;
                stack_string stack_ ;
        } ;
public:
        using      value_type =   CharType ;
        using       size_type =  size_t    ;
        using      ssize_type = ssize_t    ;
        using difference_type = ssize_type ;

        using         pointer = value_type       * ;
        using   const_pointer = value_type const * ;
        using       reference = value_type       & ;
        using const_reference = value_type const & ;

        using               iterator = iterator_base< value_type      , random_access_iterator_tag > ;
        using         const_iterator = iterator_base< value_type const, random_access_iterator_tag > ;
        using       reverse_iterator = ::uti::reverse_iterator<       iterator > ;
        using const_reverse_iterator = ::uti::reverse_iterator< const_iterator > ;

        constexpr generic_string () noexcept { _init_small() ; }

        explicit constexpr generic_string ( ssize_type _capacity_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;
        explicit constexpr generic_string ( const_pointer  _cstr_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;

        constexpr generic_string ( value_type _char_, ssize_type _count_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;

        template< meta::forward_iterator Iter >
                requires meta::convertible_to< iter_value_t< Iter >, value_type >
        constexpr generic_string ( Iter _begin_, Iter const _end_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;

        template< meta::simple_container T >
                requires meta::convertible_to< typename T::value_type, value_type >
        constexpr generic_string ( T const & _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;

        constexpr generic_string ( generic_string const &  _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;
        constexpr generic_string ( generic_string       && _other_ )     noexcept                 ;

        constexpr generic_string & operator= ( generic_string const &  _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;
        constexpr generic_string & operator= ( generic_string       && _other_ )     noexcept                 ;

        constexpr ~generic_string () noexcept { reset() ; }

        constexpr ssize_type reserve            ( ssize_type _capacity_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;
        constexpr ssize_type reserve_additional ( ssize_type _capacity_ ) UTI_NOEXCEPT_UNLESS_BADALLOC { return reserve( size() + _capacity_ ) ; }

        template< meta::forward_iterator Iter >
                requires meta::convertible_to< iter_value_t< Iter >, value_type >
        constexpr ssize_type append ( Iter _begin_, Iter const _end_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;

        template< meta::simple_container T >
                requires meta::convertible_to< typename T::value_type, value_type >
        constexpr ssize_type append ( T const & _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;

        UTI_NODISCARD constexpr const_pointer c_str () const noexcept { return ptr_ ; }

        UTI_NODISCARD constexpr       reference operator[] ( ssize_type _index_ )       noexcept { return ptr_[ _index_ ] ; }
        UTI_NODISCARD constexpr const_reference operator[] ( ssize_type _index_ ) const noexcept { return ptr_[ _index_ ] ; }

        UTI_NODISCARD constexpr       reference at ( ssize_type _index_ )       noexcept { return ptr_[ _index_ ] ; }
        UTI_NODISCARD constexpr const_reference at ( ssize_type _index_ ) const noexcept { return ptr_[ _index_ ] ; }

        UTI_NODISCARD constexpr ssize_type capacity () const noexcept { if( _is_small() ) return sso_cap                     ; return rep_.heap_.capacity_ ; }
        UTI_NODISCARD constexpr ssize_type     size () const noexcept { if( _is_small() ) return sso_cap - rep_.stack_.size_ ; return rep_.heap_.    size_ ; }
        UTI_NODISCARD constexpr bool          empty () const noexcept { return !ptr_ || ( size() == 0 ) ; }
        UTI_NODISCARD constexpr bool           null () const noexcept { return !ptr_  ; }

        constexpr void clear () noexcept ;
        constexpr void reset () noexcept ;

        UTI_NODISCARD constexpr       iterator  begin ()       noexcept { return ptr_    ; }
        UTI_NODISCARD constexpr const_iterator  begin () const noexcept { return ptr_    ; }
        UTI_NODISCARD constexpr const_iterator cbegin () const noexcept { return begin() ; }

        UTI_NODISCARD constexpr       iterator  end ()       noexcept { return ptr_ + size() ; }
        UTI_NODISCARD constexpr const_iterator  end () const noexcept { return ptr_ + size() ; }
        UTI_NODISCARD constexpr const_iterator cend () const noexcept { return         end() ; }

        UTI_NODISCARD constexpr       reverse_iterator  rbegin ()       noexcept { return  --end() ; }
        UTI_NODISCARD constexpr const_reverse_iterator  rbegin () const noexcept { return  --end() ; }
        UTI_NODISCARD constexpr const_reverse_iterator crbegin () const noexcept { return rbegin() ; }

        UTI_NODISCARD constexpr       reverse_iterator  rend ()       noexcept { return --begin() ; }
        UTI_NODISCARD constexpr const_reverse_iterator  rend () const noexcept { return --begin() ; }
        UTI_NODISCARD constexpr const_reverse_iterator crend () const noexcept { return    rend() ; }

        UTI_NODISCARD constexpr       reference  front ()       noexcept { return at( 0 ) ; }
        UTI_NODISCARD constexpr const_reference  front () const noexcept { return at( 0 ) ; }
        UTI_NODISCARD constexpr const_reference cfront () const noexcept { return at( 0 ) ; }

        UTI_NODISCARD constexpr       reference  back ()       noexcept { return at( size() - 1 ) ; }
        UTI_NODISCARD constexpr const_reference  back () const noexcept { return at( size() - 1 ) ; }
        UTI_NODISCARD constexpr const_reference cback () const noexcept { return at( size() - 1 ) ; }

        UTI_NODISCARD constexpr bool is_small () const noexcept { return _is_small() ; }
private:
        iterator   ptr_ { nullptr } ;
        string_rep rep_ ;

        constexpr void _init_small ()       noexcept ;
        constexpr bool   _is_small () const noexcept ;

        constexpr void _set_size ( ssize_type _size_ ) noexcept ;
} ;


template< typename CharType, typename Allocator >
constexpr void
generic_string< CharType, Allocator >::_init_small () noexcept
{
        rep_.stack_ = {} ;
//      ptr_ = rep_.stack_.data_ ;
        ptr_ = static_cast< pointer >( static_cast< void * >( &rep_ ) ) ;
        rep_.stack_.size_ = sso_cap ;
}

template< typename CharType, typename Allocator >
constexpr bool
generic_string< CharType, Allocator >::_is_small () const noexcept
{
        return ptr_ == static_cast< const_pointer >( static_cast< void const * >( &rep_ ) ) ;
//      return ptr_ == rep_.stack_.data_ ;
}

template< typename CharType, typename Allocator >
constexpr void
generic_string< CharType, Allocator >::_set_size ( ssize_type _size_ ) noexcept
{
        if( _is_small() )
        {
                UTI_CEXPR_ASSERT( _size_ < sso_cap, "uti::string::_set_size: internal error" ) ;

                rep_.stack_.size_ = sso_cap - _size_ ;
        }
        else
        {
                rep_.heap_.size_ = _size_ ;
        }
}


template< typename CharType, typename Allocator >
constexpr
generic_string< CharType, Allocator >::generic_string ( ssize_type _capacity_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        _init_small() ;

        reserve( _capacity_ ) ;
}

template< typename CharType, typename Allocator >
constexpr
generic_string< CharType, Allocator >::generic_string ( const_pointer _cstr_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        append( _cstr_, _cstr_ + ::uti::strlen( _cstr_ ) ) ;
}

template< typename CharType, typename Allocator >
constexpr
generic_string< CharType, Allocator >::generic_string ( value_type _char_, ssize_type _count_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        _init_small() ;

        reserve( _count_ ) ;
        ::uti::memset( begin(), end(), _char_ ) ;
        _set_size( _count_ ) ;
        at( size() ) = value_type( 0 ) ;
}

template< typename CharType, typename Allocator >
template< meta::forward_iterator Iter >
        requires meta::convertible_to< iter_value_t< Iter >, CharType >
constexpr
generic_string< CharType, Allocator >::generic_string ( Iter _begin_, Iter const _end_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        append( _begin_, _end_ ) ;
}

template< typename CharType, typename Allocator >
template< meta::simple_container T >
        requires meta::convertible_to< typename T::value_type, CharType >
constexpr
generic_string< CharType, Allocator >::generic_string ( T const & _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        append( _other_.begin(), _other_.end() ) ;
}

template< typename CharType, typename Allocator >
constexpr
generic_string< CharType, Allocator >::generic_string ( generic_string const & _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        append( _other_ ) ;
}

template< typename CharType, typename Allocator >
constexpr
generic_string< CharType, Allocator >::generic_string ( generic_string && _other_ ) noexcept
{
        if( _other_._is_small() )
        {
                _init_small() ;

                append( _other_ ) ;
        }
        else
        {
                rep_.heap_ = {} ;

                ptr_ = _other_.ptr_ ;
                rep_.heap_.capacity_ = _other_.rep_.heap_.capacity_ ;
                rep_.heap_.    size_ = _other_.rep_.heap_.    size_ ;
        }
        _other_._init_small() ;
}

template< typename CharType, typename Allocator >
constexpr
generic_string< CharType, Allocator > &
generic_string< CharType, Allocator >::operator= ( generic_string const & _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        clear() ;
        append( _other_ ) ;

        return *this ;
}

template< typename CharType, typename Allocator >
constexpr
generic_string< CharType, Allocator > &
generic_string< CharType, Allocator >::operator= ( generic_string && _other_ ) noexcept
{
        reset() ;

        if( _other_._is_small() )
        {
                uti::copy( _other_.begin(), _other_.end(), begin() ) ;
                _set_size( _other_.size() ) ;
        }
        else
        {
                rep_.heap_ = {} ;

                ptr_ = _other_.ptr_ ;
                rep_.heap_.capacity_ = _other_.rep_.heap_.capacity_ ;
                rep_.heap_.    size_ = _other_.rep_.heap_.    size_ ;
        }
        _other_._init_small() ;
        return *this ;
}

template< typename CharType, typename Allocator >
constexpr
generic_string< CharType, Allocator >::ssize_type
generic_string< CharType, Allocator >::reserve ( ssize_type _capacity_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        if( null() ) _init_small() ;

        if( _capacity_ <= capacity() ) return capacity() ;

        /// at this point, _capacity_ is definitely greater than sso_cap

        if( _is_small() )
        {
                block_type block = _alloc_traits::allocate( _capacity_ + 1 ) ;

                if( block.size_ >= _capacity_ + 1 )
                {
                        auto sz = size() ;
                        ::uti::copy( begin(), end(), block.begin_ ) ;

                        ptr_ = block.begin_ ;

                        rep_.heap_ = {} ;
                        rep_.heap_.capacity_ = block.size_ ;
                        rep_.heap_.    size_ = sz ;

                        at( sz ) = value_type( 0 ) ;
                }
        }
        else
        {
                block_type block { ptr_, rep_.heap_.capacity_ } ;

                _alloc_traits::reallocate( block, _capacity_ ) ;

                if( block.size_ >= _capacity_ )
                {
                        ptr_ = block.begin_ ;
                        rep_.heap_.capacity_ = block.size_ ;

                        at( size() ) = value_type( 0 ) ;
                }
        }
        return capacity() ;
}

template< typename CharType, typename Allocator >
template< meta::forward_iterator Iter >
        requires meta::convertible_to< iter_value_t< Iter >, CharType >
constexpr
generic_string< CharType, Allocator >::ssize_type
generic_string< CharType, Allocator >::append ( Iter _begin_, Iter const _end_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        ssize_type  sz = null() ? 0 : size() ;
        ssize_type len = ::uti::distance( _begin_, _end_ ) ;

        if( reserve( sz + len ) < sz + len ) return sz ;

        for( ssize_type i = 0; i < len; ++i )
        {
                if constexpr( meta::random_access_iterator< Iter > )
                {
                        at( sz + i ) = _begin_[ i ] ;
                }
                else
                {
                        at( sz + i ) = *_begin_++ ;
                }
        }
        _set_size( sz + len ) ;
        at( size() ) = value_type( 0 ) ;

        return sz + len ;
}

template< typename CharType, typename Allocator >
template< meta::simple_container T >
        requires meta::convertible_to< typename T::value_type, CharType >
constexpr
generic_string< CharType, Allocator >::ssize_type
generic_string< CharType, Allocator >::append ( T const & _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        return append( _other_.begin(), _other_.end() ) ;
}

template< typename CharType, typename Allocator >
constexpr void
generic_string< CharType, Allocator >::clear () noexcept
{
        _set_size( 0 ) ;
}

template< typename CharType, typename Allocator >
constexpr void
generic_string< CharType, Allocator >::reset () noexcept
{
        if( !null() && !_is_small() )
        {
                block_type block{ ptr_, capacity() } ;
                _alloc_traits::deallocate( block ) ;
        }
        _init_small() ;
}


} // namespace uti
























