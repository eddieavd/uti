//
//
//      uti.sys.test
//      sys.test.cxx
//

#include <snitch/snitch.hpp>

#include <uti/sys/test.hxx>


TEST_CASE( "sys", "[sys]" )
{
        CHECK( uti::sum( 1, 2 ) == 3 ) ;
}

