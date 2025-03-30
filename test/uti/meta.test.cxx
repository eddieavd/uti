//
//
//      uti.test
//      meta.test.cxx
//

#include <snitch/snitch.hpp>

#include "uti.test.hxx"


using namespace uti::test ;
using namespace uti::meta ;

TEMPLATE_LIST_TEST_CASE( "meta::concepts", "[meta][concepts]", uti_test_types )
{
        CONSTEVAL_CHECK(  uti::meta::same_as< TestType      , TestType       > ) ;
        CONSTEVAL_CHECK( !uti::meta::same_as< TestType      , TestType const > ) ;
        CONSTEVAL_CHECK( !uti::meta::same_as< TestType const, TestType       > ) ;
        CONSTEVAL_CHECK(  uti::meta::same_as< TestType const, TestType const > ) ;

        CONSTEVAL_CHECK(  one_of< int, float,   int, char > ) ;
        CONSTEVAL_CHECK( !one_of< int, float, short, char > ) ;

        constexpr auto l1 = []( int        , uti::string ) {} ;
        constexpr auto l2 = []( uti::string, int         ) {} ;

        CONSTEVAL_CHECK(  invocable< decltype( l1 ), int        , uti::string > ) ;
        CONSTEVAL_CHECK(  invocable< decltype( l2 ), uti::string, int         > ) ;
        CONSTEVAL_CHECK( !invocable< decltype( l2 ), int        , uti::string > ) ;
        CONSTEVAL_CHECK( !invocable< decltype( l1 ), uti::string, int         > ) ;

        CONSTEVAL_CHECK( container< uti::string > ) ;

        CONSTEVAL_CHECK( container< uti::vector      < TestType > > ) ;
        CONSTEVAL_CHECK( container< uti::prefix_array< TestType > > ) ;
        CONSTEVAL_CHECK( container< uti::segment_tree< TestType > > ) ;

        CONSTEVAL_CHECK( two_d_container< uti::vector      < uti::vector      < TestType > > > ) ;
        CONSTEVAL_CHECK( two_d_container< uti::prefix_array< uti::prefix_array< TestType > > > ) ;
        CONSTEVAL_CHECK( two_d_container< uti::segment_tree< uti::segment_tree< TestType > > > ) ;

        CONSTEVAL_CHECK( two_d_container< uti::vector      < uti::prefix_array< TestType > > > ) ;
        CONSTEVAL_CHECK( two_d_container< uti::prefix_array< uti::segment_tree< TestType > > > ) ;
        CONSTEVAL_CHECK( two_d_container< uti::segment_tree< uti::vector      < TestType > > > ) ;

        CONSTEVAL_CHECK( two_d_container< uti::vector      < uti::segment_tree< TestType > > > ) ;
        CONSTEVAL_CHECK( two_d_container< uti::prefix_array< uti::vector      < TestType > > > ) ;
        CONSTEVAL_CHECK( two_d_container< uti::segment_tree< uti::prefix_array< TestType > > > ) ;

        if constexpr( list::contains_type_v< TestType, trivial_types > )
        {
                CONSTEVAL_CHECK( !range_container< uti::vector      < TestType > > ) ;
                CONSTEVAL_CHECK(  range_container< uti::prefix_array< TestType > > ) ;
                CONSTEVAL_CHECK(  range_container< uti::segment_tree< TestType > > ) ;

                CONSTEVAL_CHECK( two_d_range_container< uti::prefix_array< uti::prefix_array< TestType > > > ) ;
                CONSTEVAL_CHECK( two_d_range_container< uti::prefix_array< uti::segment_tree< TestType > > > ) ;
                CONSTEVAL_CHECK( two_d_range_container< uti::segment_tree< uti::prefix_array< TestType > > > ) ;
                CONSTEVAL_CHECK( two_d_range_container< uti::segment_tree< uti::segment_tree< TestType > > > ) ;
        }
}

TEST_CASE( "meta::list", "[meta][list]" )
{
        CONSTEVAL_CHECK( uti::is_v    < list::empty< type_list<     > > > ) ;
        CONSTEVAL_CHECK( uti::is_not_v< list::empty< type_list< int > > > ) ;

        CONSTEVAL_CHECK( uti::is_same_v< list::front_t< type_list< int, float > >, int > ) ;

        CONSTEVAL_CHECK( uti::is_same_v< list::pop_front_t< type_list< int, float, double > > ,
                                                            type_list<      float, double > > ) ;

        CONSTEVAL_CHECK( uti::is_same_v< list::back_t< type_list< int, float > >, float > ) ;

        CONSTEVAL_CHECK( uti::is_same_v< list::pop_back_t< type_list< int, float, double > > ,
                                                           type_list< int, float         > > ) ;

        CONSTEVAL_CHECK( uti::is_same_v< list::push_back_t< type_list< int, float >, double > ,
                                                            type_list< int, float, double > > ) ;

        CONSTEVAL_CHECK( uti::is_same_v< list::at_t< 0, type_list< int, float, double > >,    int > ) ;
        CONSTEVAL_CHECK( uti::is_same_v< list::at_t< 1, type_list< int, float, double > >,  float > ) ;
        CONSTEVAL_CHECK( uti::is_same_v< list::at_t< 2, type_list< int, float, double > >, double > ) ;

        CONSTEVAL_CHECK(  list::any_match_v< uti::is_integral, type_list< int, double > > ) ;
        CONSTEVAL_CHECK( !list::any_match_v< uti::is_empty   , type_list< int, double > > ) ;

        CONSTEVAL_CHECK( list::contains_type_v< int, type_list<    int,  float, double > > ) ;
        CONSTEVAL_CHECK( list::contains_type_v< int, type_list< double,    int,  float > > ) ;
        CONSTEVAL_CHECK( list::contains_type_v< int, type_list<  float, double,    int > > ) ;

        CONSTEVAL_CHECK( !list::contains_type_v< int, type_list<               > > ) ;
        CONSTEVAL_CHECK( !list::contains_type_v< int, type_list< float, double > > ) ;
}

TEST_CASE( "meta::join", "[meta][join]" )
{
        using list_1 = type_list<   int, char, double > ;
        using list_2 = type_list< short, long,  float > ;

        using join_list = uti::meta::join< type_list, listify > ;
        using join_tup  = uti::meta::join< type_list, tuplify > ;

        CONSTEVAL_CHECK( uti::is_same_v< type_list< int, char, double, short, long, float >,
                                         join_list::template fn< list_1, list_2 > > ) ;

        CONSTEVAL_CHECK( uti::is_same_v< uti::tuple< int, char, double, short, long, float >,
                                         join_tup::template fn< list_1, list_2 > > ) ;
}

TEST_CASE( "meta::algo", "[meta][algo]" )
{
        CONSTEVAL_CHECK( uti::is_same_v< type_list< void, void, void >,
                                         transform_t< to_void, listify, int, bool, float > > ) ;

        using lazy_is_float = to_lazy_predicate< uti::is_floating_point > ;

        CONSTEVAL_CHECK( uti::is_same_v< type_list< int, char >,
                                         unpack_t< remove_if< lazy_is_float >, type_list< int, float, char > > >
        ) ;
}

TEST_CASE( "meta::random", "[meta][random]" )
{

}
