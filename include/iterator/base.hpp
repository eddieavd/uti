//
//
//      uti
//      iterator/base.hpp
//

#pragma once

#include <iterator/meta.hpp>


namespace uti
{


template< typename T, typename IterCat, typename DiffType = ptrdiff_t, typename Pointer = T *, typename Reference = T & >
struct iterator_base
{
        using _self = iterator_base ;
public:
        using        value_type =         T ;
        using           pointer =   Pointer ;
        using         reference = Reference ;
        using   difference_type =  DiffType ;
        using iterator_category =   IterCat ;

        constexpr iterator_base (                       ) noexcept requires _has_forward_iterator_category_v< _self > : ptr_( nullptr ) {}
        constexpr iterator_base ( pointer const & _ptr_ ) noexcept : ptr_(   _ptr_ ) {}

        constexpr iterator_base             ( nullptr_t ) noexcept : ptr_ ( nullptr ) {}
        constexpr iterator_base & operator= ( nullptr_t ) noexcept { ptr_ = nullptr ; return *this ; }

        constexpr iterator_base             ( iterator_base const &  ) noexcept = default ;
        constexpr iterator_base & operator= ( iterator_base const &  ) noexcept = default ;
        constexpr iterator_base             ( iterator_base       && ) noexcept = default ;
        constexpr iterator_base & operator= ( iterator_base       && ) noexcept = default ;

        constexpr iterator_base ( iterator_base< remove_const_t< T >, IterCat, DiffType, add_pointer_t< remove_const_t< T > >, add_lvalue_reference_t< remove_const_t< T > > > const & _other_ )
                noexcept requires( is_const_v< T > ) : ptr_( _other_.ptr_ ) {} ;

        constexpr iterator_base & operator= ( iterator_base< remove_const_t< T >, IterCat, DiffType, add_pointer_t< remove_const_t< T > >, add_lvalue_reference_t< remove_const_t< T > > > const & _other_ )
                noexcept requires( is_const_v< T > ) { ptr_ = _other_.ptr_ ; }

        constexpr iterator_base ( iterator_base< remove_const_t< T >, IterCat, DiffType, add_pointer_t< remove_const_t< T > >, add_lvalue_reference_t< remove_const_t< T > > > && _other_ )
                noexcept requires( is_const_v< T > ) : ptr_( _other_.ptr_ ) {} ;

        constexpr iterator_base & operator= ( iterator_base< remove_const_t< T >, IterCat, DiffType, add_pointer_t< remove_const_t< T > >, add_lvalue_reference_t< remove_const_t< T > > > && _other_ )
                noexcept requires( is_const_v< T > ) { ptr_ = _other_.ptr_ ; }


        constexpr iterator_base ( iterator_base< T const, IterCat, DiffType, add_pointer_t< T const >, add_lvalue_reference_t< T const > > const & _other_ )
                noexcept requires( !is_const_v< T > ) : ptr_( _other_.ptr_ ) {}

        constexpr iterator_base & operator= ( iterator_base< T const, IterCat, DiffType, add_pointer_t< T const >, add_lvalue_reference_t< T const > > const & _other_ )
                noexcept requires( !is_const_v< T > ) { ptr_ = _other_.ptr_ ; }

        constexpr iterator_base ( iterator_base< T const, IterCat, DiffType, add_pointer_t< T const >, add_lvalue_reference_t< T const > > && _other_ )
                noexcept requires( !is_const_v< T > ) : ptr_( _other_.ptr_ ) {}

        constexpr iterator_base & operator= ( iterator_base< T const, IterCat, DiffType, add_pointer_t< T const >, add_lvalue_reference_t< T const > > && _other_ )
                noexcept requires( !is_const_v< T > ) { ptr_ = _other_.ptr_ ; }

        constexpr ~iterator_base () noexcept = default ;

        template< typename IterCat1 >
                requires is_base_of_v< IterCat1, iterator_category >
        constexpr iterator_base ( iterator_base< T, IterCat1 > const & _iter_ ) noexcept : ptr_( _iter_.ptr_ ) {}

        constexpr operator pointer ()       noexcept { return ptr_ ; }
        constexpr operator pointer () const noexcept { return ptr_ ; }

