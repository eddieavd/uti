//
//
//      uti
//      vectorlike.hpp
//

#pragma once

#include <util/config.hpp>
#include <util/assert.hpp>
#include <meta/traits.hpp>
#include <meta/uti_traits.hpp>
#include <container/allocator.hpp>

#define UTI_STATIC_MEM_SIZE 16 * 1024 * 1024


namespace uti
{


template< typename T >
class _vectorlike_base
{
public:
        using      value_type =       T    ;
        using       size_type =  size_t    ;
        using      ssize_type = ssize_t    ;
        using difference_type = ssize_type ;

        using         pointer = value_type       * ;
        using   const_pointer = value_type const * ;
        using       reference = value_type       & ;
        using const_reference = value_type const & ;

        using        iterator =       pointer ;
        using  const_iterator = const_pointer ;
};


template< typename T >
class _vectorlike_view
{
        using _self = _vectorlike_view      ;
        using _base = _vectorlike_base< T > ;
public:
        using      value_type = typename _base::     value_type ;
        using       size_type = typename _base::      size_type ;
        using      ssize_type = typename _base::     ssize_type ;
        using difference_type = typename _base::difference_type ;

        using         pointer = typename _base::        pointer ;
        using   const_pointer = typename _base::  const_pointer ;
        using       reference = typename _base::      reference ;
        using const_reference = typename _base::const_reference ;

        using        iterator = typename _base::       iterator ;
        using  const_iterator = typename _base:: const_iterator ;

        constexpr _vectorlike_view () noexcept = default ;

        constexpr _vectorlike_view ( pointer const _begin_, pointer const _end_ ) noexcept
                : begin_( _begin_ ), end_( _end_ ) {}

        constexpr _vectorlike_view             ( _vectorlike_view const &  _other_ ) noexcept = default ;
        constexpr _vectorlike_view             ( _vectorlike_view       && _other_ ) noexcept           ;
        constexpr _vectorlike_view & operator= ( _vectorlike_view const &  _other_ ) noexcept = default ;
        constexpr _vectorlike_view & operator= ( _vectorlike_view       && _other_ ) noexcept           ;

        constexpr ~_vectorlike_view () noexcept = default ;

        constexpr void pop_back  () noexcept { --end_   ; }
        constexpr void pop_front () noexcept { ++begin_ ; }

        template< typename Self >
        UTI_NODISCARD constexpr
        auto & operator[] ( this Self && self, ssize_type const _index_ ) noexcept
        {
                return UTI_FWD( self ).begin_[ _index_ ];
        }

        template< typename Self >
        UTI_NODISCARD UTI_DEEP_INLINE constexpr
        auto & at ( this Self && self, ssize_type const _index_ ) noexcept
        {
                UTI_ASSERT( 0 <= _index_ && _index_ < UTI_FWD( self ).size(), "uti::_vectorlike_view::at: index out of range" );

                return UTI_FWD( self ).begin_[ _index_ ];
        }

        template< typename Self, typename... Idxs >
        UTI_NODISCARD UTI_DEEP_INLINE constexpr
        decltype( auto ) at ( this Self && self, ssize_type const _x_, Idxs... _idxs_ )
                noexcept requires( is_n_dim_container_v< _self, sizeof...( _idxs_ ) + 1 > )
        {
                return UTI_FWD( self ).at( _x_ ).at( _idxs_... );
        }

        UTI_NODISCARD constexpr ssize_type  size () const noexcept { return static_cast< ssize_type >( end_ - begin_ ); }
        UTI_NODISCARD constexpr       bool empty () const noexcept { return end_ == begin_; }

        UTI_NODISCARD constexpr       iterator  begin ()       noexcept { return begin_ ; }
        UTI_NODISCARD constexpr const_iterator  begin () const noexcept { return begin_ ; }
        UTI_NODISCARD constexpr const_iterator cbegin () const noexcept { return begin(); }

        UTI_NODISCARD constexpr       iterator  end ()       noexcept { return end_ ; }
        UTI_NODISCARD constexpr const_iterator  end () const noexcept { return end_ ; }
        UTI_NODISCARD constexpr const_iterator cend () const noexcept { return end(); }

        template< typename Self >
        UTI_NODISCARD constexpr
        auto & front ( this Self && self ) noexcept
        {
                UTI_ASSERT( !UTI_FWD( self ).empty(), "uti::_vectorlike_view::front: called on empty _vectorlike_view" );

                return *( UTI_FWD( self ).begin_ );
        }
        UTI_NODISCARD constexpr const_reference cfront () const noexcept { return front(); }

