//
//
//      uti
//      allocator/static_bump.hpp
//

#pragma once

#include <allocator/meta.hpp>
#include <iterator/meta.hpp>
#include <iterator/base.hpp>

#include <iostream>

#ifndef UTI_STATIC_MEM_SIZE
#define UTI_STATIC_MEM_SIZE 8 * 1024 * 1024
#endif


namespace uti
{


template< typename T, ssize_t MemSize >
class static_bump_allocator
{
        static constexpr ssize_t memsize { MemSize } ;
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

        using        iterator = uti::iterator_base< value_type      , random_access_iterator_tag > ;
        using  const_iterator = uti::iterator_base< value_type const, random_access_iterator_tag > ;

        UTI_NODISCARD constexpr block_type allocate ( ssize_type const _capacity_ ) noexcept
        {
                block_type block {} ;

                if( _mem_available() >= _capacity_ )
                {
                        block. begin_ = end_ ;
                        block.size_ = _capacity_ ;
                        end_ += _capacity_ ;
                }
                return block ;
        }
        constexpr void reallocate ( block_type & _block_, ssize_type const _new_capacity_ ) noexcept
        {
                if( _can_realloc_inplace( _block_, _new_capacity_ ) )
                {
                        _realloc_inplace( _block_, _new_capacity_ ) ;
                        std::cout << "success\n" ;
                }
                else
                {
                        block_type new_block = allocate( _new_capacity_ ) ;
                        ::uti::copy( _block_.begin_, _block_.begin_ + _block_.size_, new_block.begin_ ) ;
                        _block_ = new_block ;
                        std::cout << "fail\n" ;
                }
        }
        UTI_NODISCARD constexpr bool realloc_inplace ( block_type & _block_, ssize_type const _new_capacity_ ) noexcept
        {
                if( _can_realloc_inplace( _block_, _new_capacity_ ) )
                {
                        _realloc_inplace( _block_, _new_capacity_ ) ;
                        return true ;
                }
                return false ;
        }
        constexpr void deallocate ( block_type & _block_ ) noexcept
        {
                if( _is_last_block( _block_ ) )
                {
                        end_ = _block_.begin() ;
                }
                _block_.begin_  = nullptr ;
                _block_.size_ =       0 ;
        }

        UTI_NODISCARD constexpr       iterator  begin ()       noexcept { return mem_    ; }
        UTI_NODISCARD constexpr const_iterator  begin () const noexcept { return mem_    ; }
        UTI_NODISCARD constexpr const_iterator cbegin () const noexcept { return begin() ; }

        UTI_NODISCARD constexpr       iterator  end ()       noexcept { return end_  ; }
        UTI_NODISCARD constexpr const_iterator  end () const noexcept { return end_  ; }
        UTI_NODISCARD constexpr const_iterator cend () const noexcept { return end() ; }
private:
        inline static value_type mem_ [ memsize ] ;
        inline static iterator   end_ { mem_    } ;

        constexpr ssize_type _mem_available () noexcept { return memsize - ::uti::distance( cbegin(), cend() ) ; }

        constexpr bool _is_last_block ( block_type const & _block_ ) noexcept { return _block_.cbegin() + _block_.size_ == cend() ; }

        constexpr bool _can_realloc_inplace ( block_type const & _block_, ssize_type const _new_capacity_ ) noexcept
        {
                return _is_last_block( _block_ ) && _mem_available() >= ( _new_capacity_ - _block_.size_ ) ;
        }

        constexpr void _realloc_inplace ( block_type & _block_, ssize_type const _new_capacity_ ) noexcept
        {
                end_ += _new_capacity_ - _block_.size_ ;
                _block_.size_ = _new_capacity_ ;
        }
} ;


} // namespace uti
