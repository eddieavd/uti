//
//
//      uti
//      allocator/default.hpp
//

#pragma once

#include <allocator/meta.hpp>


namespace uti
{


template< typename T >
class allocator
{
public:
        using      value_type =       T    ;
        using       size_type =  size_t    ;
        using      ssize_type = ssize_t    ;
        using difference_type = ssize_type ;

        using      block_type = block_t< value_type > ;

        using         pointer = value_type       * ;
        using   const_pointer = value_type const * ;
        using       reference = value_type       & ;
        using const_reference = value_type const & ;

        UTI_NODISCARD constexpr block_type allocate ( ssize_type const _capacity_ ) const UTI_NOEXCEPT_UNLESS_BADALLOC
        {
                auto ptr = alloc_typed_buffer< value_type >( _capacity_ ) ;

                return ptr != nullptr ? block_type{     ptr, _capacity_ }
                                      : block_type{ nullptr,          0 } ;
        }
        constexpr void reallocate ( block_type & _block_, ssize_type const _new_capacity_ ) const UTI_NOEXCEPT_UNLESS_BADALLOC
        {
                auto ptr = realloc_typed_buffer( _block_.begin_, _new_capacity_ ) ;
                if( ptr )
                {
                        _block_.size_ = _new_capacity_ ;
                }
                if( ptr != _block_.begin_ )
                {
                        _block_.begin_ = ptr ;
                }
        }
        constexpr void deallocate ( block_type & _block_ ) const noexcept
        {
                dealloc_typed_buffer( _block_.begin_ );

                _block_. begin_ = nullptr ;
                _block_.size_ =       0 ;
        }
};


} // namespace uti
