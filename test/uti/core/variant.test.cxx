//
//
//      uti.core.test
//      variant.test.cxx
//

#include <snitch/snitch.hpp>

#include <uti/core/util/copy_counter.hxx>
#include <uti/core/string/string_view.hxx>
#include <uti/core/string/string.hxx>
#include <uti/core/container/tagged_union.hxx>
#include <uti/core/container/variant.hxx>


using variant_t = uti::variant< uti::nullvar_t, int, double, uti::test::copy_counter, uti::string > ;
using   union_t = uti::tagged_union< int, double, uti::test::copy_counter, uti::string > ;

template< typename Variant >
constexpr void check_variant_empty ( Variant const & var )
{
        CHECK( !var.has_value() ) ;
        CHECK( !var             ) ;

        CHECK( var.type() == Variant::invalid_type ) ;
        CHECK( var.has_value( uti::variant_type< uti::nullvar_t >{} ) ) ;

        uti::nullvar_t null = var.value( uti::variant_type< uti::nullvar_t >{} ) ;
        ( void ) null ;

        CHECK(  var.optional_value( uti::variant_type< uti::nullvar_t >{} ) ) ;
        CHECK( !var.optional_value( uti::variant_type< int            >{} ) ) ;
}

template< typename Variant, typename T >
constexpr void check_variant_value_impl ( Variant const & var, T const & val )
{
        CHECK( var.has_value() ) ;
        CHECK( bool( var )     ) ;
        
        CHECK( var.type() == typename Variant::type_id( uti::variant_type< T >{} ) ) ;
        CHECK( var.has_value( uti::variant_type< T >{} ) ) ;
        
        CHECK( var.value( uti::variant_type< T >{} ) == val ) ;
        
        using is_int     = uti::is_same< T, int > ;
        using is_double  = uti::is_same< T, double > ;
        using is_counter = uti::is_same< T, uti::test::copy_counter > ;
        
        CHECK(      !var.optional_value( uti::variant_type< uti::nullvar_t          >{} ) ) ;
        CHECK( bool( var.optional_value( uti::variant_type< int                     >{} ) ) == is_int::value ) ;
        CHECK( bool( var.optional_value( uti::variant_type< double                  >{} ) ) == is_double::value ) ;
        CHECK( bool( var.optional_value( uti::variant_type< uti::test::copy_counter >{} ) ) == is_counter::value ) ;
}

template< typename Variant, typename T >
constexpr void check_variant_value ( Variant const & var, T const & val, uti::string_view scope = "" )
{
        if( scope.equal_to( "" ) )
        {
                check_variant_value_impl( var, val ) ;
        }
        else
        {
                SECTION( scope.data() )
                {
                        check_variant_value_impl( var, val ) ;
                }
        }
}

TEST_CASE( "variant::ctor", "[variant][ctor]" )
{
        variant_t empty ;
        variant_t non_empty_1( 5 ) ;
        variant_t non_empty_2( uti::string( 'x', 5 ) ) ;

        SECTION( "ctor::empty" )
        {
                variant_t a ;
                check_variant_empty( a ) ;

                variant_t b( uti::nullvar ) ;
                check_variant_empty( b ) ;
        }
        SECTION( "ctor::value" )
        {
                variant_t a( 5 ) ;
                check_variant_value( a, 5 ) ;

                variant_t b( 3.0 ) ;
                check_variant_value( b, 3.0 ) ;

                variant_t c( uti::test::copy_counter{} ) ;
                check_variant_value( c, uti::test::copy_counter{} ) ;

                variant_t d( uti::string( 'x', 5 ) ) ;
                check_variant_value( d, uti::string( 'x', 5 ) ) ;
        }
        SECTION( "ctor::args" )
        {
                variant_t a( uti::variant_type< int >{}, 5 ) ;
                check_variant_value( a, 5 );

                variant_t b( uti::variant_type< double >{}, 3.0 ) ;
                check_variant_value( b, 3.0 ) ;

                variant_t c( uti::variant_type< uti::string >{}, 'x', 5 ) ;
                check_variant_value( c, uti::string( "xxxxx" ) ) ;
        }
        SECTION( "ctor::union_copy" )
        {
                union_t u ;

                variant_t a( u ) ;
                check_variant_empty( a ) ;

                u.emplace( uti::union_type< int >{}, 5 ) ;

                variant_t b( u ) ;
                check_variant_value( b, 5 ) ;

                u.destroy( uti::union_type< int >{} ) ;
                u.emplace( uti::union_type< uti::string >{}, 'x', 5 ) ;

                variant_t c( u ) ;
                check_variant_value( c, uti::string( 'x', 5 ) ) ;
        }
        SECTION( "ctor::union_move" )
        {
                union_t u ;

                variant_t a( UTI_MOVE( u ) ) ;
                check_variant_empty( a ) ;

                u.emplace( uti::union_type< int >{}, 5 ) ;

                variant_t b( UTI_MOVE( u ) ) ;
                check_variant_value( b, 5 ) ;

                u.destroy( uti::union_type< int >{} ) ;
                u.emplace( uti::union_type< uti::string >{}, 'x', 5 ) ;

                variant_t c( UTI_MOVE( u ) ) ;
                check_variant_value( c, uti::string( 'x', 5 ) ) ;
        }
        SECTION( "ctor::copy" )
        {
                variant_t a( empty ) ;
                check_variant_empty( a ) ;

                variant_t b( non_empty_1 ) ;
                check_variant_value( b, 5 ) ;

                variant_t c( non_empty_2 ) ;
                check_variant_value( c, uti::string( 'x', 5 ) ) ;
        }
        SECTION( "ctor::move" )
        {
                variant_t a( UTI_MOVE( empty ) ) ;
                check_variant_empty( a ) ;

                variant_t b( UTI_MOVE( non_empty_1 ) ) ;
                check_variant_value( b, 5 ) ;

                variant_t c( UTI_MOVE( non_empty_2 ) ) ;
                check_variant_value( c, uti::string( 'x', 5 ) ) ;
        }
}

