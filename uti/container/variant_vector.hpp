//
//
//      uti
//      variant_vector.hpp
//

#pragma once

#include <container/vector.hpp>
#include <meta/list.hpp>
#include <type/sequence.hpp>


namespace uti
{


namespace _detail
{


class offset_storage
{
public:

private:

} ;


template< typename T, typename... Ts >
constexpr size_t max_align_of () noexcept
{
        if constexpr( sizeof...( Ts ) == 0 )
        {
                return alignof( T ) ;
        }
        else
        {
                size_t align_rest = max_align_of< Ts... >() ;

                return alignof( T ) > align_rest ? alignof( T ) : align_rest ;
        }
} ;

template< typename T, typename... Ts >
constexpr size_t min_align_of () noexcept
{
        if constexpr( sizeof...( Ts ) == 0 )
        {
                return alignof( T ) ;
        }
        else
        {
                size_t align_rest = max_align_of< Ts... >() ;

                return alignof( T ) < align_rest ? alignof( T ) : align_rest ;
        }
} ;

template< typename T, typename T1, typename... Ts >
constexpr ssize_t index_of ( ssize_t _start_ = 0 ) noexcept
{
        if constexpr( meta::same_as< T, T1 > )
        {
                return _start_ ;
        }
        else if constexpr( sizeof...( Ts ) == 0 )
        {
                return -1 ;
        }
        else
        {
                return index_of< T, Ts... >( _start_ + 1 ) ;
        }
}

template< typename T >
using iterator_type_for = iterator_base< T, random_access_iterator_tag > ;


template< typename T >
using iterator_type_for = iterator_base< T, random_access_iterator_tag > ;


} // namespace _detail


template< typename Resource, typename... Ts >
class variant_vector
{
        using value_types = meta::type_list< Ts... > ;

        static constexpr ssize_t max_align { _detail::max_align_of< Ts... >() } ;
        static constexpr ssize_t min_align { _detail::min_align_of< Ts... >() } ;
public:
        using           resource_type = Resource ;
        using        _resource_traits = uti::resource_traits< resource_type > ;
        using              block_type = typename _resource_traits::block_type ;
        using internal_allocator_type = uti::allocator< ssize_t, resource_type > ;

        using       size_type =  size_t    ;
        using      ssize_type = ssize_t    ;
        using difference_type = ssize_type ;

        using       byte_pointer = typename block_type::      pointer ;
        using const_byte_pointer = typename block_type::const_pointer ;

        using               byte_iterator = typename block_type::      iterator ;
        using         const_byte_iterator = typename block_type::const_iterator ;
        using       reverse_byte_iterator = ::uti::reverse_iterator<       byte_iterator > ;
        using const_reverse_byte_iterator = ::uti::reverse_iterator< const_byte_iterator > ;

        constexpr variant_vector () noexcept = default ;

        template< typename T >
                requires meta::one_of< T, Ts... >
        constexpr variant_vector ( ssize_type _capacity_ ) ;

        constexpr variant_vector             ( variant_vector const &  ) = delete ;
        constexpr variant_vector             ( variant_vector       && ) = delete ;
        constexpr variant_vector & operator= ( variant_vector const &  ) = delete ;
        constexpr variant_vector & operator= ( variant_vector       && ) = delete ;

        constexpr ~variant_vector () noexcept { clear() ; }

        template< typename T >
                requires meta::one_of< T, Ts... >
        constexpr void push_back ( T const & _val_ ) ;

        template< typename T >
                requires meta::one_of< T, Ts... >
        constexpr void push_back ( T && _val_ ) ;

        template< typename T, typename... Args >
                requires( meta::one_of< T, Ts... > && meta::constructible_from< T, Args... > )
        constexpr void emplace_back ( Args&&... _args_ ) ;

        constexpr void reserve_bytes ( ssize_type _bytes_ ) ;

        template< typename T >
                requires meta::one_of< T, Ts... >
        constexpr void reserve ( ssize_type _count_ ) ;

        template< typename T >
                requires meta::one_of< T, Ts... >
        constexpr void reserve_additional ( ssize_type _count_ ) ;

        constexpr void clear () noexcept ;

        UTI_NODISCARD constexpr ssize_type capacity_bytes () const noexcept { return storage_.size_ ; }
        UTI_NODISCARD constexpr ssize_type     size_bytes () const noexcept { return _find_end( size_ - 1 ) - storage_.begin() ; }

