//
//
//      uti
//      buffer.hpp
//

#pragma once

#include <iterator/meta.hpp>
#include <iterator/base.hpp>
#include <container/base.hpp>
#include <allocator/meta.hpp>
#include <allocator/default.hpp>


namespace uti
{


template< typename T, typename Alloc = allocator< T > >
class buffer
{
        using _self =  buffer              ;
        using _base = _container_base< T > ;
public:
        using      value_type = typename _base::     value_type ;
        using       size_type = typename _base::      size_type ;
        using      ssize_type = typename _base::     ssize_type ;
        using difference_type = typename _base::difference_type ;

        using  allocator_type = Alloc ;
        using   _alloc_traits = allocator_traits< allocator_type > ;
        using      block_type = typename _alloc_traits::block_type ;

        using         pointer = typename _base::        pointer ;
        using   const_pointer = typename _base::  const_pointer ;
        using       reference = typename _base::      reference ;
        using const_reference = typename _base::const_reference ;

        using        iterator = iterator_base< value_type      , random_access_iterator_tag > ;
        using  const_iterator = iterator_base< value_type const, random_access_iterator_tag > ;

        constexpr          buffer (                             )     noexcept       = default ;
        constexpr explicit buffer ( ssize_type const _capacity_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;

        constexpr buffer ( pointer const _ptr_, ssize_type const _cap_ ) noexcept
                : block_ { _ptr_, _cap_ } {}

        constexpr buffer             ( buffer const &  _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;
        constexpr buffer & operator= ( buffer const &  _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;
        constexpr buffer             ( buffer       && _other_ )     noexcept                 ;
        constexpr buffer & operator= ( buffer       && _other_ )     noexcept                 ;

        constexpr bool operator== ( buffer const & _other_ ) const noexcept ;

        constexpr ~buffer () noexcept ;

        constexpr ssize_type reserve ( ssize_type const _capacity_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;

        constexpr bool realloc_inplace ( ssize_type const _capacity_ ) noexcept ;

        constexpr void deallocate () noexcept ;

        UTI_NODISCARD constexpr ssize_type capacity () const noexcept { return _capacity() ; }

        constexpr       iterator  begin ()       noexcept { return _buffer()               ; }
        constexpr const_iterator  begin () const noexcept { return _buffer()               ; }
        constexpr const_iterator cbegin () const noexcept { return _buffer()               ; }
        constexpr       iterator    end ()       noexcept { return _buffer() + _capacity() ; }
        constexpr const_iterator    end () const noexcept { return _buffer() + _capacity() ; }
        constexpr const_iterator   cend () const noexcept { return _buffer() + _capacity() ; }

        constexpr       pointer data ()       noexcept { return _buffer() ; }
        constexpr const_pointer data () const noexcept { return _buffer() ; }

        constexpr ssize_type max_size () const noexcept { return _alloc_traits::max_size() ; }

        constexpr pointer       & _begin ()       noexcept { return _buffer() ; }
        constexpr pointer const & _begin () const noexcept { return _buffer() ; }

        friend constexpr void swap ( buffer & lhs, buffer & rhs ) noexcept
        {
                buffer tmp( UTI_MOVE( lhs ) ) ;

                lhs = UTI_MOVE( rhs ) ;
                rhs = UTI_MOVE( tmp ) ;
        }
protected:
        block_type block_ { nullptr, 0 } ;

        pointer       & _buffer ()       noexcept { return block_.ptr ; }
        pointer const & _buffer () const noexcept { return block_.ptr ; }

        ssize_type       & _capacity ()       noexcept { return block_.size; }
        ssize_type const & _capacity () const noexcept { return block_.size; }
};


template< typename T, typename Alloc >
constexpr
buffer< T, Alloc >::buffer ( ssize_type const _capacity_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        if( 0 <= _capacity_ && _capacity_ < max_size() )
        {
                block_ = _alloc_traits::allocate( _capacity_ ) ;
        }
}

template< typename T, typename Alloc >
constexpr
buffer< T, Alloc >::buffer ( buffer const & _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        reserve( _other_._capacity() );
}

template< typename T, typename Alloc >
constexpr
buffer< T, Alloc >::buffer ( buffer && _other_ ) noexcept
        : block_{ _other_._buffer(), _other_._capacity() }
{
        _other_._buffer  () = nullptr ;
        _other_._capacity() =       0 ;
}

template< typename T, typename Alloc >
constexpr
buffer< T, Alloc > &
buffer< T, Alloc >::operator= ( buffer const & _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        reserve( _other_._capacity() );

        return *this;
}

template< typename T, typename Alloc >
constexpr
buffer< T, Alloc > &
buffer< T, Alloc >::operator= ( buffer && _other_ ) noexcept
{
        _buffer  () = _other_._buffer  () ;
        _capacity() = _other_._capacity() ;

        _other_._buffer  () = nullptr ;
        _other_._capacity() =       0 ;

        return *this;
}

template< typename T, typename Alloc >
constexpr bool
buffer< T, Alloc >::operator== ( buffer const & _other_ ) const noexcept
{
        if( this == &_other_ ) return true ;

        return _buffer  () == _other_._buffer  () &&
               _capacity() == _other_._capacity()  ;
}

template< typename T, typename Alloc >
constexpr
buffer< T, Alloc >::~buffer () noexcept
{
        deallocate();
}

template< typename T, typename Alloc >
constexpr
buffer< T, Alloc >::ssize_type
buffer< T, Alloc >::reserve ( ssize_type const _capacity_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        if( _capacity_ <= _capacity() ) return _capacity();

        block_type tmp = _alloc_traits::reallocate( block_, _capacity_ ) ;

        if( tmp.ptr != nullptr )
        {
                block_ = tmp ;
        }
        return _capacity();
}

template< typename T, typename Alloc >
constexpr bool
buffer< T, Alloc >::realloc_inplace ( ssize_type const _capacity_ ) noexcept
{
        if( _alloc_traits::realloc_inplace( block_, _capacity_ ) )
        {
                _capacity() = _capacity_;
                return true;
        }
        return false;
}

template< typename T, typename Alloc >
constexpr void
buffer< T, Alloc >::deallocate () noexcept
{
        if( _buffer() ) _alloc_traits::deallocate( block_ );
}


} // namespace uti
