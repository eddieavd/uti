//
//
//      uti.test
//      variant_vector.test.cxx
//

#include <snitch/snitch.hpp>

#include "uti.test.hxx"


using resource = uti::malloc_resource ;

TEST_CASE( "variant_vector::ctor_default", "[variant_vector][ctor][ctor_default]" )
{
        uti::variant_vector< resource, int                      > varvec1 ;
        uti::variant_vector< resource, int, double, uti::string > varvec2 ;

        CHECK( varvec1.          size() ==    0 ) ;
        CHECK( varvec1.         empty() == true ) ;
        CHECK( varvec1.capacity_bytes() ==    0 ) ;

        CHECK( varvec2.          size() ==    0 ) ;
        CHECK( varvec2.         empty() == true ) ;
        CHECK( varvec2.capacity_bytes() ==    0 ) ;
}

TEST_CASE( "variant_vector::ctor_reserve", "[variant_vector][ctor][ctor_reserve]" )
{
        uti::variant_vector< resource, int                      > varvec1( uti::type_identity< int >{}, CUSTOM_CAP ) ;
        uti::variant_vector< resource, int, double, uti::string > varvec2( uti::type_identity< int >{}, CUSTOM_CAP ) ;

        CHECK( varvec1.          size() ==                          0 ) ;
        CHECK( varvec1.         empty() ==                       true ) ;
        CHECK( varvec1.capacity_bytes() == static_cast< uti::ssize_t >( CUSTOM_CAP * sizeof( int ) ) ) ;

        CHECK( varvec2.          size() ==                          0 ) ;
        CHECK( varvec2.         empty() ==                       true ) ;
        CHECK( varvec2.capacity_bytes() == static_cast< uti::ssize_t >( CUSTOM_CAP * sizeof( int ) ) ) ;
}

TEST_CASE( "variant_vector::ctor_iter", "[variant_vector][ctor][ctor_iter]" )
{
        {
                int arr[] = { 0, 1, 2, 3 } ;

                int * begin = arr ;
                int *   end = arr + ( sizeof( arr ) / sizeof( int ) ) ;

                uti::variant_vector< resource, int, double, uti::string > varvec( begin, end ) ;

                for( uti::ssize_t i = 0; i < varvec.size(); ++i )
                {
                        CHECK( varvec.get< int >( i ) == arr[ i ] ) ;
                }
        }
        {
                uti::vector< int > vec( 4, 1 ) ;

                uti::variant_vector< resource, int, double, uti::string > varvec( vec.begin(), vec.end() ) ;

                for( uti::ssize_t i = 0; i < varvec.size(); ++i )
                {
                        CHECK( varvec.get< int >( i ) == vec.at( i ) ) ;
                }
        }
}

TEST_CASE( "variant_vector::ctor_copy", "[variant_vector][ctor][ctor_copy]" )
{
        uti::variant_vector< resource, int, double, uti::string > varvec ;

        varvec.push_back( 1 ) ;
        varvec.push_back( 2.0 ) ;
        varvec.push_back( uti::string( "3" ) ) ;

        CHECK( varvec.size() == 3 ) ;

        uti::variant_vector< resource, int, double, uti::string > varvec_c( varvec ) ;

        CHECK( varvec  .size() == 3 ) ;
        CHECK( varvec_c.size() == 3 ) ;

        CHECK( varvec.get<    int >( 0 ) == varvec_c.get<    int >( 0 ) ) ;
        CHECK( varvec.get< double >( 1 ) == varvec_c.get< double >( 1 ) ) ;

        auto str   = varvec  .get< uti::string >( 2 ) ;
        auto str_c = varvec_c.get< uti::string >( 2 ) ;

        CHECK( uti::string_view( str ).equal_to( str_c ) == true ) ;
}

TEST_CASE( "variant_vector::ctor_move", "[variant_vector][ctor][ctor_move]" )
{
        uti::variant_vector< resource, int, double, uti::string > varvec ;

        varvec.push_back( 1 ) ;
        varvec.push_back( 2.0 ) ;
        varvec.push_back( uti::string( "3" ) ) ;

        CHECK( varvec.size() == 3 ) ;

        uti::variant_vector< resource, int, double, uti::string > varvec_m( UTI_MOVE( varvec ) ) ;

        CHECK( varvec  .size() == 0 ) ;
        CHECK( varvec_m.size() == 3 ) ;

        CHECK( varvec_m.get<    int >( 0 ) == 1   ) ;
        CHECK( varvec_m.get< double >( 1 ) == 2.0 ) ;

        auto str_m = varvec_m.get< uti::string >( 2 ) ;

        CHECK( uti::string_view( str_m ).equal_to( "3" ) == true ) ;
}

TEST_CASE( "variant_vector::assign_copy", "[variant_vector][assign_copy]" )
{
        uti::variant_vector< resource, int, double, uti::string > varvec ;

        varvec.push_back( 1 ) ;
        varvec.push_back( 2.0 ) ;
        varvec.push_back( uti::string( "3" ) ) ;

        CHECK( varvec.size() == 3 ) ;

        uti::variant_vector< resource, int, double, uti::string > varvec_c ;

        CHECK( varvec_c.size() == 0 ) ;

        varvec_c = varvec ;

        CHECK( varvec  .size() == 3 ) ;
        CHECK( varvec_c.size() == 3 ) ;

        CHECK( varvec.get<    int >( 0 ) == varvec_c.get<    int >( 0 ) ) ;
        CHECK( varvec.get< double >( 1 ) == varvec_c.get< double >( 1 ) ) ;

        auto str   = varvec  .get< uti::string >( 2 ) ;
        auto str_c = varvec_c.get< uti::string >( 2 ) ;

        CHECK( uti::string_view( str ).equal_to( str_c ) == true ) ;
}

