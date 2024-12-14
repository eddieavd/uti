//
//
//      uti.test
//      uti.manual.cxx
//

#include <container/prefix_array.hxx>

#include <string>

#define CUSTOM_CAP 32


int main ()
{
        uti::prefix_array<         int > prefixint( CUSTOM_CAP, 1 ) ;
        uti::prefix_array< std::string > prefixstr( CUSTOM_CAP, std::string( "copy_a_test" ) ) ;

        uti::prefix_array<         int > prefixintcopy ( CUSTOM_CAP * 2, 2 ) ;
        uti::prefix_array< std::string > prefixstrcopy0( CUSTOM_CAP    , std::string( "random" ) ) ;
        uti::prefix_array< std::string > prefixstrcopy1( CUSTOM_CAP * 2, std::string( "random" ) ) ;
        uti::prefix_array< std::string > prefixstrcopy2( CUSTOM_CAP / 2, std::string( "random" ) ) ;

        prefixintcopy  = prefixint ;
        prefixstrcopy0 = prefixstr ;
        prefixstrcopy1 = prefixstr ;
        prefixstrcopy2 = prefixstr ;

        if( prefixintcopy .    size() != CUSTOM_CAP     ) printf( "failed at line %d\n", __LINE__ ) ;
        if( prefixstrcopy0.    size() != CUSTOM_CAP     ) printf( "failed at line %d\n", __LINE__ ) ;
        if( prefixstrcopy1.    size() != CUSTOM_CAP     ) printf( "failed at line %d\n", __LINE__ ) ;
        if( prefixstrcopy2.    size() != CUSTOM_CAP     ) printf( "failed at line %d\n", __LINE__ ) ;
        if( prefixintcopy .   empty() !=      false     ) printf( "failed at line %d\n", __LINE__ ) ;
        if( prefixstrcopy0.   empty() !=      false     ) printf( "failed at line %d\n", __LINE__ ) ;
        if( prefixstrcopy1.   empty() !=      false     ) printf( "failed at line %d\n", __LINE__ ) ;
        if( prefixstrcopy2.   empty() !=      false     ) printf( "failed at line %d\n", __LINE__ ) ;
        if( prefixintcopy .capacity() != CUSTOM_CAP * 2 ) printf( "failed at line %d\n", __LINE__ ) ;
        if( prefixstrcopy0.capacity() != CUSTOM_CAP     ) printf( "failed at line %d\n", __LINE__ ) ;
        if( prefixstrcopy1.capacity() != CUSTOM_CAP * 2 ) printf( "failed at line %d\n", __LINE__ ) ;
        if( prefixstrcopy2.capacity() != CUSTOM_CAP     ) printf( "failed at line %d\n", __LINE__ ) ;

        if( prefixint.    size() != CUSTOM_CAP ) printf( "failed at line %d\n", __LINE__ ) ;
        if( prefixstr.    size() != CUSTOM_CAP ) printf( "failed at line %d\n", __LINE__ ) ;
        if( prefixint.   empty() !=      false ) printf( "failed at line %d\n", __LINE__ ) ;
        if( prefixstr.   empty() !=      false ) printf( "failed at line %d\n", __LINE__ ) ;
        if( prefixint.capacity() != CUSTOM_CAP ) printf( "failed at line %d\n", __LINE__ ) ;
        if( prefixstr.capacity() != CUSTOM_CAP ) printf( "failed at line %d\n", __LINE__ ) ;

        for( int i = 0; i < prefixintcopy.size(); ++i )
        {
                if( prefixintcopy .at( i ) != i + 1 ) printf( "failed on iteration %d at line %d\n", i, __LINE__ ) ;
                if( prefixstrcopy0.at( i ).starts_with( "copy_a_test" ) != true ) printf( "failed on iteration %d at line %d\n", i, __LINE__ ) ;
                if( prefixstrcopy1.at( i ).starts_with( "copy_a_test" ) != true ) printf( "failed on iteration %d at line %d\n", i, __LINE__ ) ;
                if( prefixstrcopy2.at( i ).starts_with( "copy_a_test" ) != true ) printf( "failed on iteration %d at line %d\n", i, __LINE__ ) ;

                if( prefixintcopy .at( i ) != prefixint.at( i ) ) printf( "failed on iteration %d at line %d\n", i, __LINE__ ) ;
                if( prefixstrcopy0.at( i ) != prefixstr.at( i ) ) printf( "failed on iteration %d at line %d\n", i, __LINE__ ) ;
                if( prefixstrcopy1.at( i ) != prefixstr.at( i ) ) printf( "failed on iteration %d at line %d\n", i, __LINE__ ) ;
                if( prefixstrcopy2.at( i ) != prefixstr.at( i ) ) printf( "failed on iteration %d at line %d\n", i, __LINE__ ) ;
        }


        return 0 ;
}
