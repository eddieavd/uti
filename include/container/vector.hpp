//
//
//      uti
//      vector.hpp
//

#pragma once

#include <meta/traits.hpp>
#include <algo/copy.hpp>
#include <algo/swap.hpp>
#include <container/vectorlike.hpp>


namespace uti
{


template< typename T >
class vector : public _vectorlike_buffer< T >, public _vectorlike_view< T >
{
        using      _self =  vector                 ;
        using      _base = _vectorlike_base  < T > ;
        using _buff_base = _vectorlike_buffer< T > ;
        using _view_base = _vectorlike_view  < T > ;
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

        constexpr vector (                             ) noexcept = default ;
        explicit  vector ( ssize_type const _capacity_ )                    ;

        vector ( ssize_type const _count_, value_type const & _val_ ) ;

        vector             ( vector const &  _other_ )          ;
        vector             ( vector       && _other_ ) noexcept ;
        vector & operator= ( vector const &  _other_ )          ;
        vector & operator= ( vector       && _other_ ) noexcept ;

        ~vector () noexcept ;

        void push_back ( value_type const &  _val_ ) ;
        void push_back ( value_type       && _val_ ) ;

        template< typename... Args >
        void emplace_back ( Args&&... _args_ ) ;

        void pop_back  () noexcept ;
        void pop_front () noexcept ;

        UTI_NODISCARD value_type pop_back_val  () noexcept ;
        UTI_NODISCARD value_type pop_front_val () noexcept ;

        ssize_type reserve (                             ) ;
        ssize_type reserve ( ssize_type const _capacity_ ) ;

        ssize_type shrink ( ssize_type const _capacity_ ) ;

        void shrink_to_fit (                         )          ;
        void shrink_size   ( ssize_type const _size_ ) noexcept ;

        void insert ( value_type const &  _val_, ssize_type const _position_ ) ;
        void insert ( value_type       && _val_, ssize_type const _position_ ) ;

        void erase        ( ssize_type const _position_ ) noexcept( is_nothrow_move_assignable_v< value_type > ) ;
        void erase_stable ( ssize_type const _position_ ) noexcept( is_nothrow_move_assignable_v< value_type > ) ;

        void clear () noexcept ;

        UTI_NODISCARD       iterator  begin ()       noexcept { return _view_base:: begin(); }
        UTI_NODISCARD const_iterator  begin () const noexcept { return _view_base:: begin(); }
        UTI_NODISCARD const_iterator cbegin () const noexcept { return _view_base::cbegin(); }

        UTI_NODISCARD       iterator  end ()       noexcept { return _view_base:: end(); }
        UTI_NODISCARD const_iterator  end () const noexcept { return _view_base:: end(); }
        UTI_NODISCARD const_iterator cend () const noexcept { return _view_base::cend(); }
private:
        template< typename... Args >
        void _emplace ( Args&&... _args_ ) noexcept( is_nothrow_constructible_v< value_type, Args... > ) ;

        void _copy_buffer ( _buff_base & _buff_ ) noexcept ( is_nothrow_copy_assignable_v< value_type > && is_nothrow_destructible_v< value_type > ) ;
        void _swap_buffer ( _buff_base & _buff_ ) noexcept ;
};

template< typename T >
vector ( vector< T >::ssize_type const _count_, T const & _val_ ) -> vector< T > ;


template< typename T >
void
vector< T >::_copy_buffer ( _buff_base & _buff_ ) noexcept( is_nothrow_copy_assignable_v< value_type > && is_nothrow_destructible_v< value_type > )
{
        if constexpr( is_trivially_relocatable_v< value_type > )
        {
                ::uti::copy( _view_base::begin(), _view_base::end(), _buff_.begin() );
        }
        else
        {
                for( ssize_type i = 0; i < _view_base::size(); ++i )
                {
                        allocator_type::construct( _buff_.begin() + i, _view_base::at( i ) );
                        allocator_type::destroy( _view_base::begin() + i );
                }
        }
}

template< typename T >
void
vector< T >::_swap_buffer ( _buff_base & _buff_ ) noexcept
{
        ::uti::swap( _buff_base::  _begin(), _buff_.  _begin() );
        ::uti::swap( _buff_base::capacity(), _buff_.capacity() );
}

template< typename T >
vector< T >::vector ( ssize_type const _capacity_ )
        : _buff_base( _capacity_ ), _view_base( _buff_base::begin(), _buff_base::begin() ) {}

template< typename T >
vector< T >::vector ( ssize_type const _count_, value_type const & _val_ )
        : _buff_base( _count_ ), _view_base( _buff_base::begin(), _buff_base::begin() )
{
        if( _view_base::begin() != nullptr )
        {
                for( ssize_type i = 0; i < _count_; ++i )
                {
                        _emplace( _val_ );
                }
        }
}

template< typename T >
vector< T >::vector ( vector const & _other_ )
        : _buff_base( _other_.size() ), _view_base( _buff_base::begin(), _buff_base::begin() )
{
        if( _view_base::begin() != nullptr )
        {
                if constexpr( is_trivially_copy_assignable_v< value_type > )
                {
                        ::uti::copy( _other_.begin(), _other_.end(), _view_base::begin() );
                }
                else
                {
                        reserve( _other_.size() );

                        for( auto const & val : _other_ )
                        {
                                _emplace( val );
                        }
                }
                _view_base::_end() = _view_base::begin() + _other_.size();
        }
}

template< typename T >
vector< T >::vector ( vector && _other_ ) noexcept
        : _buff_base( UTI_MOVE( _other_ ) ), _view_base( UTI_MOVE( _other_ ) ) {}

template< typename T >
vector< T > &
vector< T >::operator= ( vector const & _other_ )
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
        _view_base::_end() = _view_base::begin() + _other_.size();