        UTI_NODISCARD constexpr ssize_type  size () const noexcept { return size_      ; }
        UTI_NODISCARD constexpr       bool empty () const noexcept { return size_ == 0 ; }
        UTI_NODISCARD constexpr       bool  null () const noexcept { return !storage_  ; }

        template< typename T > UTI_NODISCARD constexpr T       & get ( ssize_type _idx_ )       noexcept ;
        template< typename T > UTI_NODISCARD constexpr T const & get ( ssize_type _idx_ ) const noexcept ;

        template< typename T > UTI_NODISCARD constexpr _detail::iterator_type_for< T       > get_ptr ( ssize_type _idx_ )       noexcept ;
        template< typename T > UTI_NODISCARD constexpr _detail::iterator_type_for< T const > get_ptr ( ssize_type _idx_ ) const noexcept ;

        template< typename Visitor, typename Self >
        constexpr void visit ( this Self && self, ssize_type _idx_, Visitor&& _visitor_ ) noexcept
        {
                [ & ]< ssize_type... Idxs >( uti::index_sequence< Idxs... > )
                {
                        ( ...,
                        [ & ]
                        {
                                using type = meta::list::at_t< Idxs, value_types > ;
                                if constexpr( meta::invocable< Visitor, type > )
                                {
                                        if( UTI_FWD( self ).types_[ _idx_ ] == Idxs )
                                        {
                                                _visitor_( UTI_FWD( self ).template get< type >( _idx_ ) ) ;
                                        }
                                }
                        }() ) ;
                }( uti::make_index_sequence< sizeof...( Ts ) >{} ) ;
        }

        template< typename T >
                requires meta::one_of< T, Ts... >
        constexpr void replace ( ssize_type _idx_, T const & _val_ ) ;

        template< typename T >
                requires meta::one_of< T, Ts... >
        constexpr void replace ( ssize_type _idx_, T && _val_ ) ;
private:
        ssize_type                                            size_ {          0 } ;
        block_type                                         storage_ { nullptr, 0 } ;
        uti::vector< ssize_type, internal_allocator_type > offsets_ {            } ;
        uti::vector< ssize_type, internal_allocator_type >   types_ {            } ;

        constexpr void _reserve ( ssize_type _bytes_ ) ;

        template< typename T >
                requires meta::one_of< T, Ts... >
        constexpr bool _can_fit ( ssize_type _count_ ) const noexcept ;

        constexpr       byte_iterator _find_end ( ssize_type _idx_ )       noexcept ;
        constexpr const_byte_iterator _find_end ( ssize_type _idx_ ) const noexcept ;

        template< typename T > constexpr       byte_iterator _align_for (       byte_iterator _ptr_ )       noexcept ;
        template< typename T > constexpr const_byte_iterator _align_for ( const_byte_iterator _ptr_ ) const noexcept ;

