//
//
//      uti
//      vector.hpp
//

#pragma once

#include <meta/traits.hpp>
#include <algo/copy.hpp>
#include <container/vectorlike.hpp>


namespace uti
{


template< typename T >
class vector : public _vectorlike_buffer< T >, public _vectorlike_view< T >
{
        using      _self =  vector                 ;
        using _buff_base = _vectorlike_buffer< T > ;
        using _view_base = _vectorlike_view  < T > ;
public:
        using      value_type = typename _view_base::     value_type ;
        using       size_type = typename _view_base::      size_type ;
        using      ssize_type = typename _view_base::     ssize_type ;
        using difference_type = typename _view_base::difference_type ;

        using  allocator_type = allocator< value_type > ;

        using         pointer = typename _view_base::        pointer ;
        using   const_pointer = typename _view_base::  const_pointer ;
        using       reference = typename _view_base::      reference ;
        using const_reference = typename _view_base::const_reference ;

        using        iterator = typename _view_base::       iterator ;
        using  const_iterator = typename _view_base:: const_iterator ;

        constexpr vector (                             ) noexcept = default ;
        explicit  vector ( ssize_type const _capacity_ )                    ;

        vector ( ssize_type const _count_, value_type const & _val_ ) ;

        vector             ( vector const &  _other_ )                    ;
        vector             ( vector       && _other_ ) noexcept = default ;
        vector & operator= ( vector const &  _other_ )                    ;
        vector & operator= ( vector       && _other_ ) noexcept = default ;

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

        void shrink_size ( ssize_type const _size_ ) noexcept ;

        void insert ( value_type const &  _val_, ssize_type const _position_ ) ;
        void insert ( value_type       && _val_, ssize_type const _position_ ) ;

        void erase        ( ssize_type const _position_ ) noexcept( is_nothrow_move_assignable_v< value_type > ) ;
        void erase_stable ( ssize_type const _position_ ) noexcept( is_nothrow_move_assignable_v< value_type > ) ;