TEST_CASE( "variant::assign", "[variant][assign]" )
{
        variant_t empty ;
        variant_t non_empty_1( 5 ) ;
        variant_t non_empty_2( uti::string( 'x', 5 ) ) ;

        SECTION( "assign::copy" )
        {
                variant_t a ;
                a = empty ;
                check_variant_empty( a ) ;
                a = non_empty_1 ;
                check_variant_value( a, 5 ) ;
                a = non_empty_2 ;
                check_variant_value( a, uti::string( 'x', 5 ) ) ;

                variant_t b( 5 ) ;
                b = non_empty_1 ;
                check_variant_value( b, 5 ) ;
                b = non_empty_2 ;
                check_variant_value( b, uti::string( 'x', 5 ) ) ;
                b = empty ;
                check_variant_empty( b ) ;

                variant_t c( uti::string( 'a', 32 ) ) ;
                c = non_empty_2 ;
                check_variant_value( c, uti::string( 'x', 5 ) ) ;
                c = non_empty_1 ;
                check_variant_value( c, 5 ) ;
                c = empty ;
                check_variant_empty( c ) ;
        }
        SECTION( "assign::move" )
        {
                variant_t a ;
                a = UTI_MOVE( empty ) ;
                check_variant_empty( a ) ;
                a = UTI_MOVE( non_empty_1 ) ;
                check_variant_value( a, 5 ) ;
                a = UTI_MOVE( non_empty_2 ) ;
                check_variant_value( a, uti::string( 'x', 5 ) ) ;

                non_empty_2.emplace( uti::variant_type< uti::string >{}, 'x', 5 ) ;

                variant_t b( 5 ) ;
                b = UTI_MOVE( non_empty_1 ) ;
                check_variant_value( b, 5 ) ;
                b = UTI_MOVE( non_empty_2 ) ;
                check_variant_value( b, uti::string( 'x', 5 ) ) ;
                b = UTI_MOVE( empty ) ;
                check_variant_empty( b ) ;

                non_empty_2.emplace( uti::variant_type< uti::string >{}, 'x', 5 ) ;

                variant_t c( uti::string( 'a', 32 ) ) ;
                c = UTI_MOVE( non_empty_2 ) ;
                check_variant_value( c, uti::string( 'x', 5 ) ) ;
                c = UTI_MOVE( non_empty_1 ) ;
                check_variant_value( c, 5 ) ;
                c = UTI_MOVE( empty ) ;
                check_variant_empty( c ) ;
        }
}

