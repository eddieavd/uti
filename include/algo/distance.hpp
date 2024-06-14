//
//
//      uti
//      distance.hpp
//

#pragma once

#include <type/traits.hpp>


namespace uti
{


template< typename Iter >
constexpr ssize_t distance ( Iter begin, Iter end ) noexcept
{
        if constexpr( true )
        {
                return end - begin ;
        }
        else if constexpr( false )
        {

        }
        else
        {

        }
}


} // namespace uti
