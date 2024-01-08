//
//
//	uti
//	main.cpp
//

#include <string_switch.hpp>


int main ()
{
        constexpr int result = uti::string_switch< int >( "test", 0 )
                .CASE       ( "est", 1 )
                .CASE       ( "tet", 2 )
                .STARTS_WITH( "tes", 3 )
                .ENDS_WITH  ( "est", 4 );

        static_assert( result == 3 );


        return 0;
}
