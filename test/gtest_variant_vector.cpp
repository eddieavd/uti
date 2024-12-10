//
//
//      uti
//      gtest_variant_vector.cpp
//

#include "gtest_vector.hpp"

#include <string/string_view.hpp>


using resource = uti::malloc_resource ;

TEST( VariantVectorTest, DefaultConstruct )
{
        uti::variant_vector< resource, int                      > varvec1 ;
        uti::variant_vector< resource, int, double, uti::string > varvec2 ;

        EXPECT_EQ( varvec1.          size(),    0 ) ;
        EXPECT_EQ( varvec1.         empty(), true ) ;
        EXPECT_EQ( varvec1.capacity_bytes(),    0 ) ;

        EXPECT_EQ( varvec2.          size(),    0 ) ;
        EXPECT_EQ( varvec2.         empty(), true ) ;
        EXPECT_EQ( varvec2.capacity_bytes(),    0 ) ;
}

TEST( VariantVectorTest, ReserveConstruct )
{
        uti::variant_vector< resource, int                      > varvec1( uti::type_identity< int >{}, CUSTOM_CAP ) ;
        uti::variant_vector< resource, int, double, uti::string > varvec2( uti::type_identity< int >{}, CUSTOM_CAP ) ;

        EXPECT_EQ( varvec1.          size(),                          0 ) ;
        EXPECT_EQ( varvec1.         empty(),                       true ) ;
        EXPECT_EQ( varvec1.capacity_bytes(), CUSTOM_CAP * sizeof( int ) ) ;

        EXPECT_EQ( varvec2.          size(),                          0 ) ;
        EXPECT_EQ( varvec2.         empty(),                       true ) ;
        EXPECT_EQ( varvec2.capacity_bytes(), CUSTOM_CAP * sizeof( int ) ) ;
}

TEST( VariantVectorTest, IteratorConstruct )
{
        {
                int arr[] = { 0, 1, 2, 3 } ;

                int * begin = arr ;
                int *   end = arr + ( sizeof( arr ) / sizeof( int ) ) ;

                uti::variant_vector< resource, int, double, uti::string > varvec( begin, end ) ;

                for( uti::ssize_t i = 0; i < varvec.size(); ++i )
                {
                        EXPECT_EQ( varvec.get< int >( i ), arr[ i ] ) ;
                }
        }
        {
                uti::vector< int > vec( 4, 1 ) ;

                uti::variant_vector< resource, int, double, uti::string > varvec( vec.begin(), vec.end() ) ;

                for( uti::ssize_t i = 0; i < varvec.size(); ++i )
                {
                        EXPECT_EQ( varvec.get< int >( i ), vec.at( i ) ) ;
                }
        }
}

TEST( VariantVectorTest, CopyConstruct )
{
        uti::variant_vector< resource, int, double, uti::string > varvec ;

        varvec.push_back( 1 ) ;
        varvec.push_back( 2.0 ) ;
        varvec.push_back( uti::string( "3" ) ) ;

        EXPECT_EQ( varvec.size(), 3 ) ;

        uti::variant_vector< resource, int, double, uti::string > varvec_c( varvec ) ;

        EXPECT_EQ( varvec  .size(), 3 ) ;
        EXPECT_EQ( varvec_c.size(), 3 ) ;

        EXPECT_EQ( varvec.get<    int >( 0 ), varvec_c.get<    int >( 0 ) ) ;
        EXPECT_EQ( varvec.get< double >( 1 ), varvec_c.get< double >( 1 ) ) ;

        auto str   = varvec  .get< uti::string >( 2 ) ;
        auto str_c = varvec_c.get< uti::string >( 2 ) ;

        EXPECT_EQ( uti::string_view( str ).equal_to( str_c ), true ) ;
}

TEST( VariantVectorTest, MoveConstruct )
{
        uti::variant_vector< resource, int, double, uti::string > varvec ;

        varvec.push_back( 1 ) ;
        varvec.push_back( 2.0 ) ;
        varvec.push_back( uti::string( "3" ) ) ;

        EXPECT_EQ( varvec.size(), 3 ) ;

        uti::variant_vector< resource, int, double, uti::string > varvec_m( UTI_MOVE( varvec ) ) ;

        EXPECT_EQ( varvec  .size(), 0 ) ;
        EXPECT_EQ( varvec_m.size(), 3 ) ;

        EXPECT_EQ( varvec_m.get<    int >( 0 ), 1   ) ;
        EXPECT_EQ( varvec_m.get< double >( 1 ), 2.0 ) ;

        auto str_m = varvec_m.get< uti::string >( 2 ) ;

        EXPECT_EQ( uti::string_view( str_m ).equal_to( "3" ), true ) ;
}