TEST_CASE( "variant_vector::assign_move", "[variant_vector][assign_move]" )
{
        uti::variant_vector< resource, int, double, uti::string > varvec ;

        varvec.push_back( 1 ) ;
        varvec.push_back( 2.0 ) ;
        varvec.push_back( uti::string( "3" ) ) ;

        CHECK( varvec.size() == 3 ) ;

        uti::variant_vector< resource, int, double, uti::string > varvec_m ;

        CHECK( varvec_m.size() == 0 ) ;

        varvec_m = UTI_MOVE( varvec ) ;

        CHECK( varvec  .size() == 0 ) ;
        CHECK( varvec_m.size() == 3 ) ;

        CHECK( varvec_m.get<    int >( 0 ) == 1   ) ;
        CHECK( varvec_m.get< double >( 1 ) == 2.0 ) ;

        auto str_m = varvec_m.get< uti::string >( 2 ) ;

        CHECK( uti::string_view( str_m ).equal_to( "3" ) == true ) ;
}

TEST_CASE( "variant_vector::push_back", "[variant_vector][modify][push_back]" )
{
        uti::variant_vector< resource, int, double, uti::string > varvec ;

        for( uti::ssize_t i = 0; i < 1024; ++i )
        {
                if( i % 3 == 0 )
                {
                        varvec.push_back< int >( i + 1 ) ;
                }
                else if( i % 3 == 1 )
                {
                        varvec.push_back( i + 1.0 ) ;
                }
                else 
                {
                        varvec.push_back( uti::string( "1234567890123456789012345" ) ) ;
                }
        }
        uti::string_view strv( "1234567890123456789012345" ) ;
        for( uti::ssize_t i = 0; i < varvec.size(); ++i )
        {
                if( i % 3 == 0 )
                {
                        CHECK( varvec.get< int >( i ) == i + 1 ) ;
                }
                else if( i % 3 == 1 )
                {
                        CHECK( varvec.get< double >( i ) == i + 1.0 ) ;
                }
                else
                {
                        auto str = varvec.get< uti::string >( i ) ;
                        CHECK( strv.equal_to( str ) == true ) ;
                }
        }
}

TEST_CASE( "variant_vector::emplace_back", "[variant_vector][modify][emplace_back]" )
{
        uti::variant_vector< resource, int, double, uti::string > varvec ;

        for( uti::ssize_t i = 0; i < 1024; ++i )
        {
                if( i % 3 == 0 )
                {
                        varvec.emplace_back< int >( i + 1 ) ;
                }
                else if( i % 3 == 1 )
                {
                        varvec.emplace_back< double >( i + 1.0 ) ;
                }
                else 
                {
                        varvec.emplace_back< uti::string >( "1234567890123456789012345" ) ;
                }
        }
        uti::string_view strv( "1234567890123456789012345" ) ;
        for( uti::ssize_t i = 0; i < varvec.size(); ++i )
        {
                if( i % 3 == 0 )
                {
                        CHECK( varvec.get< int >( i ) == i + 1 ) ;
                }
                else if( i % 3 == 1 )
                {
                        CHECK( varvec.get< double >( i ) == i + 1.0 ) ;
                }
                else
                {
                        auto str = varvec.get< uti::string >( i ) ;
                        CHECK( strv.equal_to( str ) == true ) ;
                }
        }
}

TEST_CASE( "variant_vector::get", "[variant_vector][access][get]" )
{
        uti::variant_vector< resource, int, double, uti::string > varvec ;

        for( uti::ssize_t i = 0; i < 1024; ++i )
        {
                if( i % 3 == 0 )
                {
                        varvec.push_back< int >( i + 1 ) ;
                }
                else if( i % 3 == 1 )
                {
                        varvec.push_back( i + 1.0 ) ;
                }
                else 
                {
                        varvec.push_back( uti::string( "1234567890123456789012345" ) ) ;
                }
        }
        uti::string_view strv( "1234567890123456789012345" ) ;
        for( uti::ssize_t i = 0; i < varvec.size(); ++i )
        {
                if( i % 3 == 0 )
                {
                        CHECK( varvec.get< int >( i ) == i + 1 ) ;
                }
                else if( i % 3 == 1 )
                {
                        CHECK( varvec.get< double >( i ) == i + 1.0 ) ;
                }
                else
                {
                        auto str = varvec.get< uti::string >( i ) ;
                        CHECK( strv.equal_to( str ) == true ) ;
                }
        }
}

TEST_CASE( "variant_vector::clear", "[variant_vector][modify][clear]" )
{
        uti::variant_vector< resource, int, double, uti::string > varvec1 ;
        uti::variant_vector< resource, int, double, uti::string > varvec2 ( uti::type_identity< uti::string >{}, 32 ) ;
        uti::variant_vector< resource, int, double, uti::string > varvec3 ;

        varvec3.push_back( 1   ) ;
        varvec3.push_back( 2.0 ) ;
        varvec3.push_back( uti::string( "3" ) ) ;

        CHECK( varvec1.size() == 0 ) ;
        CHECK( varvec2.size() == 0 ) ;
        CHECK( varvec3.size() == 3 ) ;

        varvec1.clear() ;
        varvec2.clear() ;
        varvec3.clear() ;

        CHECK( varvec1.size() == 0 ) ;
        CHECK( varvec2.size() == 0 ) ;
        CHECK( varvec3.size() == 0 ) ;
}