        template< typename Self >
        UTI_NODISCARD constexpr
        auto & back ( this Self && self ) noexcept
        {
                UTI_ASSERT( !UTI_FWD( self ).empty(), "uti::_vectorlike_view::back: called on empty _vectorlike_view" );

                return *( UTI_FWD( self ).end_ - 1 );
        }
        UTI_NODISCARD constexpr const_reference cback () const noexcept { return back(); }
protected:
        pointer begin_ { nullptr } ;
        pointer   end_ { nullptr } ;

        UTI_NODISCARD constexpr pointer       & _begin ()       noexcept { return begin_; }
        UTI_NODISCARD constexpr pointer const & _begin () const noexcept { return begin_; }
        UTI_NODISCARD constexpr pointer       & _end   ()       noexcept { return   end_; }
        UTI_NODISCARD constexpr pointer const & _end   () const noexcept { return   end_; }
};

template< typename T >
constexpr
_vectorlike_view< T >::_vectorlike_view ( _vectorlike_view && _other_ ) noexcept
        : begin_( _other_.begin_ ), end_( _other_.end_ )
{
        _other_.begin_ = _other_.end_ = nullptr ;
}

template< typename T >
constexpr
_vectorlike_view< T > &
_vectorlike_view< T >::operator= ( _vectorlike_view && _other_ ) noexcept
{
        begin_ = _other_.begin_ ;
        end_   = _other_.end_   ;

        _other_.begin_ = _other_.end_ = nullptr ;

        return *this;
}


template< typename T, typename Alloc >
class _vectorlike_buffer
{
        using _self = _vectorlike_buffer    ;
        using _base = _vectorlike_base< T > ;
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

        constexpr _vectorlike_buffer (                             ) noexcept = default ;
        explicit  _vectorlike_buffer ( ssize_type const _capacity_ )                    ;

        constexpr _vectorlike_buffer ( pointer const _ptr_, ssize_type const _cap_ ) noexcept
                : buffer_( _ptr_ ), capacity_( _cap_ ) {}

        _vectorlike_buffer             ( _vectorlike_buffer const &  _other_ )          ;
        _vectorlike_buffer & operator= ( _vectorlike_buffer const &  _other_ )          ;
        _vectorlike_buffer             ( _vectorlike_buffer       && _other_ ) noexcept ;
        _vectorlike_buffer & operator= ( _vectorlike_buffer       && _other_ ) noexcept ;

        ~_vectorlike_buffer () noexcept ;

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
_vectorlike_buffer< T, Alloc >::_vectorlike_buffer ( ssize_type const _capacity_ )
{
        buffer_ = _alloc_traits::allocate( _capacity_ ).ptr;

        if( buffer_ ) capacity_ = _capacity_;
}

template< typename T, typename Alloc >
_vectorlike_buffer< T, Alloc >::_vectorlike_buffer ( _vectorlike_buffer const & _other_ )
{
        reserve( _other_.capacity_ );
}

template< typename T, typename Alloc >
_vectorlike_buffer< T, Alloc >::_vectorlike_buffer ( _vectorlike_buffer && _other_ ) noexcept
        : buffer_( _other_.buffer_ ), capacity_( _other_.capacity_ )
{
        _other_.buffer_   = nullptr ;
        _other_.capacity_ =       0 ;
}

template< typename T, typename Alloc >
_vectorlike_buffer< T, Alloc > &
_vectorlike_buffer< T, Alloc >::operator= ( _vectorlike_buffer const & _other_ )
{
        reserve( _other_.capacity_ );

        return *this;
}

template< typename T, typename Alloc >
_vectorlike_buffer< T, Alloc > &
_vectorlike_buffer< T, Alloc >::operator= ( _vectorlike_buffer && _other_ ) noexcept
{
        buffer_   = _other_.buffer_   ;
        capacity_ = _other_.capacity_ ;

        _other_.buffer_   = nullptr ;
        _other_.capacity_ =       0 ;

        return *this;
}

template< typename T, typename Alloc >
_vectorlike_buffer< T, Alloc >::~_vectorlike_buffer () noexcept
{
        deallocate();
}

template< typename T, typename Alloc >
_vectorlike_buffer< T, Alloc >::ssize_type
_vectorlike_buffer< T, Alloc >::reserve ( ssize_type const _capacity_ )
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
_vectorlike_buffer< T, Alloc >::try_realloc_inplace ( ssize_type const _capacity_ ) noexcept
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
_vectorlike_buffer< T, Alloc >::can_realloc_inplace ( ssize_type const _capacity_ ) noexcept
{
        return _alloc_traits::can_realloc_inplace( { buffer_, capacity_ }, _capacity_ );
}

template< typename T, typename Alloc >
void
_vectorlike_buffer< T, Alloc >::deallocate () noexcept
{
        if( buffer_ ) _alloc_traits::deallocate( { buffer_, capacity_ } );
}


} // namespace uti
