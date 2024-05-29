//
//
//      uti
//      segment_tree.hpp
//

#pragma once

#include <util/assert.hpp>
#include <mem/allocator.hpp>
#include <container/vector.hpp>

#include <iostream>


namespace uti
{


namespace _detail
{

template< typename T >
constexpr auto less = []( T const & lhs, T const & rhs )
{
        return lhs < rhs ;
} ;

} // namespace _detail


template< typename T, auto Compare = _detail::less< T >, typename Alloc = allocator< T > >
class segment_tree : public buffer< T, Alloc >, public view< T >
{
        using       _self =  segment_tree               ;
        using       _base = _container_base< T        > ;
        using  _buff_base =  buffer        < T, Alloc > ;
        using  _view_base =  view          < T        > ;

        using _comparator = decltype( Compare ) ;

        static constexpr _comparator comp_ { Compare } ;
public:
        using      value_type = typename      _base::     value_type ;
        using       size_type = typename      _base::      size_type ;
        using      ssize_type = typename      _base::     ssize_type ;
        using difference_type = typename      _base::difference_type ;

        using  allocator_type = typename _buff_base:: allocator_type ;
        using   _alloc_traits = typename _buff_base::  _alloc_traits ;

        using         pointer = typename      _base::        pointer ;
        using   const_pointer = typename      _base::  const_pointer ;
        using       reference = typename      _base::      reference ;
        using const_reference = typename      _base::const_reference ;

        using        iterator = typename      _base::       iterator ;
        using  const_iterator = typename      _base:: const_iterator ;

        constexpr segment_tree (                             ) noexcept = default ;
        explicit  segment_tree ( ssize_type const _capacity_ )                    ;

        segment_tree ( ssize_type const _count_, value_type const & _val_ ) ;

        constexpr bool operator== ( segment_tree const & _other_ ) const noexcept ;

        segment_tree & operator+= ( segment_tree const & _other_ ) noexcept ;
        segment_tree & operator-= ( segment_tree const & _other_ ) noexcept ;

        segment_tree operator- () noexcept ;

        friend segment_tree operator+ ( segment_tree & _lhs_, segment_tree const & _rhs_ ) noexcept
        {
                _lhs_ += _rhs_ ;
                return   _lhs_ ;
        }
        friend segment_tree operator- ( segment_tree & _lhs_, segment_tree const & _rhs_ ) noexcept
        {
                _lhs_ -= _rhs_ ;
                return   _lhs_ ;
        }

        ~segment_tree () noexcept = default ;

        UTI_NODISCARD constexpr
        decltype( auto ) element_at ( auto&&... _coords_ ) const noexcept
                requires( is_n_dim_container_v< _self, sizeof...( _coords_ ) > ) ;

        UTI_NODISCARD constexpr
        decltype( auto ) range ( auto&&... _coords_ ) const noexcept
                requires( sizeof...( _coords_ ) % 2 == 0 &&
                          is_n_dim_container_v< _self, sizeof...( _coords_ ) / 2 > ) ;

        constexpr void push_back ( value_type const &  _val_ ) ;
        constexpr void push_back ( value_type       && _val_ ) ;

        constexpr void emplace_back ( auto&&... _args_ ) ;

        constexpr void insert ( value_type const &  _val_, ssize_type const _position_ ) ;
        constexpr void insert( value_type        && _val_, ssize_type const _position_ ) ;

        constexpr ssize_type reserve (                             ) ;
        constexpr ssize_type reserve ( ssize_type const _capacity_ ) ;

        constexpr void erase ( ssize_type const _position_ ) noexcept ;

        constexpr void clear () noexcept ;

        UTI_NODISCARD constexpr       iterator  begin ()       noexcept { return _view_base::begin() ; }
        UTI_NODISCARD constexpr const_iterator  begin () const noexcept { return _view_base::begin() ; }
        UTI_NODISCARD constexpr const_iterator cbegin () const noexcept { return begin() ; }

        UTI_NODISCARD constexpr       iterator  end ()       noexcept { return _view_base::end() ; }
        UTI_NODISCARD constexpr const_iterator  end () const noexcept { return _view_base::end() ; }
        UTI_NODISCARD constexpr const_iterator cend () const noexcept { return end() ; }

        UTI_NODISCARD constexpr       bool    empty () const noexcept { return _view_base::   empty()     ; }
        UTI_NODISCARD constexpr ssize_type     size () const noexcept { return _view_base::    size()     ; }
        UTI_NODISCARD constexpr ssize_type capacity () const noexcept { return _buff_base::capacity() / 2 ; }

