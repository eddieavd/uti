//
//
//      uti
//      iterator/base.hpp
//

#pragma once

#include <iterator/meta.hpp>


namespace uti
{


template< typename T >
struct _iterator
{
        using      value_type = T   ;
        using         pointer = T * ;
        using       reference = T & ;
        using difference_type = ptrdiff_t ;

        constexpr _iterator ( pointer const & _ptr_ ) noexcept : ptr_( _ptr_ ) {}

        constexpr operator pointer ()       noexcept { return ptr_ ; }
        constexpr operator pointer () const noexcept { return ptr_ ; }

        constexpr _iterator & operator++ () noexcept { ++ptr_ ; return *this ; }

        constexpr reference operator* () const noexcept { return *ptr_ ; }

        friend constexpr void swap ( _iterator & _lhs_, _iterator & _rhs_ ) noexcept
        {
                auto _tmp_ = _lhs_.ptr_ ;
                _lhs_.ptr_ = _rhs_.ptr_ ;
                _rhs_.ptr_ = _tmp_ ;
        }
private:
        pointer ptr_ ;
} ;

template< typename T >
struct _input_iterator
{
        using _base = _iterator< T > ;

        using      value_type = typename _base::     value_type ;
        using         pointer = typename _base::        pointer ;
        using       reference = typename _base::      reference ;
        using difference_type = typename _base::difference_type ;

        using iterator_category = input_iterator_tag ;

        constexpr _input_iterator ( pointer const & _ptr_ ) noexcept : ptr_( _ptr_ ) {}

        constexpr operator pointer ()       noexcept { return ptr_ ; }
        constexpr operator pointer () const noexcept { return ptr_ ; }

        constexpr value_type operator* () noexcept { return *ptr_ ; }

        constexpr _input_iterator & operator++ () noexcept { ++ptr_ ; return *this ; }

        constexpr _input_iterator operator++ ( int ) noexcept { auto prev = *this ; ++this->ptr_ ; return prev ; }

        constexpr pointer operator-> () const noexcept { return  this->ptr_ ; }

        friend constexpr bool operator== ( _input_iterator const & _lhs_, _input_iterator const & _rhs_ ) noexcept
        {
                return _lhs_.ptr_ == _rhs_.ptr_ ;
        }
        friend constexpr bool operator!= ( _input_iterator const & _lhs_, _input_iterator const & _rhs_ ) noexcept
        {
                return _lhs_.ptr_ != _rhs_.ptr_ ;
        }
        friend constexpr void swap ( _input_iterator & _lhs_, _input_iterator & _rhs_ ) noexcept
        {
                auto _tmp_ = _lhs_.ptr_ ;
                _lhs_.ptr_ = _rhs_.ptr_ ;
                _rhs_.ptr_ = _tmp_ ;
        }
private:
        pointer ptr_ ;
} ;

template< typename T >
struct _output_iterator
{
        using _base = _iterator< T > ;

        using      value_type = typename _base::     value_type ;
        using         pointer = typename _base::        pointer ;
        using       reference = typename _base::      reference ;
        using difference_type = typename _base::difference_type ;

        using iterator_category = output_iterator_tag ;

        constexpr _output_iterator ( pointer const & _ptr_ ) noexcept : ptr_( _ptr_ ) {}

        constexpr operator pointer ()       noexcept { return ptr_ ; }
        constexpr operator pointer () const noexcept { return ptr_ ; }

        constexpr reference operator* () noexcept { return *ptr_ ; }

        constexpr _output_iterator & operator++ () noexcept { ++ptr_ ; return *this ; }

        constexpr _output_iterator operator++ ( int ) noexcept { auto prev = *this ; ++this->ptr_ ; return prev ; }

        friend constexpr bool operator== ( _output_iterator const & _lhs_, _output_iterator const & _rhs_ ) noexcept
        {
                return _lhs_.ptr_ == _rhs_.ptr_ ;
        }
        friend constexpr bool operator!= ( _output_iterator const & _lhs_, _output_iterator const & _rhs_ ) noexcept
        {
                return _lhs_.ptr_ != _rhs_.ptr_ ;
        }
        friend constexpr void swap ( _output_iterator & _lhs_, _output_iterator & _rhs_ ) noexcept
        {
                auto _tmp_ = _lhs_.ptr_ ;
                _lhs_.ptr_ = _rhs_.ptr_ ;
                _rhs_.ptr_ = _tmp_ ;
        }
private:
        pointer ptr_ ;
} ;

template< typename T >
struct _forward_iterator
{
        using _base = _input_iterator< T > ;

