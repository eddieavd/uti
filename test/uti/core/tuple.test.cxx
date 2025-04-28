//
//
//      uti.core.test
//      tuple.test.cxx
//

#include <snitch/snitch.hpp>

#include <uti.core.hxx>

#include <tuple>

#include <uti/core/util/copy_counter.hxx>
//#include "deps/boq.hxx"

#define UTI_TUP_ID 1
#define STD_TUP_ID 2


//using namespace bits_of_q ;
using namespace uti::test ;


TEST_CASE( "tuple::ctor", "[tuple][ctor]" )
{
        auto c1 = make_copy_counter< UTI_TUP_ID >() ;
        auto c2 = make_copy_counter< STD_TUP_ID >() ;

        uti::tuple t1{ 9, c1, 1.4 } ;
        std::tuple t2{ 9, c2, 1.4 } ;

        CHECK( c1 == c2 ) ;
}

TEST_CASE( "tuple::make_tuple", "[tuple][make_tuple]" )
{
        auto c1 = make_copy_counter< UTI_TUP_ID >() ;
        auto c2 = make_copy_counter< STD_TUP_ID >() ;

        [[ maybe_unused ]] auto && dummy1 = uti::make_tuple( 8, c1, 1.1 ) ;
        [[ maybe_unused ]] auto && dummy2 = uti::make_tuple( 8, c2, 1.1 ) ;

        CHECK( c1 == c2 ) ;
}

/*
TEST_CASE( "tuple::get", "[tuple][get]" )
{
        testing::TesterWithBuilder< 1 >::test( "tuple::get", []( auto && builder )
        {
                auto c1 = make_copy_counter< UTI_TUP_ID >() ;
                auto c2 = make_copy_counter< STD_TUP_ID >() ;

                auto && tuple1 = builder.build( uti::tuple{ 42, c1, true } ) ;
                auto && tuple2 = builder.build( std::tuple{ 42, c2, true } ) ;

                auto v1 = uti::get< 1 >( UTI_FWD( tuple1 ) ) ;
                auto v2 = uti::get< 1 >( UTI_FWD( tuple2 ) ) ;
                auto v3 = uti::get< 0 >( UTI_FWD( tuple1 ) ) ;
                auto v4 = uti::get< 0 >( UTI_FWD( tuple2 ) ) ;

                CHECK( v1 == v2 ) ;
                CHECK( v3 == v4 ) ;
        } ) ;
}

TEST_CASE( "tuple::tuple_cat", "[tuple][tuple_cat]" )
{
        testing::TesterWithBuilder< 2 >::test( "tuple::tuple_cat", []( auto && builder )
        {
                auto c1 = make_copy_counter< UTI_TUP_ID >() ;
                auto c2 = make_copy_counter< STD_TUP_ID >() ;

                auto &&[ uti_tuple1, uti_tuple2 ] = builder.build( uti::tuple{ 42, c1, true }, uti::tuple{ false, c1, 1.2 } ) ;
                auto &&[ std_tuple1, std_tuple2 ] = builder.build( std::tuple{ 42, c2, true }, std::tuple{ false, c2, 1.2 } ) ;

                auto uti_t1_2 = uti::tuple_cat( UTI_FWD( uti_tuple1 ), UTI_FWD( uti_tuple2 ) ) ;
                auto std_t1_2 = std::tuple_cat( UTI_FWD( std_tuple1 ), UTI_FWD( std_tuple2 ) ) ;

                static_for< 0, uti::tuple_size_v< decltype( uti_t1_2 ) > >(
                        [ & ]( auto i ){ CHECK( uti::get< i.value >( uti_t1_2 ), uti::get< i.value >( std_t1_2 ) ) ; }
                ) ;
        } ) ;

        testing::TesterWithBuilder< 2 >::test( "tuple::tuple_cat_multi", []( auto && builder )
        {
                auto c1 = make_copy_counter< UTI_TUP_ID >() ;
                auto c2 = make_copy_counter< STD_TUP_ID >() ;

                auto &&[ uti_tuple1, uti_tuple3 ] = builder.build( uti::tuple{ 42, c1, true }, uti::tuple{ 7, 'c' } ) ;
                uti::tuple uti_tuple2{ false, c1, 1.2 } ;

                auto &&[ std_tuple1, std_tuple3 ] = builder.build( std::tuple{ 42, c2, true }, std::tuple{ 7, 'c' } ) ;
                std::tuple std_tuple2{ false, c2, 1.2 } ;

                auto uti_t1_2_3 = uti::tuple_cat( UTI_FWD( uti_tuple1 ), UTI_MOVE( uti_tuple2 ), UTI_FWD( uti_tuple3 ) ) ;
                auto std_t1_2_3 = std::tuple_cat( UTI_FWD( std_tuple1 ), UTI_MOVE( std_tuple2 ), UTI_FWD( std_tuple3 ) ) ;

                static_for< 0, uti::tuple_size_v< decltype( uti_t1_2_3 ) > >(
                        [ & ]( auto i ){ CHECK( uti::get< i.value >( uti_t1_2_3 ), uti::get< i.value >( std_t1_2_3 ) ) ; }
                ) ;
        } ) ;
}
*/