        void clear () noexcept ;
private:
        template< typename... Args >
        void _emplace ( Args&&... _args_ ) noexcept( is_nothrow_constructible_v< value_type, Args... > ) ;
};

template< typename T >
vector ( vector< T >::ssize_type const _count_, T const & _val_ ) -> vector< T > ;


template< typename T >
vector< T >::vector ( ssize_type const _capacity_ )
        : _buff_base( _capacity_ ), _view_base( this->buffer_, this->buffer_ ) {}

template< typename T >
vector< T >::vector ( ssize_type const _count_, value_type const & _val_ )
        : _buff_base( _count_ ), _view_base( this->buffer_, this->buffer_ )
{
        if( this->begin_ != nullptr )
        {
                for( ssize_type i = 0; i < _count_; ++i )
                {
                        _emplace( _val_ );
                }
        }
}

template< typename T >
vector< T >::vector ( vector const & _other_ )
        : _buff_base( _other_.size() ), _view_base( this->buffer_, this->buffer_ )
{
        if( this->begin_ != nullptr )
        {
                if constexpr( is_trivially_copy_assignable_v< value_type > )
                {
                        ::uti::copy( _other_.begin_, _other_.end_, this->begin_ );
                }
                else
                {
                        for( ssize_type i = 0; i < _other_.size(); ++i )
                        {
                                allocator_type::construct( this->begin_ + i, _other_.begin_[ i ] );
                        }
                }
                this->end_ = this->begin_ + _other_.size();
        }
}

template< typename T >
vector< T > &
vector< T >::operator= ( vector const & _other_ )
{
        if constexpr( is_trivially_copy_assignable_v< value_type > )
        {
                this->reserve( _other_.size() );
                ::uti::copy( _other_.begin_, _other_.end_, this->begin_ );
        }
        else
        {
                if( this->size() >= _other_.size() )
                {
                        for( ssize_type i = 0; i < _other_.size(); ++i )
                        {
                                this->begin_[ i ] = _other_.begin_[ i ];
                        }
                        shrink_size( _other_.size() );
                }
                else
                {
                        if( this->capacity() < _other_.size() ) reserve( _other_.size() );

                        ssize_type pos { 0 } ;
                        for( ; pos < this->size(); ++pos )
                        {
                                this->begin_[ pos ] = _other_.begin_[ pos ];
                        }
                        for( ; pos < _other_.size(); ++pos )
                        {
                                _emplace( _other_.begin_[ pos ] );
                        }
                }
        }
        this->end_ = this->begin_ + _other_.size();

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
        if( this->end_ >= this->_buff_end() )
        {
                reserve();
        }
        _emplace( _val_ );
}

template< typename T >
void
vector< T >::push_back ( value_type && _val_ )
{
        if( this->end_ >= this->_buff_end() )
        {
                reserve();
        }
        _emplace( UTI_MOVE( _val_ ) );
}

template< typename T >
template< typename... Args >
void
vector< T >::emplace_back ( Args&&... _args_ )
{
        if( this->end_ >= this->_buff_end() )
        {
                reserve();
        }
        _emplace( UTI_FWD( _args_ )... );
}

template< typename T >
template< typename... Args >
void
vector< T >::_emplace ( Args&&... _args_ ) noexcept( is_nothrow_constructible_v< value_type, Args... > )
{
        allocator_type::construct( this->end_, UTI_FWD( _args_ )... );
        ++this->end_;
}

template< typename T >
void
vector< T >::pop_back () noexcept
{
        if constexpr( !is_trivially_destructible_v< value_type > )
        {
                allocator_type::destroy( this->end_ );
        }
        _view_base::pop_back();
}

template< typename T >
void
vector< T >::pop_front () noexcept
{
        if constexpr( !is_trivially_destructible_v< value_type > )
        {
                allocator_type::destroy( this->begin_ );
        }
        _view_base::pop_front();
}

template< typename T >
vector< T >::value_type
vector< T >::pop_back_val () noexcept
{
        value_type val( this->back() );
        pop_back();
        return val;
}

template< typename T >
vector< T >::value_type
vector< T >::pop_front_val () noexcept
{
        value_type val( this->front() );
        pop_front();
        return val;
}

template< typename T >
vector< T >::ssize_type
vector< T >::reserve ()
{
        return reserve( this->capacity_ == 0 ? 1 : this->capacity_ * 2 );
}

template< typename T >
vector< T >::ssize_type
vector< T >::reserve ( ssize_type const _capacity_ )
{
        ssize_type begin_pos = this->begin_ - this->buffer_ ;
        ssize_type   end_pos = this->end_   - this->buffer_ ;

        _buff_base::reserve( _capacity_ );

        this->begin_ = this->buffer_ + begin_pos ;
        this->end_   = this->buffer_ +   end_pos ;

        return this->capacity_;
}

template< typename T >
vector< T >::ssize_type
vector< T >::shrink ( ssize_type const _capacity_ )
{
        ( void ) _capacity_;
        return this->capacity_;
}

template< typename T >
void
vector< T >::shrink_size ( ssize_type const _size_ ) noexcept
{
        if( _size_ >= this->size() ) return;

        if constexpr( !is_trivially_destructible_v< value_type > )
        {
                for( ssize_type i = _size_; i < this->size(); ++i )
                {
                        allocator_type::destroy( this->begin_ + i );
                }
        }
        this->end_ = this->begin_ + _size_;
}

template< typename T >
void
vector< T >::insert ( value_type const & _val_, ssize_type const _position_ )
{
        UTI_ASSERT( 0 <= _position_ && _position_ <= this->size(), "uti::vector::insert: index out of range" );

        if( _position_ == this->size() )
        {
                push_back( _val_ );
                return;
        }
        if( this->end_ >= this->_buff_end() ) reserve();

        for( ssize_type i = this->size(); i > _position_; --i )
        {
                this->begin_[ i ] = UTI_MOVE( this->begin_[ i - 1 ] );
        }
        this->begin_[ _position_ ] = _val_;
        ++this->end_;
}

template< typename T >
void
vector< T >::insert ( value_type && _val_, ssize_type const _position_ )
{
        UTI_ASSERT( 0 <= _position_ && _position_ <= this->size(), "uti::vector::insert: index out of range" );

        if( _position_ == this->size() )
        {
                push_back( _val_ );
                return;
        }
        if( this->end_ >= this->_buff_end() ) reserve();

        for( ssize_type i = this->size(); i > _position_; --i )
        {
                this->begin_[ i ] = UTI_MOVE( this->begin_[ i - 1 ] );
        }
        this->begin_[ _position_ ] = UTI_MOVE( _val_ );
        ++this->end_;
}

template< typename T >
void
vector< T >::erase ( ssize_type const _position_ ) noexcept( is_nothrow_move_assignable_v< value_type > )
{
        UTI_ASSERT( 0 <= _position_ && _position_ < this->size(), "uti::vector::erase: index out of range" );

        this->begin_[ _position_ ] = UTI_MOVE( this->begin_[ this->size() - 1 ] );

        pop_back();
}

template< typename T >
void
vector< T >::erase_stable ( ssize_type const _position_ ) noexcept( is_nothrow_move_assignable_v< value_type > )
{
        UTI_ASSERT( 0 <= _position_ && _position_ < this->size(), "uti::vector::erase_stable: index out of range" );

        for( ssize_type i = _position_; i < this->size() - 1; ++i )
        {
                this->begin_[ i ] = this->begin_[ i + 1 ];
        }
        pop_back();
}

template< typename T >
void
vector< T >::clear () noexcept
{
        if constexpr( !is_trivially_destructible_v< value_type > )
        {
                for( ssize_type i = 0; i < this->size(); ++i )
                {
                        allocator_type::destroy( this->begin_ + i );
                }
        }
        this->begin_ = this->end_ = this->buffer_ ;
}


} // namespace uti