        using      value_type = typename _base::     value_type ;
        using         pointer = typename _base::        pointer ;
        using       reference = typename _base::      reference ;
        using difference_type = typename _base::difference_type ;

        using iterator_category = forward_iterator_tag ;

        constexpr _forward_iterator (                       ) noexcept : ptr_( nullptr ) {}
        constexpr _forward_iterator ( pointer const & _ptr_ ) noexcept : ptr_(   _ptr_ ) {}

        constexpr operator pointer ()       noexcept { return ptr_ ; }
        constexpr operator pointer () const noexcept { return ptr_ ; }

        constexpr reference operator* () noexcept { return *ptr_ ; }

        constexpr _forward_iterator & operator++ () noexcept { ++ptr_ ; return *this ; }

        constexpr _forward_iterator operator++ ( int ) noexcept { auto prev = *this ; ++ptr_ ; return prev ; }

        friend constexpr bool operator== ( _forward_iterator const & _lhs_, _forward_iterator const & _rhs_ ) noexcept
        {
                return _lhs_.ptr_ == _rhs_.ptr_ ;
        }
        friend constexpr bool operator!= ( _forward_iterator const & _lhs_, _forward_iterator const & _rhs_ ) noexcept
        {
                return _lhs_.ptr_ != _rhs_.ptr_ ;
        }
        friend constexpr void swap ( _forward_iterator & _lhs_, _forward_iterator & _rhs_ ) noexcept
        {
                auto _tmp_ = _lhs_.ptr_ ;
                _lhs_.ptr_ = _rhs_.ptr_ ;
                _rhs_.ptr_ = _tmp_ ;
        }
private:
        pointer ptr_ ;
} ;

template< typename T >
struct _bidirectional_iterator
{
        using _base = _forward_iterator< T > ;

        using      value_type = typename _base::     value_type ;
        using         pointer = typename _base::        pointer ;
        using       reference = typename _base::      reference ;
        using difference_type = typename _base::difference_type ;

        using iterator_category = bidirectional_iterator_tag ;

        constexpr _bidirectional_iterator (                       ) noexcept : ptr_( nullptr ) {}
        constexpr _bidirectional_iterator ( pointer const & _ptr_ ) noexcept : ptr_(   _ptr_ ) {}

        constexpr operator pointer ()       noexcept { return ptr_ ; }
        constexpr operator pointer () const noexcept { return ptr_ ; }

        constexpr reference operator* () noexcept { return *ptr_ ; }

        constexpr _bidirectional_iterator & operator++ () noexcept { ++ptr_ ; return *this ; }

        constexpr _bidirectional_iterator operator++ ( int ) noexcept { auto prev = *this ; ++ptr_ ; return prev ; }

        constexpr _bidirectional_iterator & operator-- (     ) noexcept { --this->ptr_ ; return *this ; }
        constexpr _bidirectional_iterator   operator-- ( int ) noexcept { auto prev = *this ; --this->ptr_ ; return prev ; }

        friend constexpr bool operator== ( _bidirectional_iterator const & _lhs_, _bidirectional_iterator const & _rhs_ ) noexcept
        {
                return _lhs_.ptr_ == _rhs_.ptr_ ;
        }
        friend constexpr bool operator!= ( _bidirectional_iterator const & _lhs_, _bidirectional_iterator const & _rhs_ ) noexcept
        {
                return _lhs_.ptr_ != _rhs_.ptr_ ;
        }
        friend constexpr void swap ( _bidirectional_iterator & _lhs_, _bidirectional_iterator & _rhs_ ) noexcept
        {
                auto _tmp_ = _lhs_.ptr_ ;
                _lhs_.ptr_ = _rhs_.ptr_ ;
                _rhs_.ptr_ = _tmp_ ;
        }
private:
        pointer ptr_ ;
} ;

template< typename T >
struct _random_access_iterator
{
        using _base = _bidirectional_iterator< T > ;

