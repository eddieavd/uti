//
//
//      uti.core.test
//      string_switch.test.cxx
//

#include <snitch/snitch.hpp>

#include <uti.core.hxx>
#include <uti/core/util/copy_counter.hxx>


TEST_CASE( "string_switch::case", "[string_switch][case]" )
{
        INFO( "string_switch::case::1" ) ;
        CONSTEXPR_CHECK( []
        {
                uti::string_view str( "abc" ) ;
                int result = uti::string_switch( str, 0 )
                                .CASE( "abc", 1 )
                                .CASE( "bcd", 2 )
                                .CASE( "cde", 3 )
                                .DEFAULT( 0 ) ;

                return result ;
        }() == 1 ) ;

        INFO( "string_switch::case::2" ) ;
        CONSTEXPR_CHECK( []
        {
                uti::string_view str( "bcd" ) ;
                int result = uti::string_switch( str, 0 )
                                .CASE( "abc", 1 )
                                .CASE( "bcd", 2 )
                                .CASE( "cde", 3 )
                                .DEFAULT( 0 ) ;

                return result ;
        }() == 2 ) ;

        INFO( "string_switch::case::3" ) ;
        CONSTEXPR_CHECK( []
        {
                uti::string_view str( "cde" ) ;
                int result = uti::string_switch( str, 0 )
                                .CASE( "abc", 1 )
                                .CASE( "bcd", 2 )
                                .CASE( "cde", 3 )
                                .DEFAULT( 0 ) ;

                return result ;
        }() == 3 ) ;
}

TEST_CASE( "string_switch::starts_with", "[string_switch][starts_with]" )
{
        INFO( "string_switch::starts_with::1" ) ;
        CONSTEXPR_CHECK( []
        {
                uti::string_view str( "abcde" ) ;
                int result = uti::string_switch( str, 0 )
                                .STARTS_WITH( "abc", 1 )
                                .STARTS_WITH( "bcd", 2 )
                                .STARTS_WITH( "cde", 3 )
                                .DEFAULT( 0 ) ;

                return result ;
        }() == 1 ) ;

        INFO( "string_switch::starts_with::2" ) ;
        CONSTEXPR_CHECK( []
        {
                uti::string_view str( "bcdef" ) ;
                int result = uti::string_switch( str, 0 )
                                .STARTS_WITH( "abc", 1 )
                                .STARTS_WITH( "bcd", 2 )
                                .STARTS_WITH( "cde", 3 )
                                .DEFAULT( 0 ) ;

                return result ;
        }() == 2 ) ;

        INFO( "string_switch::starts_with::3" ) ;
        CONSTEXPR_CHECK( []
        {
                uti::string_view str( "cdefg" ) ;
                int result = uti::string_switch( str, 0 )
                                .STARTS_WITH( "abc", 1 )
                                .STARTS_WITH( "bcd", 2 )
                                .STARTS_WITH( "cde", 3 )
                                .DEFAULT( 0 ) ;

                return result ;
        }() == 3 ) ;
}

TEST_CASE( "string_switch::ends_with", "[string_switch][ends_with]" )
{
        INFO( "string_switch::ends_with::1" ) ;
        CONSTEXPR_CHECK( []
        {
                uti::string_view str( "abcde" ) ;
                int result = uti::string_switch( str, 0 )
                                .ENDS_WITH( "cde", 1 )
                                .ENDS_WITH( "def", 2 )
                                .ENDS_WITH( "efg", 3 )
                                .DEFAULT( 0 ) ;

                return result ;
        }() == 1 ) ;

        INFO( "string_switch::ends_with::2" ) ;
        CONSTEXPR_CHECK( []
        {
                uti::string_view str( "bcdef" ) ;
                int result = uti::string_switch( str, 0 )
                                .ENDS_WITH( "cde", 1 )
                                .ENDS_WITH( "def", 2 )
                                .ENDS_WITH( "efg", 3 )
                                .DEFAULT( 0 ) ;

                return result ;
        }() == 2 ) ;

        INFO( "string_switch::ends_with::3" ) ;
        CONSTEXPR_CHECK( []
        {
                uti::string_view str( "cdefg" ) ;
                int result = uti::string_switch( str, 0 )
                                .ENDS_WITH( "cde", 1 )
                                .ENDS_WITH( "def", 2 )
                                .ENDS_WITH( "efg", 3 )
                                .DEFAULT( 0 ) ;

                return result ;
        }() == 3 ) ;
}

TEST_CASE( "string_switch::default", "[string_switch][default]" )
{
        INFO( "string_switch::default::1" ) ;
        CONSTEXPR_CHECK( []
        {
                uti::string_view str( "x" ) ;
                int result = uti::string_switch( str, 0 )
                                .CASE( "a", 1 )
                                .CASE( "b", 2 )
                                .CASE( "c", 3 )
                                .DEFAULT( 0 ) ;

                return result ;
        }() == 0 ) ;

        INFO( "string_switch::default::2" ) ;
        CONSTEXPR_CHECK( []
        {
                uti::string_view str( "y" ) ;
                int result = uti::string_switch( str, 0 )
                                .CASE( "a", 1 )
                                .CASE( "b", 2 )
                                .CASE( "c", 3 )
                                .DEFAULT( 0 ) ;

                return result ;
        }() == 0 ) ;

        INFO( "string_switch::default::3" ) ;
        CONSTEXPR_CHECK( []
        {
                uti::string_view str( "z" ) ;
                int result = uti::string_switch( str, 0 )
                                .CASE( "a", 1 )
                                .CASE( "b", 2 )
                                .CASE( "c", 3 )
                                .DEFAULT( 0 ) ;

                return result ;
        }() == 0 ) ;
}

TEST_CASE( "string_switch::complex", "[string_switch][complex]" )
{
        INFO( "string_switch::complex::1" ) ;
        CHECK( []
        {
                uti::string_view str( "abc" ) ;
                uti::test::copy_counter ctr = uti::string_switch( str, uti::test::copy_counter{} )
                                                .CASE( "cba", {} )
                                                .CASE( "acb", {} )
                                                .CASE( "abc", {} )
                                                .DEFAULT( {} ) ;

                return ctr ;
        }().stats.n_copies == 0 ) ;
}
