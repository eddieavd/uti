//
//
//      uti
//      string.hpp
//

#pragma once

#include <type/traits.hpp>
#include <iterator/meta.hpp>
#include <iterator/base.hpp>
#include <iterator/reverse_iterator.hpp>
#include <algo/copy.hpp>
#include <algo/mem.hpp>
#include <allocator/meta.hpp>
#include <string/string_view.hpp> // refactor: move strlen somewhere else

#define UTI_SSO_CAP 23


namespace uti
{


namespace _detail
{


template< typename CharType = char >
class _string_storage
{
        struct alignas( 8 ) small_string
        {
                CharType  data_ [ UTI_SSO_CAP ] ;
                u8_t      size_ ;
        } ;
        struct alignas( 8 ) heap_string
        {
                u64_t     size_ ;
                u64_t capacity_ ;
                u64_t  padding_ ;
        } ;

        static_assert(  sizeof( small_string ) ==  sizeof( heap_string ) ) ;
        static_assert( alignof( small_string ) == alignof( heap_string ) ) ;

        struct string_data
        {
                CharType * ptr_ ;

                union string_rep
                {
                        small_string small_string_ ;
                        heap_string   heap_string_ ;
                } rep_ ;
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

        constexpr _string_storage (                             ) noexcept ;
        constexpr _string_storage ( ssize_type const _capacity_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;

        constexpr _string_storage             ( _string_storage const &  ) UTI_NOEXCEPT_UNLESS_BADALLOC ;
        constexpr _string_storage & operator= ( _string_storage const &  ) UTI_NOEXCEPT_UNLESS_BADALLOC ;
        constexpr _string_storage             ( _string_storage       && )     noexcept                 ;
        constexpr _string_storage & operator= ( _string_storage       && )     noexcept                 ;

        constexpr ~_string_storage () noexcept ;

        constexpr void reserve ( ssize_type const _capacity_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;

        constexpr void deallocate () noexcept ;

        UTI_NODISCARD constexpr       pointer data ()       noexcept { return string_data_.ptr_ ; }
        UTI_NODISCARD constexpr const_pointer data () const noexcept { return string_data_.ptr_ ; }

        UTI_NODISCARD constexpr ssize_type capacity () const noexcept ;
        UTI_NODISCARD constexpr ssize_type     size () const noexcept ;
        UTI_NODISCARD constexpr bool          empty () const noexcept ;

        UTI_NODISCARD constexpr       iterator  begin ()       noexcept { return string_data_.ptr_ ; }
        UTI_NODISCARD constexpr const_iterator  begin () const noexcept { return string_data_.ptr_ ; }
        UTI_NODISCARD constexpr const_iterator cbegin () const noexcept { return begin() ; }

        UTI_NODISCARD constexpr       iterator  end ()       noexcept { return string_data_.ptr_ + size() ; }
        UTI_NODISCARD constexpr const_iterator  end () const noexcept { return string_data_.ptr_ + size() ; }
        UTI_NODISCARD constexpr const_iterator cend () const noexcept { return end() ; }

        UTI_NODISCARD constexpr       reverse_iterator  rbegin ()       noexcept { return  --end() ; }
        UTI_NODISCARD constexpr const_reverse_iterator  rbegin () const noexcept { return  --end() ; }
        UTI_NODISCARD constexpr const_reverse_iterator crbegin () const noexcept { return rbegin() ; }

        UTI_NODISCARD constexpr       reverse_iterator  rend ()       noexcept { return --begin() ; }
        UTI_NODISCARD constexpr const_reverse_iterator  rend () const noexcept { return --begin() ; }
        UTI_NODISCARD constexpr const_reverse_iterator crend () const noexcept { return    rend() ; }
protected:
        string_data string_data_ ;

        constexpr bool _index_in_bounds ( ssize_type const _index_ ) const noexcept ;

        constexpr void _set_size ( ssize_type const _size_ ) noexcept ;
        constexpr void _inc_size (                         ) noexcept ;
        constexpr void _inc_size ( ssize_type const _size_ ) noexcept ;
        constexpr void _dec_size (                         ) noexcept ;
        constexpr void _dec_size ( ssize_type const _size_ ) noexcept ;
} ;


template< typename CharType >
constexpr
_string_storage< CharType >::_string_storage () noexcept
        : string_data_{}
{}

template< typename CharType >
constexpr
_string_storage< CharType >::_string_storage ( ssize_type const _capacity_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        if( _capacity_ <= UTI_SSO_CAP )
        {
                string_data_.rep_.small_string_ = small_string{} ;

                string_data_.ptr_ = string_data_.rep_.small_string_.data_ ;
                string_data_.rep_.small_string_.size_ = UTI_SSO_CAP ;
        }
        else
        {
                string_data_.rep_.heap_string_ = heap_string{} ;

                string_data_.ptr_ = ::uti::alloc_typed_buffer< value_type >( _capacity_ ) ;
                string_data_.rep_.heap_string_.capacity_ = _capacity_ ;
        }
}

template< typename CharType >
constexpr
_string_storage< CharType >::_string_storage ( _string_storage const & _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
        : string_data_{}
{
        if( _other_.capacity() > UTI_SSO_CAP )
        {
                string_data_.rep_.heap_string_ = heap_string{} ;

                string_data_.ptr_ = ::uti::alloc_typed_buffer< CharType >( _other_.capacity() ) ;

                string_data_.rep_.heap_string_.capacity_ = _other_.capacity() ;
        }
        else
        {
                string_data_.rep_.small_string_ = small_string{} ;

                ::uti::copy( &string_data_, &string_data_ + 1, &_other_ ) ;

                string_data_.ptr_ = string_data_.rep_.small_string_.data_ ;
        }
}

template< typename CharType >
constexpr
_string_storage< CharType >::_string_storage ( _string_storage && _other_ ) noexcept
        : string_data_{}
{
        ::uti::copy( &_other_.string_data_, &_other_.string_data_ + 1, &string_data_ ) ;
        if( _other_.string_data_.ptr_ == static_cast< void const * >( &_other_.string_data_.rep_ ) )
        {
                string_data_.ptr_ = string_data_.rep_.small_string_.data_ ;
        }
        ::uti::memclr( &_other_.string_data_, &_other_.string_data_ + 1 ) ;
}

template< typename CharType >
constexpr
_string_storage< CharType > &
_string_storage< CharType >::operator= ( _string_storage const & _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        reserve( _other_.size() ) ;

        return *this ;
}

template< typename CharType >
constexpr
_string_storage< CharType > &
_string_storage< CharType >::operator= ( _string_storage && _other_ ) noexcept
{
        deallocate() ;

        ::uti::copy( &_other_.string_data_, &_other_.string_data_ + 1, &string_data_ ) ;
        if( _other_.string_data_.ptr_ == static_cast< void const * >( &_other_.string_data_.rep_ ) )
        {
                string_data_.ptr_ = string_data_.rep_.small_string_.data_ ;
        }
        ::uti::memclr( &_other_.string_data_, &_other_.string_data_ + 1 ) ;

        return *this ;
}

template< typename CharType >
constexpr
_string_storage< CharType >::~_string_storage () noexcept
{
        deallocate() ;
}

template< typename CharType >
constexpr
void _string_storage< CharType >::reserve ( ssize_type const _capacity_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        if( !capacity() )
        {
                if( _capacity_ <= UTI_SSO_CAP )
                {
                        string_data_.rep_.small_string_ = small_string{} ;

                        string_data_.ptr_ = string_data_.rep_.small_string_.data_ ;
                        string_data_.rep_.small_string_.size_ = UTI_SSO_CAP ;
                }
                else
                {
                        string_data_.rep_.heap_string_ = heap_string{} ;

                        string_data_.ptr_ = ::uti::alloc_typed_buffer< value_type >( _capacity_ ) ;

                        string_data_.rep_.heap_string_.capacity_ = _capacity_ ;
                }
        }
        if( string_data_.ptr_ == static_cast< void const * >( &string_data_.rep_ ) )
        {
                if( _capacity_ <= UTI_SSO_CAP ) return ;

                auto sz = size() ;

                string_data_.ptr_ = ::uti::alloc_typed_buffer< value_type >( _capacity_ ) ;

                ::uti::copy( string_data_.rep_.small_string_.data_ ,
                             string_data_.rep_.small_string_.data_ + sz ,
                             string_data_.ptr_
                ) ;

                string_data_.rep_.heap_string_ = heap_string{} ;

                string_data_.rep_.heap_string_.size_     = sz ;
                string_data_.rep_.heap_string_.capacity_ = _capacity_ ;
        }
        else
        {
                if( static_cast< size_type >( _capacity_ ) <= string_data_.rep_.heap_string_.capacity_ ) return ;

                pointer tmp = ::uti::alloc_typed_buffer< value_type >( _capacity_ ) ;

                ::uti::copy( string_data_.ptr_ ,
                             string_data_.ptr_ + string_data_.rep_.heap_string_.size_ ,
                             tmp
                ) ;
                string_data_.ptr_ = tmp ;
                string_data_.rep_.heap_string_.capacity_ = _capacity_ ;
        }
}

template< typename CharType >
constexpr void
_string_storage< CharType >::deallocate () noexcept
{
        if( string_data_.ptr_ &&
            string_data_.ptr_ != static_cast< void const * >( &string_data_.rep_ ) )
        {
                ::uti::dealloc_typed_buffer( string_data_.ptr_ ) ;
        }
}

template< typename CharType >
UTI_NODISCARD constexpr
_string_storage< CharType >::ssize_type
_string_storage< CharType >::capacity () const noexcept
{
        if( !string_data_.ptr_ )
        {
                return 0 ;
        }
        else if( string_data_.ptr_ == static_cast< void const * >( &string_data_.rep_ ) )
        {
                return UTI_SSO_CAP ;
        }
        else
        {
                return string_data_.rep_.heap_string_.capacity_ ;
        }
}

template< typename CharType >
UTI_NODISCARD constexpr
_string_storage< CharType >::ssize_type
_string_storage< CharType >::size () const noexcept
{
        if( !string_data_.ptr_ )
        {
                return 0 ;
        }
        else if( string_data_.ptr_ == static_cast< void const * >( &string_data_.rep_ ) )
        {
                return UTI_SSO_CAP - string_data_.rep_.small_string_.size_ ;
        }
        else
        {
                return string_data_.rep_.heap_string_.size_ ;
        }
}

template< typename CharType >
UTI_NODISCARD constexpr
bool
_string_storage< CharType >::empty () const noexcept
{
        return !string_data_.ptr_ || !size() ;
}

template< typename CharType >
UTI_NODISCARD constexpr
bool
_string_storage< CharType >::_index_in_bounds ( ssize_type const _index_ ) const noexcept
{
        return 0 <= _index_ && _index_ < size() ;
}

template< typename CharType >
constexpr
void
_string_storage< CharType >::_set_size ( ssize_type const _size_ ) noexcept
{
        if( !string_data_.ptr_ ) return ;

        if( string_data_.ptr_ == static_cast< void const * >( &string_data_.rep_ ) )
        {
                UTI_CEXPR_ASSERT( _size_ < u8_t_max, "uti::string::_set_size: bad size" ) ;

                string_data_.rep_.small_string_.size_ = UTI_SSO_CAP - _size_ ;
        }
        else
        {
                string_data_.rep_.heap_string_.size_ = _size_ ;
        }
}

template< typename CharType >
constexpr
void
_string_storage< CharType >::_inc_size () noexcept
{
        _inc_size( 1 ) ;
}

template< typename CharType >
constexpr
void
_string_storage< CharType >::_inc_size ( ssize_type const _size_ ) noexcept
{
        if( !string_data_.ptr_ ) return ;

        if( string_data_.ptr_ == static_cast< void const * >( &string_data_.rep_ ) )
        {
                string_data_.rep_.small_string_.size_ -= _size_ ;
        }
        else
        {
                string_data_.rep_.heap_string_.size_ += _size_ ;
        }
}

template< typename CharType >
constexpr
void
_string_storage< CharType >::_dec_size () noexcept
{
        _dec_size( 1 ) ;
}

template< typename CharType >
constexpr
void
_string_storage< CharType >::_dec_size ( ssize_type const _size_ ) noexcept
{
        if( !string_data_.ptr_ ) return ;

        if( string_data_.ptr_ == static_cast< void const * >( &string_data_.rep_ ) )
        {
                string_data_.rep_.small_string_.size_ += _size_ ;
        }
        else
        {
                string_data_.rep_.heap_string_.size_ -= _size_ ;
        }
}


} // namespace _detail


template< typename CharType = char >
class string : public _detail::_string_storage< CharType >
{
        using _base = _detail::_string_storage< CharType > ;
public:
        using      value_type = typename _base::     value_type ;
        using       size_type = typename _base::      size_type ;
        using      ssize_type = typename _base::     ssize_type ;
        using difference_type = typename _base::difference_type ;

        using         pointer = typename _base::        pointer ;
        using   const_pointer = typename _base::  const_pointer ;
        using       reference = typename _base::      reference ;
        using const_reference = typename _base::const_reference ;

        using               iterator = typename _base::               iterator   ;
        using         const_iterator = typename _base::         const_iterator   ;
        using       reverse_iterator = ::uti::reverse_iterator<       iterator > ;
        using const_reverse_iterator = ::uti::reverse_iterator< const_iterator > ;

        constexpr string () noexcept = default ;

        constexpr string             ( string const &  ) UTI_NOEXCEPT_UNLESS_BADALLOC ;
        constexpr string & operator= ( string const &  ) UTI_NOEXCEPT_UNLESS_BADALLOC ;
        constexpr string             ( string       && )     noexcept       = default ;
        constexpr string & operator= ( string       && )     noexcept       = default ;

        constexpr explicit string ( ssize_type    const _capacity_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;
        constexpr          string ( const_pointer const &   _cstr_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;
        constexpr          string ( const_pointer const &    _ptr_ , ssize_type const _len_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;

        constexpr ~string () noexcept = default ;

        template< meta::forward_iterator Iter >
        constexpr string ( Iter _begin_, Iter const & _end_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;

        UTI_NODISCARD constexpr       reference operator[] ( ssize_type const _index_ )       noexcept { return _base::string_data_.ptr_[ _index_ ] ; }
        UTI_NODISCARD constexpr const_reference operator[] ( ssize_type const _index_ ) const noexcept { return _base::string_data_.ptr_[ _index_ ] ; }

        UTI_NODISCARD constexpr       reference at ( ssize_type const _index_ )       noexcept { return operator[]( _index_ ) ; }
        UTI_NODISCARD constexpr const_reference at ( ssize_type const _index_ ) const noexcept { return operator[]( _index_ ) ; }

        UTI_NODISCARD constexpr       reference front ()       noexcept { return *_base::begin() ; }
        UTI_NODISCARD constexpr const_reference front () const noexcept { return *_base::begin() ; }

        UTI_NODISCARD constexpr       reference back ()       noexcept { return *_base::rbegin() ; }
        UTI_NODISCARD constexpr const_reference back () const noexcept { return *_base::rbegin() ; }

        constexpr const_pointer c_str () const noexcept { return _base::data() ; }

        constexpr void reserve () UTI_NOEXCEPT_UNLESS_BADALLOC ;

        constexpr void push_back ( value_type const & _char_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;

        constexpr string & append ( string const & _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;

        template< meta::forward_iterator Iter >
        constexpr string & append ( Iter _begin_, Iter const & _end_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;

        constexpr void insert ( ssize_type const _position_, value_type const & _char_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;
        constexpr void insert ( ssize_type const _position_, string     const & _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;

        constexpr void clear () noexcept ;
} ;


template< typename CharType >
constexpr
string< CharType >::string ( ssize_type const _capacity_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
        : _base( _capacity_ )
{}

template< typename CharType >
constexpr
string< CharType >::string ( string const & _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
        : _base( _other_.size() + 1 )
{
        ::uti::copy( _other_.begin(), _other_.end(), _base::begin() ) ;

        _base::_set_size( _other_.size() ) ;

        *_base::end() = '\0' ;
}

template< typename CharType >
constexpr
string< CharType > &
string< CharType >::operator= ( string const & _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        _base::reserve( _other_.size() + 1 ) ;

        ::uti::copy( _other_.begin(), _other_.end(), _base::begin() ) ;

        _base::_set_size( _other_.size() ) ;

        *_base::end() = '\0' ;

        return *this ;
}

template< typename CharType >
constexpr
string< CharType >::string ( const_pointer const & _cstr_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
        : _base( ::uti::strlen( _cstr_ ) + 1 )
{
        _base::_set_size( ::uti::strlen( _cstr_ ) ) ;

        ::uti::copy( _cstr_, _cstr_ + _base::size(), _base::data() ) ;

        *_base::end() = '\0' ;
}

template< typename CharType >
constexpr
string< CharType >::string ( const_pointer const & _ptr_, ssize_type const _len_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
        : _base( _len_ + 1 )
{
        _base::_set_size( _len_ ) ;

        ::uti::copy( _ptr_, _ptr_ + _len_, _base::data() ) ;

        *_base::end() = '\0' ;
}

template< typename CharType >
template< meta::forward_iterator Iter >
constexpr
string< CharType >::string ( Iter _begin_, Iter const & _end_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
        : _base( ::uti::distance( _begin_, _end_ ) + 1 )
{
        _base::_set_size( ::uti::distance( _begin_, _end_ ) ) ;

        ::uti::copy( _begin_, _end_, _base::data() ) ;

        *_base::end() = '\0' ;
}

template< typename CharType >
constexpr void
string< CharType >::reserve () UTI_NOEXCEPT_UNLESS_BADALLOC
{
        if( _base::empty() || _base::size() + 1 >= _base::capacity() )
        {
                _base::reserve( _base::empty() ? 1 : 2 * _base::capacity() ) ;
        }
}

template< typename CharType >
constexpr void
string< CharType >::push_back ( value_type const & _char_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        reserve() ;

        *_base::end() = _char_ ;

        _base::_inc_size() ;

        *_base::end() = '\0' ;
}

template< typename CharType >
constexpr
string< CharType > &
string< CharType >::append ( string const & _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        _base::reserve( _base::size() + _other_.size() + 1 ) ;

        ::uti::copy( _other_.begin(), _other_.end(), _base::data() + _base::size() ) ;

        _base::_inc_size( _other_.size() ) ;

        *_base::end() = '\0' ;

        return *this ;
}

template< typename CharType >
template< meta::forward_iterator Iter >
constexpr
string< CharType > &
string< CharType >::append ( Iter _begin_, Iter const & _end_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        auto sz = ::uti::distance( _begin_, _end_ ) ;

        _base::reserve( _base::size() + sz + 1 ) ;

        ::uti::copy( _begin_, _end_, _base::data() + _base::size() ) ;

        _base::_inc_size( sz ) ;

        *_base::end() = '\0' ;

        return *this ;
}

template< typename CharType >
constexpr void
string< CharType >::insert ( ssize_type const _position_, value_type const & _char_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        if( _position_ >= _base::size() )
        {
                push_back( _char_ ) ;
                return ;
        }
        reserve() ;

        ::uti::copy_backward( _base::end() - 1, _base::begin() + _position_, _base::end() ) ;

        at( _position_ ) = _char_ ;
        _base::_inc_size() ;

        *_base::end() = '\0' ;
}

template< typename CharType >
constexpr void
string< CharType >::insert ( ssize_type const _position_, string const & _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        if( _position_ >= _base::size() )
        {
                append( _other_ ) ;
                return ;
        }
        _base::reserve( _base::size() + _other_.size() + 1 ) ;

        ::uti::copy_backward( _base::end() - 1, _base::begin() + _position_ - 1, _base::end() + _other_.size() - 1 ) ;
        ::uti::copy( _other_.begin(), _other_.end(), _base::begin() + _position_ ) ;

        _base::_inc_size( _other_.size() ) ;

        *_base::end() = '\0' ;
}

template< typename CharType >
constexpr void
string< CharType >::clear () noexcept
{
        _base::deallocate() ;
}


} // namespace uti