        constexpr iterator_base & operator++ (     ) noexcept {                     ++ptr_ ; return *this ; }
        constexpr iterator_base   operator++ ( int ) noexcept { auto prev = *this ; ++ptr_ ; return  prev ; }

        constexpr iterator_base & operator-- (     ) noexcept requires _has_bidirectional_iterator_category_v< _self > {                     --ptr_ ; return *this ; }
        constexpr iterator_base   operator-- ( int ) noexcept requires _has_bidirectional_iterator_category_v< _self > { auto prev = *this ; --ptr_ ; return  prev ; }

        constexpr iterator_base & operator+= ( difference_type const _n_ ) noexcept requires _has_random_access_iterator_category_v< _self > { this->ptr_ += _n_ ; return *this ; }
        constexpr iterator_base & operator-= ( difference_type const _n_ ) noexcept requires _has_random_access_iterator_category_v< _self > { this->ptr_ -= _n_ ; return *this ; }

        constexpr reference operator*  () noexcept { return *ptr_ ; }
        constexpr pointer   operator-> () noexcept { return  ptr_ ; }

        friend constexpr bool operator== ( iterator_base const & _lhs_, iterator_base const & _rhs_ ) noexcept
                requires _has_input_iterator_category_v< _self >
        {
                return _lhs_.ptr_ == _rhs_.ptr_ ;
        }
        friend constexpr bool operator!= ( iterator_base const & _lhs_, iterator_base const & _rhs_ ) noexcept
                requires _has_input_iterator_category_v< _self >
        {
                return _lhs_.ptr_ != _rhs_.ptr_ ;
        }
        friend constexpr void swap ( iterator_base & _lhs_, iterator_base & _rhs_ ) noexcept
                requires _has_input_iterator_category_v< _self >
        {
                auto _tmp_ = _lhs_.ptr_ ;
                _lhs_.ptr_ = _rhs_.ptr_ ;
                _rhs_.ptr_ = _tmp_ ;
        }

        friend constexpr bool operator< ( iterator_base const & _lhs_, iterator_base const & _rhs_ ) noexcept
                requires _has_random_access_iterator_category_v< _self >
        {
                return _lhs_.ptr_ < _rhs_.ptr_ ;
        }
        friend constexpr bool operator> ( iterator_base const & _lhs_, iterator_base const & _rhs_ ) noexcept
                requires _has_random_access_iterator_category_v< _self >
        {
                return _lhs_.ptr_ > _rhs_.ptr_ ;
        }
        friend constexpr bool operator<= ( iterator_base const & _lhs_, iterator_base const & _rhs_ ) noexcept
                requires _has_random_access_iterator_category_v< _self >
        {
                return _lhs_.ptr_ <= _rhs_.ptr_ ;
        }
        friend constexpr bool operator>= ( iterator_base const & _lhs_, iterator_base const & _rhs_ ) noexcept
                requires _has_random_access_iterator_category_v< _self >
        {
                return _lhs_.ptr_ >= _rhs_.ptr_ ;
        }

        friend constexpr iterator_base operator+ ( iterator_base const & _iter_, difference_type const _diff_ ) noexcept
                requires _has_random_access_iterator_category_v< _self >
        {
                return iterator_base{ _iter_.ptr_ + _diff_ } ;
        }
        friend constexpr iterator_base operator+ ( difference_type const _diff_, iterator_base const & _iter_ ) noexcept
                requires _has_random_access_iterator_category_v< _self >
        {
                return iterator_base{ _iter_.ptr_ + _diff_ } ;
        }

        friend constexpr iterator_base operator- ( iterator_base const & _iter_, difference_type const _diff_ ) noexcept
                requires _has_random_access_iterator_category_v< _self >
        {
                return iterator_base{ _iter_.ptr_ - _diff_ } ;
        }
        friend constexpr difference_type operator- ( iterator_base const & _lhs_, iterator_base const & _rhs_ ) noexcept
                requires _has_random_access_iterator_category_v< _self >
        {
                return _lhs_.ptr_ - _rhs_.ptr_ ;
        }

        constexpr reference operator[] ( difference_type const _idx_ ) const noexcept
                requires _has_random_access_iterator_category_v< _self >
        {
                return this->ptr_[ _idx_ ] ;
        }

        pointer ptr_ ;
} ;


} // namespace uti
