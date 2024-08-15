//
//
//      uti
//      container_base.hpp
//

#pragma once

#include <type/traits.hpp>
#include <meta/iterator.hpp>


namespace uti
{


template< typename T >
class _container_base
{
public:
        using      value_type =       T    ;
        using       size_type =  size_t    ;
        using      ssize_type = ssize_t    ;
        using difference_type = ssize_type ;

        using         pointer = value_type       * ;
        using   const_pointer = value_type const * ;
        using       reference = value_type       & ;
        using const_reference = value_type const & ;

        using        iterator =       pointer ;
        using  const_iterator = const_pointer ;
};


} // namespace uti