        void print_tree () const noexcept
        {
                for( auto it = _buff_base::begin(); it != _buff_base::end(); ++it )
                {
                        std::cout << *it << " " ;
                }
                std::cout << "\n" ;
        }
private:
        void _emplace ( auto&&... _args_ ) noexcept( is_nothrow_constructible_v< value_type, decltype( _args_ )... > ) ;

        constexpr       reference _at ( ssize_type const _index_ )       noexcept ;
        constexpr const_reference _at ( ssize_type const _index_ ) const noexcept ;

        constexpr ssize_type _msb           ( ssize_type _num_ ) const noexcept ;
        constexpr ssize_type _round_to_pow2 ( ssize_type _num_ ) const noexcept ;

        constexpr void _rebuild_tree () noexcept ;

        constexpr void _update ( ssize_type _position_, value_type const & _val_ ) ;
} ;


template< typename T, auto Compare, typename Alloc >
segment_tree< T, Compare, Alloc >::segment_tree ( ssize_type const _capacity_ )
        : _buff_base( 2 * _round_to_pow2( _capacity_ ) ),
          _view_base( _buff_base::begin() + capacity() ,
                      _buff_base::begin() + capacity() )
{}

template< typename T, auto Compare, typename Alloc >
segment_tree< T, Compare, Alloc >::segment_tree ( ssize_type const _count_, value_type const & _val_ )
        : _buff_base( 2 * _round_to_pow2( _count_ ) )  ,
          _view_base( _buff_base::begin() + capacity() ,
                      _buff_base::begin() + capacity() )
{
        for( ssize_type i = 0; i < _count_; ++i )
        {
                _emplace( _val_ ) ;
        }
        _rebuild_tree() ;
}


template< typename T, auto Compare, typename Alloc >
void
segment_tree< T, Compare, Alloc >::_emplace ( auto&&... _args_ ) noexcept( is_nothrow_constructible_v< value_type, decltype( _args_ )... > )
{
        _alloc_traits::construct( _view_base::_end()++, UTI_FWD( _args_ )... ) ;
}

template< typename T, auto Compare, typename Alloc >
constexpr
typename
segment_tree< T, Compare, Alloc >::reference
segment_tree< T, Compare, Alloc >::_at ( ssize_type const _index_ ) noexcept
{
        UTI_CEXPR_ASSERT( 0 <= _index_ && _index_ < _buff_base::capacity(), "uti::segment_tree::_at: index out of bounds" ) ;

        return *( _buff_base::begin() + _index_ ) ;
}

template< typename T, auto Compare, typename Alloc >
constexpr
typename
segment_tree< T, Compare, Alloc >::const_reference
segment_tree< T, Compare, Alloc >::_at ( ssize_type const _index_ ) const noexcept
{
        UTI_CEXPR_ASSERT( 0 <= _index_ && _index_ < _buff_base::capacity(), "uti::segment_tree::_at: index out of bounds" ) ;

        return *( _buff_base::begin() + _index_ ) ;
}

template< typename T, auto Compare, typename Alloc >
constexpr
typename
segment_tree< T, Compare, Alloc >::ssize_type
segment_tree< T, Compare, Alloc >::_msb ( ssize_type _num_ ) const noexcept
{
        _num_ |= ( _num_ >>  1 ) ;
        _num_ |= ( _num_ >>  2 ) ;
        _num_ |= ( _num_ >>  4 ) ;
        _num_ |= ( _num_ >>  8 ) ;
        _num_ |= ( _num_ >> 16 ) ;
        _num_ |= ( _num_ >> 32 ) ;

        return ( _num_ & ~( _num_ >> 1 ) ) ;
}

template< typename T, auto Compare, typename Alloc >
constexpr
typename
segment_tree< T, Compare, Alloc >::ssize_type
segment_tree< T, Compare, Alloc >::_round_to_pow2 ( ssize_type _num_ ) const noexcept
{
        auto msb = _msb( _num_ ) ;

        return _num_ == msb ? _num_ : ( msb << 1 ) ;
}

template< typename T, auto Compare, typename Alloc >
constexpr void
segment_tree< T, Compare, Alloc >::_rebuild_tree () noexcept
{
        for( auto i = capacity() - 1; i > 0; --i )
        {
                if( i > size() )
                {
                        _at( i ) = value_type() ;
                }
                else if( i + 1 > size() )
                {
                        _at( i ) = _at( 2 * i ) ;
                }
                else
                {
                        _at( i ) = comp_( _at( 2 * i ), _at( ( 2 * i ) + 1 ) ) ;
                }
        }
}


} // namespace uti
