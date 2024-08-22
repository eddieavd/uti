//
//
//      uti
//      vector.hpp
//

#pragma once

#include <algo/swap.hpp>
#include <algo/mem.hpp>
#include <container/view.hpp>
#include <container/buffer.hpp>
#include <meta/concepts.hpp>


namespace uti
{


template< typename T, typename Alloc = allocator< T > >
class vector : public buffer< T, Alloc >, public view< T >
{
protected:
        using      _self =  vector                     ;
        using      _base = _container_base< T        > ;
        using _buff_base =  buffer        < T, Alloc > ;
        using _view_base =  view          < T        > ;
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

        constexpr          vector (                             ) noexcept = default ;
        constexpr explicit vector ( ssize_type const _capacity_ )                    ;

        constexpr vector ( ssize_type const _count_, value_type const & _val_ ) ;

        constexpr vector ( _buff_base && _buffer_, ssize_type const _size_ ) noexcept ;

//      template< meta::random_access_iterator Iter >
//      constexpr vector ( Iter begin, Iter const & end ) ;

        constexpr vector             ( vector const &  _other_ )          ;
        constexpr vector             ( vector       && _other_ ) noexcept ;
        constexpr vector & operator= ( vector const &  _other_ )          ;
        constexpr vector & operator= ( vector       && _other_ ) noexcept ;

        constexpr bool operator== ( vector const & _other_ ) const noexcept ;

        constexpr ~vector () noexcept ;

        constexpr void push_back ( value_type const &  _val_ ) ;
        constexpr void push_back ( value_type       && _val_ ) ;

        template< typename... Args >
        constexpr void emplace_back ( Args&&... _args_ ) ;

        constexpr void pop_back  () noexcept ;
        constexpr void pop_front () noexcept ;

        UTI_NODISCARD constexpr value_type pop_back_val  () noexcept ;
        UTI_NODISCARD constexpr value_type pop_front_val () noexcept ;

        constexpr void reserve (                             ) ;
        constexpr void reserve ( ssize_type const _capacity_ ) ;

        constexpr void shrink ( ssize_type const _capacity_ ) ;

        constexpr void shrink_to_fit (                         )          ;
        constexpr void shrink_size   ( ssize_type const _size_ ) noexcept ;

        constexpr void insert ( ssize_type const _position_, value_type const &  _val_ ) ;
        constexpr void insert ( ssize_type const _position_, value_type       && _val_ ) ;

        constexpr void erase        ( ssize_type const _position_ ) noexcept( is_nothrow_move_assignable_v< value_type > ) ;
        constexpr void erase_stable ( ssize_type const _position_ ) noexcept( is_nothrow_move_assignable_v< value_type > ) ;

        constexpr void clear () noexcept ;

        UTI_NODISCARD constexpr       iterator  begin ()       noexcept { return _view_base:: begin(); }
        UTI_NODISCARD constexpr const_iterator  begin () const noexcept { return _view_base:: begin(); }
        UTI_NODISCARD constexpr const_iterator cbegin () const noexcept { return _view_base::cbegin(); }

        UTI_NODISCARD constexpr       iterator  end ()       noexcept { return _view_base:: end(); }
        UTI_NODISCARD constexpr const_iterator  end () const noexcept { return _view_base:: end(); }
        UTI_NODISCARD constexpr const_iterator cend () const noexcept { return _view_base::cend(); }
protected:
        template< typename... Args >
        constexpr void _emplace ( Args&&... _args_ ) noexcept( is_nothrow_constructible_v< value_type, Args... > ) ;

