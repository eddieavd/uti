//
//
//      uti
//      view.hpp
//

#pragma once

#include <util/assert.hpp>
#include <mem/container_base.hpp>
#include <meta/uti_traits.hpp>


namespace uti
{


template< typename T >
class view
{
        using _self =  view                ;
        using _base = _container_base< T > ;
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

        constexpr view () noexcept = default ;

        constexpr view ( pointer const _begin_, pointer const _end_ ) noexcept
                : begin_( _begin_ ), end_( _end_ ) {}

        constexpr view             ( view const &  _other_ ) noexcept = default ;
        constexpr view             ( view       && _other_ ) noexcept           ;
        constexpr view & operator= ( view const &  _other_ ) noexcept = default ;
        constexpr view & operator= ( view       && _other_ ) noexcept           ;

        constexpr ~view () noexcept = default ;

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
                UTI_ASSERT( 0 <= _index_ && _index_ < UTI_FWD( self ).size(), "uti::view::at: index out of range" );

                return UTI_FWD( self ).begin_[ _index_ ];
        }

        template< typename Self, typename... Idxs >
        UTI_NODISCARD UTI_DEEP_INLINE constexpr
        decltype( auto ) at ( this Self && self, ssize_type const _x_, Idxs... _idxs_ ) noexcept
                requires( is_n_dim_container_v< _self, sizeof...( _idxs_ ) + 1 > )
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
                UTI_ASSERT( !UTI_FWD( self ).empty(), "uti::view::front: called on empty view" );

                return *( UTI_FWD( self ).begin_ );
        }
        UTI_NODISCARD constexpr const_reference cfront () const noexcept { return front(); }

        template< typename Self >
        UTI_NODISCARD constexpr
        auto & back ( this Self && self ) noexcept
        {
                UTI_ASSERT( !UTI_FWD( self ).empty(), "uti::view::back: called on empty view" );

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
view< T >::view ( view && _other_ ) noexcept
        : begin_( _other_.begin_ ), end_( _other_.end_ )
{
        _other_.begin_ = _other_.end_ = nullptr ;
}

template< typename T >
constexpr
view< T > &
view< T >::operator= ( view && _other_ ) noexcept
{
        begin_ = _other_.begin_ ;
        end_   = _other_.end_   ;

        _other_.begin_ = _other_.end_ = nullptr ;

        return *this;
}


} // namespace uti
