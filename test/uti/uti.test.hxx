//
//
//      uti.test
//      uti.test.hxx
//

#pragma once

#include <uti/type/traits.hxx>
#include <uti/meta/list.hxx>
#include <uti/meta/join.hxx>
#include <uti/string/string.hxx>
#include <uti/container/vector.hxx>

#include <string>
#include <vector>

#define CUSTOM_CAP 32


using join = uti::meta::join< uti::meta::type_list > ;

using trivial_types = uti::meta::type_list< int, char, double > ;
using complex_types = uti::meta::type_list< uti::string, std::string > ;
using contain_types = uti::meta::type_list< uti::vector< std::string >, std::vector< uti::string > > ;

using comparable_types = join::fn< trivial_types, complex_types                > ;
using all_test_types   = join::fn< trivial_types, complex_types, contain_types > ;

