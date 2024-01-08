//
//
//      uti
//      type_traits.hpp
//

#pragma once


namespace uti
{


constexpr bool is_constant_evaluated () noexcept
{
        if consteval
        {
                return true;
        }
        return false;
}


} // namespace uti