        return *this;
}

template< typename T >
vector< T > &
vector< T >::operator= ( vector && _other_ ) noexcept
{
        clear();
        _buff_base::deallocate();

        this->buffer_   = _other_.buffer_   ;
        this->begin_    = _other_.begin_    ;
        this->end_      = _other_.end_      ;
        this->capacity_ = _other_.capacity_ ;

        _other_.buffer_ = _other_.begin_ = _other_.end_ = nullptr;
        _other_.capacity_ = 0 ;

        return *this;
}

template< typename T >
vector< T >::~vector () noexcept
{
        clear();
}

template< typename T >
void
vector< T >::push_back ( value_type const & _val_ )
{
        reserve();
        _emplace( _val_ );
}

template< typename T >
void
vector< T >::push_back ( value_type && _val_ )
{
        reserve();
        _emplace( UTI_MOVE( _val_ ) );
}

template< typename T >
template< typename... Args >
void
vector< T >::emplace_back ( Args&&... _args_ )
{
        reserve();
        _emplace( UTI_FWD( _args_ )... );
}

template< typename T >
template< typename... Args >
void
vector< T >::_emplace ( Args&&... _args_ ) noexcept( is_nothrow_constructible_v< value_type, Args... > )
{
        allocator_type::construct( _view_base::_end()++, UTI_FWD( _args_ )... );
}

template< typename T >
void
vector< T >::pop_back () noexcept
{
        UTI_ASSERT( !_view_base::empty(), "uti::vector::pop_back: called on empty vector" );

        if constexpr( !is_trivially_destructible_v< value_type > )
        {
                allocator_type::destroy( _view_base::end() - 1 );
        }
        _view_base::pop_back();
}

template< typename T >
void
vector< T >::pop_front () noexcept
{
        UTI_ASSERT( !_view_base::empty(), "uti::vector::pop_front: called on empty vector" );

        if constexpr( !is_trivially_destructible_v< value_type > )
        {
                allocator_type::destroy( _view_base::begin() );
        }
        _view_base::pop_front();
}

template< typename T >
vector< T >::value_type
vector< T >::pop_back_val () noexcept
{
        value_type val( _view_base::cback() );
        pop_back();
        return val;
}

template< typename T >
vector< T >::value_type
vector< T >::pop_front_val () noexcept
{
        value_type val( _view_base::cfront() );
        pop_front();
        return val;
}

template< typename T >
vector< T >::ssize_type
vector< T >::reserve ()
{
        if( _view_base::size() >= _buff_base::capacity() )
        {
                return reserve( _buff_base::capacity() == 0 ? 1 : _buff_base::capacity() * 2 );
        }
        return _buff_base::capacity();
}