        constexpr void _copy_buffer ( _buff_base & _buff_ ) noexcept ( is_nothrow_copy_assignable_v< value_type > && is_nothrow_destructible_v< value_type > ) ;
        constexpr void _swap_buffer ( _buff_base & _buff_ ) noexcept ( is_nothrow_swappable_v< value_type > ) ;
};

template< typename T >
vector ( vector< T >::ssize_type const _count_, T const & _val_ ) -> vector< T > ;


template< typename T, typename Alloc >
constexpr void
vector< T, Alloc >::_copy_buffer ( _buff_base & _buff_ ) noexcept( is_nothrow_copy_assignable_v< value_type > && is_nothrow_destructible_v< value_type > )
{
        if constexpr( is_trivially_relocatable_v< value_type > )
        {
                ::uti::copy( _view_base::begin(), _view_base::end(), _buff_.begin() );
        }
        else
        {
                for( ssize_type i = 0; i < _view_base::size(); ++i )
                {
                        ::uti::construct( _buff_.begin() + i, UTI_MOVE( _view_base::at( i ) ) );
                        ::uti::destroy( _view_base::begin() + i );
                }
        }
}

template< typename T, typename Alloc >
constexpr void
vector< T, Alloc >::_swap_buffer ( _buff_base & _buff_ ) noexcept( is_nothrow_swappable_v< value_type > )
{
        using uti::swap ;
        swap( _buff_, *this ) ;
}

template< typename T, typename Alloc >
constexpr
vector< T, Alloc >::vector ( ssize_type const _capacity_ )
        : _buff_base( _capacity_ ), _view_base( _buff_base::begin(), _buff_base::begin() ) {}

template< typename T, typename Alloc >
constexpr
vector< T, Alloc >::vector ( ssize_type const _count_, value_type const & _val_ )
        : _buff_base( _count_ ), _view_base( _buff_base::begin(), _buff_base::begin() )
{
        if constexpr( is_trivially_copy_constructible_v< value_type > )
        {
                ::uti::memset( _buff_base::begin(), _buff_base::end(), _val_ ) ;
                _view_base::_size() = _buff_base::capacity() ;
        }
        else
        {
                for( ssize_type i = 0; i < _count_; ++i )
                {
                        _emplace( _val_ );
                }
        }
}

template< typename T, typename Alloc >
constexpr
vector< T, Alloc >::vector ( _buff_base && _buffer_, ssize_type const _size_ ) noexcept
        : _buff_base( UTI_MOVE( _buffer_ ) ),
          _view_base( _buff_base::begin(), _buff_base::begin() + _size_ )
{}

/*
template< typename T, typename Alloc >
template< meta::random_access_iterator Iter >
constexpr
vector< T, Alloc >::vector ( Iter _begin_, Iter const & _end_ )
        : _buff_base( ::uti::distance( _begin_, _end_ ) ),
          _view_base( _buff_base::begin(), _buff_base::end() )
{
        if constexpr( is_trivially_copy_constructible_v< value_type > )
        {
                uti::_memmove_impl( _begin_, _end_, _view_base::begin() ) ;
        }
        else
        {
                while( _begin_ != _end_ )
                {
                        _emplace( *_begin_++ ) ;
                }
        }
}
*/

template< typename T, typename Alloc >
constexpr
vector< T, Alloc >::vector ( vector const & _other_ )
        : _buff_base( _other_.size() ), _view_base( _buff_base::begin(), _buff_base::begin() )
{
        if constexpr( is_trivially_copy_assignable_v< value_type > )
        {
                ::uti::copy( _other_.begin(), _other_.end(), _view_base::begin() );
                _view_base::_size() = _other_.size() ;
        }
        else
        {
                for( auto const & val : _other_ )
                {
                        _emplace( val );
                }
        }
}

template< typename T, typename Alloc >
constexpr
vector< T, Alloc >::vector ( vector && _other_ ) noexcept
        : _buff_base( UTI_MOVE( _other_ ) ), _view_base( UTI_MOVE( _other_ ) ) {}

template< typename T, typename Alloc >
constexpr
vector< T, Alloc > &
vector< T, Alloc >::operator= ( vector const & _other_ )
{
        if constexpr( is_trivially_copy_assignable_v< value_type > && is_trivially_destructible_v< value_type > )
        {
                reserve( _other_.size() );
                ::uti::copy( _other_.begin(), _other_.end(), _view_base::begin() );
        }
        else
        {
                if( _view_base::size() >= _other_.size() )
                {
                        for( ssize_type i = 0; i < _other_.size(); ++i )
                        {
                                _view_base::at( i ) = _other_.at( i );
                        }
                        shrink_size( _other_.size() );
                }
                else
                {
                        reserve( _other_.size() );

                        ssize_type pos { 0 } ;
                        for( ; pos < _view_base::size(); ++pos )
                        {
                                _view_base::at( pos ) = _other_.at( pos );
                        }
                        for( ; pos < _other_.size(); ++pos )
                        {
                                _emplace( _other_.at( pos ) );
                        }
                }
        }
        _view_base::_size() = _other_.size();

        return *this;
}

template< typename T, typename Alloc >
constexpr
vector< T, Alloc > &
vector< T, Alloc >::operator= ( vector && _other_ ) noexcept
{
        clear();
        _buff_base::deallocate();

        this->_buffer()   = _other_._buffer()   ;
        this->begin_      = _other_.begin_      ;
        this->size_       = _other_.size_       ;
        this->_capacity() = _other_._capacity() ;

        _other_._buffer() = _other_.begin_ = nullptr;
        _other_.size_ = 0 ;
        _other_._capacity() = 0 ;

        return *this;
}

template< typename T, typename Alloc >
constexpr bool
vector< T, Alloc >::operator== ( vector const & _other_ ) const noexcept
{
        if( _buff_base::data() == _other_.data() && _view_base::size() == _other_.size() )
        {
                return true;
        }
        for( ssize_type i = 0; i < _view_base::size(); ++i )
        {
                if( _view_base::at( i ) != _other_.at( i ) )
                {
                        return false;
                }
        }
        return true;
}

template< typename T, typename Alloc >
constexpr
vector< T, Alloc >::~vector () noexcept
{
        clear();
}

template< typename T, typename Alloc >
constexpr void
vector< T, Alloc >::push_back ( value_type const & _val_ )
{
        emplace_back( _val_ ) ;
}

template< typename T, typename Alloc >
constexpr void
vector< T, Alloc >::push_back ( value_type && _val_ )
{
        emplace_back( UTI_MOVE( _val_ ) ) ;
}

template< typename T, typename Alloc >
template< typename... Args >
constexpr void
vector< T, Alloc >::emplace_back ( Args&&... _args_ )
{
        reserve();
        _emplace( UTI_FWD( _args_ )... );
}

template< typename T, typename Alloc >
template< typename... Args >
constexpr void
vector< T, Alloc >::_emplace ( Args&&... _args_ ) noexcept( is_nothrow_constructible_v< value_type, Args... > )
{
        ::uti::construct( _view_base::end(), UTI_FWD( _args_ )... );
        _view_base::_size()++ ;
}

template< typename T, typename Alloc >
constexpr void
vector< T, Alloc >::pop_back () noexcept
{
        UTI_ASSERT( !_view_base::empty(), "uti::vector::pop_back: called on empty vector" );

        if constexpr( !is_trivially_destructible_v< value_type > )
        {
                ::uti::destroy( _view_base::end() - 1 );
        }
        _view_base::pop_back();
}

template< typename T, typename Alloc >
constexpr void
vector< T, Alloc >::pop_front () noexcept
{
        UTI_ASSERT( !_view_base::empty(), "uti::vector::pop_front: called on empty vector" );

        if constexpr( !is_trivially_destructible_v< value_type > )
        {
                ::uti::destroy( _view_base::begin() );
        }
        _view_base::pop_front();
}

template< typename T, typename Alloc >
constexpr
vector< T, Alloc >::value_type
vector< T, Alloc >::pop_back_val () noexcept
{
        value_type val( _view_base::cback() );
        pop_back();
        return val;
}

template< typename T, typename Alloc >
constexpr
vector< T, Alloc >::value_type
vector< T, Alloc >::pop_front_val () noexcept
{
        value_type val( _view_base::cfront() );
        pop_front();
        return val;
}

template< typename T, typename Alloc >
constexpr void
vector< T, Alloc >::reserve ()
{
        if( _view_base::size() >= _buff_base::capacity() )
        {
                reserve( _buff_base::capacity() == 0 ? 4 : _buff_base::capacity() * 2 );
        }
}

template< typename T, typename Alloc >
constexpr void
vector< T, Alloc >::reserve ( ssize_type const _capacity_ )
{
        if( _capacity_ <= _buff_base::capacity() ) return ;

        if( _buff_base::capacity() == 0 )
        {
                _buff_base::reserve( _capacity_ );
                _view_base::_begin() = _buff_base::begin();
                _view_base::_size () = 0 ;

                return ;
        }
        if( _buff_base::realloc_inplace( _capacity_ ) )
        {
                return ;
        }
        if constexpr( is_trivially_relocatable_v< value_type > )
        {
                ssize_type begin_pos = _view_base::begin() - _buff_base::begin();
                ssize_type        sz = _view_base::size() ;

                _buff_base::reserve( _capacity_ );

                _view_base::_begin() = _buff_base::begin() + begin_pos ;
                _view_base:: _size() = sz ;
        }
        else
        {
                ssize_type size = _view_base::size();
                _buff_base buff( _capacity_ );

                _copy_buffer( buff );
                _swap_buffer( buff );

                _view_base::_begin() = _buff_base::begin();
                _view_base:: _size() = size ;
        }
}

template< typename T, typename Alloc >
constexpr void
vector< T, Alloc >::shrink ( ssize_type const _capacity_ )
{
        shrink_size( _capacity_ );
        shrink_to_fit();
}

template< typename T, typename Alloc >
constexpr void
vector< T, Alloc >::shrink_to_fit ()
{
        if( _view_base::size() >= _buff_base::capacity() ) return;

        _buff_base buff( _view_base::size() );

        _copy_buffer( buff );
        _swap_buffer( buff );

        _view_base::_begin() = _buff_base::begin();
        _view_base:: _size() = _buff_base::capacity();
}

template< typename T, typename Alloc >
constexpr void
vector< T, Alloc >::shrink_size ( ssize_type const _size_ ) noexcept
{
        if( _size_ >= _view_base::size() ) return;

        if constexpr( !is_trivially_destructible_v< value_type > )
        {
                for( ssize_type i = _size_; i < _view_base::size(); ++i )
                {
                        ::uti::destroy( _view_base::begin() + i );
                }
        }
        _view_base::_size() = _size_;
}

template< typename T, typename Alloc >
constexpr void
vector< T, Alloc >::insert ( ssize_type const _position_, value_type const & _val_ )
{
        UTI_ASSERT( 0 <= _position_ && _position_ <= _view_base::size(), "uti::vector::insert: index out of range" );

        if( _position_ == _view_base::size() )
        {
                push_back( _val_ );
                return;
        }
        reserve();

        if constexpr( is_trivially_relocatable_v< value_type > )
        {
                ::uti::memmove_back( _view_base::end() - 1, _view_base::begin() + _position_, _view_base::end() ) ;
        }
        else
        {
                ::uti::construct( _view_base::end(), UTI_MOVE( _view_base::back() ) );
                for( ssize_type i = _view_base::size() - 1; i > _position_; --i )
                {
                        _view_base::at( i ) = UTI_MOVE( _view_base::at( i - 1 ) );
                }
        }
        _view_base::at( _position_ ) = _val_;
        ++_view_base::_size();
}

template< typename T, typename Alloc >
constexpr void
vector< T, Alloc >::insert ( ssize_type const _position_, value_type && _val_ )
{
        UTI_ASSERT( 0 <= _position_ && _position_ <= _view_base::size(), "uti::vector::insert: index out of range" );

        if( _position_ == _view_base::size() )
        {
                push_back( _val_ );
                return;
        }
        reserve();

        if constexpr( is_trivially_relocatable_v< value_type > )
        {
                ::uti::memmove_back( _view_base::end() - 1, _view_base::begin() + _position_, _view_base::end() ) ;
        }
        else
        {
                ::uti::construct( _view_base::end(), UTI_MOVE( _view_base::back() ) );
                for( ssize_type i = _view_base::size() - 1; i > _position_; --i )
                {
                        _view_base::at( i ) = UTI_MOVE( _view_base::at( i - 1 ) );
                }
        }
        _view_base::at( _position_ ) = UTI_MOVE( _val_ );
        ++_view_base::_size();
}

template< typename T, typename Alloc >
constexpr void
vector< T, Alloc >::erase ( ssize_type const _position_ ) noexcept( is_nothrow_move_assignable_v< value_type > )
{
        UTI_ASSERT( 0 <= _position_ && _position_ < _view_base::size(), "uti::vector::erase: index out of range" );

        _view_base::at( _position_ ) = UTI_MOVE( _view_base::back() );

        pop_back();
}

template< typename T, typename Alloc >
constexpr void
vector< T, Alloc >::erase_stable ( ssize_type const _position_ ) noexcept( is_nothrow_move_assignable_v< value_type > )
{
        UTI_ASSERT( 0 <= _position_ && _position_ < _view_base::size(), "uti::vector::erase_stable: index out of range" );

        for( ssize_type i = _position_; i < _view_base::size() - 1; ++i )
        {
                _view_base::at( i ) = UTI_MOVE( _view_base::at( i + 1 ) );
        }
        pop_back();
}

template< typename T, typename Alloc >
constexpr void
vector< T, Alloc >::clear () noexcept
{
        if constexpr( !is_trivially_destructible_v< value_type > )
        {
                for( ssize_type i = 0; i < _view_base::size(); ++i )
                {
                        ::uti::destroy( _view_base::begin() + i );
                }
        }
        _view_base::_begin() = _buff_base::begin();
        _view_base::_size() = 0 ;
}


} // namespace uti
