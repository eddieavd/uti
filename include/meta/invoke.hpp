//
//
//      uti
//      invoke.hpp
//

#pragma once

#include <functional>


namespace uti
{


template< typename Fn, typename... Args >
std::invoke_result_t< Fn, Args... > invoke ( Fn && fn, Args&&... args ) noexcept( std::is_nothrow_invocable_v< Fn, Args... > )
{
        std::invoke( UTI_FWD( fn ), UTI_FWD( args )... );
}


} // namespace uti
