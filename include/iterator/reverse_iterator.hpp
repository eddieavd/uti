//
//
//      uti
//      reverse_iterator.hpp
//

#pragma once

#include <iterator/meta.hpp>


namespace uti
{


template< typename Iter >
class reverse_iterator
{
        using        _self = reverse_iterator        ;
        using _iter_traits = iterator_traits< Iter > ;
public:
        using        value_type = typename _iter_traits::       value_type ;
        using           pointer = typename _iter_traits::          pointer ;
        using         reference = typename _iter_traits::        reference ;
        using   difference_type = typename _iter_traits::  difference_type ;
        using iterator_category = typename _iter_traits::iterator_category ;

        using iterator_type = Iter ;

        constexpr reverse_iterator (                              ) noexcept requires _has_forward_iterator_category_v< _self > : iter_(        ) {}
        constexpr reverse_iterator ( iterator_type const & _iter_ ) noexcept                                                    : iter_( _iter_ ) {}

        constexpr reverse_iterator             ( reverse_iterator const &  ) noexcept = default ;
        constexpr reverse_iterator & operator= ( reverse_iterator const &  ) noexcept = default ;
        constexpr reverse_iterator             ( reverse_iterator       && ) noexcept = default ;
        constexpr reverse_iterator & operator= ( reverse_iterator       && ) noexcept = default ;

        constexpr ~reverse_iterator () noexcept = default ;

        constexpr operator pointer ()       noexcept { return static_cast< pointer >( iter_ ) ; }
        constexpr operator pointer () const noexcept { return static_cast< pointer >( iter_ ) ; }

        constexpr reverse_iterator & operator++ (     ) noexcept { --iter_ ; return *this ; }
        constexpr reverse_iterator   operator++ ( int ) noexcept { auto prev = *this ; --iter_ ; return prev ; }

        constexpr reverse_iterator & operator-- (     ) noexcept requires _has_bidirectional_iterator_category_v< _self > { ++iter_ ; return *this ; }
        constexpr reverse_iterator   operator-- ( int ) noexcept requires _has_bidirectional_iterator_category_v< _self > { auto prev = *this ; ++iter_ ; return prev ; }

        constexpr reverse_iterator & operator+= ( difference_type const _n_ ) noexcept requires _has_random_access_iterator_category_v< _self > { iter_ -= _n_ ; return *this ; }
        constexpr reverse_iterator & operator-= ( difference_type const _n_ ) noexcept requires _has_random_access_iterator_category_v< _self > { iter_ += _n_ ; return *this ; }

        constexpr reference operator*  () noexcept { return *iter_ ; }
        constexpr pointer   operator-> () noexcept { return  iter_ ; }

        friend constexpr bool operator== ( reverse_iterator const & _lhs_, reverse_iterator const & _rhs_ ) noexcept
                requires _has_input_iterator_category_v< _self >
        {
                return _lhs_.iter_ == _rhs_.iter_ ;
        }
        friend constexpr bool operator!= ( reverse_iterator const & _lhs_, reverse_iterator const & _rhs_ ) noexcept
                requires _has_input_iterator_category_v< _self >
        {
                return _lhs_.iter_ != _rhs_.iter_ ;
        }
        friend constexpr void swap ( reverse_iterator & _lhs_, reverse_iterator & _rhs_ ) noexcept
                requires _has_input_iterator_category_v< _self >
        {
                using ::uti::swap ;
                swap( _lhs_.iter_, _rhs_.iter_ ) ;
        }

        friend constexpr bool operator< ( reverse_iterator const & _lhs_, reverse_iterator const & _rhs_ ) noexcept
                requires _has_random_access_iterator_category_v< _self >
        {
                return _lhs_.iter_ > _rhs_.iter_ ;
        }
        friend constexpr bool operator> ( reverse_iterator const & _lhs_, reverse_iterator const & _rhs_ ) noexcept
                requires _has_random_access_iterator_category_v< _self >
        {
                return _lhs_.iter_ < _rhs_.iter_ ;
        }
        friend constexpr bool operator<= ( reverse_iterator const & _lhs_, reverse_iterator const & _rhs_ ) noexcept
                requires _has_random_access_iterator_category_v< _self >
        {
                return _lhs_.iter_ >= _rhs_.iter_ ;
        }
        friend constexpr bool operator>= ( reverse_iterator const & _lhs_, reverse_iterator const & _rhs_ ) noexcept
                requires _has_random_access_iterator_category_v< _self >
        {
                return _lhs_.iter_ <= _rhs_.iter_ ;
        }

        friend constexpr reverse_iterator operator+ ( reverse_iterator const & _iter_, difference_type const _diff_ ) noexcept
                requires _has_random_access_iterator_category_v< _self >
        {
                return reverse_iterator{ _iter_.iter_ - _diff_ } ;
        }
        friend constexpr reverse_iterator operator+ ( difference_type const _diff_, reverse_iterator const & _iter_ ) noexcept
                requires _has_random_access_iterator_category_v< _self >
        {
                return reverse_iterator{ _iter_.iter_ - _diff_ } ;
        }

        friend constexpr reverse_iterator operator- ( reverse_iterator const & _iter_, difference_type const _diff_ ) noexcept
                requires _has_random_access_iterator_category_v< _self >
        {
                return reverse_iterator{ _iter_.iter_ + _diff_ } ;
        }
        friend constexpr difference_type operator- ( reverse_iterator const & _lhs_, reverse_iterator const & _rhs_ ) noexcept
                requires _has_random_access_iterator_category_v< _self >
        {
                return _rhs_.iter_ - _lhs_.iter_ ;
        }

        constexpr reference operator[] ( difference_type const _idx_ ) const noexcept
                requires _has_random_access_iterator_category_v< _self >
        {
                return *( iter_ - _idx_ ) ;
        }
private:
        iterator_type iter_ ;
} ;


} // namespace uti