        template< typename T >
        constexpr ssize_type _padding_for ( const_byte_iterator _ptr_ ) const noexcept ;
} ;


template< typename Resource, typename... Ts >
constexpr void
variant_vector< Resource, Ts... >::_reserve ( ssize_type _bytes_ )
{
        if( !storage_ )
        {
                storage_ = _resource_traits::allocate( _bytes_, max_align ) ;
                return ;
        }
        if( storage_.size_ >= _bytes_ ) return ;

        if constexpr( conjunction_v< is_trivially_relocatable< Ts >... > )
        {
                _resource_traits::reallocate( storage_, _bytes_, max_align ) ;
        }
        else
        {
                if( _resource_traits::realloc_inplace( storage_, _bytes_ ) ) return ;

                block_type new_block = _resource_traits::allocate( _bytes_, max_align ) ;

                if( !new_block ) return ;

                for( ssize_type i = 0; i < size_; ++i )
                {
                        visit( i, [ & ]( auto const & elem )
                            {
                                using type = remove_cvref_t< decltype( elem ) > ;
                                using iter = _detail::iterator_type_for< type > ;

                                if constexpr( !is_trivially_relocatable_v< type > )
                                {
                                        ::uti::construct< iter >( new_block.begin() + offsets_[ i ], UTI_MOVE( elem ) ) ;
                                        ::uti::destroy( &elem ) ;
                                }
                                else
                                {
                                        ::uti::copy( storage_.begin() + offsets_[ i ], _find_end( i ), new_block.begin() + offsets_[ i ] ) ;
//                                      ::uti::copy( &elem, &elem + 1, new_block.begin() + offsets_[ i ] ) ;
                                }
                            }
                        ) ;
                }
                storage_ = new_block ;
        }
}

template< typename Resource, typename... Ts >
template< typename T >
        requires meta::one_of< T, Ts... >
constexpr bool
variant_vector< Resource, Ts... >::_can_fit ( ssize_type _count_ ) const noexcept
{
        const_byte_iterator     end = _find_end( size_ - 1 ) ;
        const_byte_iterator aligned = _align_for< T >( end ) ;

        size_type free_space = storage_.end() - aligned ;

        if( _count_ * sizeof( T ) <= free_space )
        {
                return true ;
        }
        return false ;
}

template< typename Resource, typename... Ts >
constexpr
variant_vector< Resource, Ts... >::byte_iterator
variant_vector< Resource, Ts... >::_find_end ( ssize_type _idx_ ) noexcept
{
        byte_iterator elem_start = storage_.begin() + offsets_[ _idx_ ] ;

        ssize_type elem_size { 0 } ;

        visit( _idx_, [ & ]( auto const & elem ){ elem_size = sizeof( remove_reference_t< decltype( elem ) > ) ; } ) ;

        return elem_start + elem_size ;
}

template< typename Resource, typename... Ts >
constexpr
variant_vector< Resource, Ts... >::const_byte_iterator
variant_vector< Resource, Ts... >::_find_end ( ssize_type _idx_ ) const noexcept
{
        const_byte_iterator elem_start = storage_.begin() + offsets_[ _idx_ ] ;

        ssize_type elem_size { 0 } ;

        visit( _idx_, [ & ]( auto const & elem ){ elem_size = sizeof( remove_reference_t< decltype( elem ) > ) ; } ) ;

        return elem_start + elem_size ;
}

template< typename Resource, typename... Ts >
template< typename T >
constexpr
variant_vector< Resource, Ts... >::byte_iterator
variant_vector< Resource, Ts... >::_align_for ( byte_iterator _ptr_ ) noexcept
{
        ssize_type align = alignof( T ) ;
        ssize_type  mask = align - 1 ;

        while( ( _ptr_ & mask ) != 0 )
        {
                ++_ptr_ ;
        }
        return _ptr_ ;
}

template< typename Resource, typename... Ts >
template< typename T >
constexpr
variant_vector< Resource, Ts... >::const_byte_iterator
variant_vector< Resource, Ts... >::_align_for ( const_byte_iterator _ptr_ ) const noexcept
{
        ssize_type align = alignof( T ) ;
        ssize_type  mask = align - 1 ;

        while( ( _ptr_ & mask ) != 0 )
        {
                ++_ptr_ ;
        }
        return _ptr_ ;
}

template< typename Resource, typename... Ts >
template< typename T >
constexpr
variant_vector< Resource, Ts... >::ssize_type
variant_vector< Resource, Ts... >::_padding_for ( const_byte_iterator _ptr_ ) const noexcept
{
        const_byte_iterator aligned = _align_for< T >( _ptr_ ) ;

        return aligned - _ptr_ ;
}

template< typename Resource, typename... Ts >
template< typename T >
        requires meta::one_of< T, Ts... >
constexpr
variant_vector< Resource, Ts... >::variant_vector ( ssize_type _capacity_ )
{
        _reserve( _capacity_ * sizeof( T ) ) ;
}

template< typename Resource, typename... Ts >
template< typename T >
        requires meta::one_of< T, Ts... >
constexpr void
variant_vector< Resource, Ts... >::push_back ( T const & _val_ )
{
        emplace_back< T >( _val_ ) ;
}

template< typename Resource, typename... Ts >
template< typename T >
        requires meta::one_of< T, Ts... >
constexpr void
variant_vector< Resource, Ts... >::push_back ( T && _val_ )
{
        emplace_back< T >( UTI_MOVE( _val_ ) ) ;
}

template< typename Resource, typename... Ts >
template< typename T, typename... Args >
        requires( meta::one_of< T, Ts... > && meta::constructible_from< T, Args... > )
constexpr void
variant_vector< Resource, Ts... >::emplace_back ( Args&&... _args_ )
{
        using iter_t = _detail::iterator_type_for< T > ;

        iter_t dest { nullptr } ;

        if( null() || empty() )
        {
                _reserve( sizeof( T ) ) ;
                dest = storage_.begin() ;

                offsets_.push_back( 0 ) ;
                types_.push_back( _detail::index_of< T, Ts... >() ) ;
        }
        else
        {
                if( !_can_fit< T >( 1 ) )
                {
                        reserve_bytes( capacity_bytes() * 2 ) ;
                        reserve_additional< T >( 1 ) ;
                }
                if( !_can_fit< T >( 1 ) ) return ;

                dest = _align_for< T >( _find_end( size_ - 1 ) ) ;

                offsets_.push_back( static_cast< const_byte_iterator >( dest ) - storage_.begin() ) ;
                types_.push_back( _detail::index_of< T, Ts... >() ) ;
        }
        if( dest )
        {
                ::uti::construct( dest, UTI_FWD( _args_ )... ) ;
                ++size_ ;
        }
}

template< typename Resource, typename... Ts >
constexpr void
variant_vector< Resource, Ts... >::reserve_bytes ( ssize_type _bytes_ )
{
        _reserve( _bytes_ ) ;
}

template< typename Resource, typename... Ts >
template< typename T >
        requires meta::one_of< T, Ts... >
constexpr void
variant_vector< Resource, Ts... >::reserve ( ssize_type _count_ )
{
        _reserve( _count_ * sizeof( T ) ) ;

        offsets_.reserve( _count_ ) ;
        types_  .reserve( _count_ ) ;
}

template< typename Resource, typename... Ts >
template< typename T >
        requires meta::one_of< T, Ts... >
constexpr void
variant_vector< Resource, Ts... >::reserve_additional ( ssize_type _count_ )
{
        const_byte_iterator end = _find_end( size_ - 1 ) ;
        ssize_type   size_bytes = end - storage_.begin() ;
        ssize_type      padding = _padding_for< T >( end ) ;

        _reserve( size_bytes + padding + sizeof( T ) * _count_ ) ;

        offsets_.reserve( size_ + _count_ ) ;
        types_  .reserve( size_ + _count_ ) ;
}

template< typename Resource, typename... Ts >
constexpr void
variant_vector< Resource, Ts... >::clear () noexcept
{
        if( null() ) return ;

        for( ssize_type i = 0; i < size_; ++i )
        {
                visit( i, []( auto & val )
                        {
                                using type = remove_reference_t< decltype( val ) > ;
                                if constexpr( !is_trivially_destructible_v< type > )
                                {
                                        ::uti::destroy( &val ) ;
                                }
                        }
                ) ;
        }
        size_ = 0 ;
        offsets_.clear() ;
        types_  .clear() ;
        _resource_traits::deallocate( storage_ ) ;
}

template< typename Resource, typename... Ts >
template< typename T >
UTI_NODISCARD constexpr T &
variant_vector< Resource, Ts... >::get ( ssize_type _idx_ ) noexcept
{
        return *get_ptr< T >( _idx_ ) ;
}

template< typename Resource, typename... Ts >
template< typename T >
UTI_NODISCARD constexpr T const &
variant_vector< Resource, Ts... >::get ( ssize_type _idx_ ) const noexcept
{
        return *get_ptr< T >( _idx_ ) ;
}

template< typename Resource, typename... Ts >
template< typename T >
UTI_NODISCARD constexpr
_detail::iterator_type_for< T >
variant_vector< Resource, Ts... >::get_ptr ( ssize_type _idx_ ) noexcept
{
        if( _detail::index_of< T, Ts... >() == types_[ _idx_ ] )
        {
                return storage_.begin() + offsets_[ _idx_ ] ;
        }
        return nullptr ;
}

template< typename Resource, typename... Ts >
template< typename T >
UTI_NODISCARD constexpr
_detail::iterator_type_for< T const >
variant_vector< Resource, Ts... >::get_ptr ( ssize_type _idx_ ) const noexcept
{
        if( _detail::index_of< T, Ts... >() == types_[ _idx_ ] )
        {
                return storage_.begin() + offsets_[ _idx_ ] ;
        }
        return nullptr ;
}


} // namespace uti