template< typename T >
vector< T >::ssize_type
vector< T >::reserve ( ssize_type const _capacity_ )
{
        if( _capacity_ <= _buff_base::capacity() ) return _buff_base::capacity();

        if( _buff_base::capacity() == 0 )
        {
                _buff_base::reserve( _capacity_ );
                _view_base::_begin() = _view_base::_end() = _buff_base::begin();

                return _buff_base::capacity();
        }
        if constexpr( is_trivially_relocatable_v< value_type > )
        {
                ssize_type begin_pos = _view_base::begin() - _buff_base::begin();
                ssize_type   end_pos = _view_base::  end() - _buff_base::begin();

                _buff_base::reserve( _capacity_ );

                _view_base::_begin() = _buff_base::begin() + begin_pos ;
                _view_base::  _end() = _buff_base::begin() +   end_pos ;
        }
        else
        {
                if( !_buff_base::try_realloc_inplace( _capacity_ ) )
                {
                        ssize_type size = _view_base::size();
                        _buff_base buff( _capacity_ );

                        _copy_buffer( buff );
                        _swap_buffer( buff );

                        _view_base::_begin() = _buff_base::begin();
                        _view_base::  _end() = _buff_base::begin() + size;
                }
        }
        return _buff_base::capacity();
}

template< typename T >
vector< T >::ssize_type
vector< T >::shrink ( ssize_type const _capacity_ )
{
        shrink_size( _capacity_ );
        shrink_to_fit();

        return _buff_base::capacity();
}

template< typename T >
void
vector< T >::shrink_to_fit ()
{
        if( _view_base::size() == _buff_base::capacity() ) return;

        _buff_base buff( _view_base::size() );

        _copy_buffer( buff );
        _swap_buffer( buff );

        _view_base::_begin() = _buff_base::begin();
        _view_base::  _end() = _buff_base::begin() + _buff_base::capacity();
}

template< typename T >
void
vector< T >::shrink_size ( ssize_type const _size_ ) noexcept
{
        if( _size_ >= _view_base::size() ) return;

        if constexpr( !is_trivially_destructible_v< value_type > )
        {
                for( ssize_type i = _size_; i < _view_base::size(); ++i )
                {
                        allocator_type::destroy( _view_base::begin() + i );
                }
        }
        _view_base::_end() = _view_base::begin() + _size_;
}

template< typename T >
void
vector< T >::insert ( value_type const & _val_, ssize_type const _position_ )
{
        UTI_ASSERT( 0 <= _position_ && _position_ <= _view_base::size(), "uti::vector::insert: index out of range" );

        if( _position_ == _view_base::size() )
        {
                push_back( _val_ );
                return;
        }
        reserve();

        allocator_type::construct( _view_base::end(), UTI_MOVE( _view_base::back() ) );
        for( ssize_type i = _view_base::size() - 1; i > _position_; --i )
        {
                _view_base::at( i ) = UTI_MOVE( _view_base::at( i - 1 ) );
        }
        _view_base::at( _position_ ) = _val_;
        ++_view_base::_end();
}

template< typename T >
void
vector< T >::insert ( value_type && _val_, ssize_type const _position_ )
{
        UTI_ASSERT( 0 <= _position_ && _position_ <= _view_base::size(), "uti::vector::insert: index out of range" );

        if( _position_ == _view_base::size() )
        {
                push_back( _val_ );
                return;
        }
        reserve();

        allocator_type::construct( _view_base::end(), UTI_MOVE( _view_base::back() ) );
        for( ssize_type i = _view_base::size() - 1; i > _position_; --i )
        {
                _view_base::at( i ) = UTI_MOVE( _view_base::at( i - 1 ) );
        }
        _view_base::at( _position_ ) = UTI_MOVE( _val_ );
        ++_view_base::_end();
}

template< typename T >
void
vector< T >::erase ( ssize_type const _position_ ) noexcept( is_nothrow_move_assignable_v< value_type > )
{
        UTI_ASSERT( 0 <= _position_ && _position_ < _view_base::size(), "uti::vector::erase: index out of range" );

        _view_base::at( _position_ ) = UTI_MOVE( _view_base::back() );

        pop_back();
}

template< typename T >
void
vector< T >::erase_stable ( ssize_type const _position_ ) noexcept( is_nothrow_move_assignable_v< value_type > )
{
        UTI_ASSERT( 0 <= _position_ && _position_ < _view_base::size(), "uti::vector::erase_stable: index out of range" );

        for( ssize_type i = _position_; i < _view_base::size() - 1; ++i )
        {
                _view_base::at( i ) = UTI_MOVE( _view_base::at( i + 1 ) );
        }
        pop_back();
}

template< typename T >
void
vector< T >::clear () noexcept
{
        if constexpr( !is_trivially_destructible_v< value_type > )
        {
                for( ssize_type i = 0; i < _view_base::size(); ++i )
                {
                        allocator_type::destroy( _view_base::begin() + i );
                }
        }
        _view_base::_begin() = _view_base::_end() = _buff_base::begin();
}


} // namespace uti
