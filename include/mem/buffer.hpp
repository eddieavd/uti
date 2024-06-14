//
//
//      uti
//      buffer.hpp
//

#pragma once

#include <container/container_base.hpp>
#include <mem/allocator.hpp>


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

        using         pointer = typename _base::        pointer ;
        using   const_pointer = typename _base::  const_pointer ;
        using       reference = typename _base::      reference ;
        using const_reference = typename _base::const_reference ;

        using        iterator = typename _base::       iterator ;
        using  const_iterator = typename _base:: const_iterator ;

        constexpr           buffer (                             )     noexcept       = default ;
        constexpr explicit  buffer ( ssize_type const _capacity_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;

        constexpr buffer ( pointer const _ptr_, ssize_type const _cap_ ) noexcept
                : buffer_( _ptr_ ), capacity_( _cap_ ) {}

        constexpr buffer             ( buffer const &  _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;
        constexpr buffer & operator= ( buffer const &  _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;
        constexpr buffer             ( buffer       && _other_ )     noexcept                 ;
        constexpr buffer & operator= ( buffer       && _other_ )     noexcept                 ;

        constexpr bool operator== ( buffer const & _other_ ) const noexcept ;

        constexpr ~buffer () noexcept ;

        constexpr ssize_type reserve ( ssize_type const _capacity_ ) UTI_NOEXCEPT_UNLESS_BADALLOC ;

        constexpr bool try_realloc_inplace ( ssize_type const _capacity_ ) noexcept ;
        constexpr bool can_realloc_inplace ( ssize_type const _capacity_ ) noexcept ;

        constexpr void deallocate () noexcept ;

        UTI_NODISCARD constexpr ssize_type       & capacity ()       noexcept { return capacity_ ; }
        UTI_NODISCARD constexpr ssize_type const & capacity () const noexcept { return capacity_ ; }

        constexpr       iterator  begin ()       noexcept { return buffer_             ; }
        constexpr const_iterator  begin () const noexcept { return buffer_             ; }
        constexpr const_iterator cbegin () const noexcept { return buffer_             ; }
        constexpr       iterator    end ()       noexcept { return buffer_ + capacity_ ; }
        constexpr const_iterator    end () const noexcept { return buffer_ + capacity_ ; }
        constexpr const_iterator   cend () const noexcept { return buffer_ + capacity_ ; }

        constexpr       pointer data ()       noexcept { return buffer_ ; }
        constexpr const_pointer data () const noexcept { return buffer_ ; }

        constexpr ssize_type max_size () const noexcept { return _alloc_traits::max_size() ; }

        constexpr pointer       & _begin ()       noexcept { return buffer_ ; }
        constexpr pointer const & _begin () const noexcept { return buffer_ ; }

        friend constexpr void swap ( buffer & lhs, buffer & rhs ) noexcept
        {
                buffer tmp( UTI_MOVE( lhs ) ) ;

                lhs = UTI_MOVE( rhs ) ;
                rhs = UTI_MOVE( tmp ) ;
        }
protected:
        pointer      buffer_ { nullptr } ;
        ssize_type capacity_ {       0 } ;
};


template< typename T, typename Alloc >
constexpr
buffer< T, Alloc >::buffer ( ssize_type const _capacity_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        if( 0 <= _capacity_ && _capacity_ < max_size() )
        {
                buffer_ = _alloc_traits::allocate( _capacity_ ).ptr;

                if( buffer_ ) capacity_ = _capacity_;
        }
}

template< typename T, typename Alloc >
constexpr
buffer< T, Alloc >::buffer ( buffer const & _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        reserve( _other_.capacity_ );
}

template< typename T, typename Alloc >
constexpr
buffer< T, Alloc >::buffer ( buffer && _other_ ) noexcept
        : buffer_( _other_.buffer_ ), capacity_( _other_.capacity_ )
{
        _other_.buffer_   = nullptr ;
        _other_.capacity_ =       0 ;
}

template< typename T, typename Alloc >
constexpr
buffer< T, Alloc > &
buffer< T, Alloc >::operator= ( buffer const & _other_ ) UTI_NOEXCEPT_UNLESS_BADALLOC
{
        reserve( _other_.capacity_ );

        return *this;
}

template< typename T, typename Alloc >
constexpr
buffer< T, Alloc > &
buffer< T, Alloc >::operator= ( buffer && _other_ ) noexcept
{
        buffer_   = _other_.buffer_   ;
        capacity_ = _other_.capacity_ ;

        _other_.buffer_   = nullptr ;
        _other_.capacity_ =       0 ;

        return *this;
}

template< typename T, typename Alloc >
constexpr bool
buffer< T, Alloc >::operator== ( buffer const & _other_ ) const noexcept
{
        if( this == &_other_ ) return true ;

        return buffer_   == _other_.  buffer_ &&
               capacity_ == _other_.capacity_  ;
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
        if( _capacity_ <= capacity_ ) return capacity_;

        auto tmp = _alloc_traits::reallocate( { buffer_, capacity_ }, _capacity_ ).ptr;

        if( tmp != nullptr )
        {
                buffer_   = tmp;
                capacity_ = _capacity_;
        }
        return capacity_;
}

template< typename T, typename Alloc >
constexpr bool
buffer< T, Alloc >::try_realloc_inplace ( ssize_type const _capacity_ ) noexcept
{
        if( _alloc_traits::try_realloc_inplace( { buffer_, capacity_ }, _capacity_ ) )
        {
                capacity_ = _capacity_;
                return true;
        }
        return false;
}

template< typename T, typename Alloc >
constexpr bool
buffer< T, Alloc >::can_realloc_inplace ( ssize_type const _capacity_ ) noexcept
{
        return _alloc_traits::can_realloc_inplace( { buffer_, capacity_ }, _capacity_ );
}

template< typename T, typename Alloc >
constexpr void
buffer< T, Alloc >::deallocate () noexcept
{
        if( buffer_ ) _alloc_traits::deallocate( { buffer_, capacity_ } );
}


} // namespace uti
