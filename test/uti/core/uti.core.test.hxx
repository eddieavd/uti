//
//
//      uti.core.test
//      uti.core.test.hxx
//

#pragma once

#include <uti.core.hxx>

#include <string>
#include <vector>

#define CUSTOM_CAP 32


namespace uti::test
{


using join = uti::meta::join< uti::meta::type_list > ;

using trivial_types = uti::meta::type_list< int, char, double > ;
using complex_types = uti::meta::type_list< uti::string, std::string > ;
using contain_types = uti::meta::type_list< uti::vector< std::string >, std::vector< uti::string > > ;

using comparable_types = join::fn< trivial_types, complex_types                > ;
using uti_test_types   = join::fn< trivial_types, complex_types, contain_types > ;


} // namespace uti::test