        using      value_type = typename _base::     value_type ;
        using         pointer = typename _base::        pointer ;
        using       reference = typename _base::      reference ;
        using difference_type = typename _base::difference_type ;

        using iterator_category = random_access_iterator_tag ;

        constexpr _random_access_iterator (                       ) noexcept : ptr_( nullptr ) {}
        constexpr _random_access_iterator ( pointer const & _ptr_ ) noexcept : ptr_(   _ptr_ ) {}

        constexpr operator pointer ()       noexcept { return ptr_ ; }
        constexpr operator pointer () const noexcept { return ptr_ ; }

        constexpr reference operator* () noexcept { return *ptr_ ; }

        constexpr _random_access_iterator & operator++ () noexcept { ++ptr_ ; return *this ; }
        constexpr _random_access_iterator & operator-- () noexcept { --ptr_ ; return *this ; }

        constexpr _random_access_iterator operator++ ( int ) noexcept { auto prev = *this ; ++ptr_ ; return prev ; }
        constexpr _random_access_iterator operator-- ( int ) noexcept { auto prev = *this ; --ptr_ ; return prev ; }

        friend constexpr bool operator== ( _random_access_iterator const & _lhs_, _random_access_iterator const & _rhs_ ) noexcept
        {
                return _lhs_.ptr_ == _rhs_.ptr_ ;
        }
        friend constexpr bool operator!= ( _random_access_iterator const & _lhs_, _random_access_iterator const & _rhs_ ) noexcept
        {
                return _lhs_.ptr_ != _rhs_.ptr_ ;
        }
        friend constexpr void swap ( _random_access_iterator & _lhs_, _random_access_iterator & _rhs_ ) noexcept
        {
                auto _tmp_ = _lhs_.ptr_ ;
                _lhs_.ptr_ = _rhs_.ptr_ ;
                _rhs_.ptr_ = _tmp_ ;
        }

        friend constexpr bool operator< ( _random_access_iterator const & _lhs_, _random_access_iterator const & _rhs_ ) noexcept
        {
                return _lhs_.ptr_ < _rhs_.ptr_ ;
        }
        friend constexpr bool operator> ( _random_access_iterator const & _lhs_, _random_access_iterator const & _rhs_ ) noexcept
        {
                return _lhs_.ptr_ > _rhs_.ptr_ ;
        }
        friend constexpr bool operator<= ( _random_access_iterator const & _lhs_, _random_access_iterator const & _rhs_ ) noexcept
        {
                return _lhs_.ptr_ <= _rhs_.ptr_ ;
        }
        friend constexpr bool operator>= ( _random_access_iterator const & _lhs_, _random_access_iterator const & _rhs_ ) noexcept
        {
                return _lhs_.ptr_ >= _rhs_.ptr_ ;
        }

        constexpr _random_access_iterator & operator+= ( difference_type const _n_ ) noexcept { this->ptr_ += _n_ ; return *this ; }
        constexpr _random_access_iterator & operator-= ( difference_type const _n_ ) noexcept { this->ptr_ -= _n_ ; return *this ; }

        friend constexpr _random_access_iterator operator+ ( _random_access_iterator const & _iter_, difference_type const _diff_ ) noexcept
        {
                return _random_access_iterator{ _iter_.ptr_ + _diff_ } ;
        }
        friend constexpr _random_access_iterator operator+ ( difference_type const _diff_, _random_access_iterator const & _iter_ ) noexcept
        {
                return _random_access_iterator{ _iter_.ptr_ + _diff_ } ;
        }

        friend constexpr _random_access_iterator operator- ( _random_access_iterator const & _iter_, difference_type const _diff_ ) noexcept
        {
                return _random_access_iterator{ _iter_.ptr_ - _diff_ } ;
        }
        friend constexpr difference_type operator- ( _random_access_iterator const & _lhs_, _random_access_iterator const & _rhs_ ) noexcept
        {
                return _lhs_.ptr_ - _rhs_.ptr_ ;
        }

        constexpr reference operator[] ( difference_type const _idx_ ) const noexcept
        {
                return this->ptr_[ _idx_ ] ;
        }
private:
        pointer ptr_ ;
} ;


} // namespace uti
