//
//
//      uti
//      buffer.hpp
//

#pragma once

#include <mem/container_base.hpp>
#include <mem/allocator.hpp>


namespace uti
{


template< typename T, typename Alloc >
class buffer
{
        using _self =  buffer              ;
        using _base = _container_base< T > ;
public:
        using      value_type = typename _base::     value_type ;
        using       size_type = typename _base::      size_type ;
        using      ssize_type = typename _base::     ssize_type ;
        using difference_type = typename _base::difference_type ;

        using allocator_type = Alloc ;
        using  _alloc_traits = allocator_traits< allocator_type > ;

        using         pointer = typename _base::        pointer ;
        using   const_pointer = typename _base::  const_pointer ;
        using       reference = typename _base::      reference ;
        using const_reference = typename _base::const_reference ;

        using        iterator = typename _base::       iterator ;
        using  const_iterator = typename _base:: const_iterator ;

        constexpr buffer (                             ) noexcept = default ;
        explicit  buffer ( ssize_type const _capacity_ )                    ;

        constexpr buffer ( pointer const _ptr_, ssize_type const _cap_ ) noexcept
                : buffer_( _ptr_ ), capacity_( _cap_ ) {}

        buffer             ( buffer const &  _other_ )          ;
        buffer & operator= ( buffer const &  _other_ )          ;
        buffer             ( buffer       && _other_ ) noexcept ;
        buffer & operator= ( buffer       && _other_ ) noexcept ;

        ~buffer () noexcept ;

        ssize_type reserve ( ssize_type const _capacity_ ) ;

        bool try_realloc_inplace ( ssize_type const _capacity_ ) noexcept ;
        bool can_realloc_inplace ( ssize_type const _capacity_ ) noexcept ;

        void deallocate () noexcept ;

        UTI_NODISCARD ssize_type       & capacity ()       noexcept { return capacity_ ; }
        UTI_NODISCARD ssize_type const & capacity () const noexcept { return capacity_ ; }

              pointer  begin ()       noexcept { return buffer_             ; }
        const_pointer  begin () const noexcept { return buffer_             ; }
        const_pointer cbegin () const noexcept { return buffer_             ; }
              pointer    end ()       noexcept { return buffer_ + capacity_ ; }
        const_pointer    end () const noexcept { return buffer_ + capacity_ ; }
        const_pointer   cend () const noexcept { return buffer_ + capacity_ ; }

        pointer       & _begin ()       noexcept { return buffer_ ; }
        pointer const & _begin () const noexcept { return buffer_ ; }
protected:
        pointer      buffer_ { nullptr } ;
        ssize_type capacity_ {       0 } ;
};


template< typename T, typename Alloc >
buffer< T, Alloc >::buffer ( ssize_type const _capacity_ )
{
        buffer_ = _alloc_traits::allocate( _capacity_ ).ptr;

        if( buffer_ ) capacity_ = _capacity_;
}

template< typename T, typename Alloc >
buffer< T, Alloc >::buffer ( buffer const & _other_ )
{
        reserve( _other_.capacity_ );
}

template< typename T, typename Alloc >
buffer< T, Alloc >::buffer ( buffer && _other_ ) noexcept
        : buffer_( _other_.buffer_ ), capacity_( _other_.capacity_ )
{
        _other_.buffer_   = nullptr ;
        _other_.capacity_ =       0 ;
}

template< typename T, typename Alloc >
buffer< T, Alloc > &
buffer< T, Alloc >::operator= ( buffer const & _other_ )
{
        reserve( _other_.capacity_ );

        return *this;
}

template< typename T, typename Alloc >
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
buffer< T, Alloc >::~buffer () noexcept
{
        deallocate();
}

template< typename T, typename Alloc >
buffer< T, Alloc >::ssize_type
buffer< T, Alloc >::reserve ( ssize_type const _capacity_ )
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
bool
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
bool
buffer< T, Alloc >::can_realloc_inplace ( ssize_type const _capacity_ ) noexcept
{
        return _alloc_traits::can_realloc_inplace( { buffer_, capacity_ }, _capacity_ );
}

template< typename T, typename Alloc >
void
buffer< T, Alloc >::deallocate () noexcept
{
        if( buffer_ ) _alloc_traits::deallocate( { buffer_, capacity_ } );
}


} // namespace uti