TEST( VariantVectorTest, CopyAssign )
{
        uti::variant_vector< resource, int, double, uti::string > varvec ;

        varvec.push_back( 1 ) ;
        varvec.push_back( 2.0 ) ;
        varvec.push_back( uti::string( "3" ) ) ;

        EXPECT_EQ( varvec.size(), 3 ) ;

        uti::variant_vector< resource, int, double, uti::string > varvec_c ;

        EXPECT_EQ( varvec_c.size(), 0 ) ;

        varvec_c = varvec ;

        EXPECT_EQ( varvec  .size(), 3 ) ;
        EXPECT_EQ( varvec_c.size(), 3 ) ;

        EXPECT_EQ( varvec.get<    int >( 0 ), varvec_c.get<    int >( 0 ) ) ;
        EXPECT_EQ( varvec.get< double >( 1 ), varvec_c.get< double >( 1 ) ) ;

        auto str   = varvec  .get< uti::string >( 2 ) ;
        auto str_c = varvec_c.get< uti::string >( 2 ) ;

        EXPECT_EQ( uti::string_view( str ).equal_to( str_c ), true ) ;
}

TEST( VariantVectorTest, MoveAssign )
{
        uti::variant_vector< resource, int, double, uti::string > varvec ;

        varvec.push_back( 1 ) ;
        varvec.push_back( 2.0 ) ;
        varvec.push_back( uti::string( "3" ) ) ;

        EXPECT_EQ( varvec.size(), 3 ) ;

        uti::variant_vector< resource, int, double, uti::string > varvec_m ;

        EXPECT_EQ( varvec_m.size(), 0 ) ;

        varvec_m = UTI_MOVE( varvec ) ;

        EXPECT_EQ( varvec  .size(), 0 ) ;
        EXPECT_EQ( varvec_m.size(), 3 ) ;

        EXPECT_EQ( varvec_m.get<    int >( 0 ), 1   ) ;
        EXPECT_EQ( varvec_m.get< double >( 1 ), 2.0 ) ;

        auto str_m = varvec_m.get< uti::string >( 2 ) ;

        EXPECT_EQ( uti::string_view( str_m ).equal_to( "3" ), true ) ;
}

TEST( VariantVectorTest, PushBack )
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
                        EXPECT_EQ( varvec.get< int >( i ), i + 1 ) ;
                }
                else if( i % 3 == 1 )
                {
                        EXPECT_EQ( varvec.get< double >( i ), i + 1.0 ) ;
                }
                else
                {
                        auto str = varvec.get< uti::string >( i ) ;
                        EXPECT_EQ( strv.equal_to( str ), true ) ;
                }
        }
}

TEST( VariantVectorTest, EmplaceBack )
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
                        EXPECT_EQ( varvec.get< int >( i ), i + 1 ) ;
                }
                else if( i % 3 == 1 )
                {
                        EXPECT_EQ( varvec.get< double >( i ), i + 1.0 ) ;
                }
                else
                {
                        auto str = varvec.get< uti::string >( i ) ;
                        EXPECT_EQ( strv.equal_to( str ), true ) ;
                }
        }
}

TEST( VariantVectorTest, Get )
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
                        EXPECT_EQ( varvec.get< int >( i ), i + 1 ) ;
                }
                else if( i % 3 == 1 )
                {
                        EXPECT_EQ( varvec.get< double >( i ), i + 1.0 ) ;
                }
                else
                {
                        auto str = varvec.get< uti::string >( i ) ;
                        EXPECT_EQ( strv.equal_to( str ), true ) ;
                }
        }
}

TEST( VariantVectorTest, Clear )
{
        uti::variant_vector< resource, int, double, uti::string > varvec1 ;
        uti::variant_vector< resource, int, double, uti::string > varvec2 ( uti::type_identity< uti::string >{}, 32 ) ;
        uti::variant_vector< resource, int, double, uti::string > varvec3 ;

        varvec3.push_back( 1   ) ;
        varvec3.push_back( 2.0 ) ;
        varvec3.push_back( uti::string( "3" ) ) ;

        EXPECT_EQ( varvec1.size(), 0 ) ;
        EXPECT_EQ( varvec2.size(), 0 ) ;
        EXPECT_EQ( varvec3.size(), 3 ) ;

        varvec1.clear() ;
        varvec2.clear() ;
        varvec3.clear() ;

        EXPECT_EQ( varvec1.size(), 0 ) ;
        EXPECT_EQ( varvec2.size(), 0 ) ;
        EXPECT_EQ( varvec3.size(), 0 ) ;
}