TEST_CASE( "variant::swap", "[variant][swap]" )
{
        variant_t empty ;
        variant_t non_empty_1( 5 ) ;
        variant_t non_empty_2( uti::string( 'x', 5 ) ) ;
        variant_t non_empty_3( 3.0 ) ;

        SECTION( "swap::empty::empty" )
        {
                swap( empty, empty ) ;
                check_variant_empty( empty ) ;

                variant_t empty_2( empty ) ;
                swap( empty, empty_2 ) ;
                check_variant_empty( empty ) ;
                check_variant_empty( empty_2 ) ;
        }
        SECTION( "swap::empty::non_empty_1" )
        {
                swap( empty, non_empty_1 ) ;
                check_variant_value( empty, 5 ) ;
                check_variant_empty( non_empty_1 ) ;

                swap( empty, non_empty_1 ) ;
                check_variant_value( non_empty_1, 5 ) ;
                check_variant_empty( empty ) ;
        }
        SECTION( "swap::empty::non_empty_2" )
        {
                swap( empty, non_empty_2 ) ;
                check_variant_value( empty, uti::string( 'x', 5 ) ) ;
                check_variant_empty( non_empty_2 ) ;

                swap( empty, non_empty_2 ) ;
                check_variant_value( non_empty_2, uti::string( 'x', 5 ) ) ;
                check_variant_empty( empty ) ;
        }
//      SECTION( "swap::non_empty::different" )
//      {
//              swap( non_empty_1, non_empty_2 ) ;
//              check_variant_value( non_empty_1, uti::string( 'x', 5 ) ) ;
//              check_variant_value( non_empty_2, 5 ) ;

//              swap( non_empty_1, non_empty_2 ) ;
//              check_variant_value( non_empty_1, 5 ) ;
//              check_variant_value( non_empty_2, uti::string( 'x', 5 ) ) ;
//      }
        SECTION( "swap::non_empty::different" )
        {
                swap( non_empty_1, non_empty_3 ) ;
                check_variant_value( non_empty_1, 3.0, "swap::non_empty::different::1" ) ;
                check_variant_value( non_empty_3, 5, "swap::non_empty::different::2" ) ;

                swap( non_empty_1, non_empty_3 ) ;
                check_variant_value( non_empty_1, 5, "swap::non_empty::different::3" ) ;
                check_variant_value( non_empty_3, 3.0, "swap::non_empty::different::4" ) ;
        }
        SECTION( "swap::non_empty::same" )
        {
                swap( non_empty_2, non_empty_2 ) ;
                check_variant_value( non_empty_2, uti::string( 'x', 5 ) ) ;

                variant_t other( uti::string( 'y', 5 ) ) ;
                swap( non_empty_2, other ) ;
                check_variant_value( non_empty_2, uti::string( 'y', 5 ) ) ;
                check_variant_value( other, uti::string( 'x', 5 ) ) ;

                swap( non_empty_2, other ) ;
                check_variant_value( non_empty_2, uti::string( 'x', 5 ) ) ;
                check_variant_value( other, uti::string( 'y', 5 ) ) ;
        }
}

TEST_CASE( "variant::reset", "[variant][reset]" )
{
        variant_t empty ;
        variant_t non_empty_1( 5 ) ;
        variant_t non_empty_2( uti::string( 'x', 5 ) ) ;

        SECTION( "reset" )
        {
                empty.reset() ;
                check_variant_empty( empty ) ;

                non_empty_1.reset() ;
                check_variant_empty( non_empty_1 ) ;

                non_empty_2.reset() ;
                check_variant_empty( non_empty_2 ) ;
        }
        SECTION( "reset assign" )
        {
                empty = uti::nullvar ;
                check_variant_empty( empty ) ;

                non_empty_1 = uti::nullvar ;
                check_variant_empty( non_empty_1 ) ;

                non_empty_2 = uti::nullvar ;
                check_variant_empty( non_empty_2 ) ;
        }
}

TEST_CASE( "variant::emplace", "[variant][emplace]" )
{
        variant_t empty ;
        variant_t non_empty_1( 5 ) ;
        variant_t non_empty_2( uti::string( 'x', 5 ) ) ;

        SECTION( "emplace::single_arg" )
        {
                empty.emplace( uti::variant_type< uti::string >{}, uti::string( 'y', 5 ) ) ;
                check_variant_value( empty, uti::string( 'y', 5 ) ) ;

                non_empty_1.emplace( uti::variant_type< uti::string >{}, uti::string( 'y', 5 ) ) ;
                check_variant_value( non_empty_1, uti::string( 'y', 5 ) ) ;

                non_empty_2.emplace( uti::variant_type< uti::string >{}, uti::string( 'y', 5 ) ) ;
                check_variant_value( non_empty_2, uti::string( 'y', 5 ) ) ;
        }
        SECTION( "emplace::multi_arg" )
        {
                empty.emplace( uti::variant_type< uti::string >{}, 'y', 5 ) ;
                check_variant_value( empty, uti::string( 'y', 5 ) ) ;

                non_empty_1.emplace( uti::variant_type< uti::string >{}, 'y', 5 ) ;
                check_variant_value( non_empty_1, uti::string( 'y', 5 ) ) ;

                non_empty_2.emplace( uti::variant_type< uti::string >{}, 'y', 5 ) ;
                check_variant_value( non_empty_2, uti::string( 'y', 5 ) ) ;
        }
}

TEST_CASE( "variant::value_or", "[variant][value_or]" )
{
        variant_t empty ;
        variant_t non_empty_1( 5 ) ;
        variant_t non_empty_2( uti::string( 'x', 5 ) ) ;

        CHECK(     empty  .value_or( uti::variant_type< int >{}, 3 ) == 3 ) ;
        CHECK( non_empty_1.value_or( uti::variant_type< int >{}, 3 ) == 5 ) ;
        CHECK( non_empty_2.value_or( uti::variant_type< int >{}, 3 ) == 3 ) ;

        CHECK( non_empty_2.value_or( uti::variant_type< double >{}, 1.618 ) == 1.618 ) ;
}

TEST_CASE( "variant::map", "[variant][map]" )
{

}

TEST_CASE( "variant::compare", "[variant][compare]" )
{

}

























