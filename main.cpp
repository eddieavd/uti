//
//
//	uti
//	main.cpp
//

#include <container/prefix_array.hpp>

#include <cstdio>


int main ()
{

        uti::prefix_array prefix1d( 4,        1 );
        uti::prefix_array prefix2d( 4, prefix1d ) ;
        uti::prefix_array prefix3d( 4, prefix2d ) ;

        auto val1d = prefix1d.range( 1, 3 ) ;
        auto val2d = prefix2d.range( 1, 1, 3, 3 ) ;
        auto val3d = prefix3d.range( 1, 1, 1, 3, 3, 3 ) ;

        printf( "prefix1d queried range: %2d\n", val1d ) ;
        printf( "prefix2d queried range: %2d\n", val2d ) ;
        printf( "prefix3d queried range: %2d\n", val3d ) ;


        return val3d ;
}
