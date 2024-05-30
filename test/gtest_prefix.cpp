//
//
//      uti
//      gtest_prefix.cpp
//

#include "gtest_prefix.hpp"


TEST( PrefixTest, DefaultConstruct )
{
        uti::prefix_array<         int > prefixint ;
        uti::prefix_array< std::string > prefixstr ;

        EXPECT_EQ( prefixint.    size(),    0 ) ;
        EXPECT_EQ( prefixstr.    size(),    0 ) ;
        EXPECT_EQ( prefixint.   empty(), true ) ;
        EXPECT_EQ( prefixstr.   empty(), true ) ;
        EXPECT_EQ( prefixint.capacity(),    0 ) ;
        EXPECT_EQ( prefixstr.capacity(),    0 ) ;
}

TEST( PrefixTest, ReserveConstruct )
{
        uti::prefix_array<         int > prefixint( CUSTOM_CAP ) ;
        uti::prefix_array< std::string > prefixstr( CUSTOM_CAP ) ;

        EXPECT_EQ( prefixint.    size(),          0 ) ;
        EXPECT_EQ( prefixstr.    size(),          0 ) ;
        EXPECT_EQ( prefixint.   empty(),       true ) ;
        EXPECT_EQ( prefixstr.   empty(),       true ) ;
        EXPECT_EQ( prefixint.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixstr.capacity(), CUSTOM_CAP ) ;
}

TEST( PrefixTest, FillConstruct )
{
        uti::prefix_array<         int > prefixint( CUSTOM_CAP, CUSTOM_VAL ) ;
        uti::prefix_array< std::string > prefixstr( CUSTOM_CAP, std::string( "fill_test" ) ) ;

        EXPECT_EQ( prefixint.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixstr.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixint.   empty(),      false ) ;
        EXPECT_EQ( prefixstr.   empty(),      false ) ;
        EXPECT_EQ( prefixint.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixstr.capacity(), CUSTOM_CAP ) ;

        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                EXPECT_EQ( prefixint.at( i ), i + 1 ) ;
                EXPECT_EQ( prefixstr.at( i ).starts_with( "fill_test" ), true ) ;
        }
}

TEST( PrefixTest, CopyConstruct )
{
        uti::prefix_array<         int > prefixint( CUSTOM_CAP, CUSTOM_VAL ) ;
        uti::prefix_array< std::string > prefixstr( CUSTOM_CAP, std::string( "copy_c_test" ) ) ;

        uti::prefix_array<         int > prefixintcopy( prefixint ) ;
        uti::prefix_array< std::string > prefixstrcopy( prefixstr ) ;

        EXPECT_EQ( prefixintcopy.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixstrcopy.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixintcopy.   empty(),      false ) ;
        EXPECT_EQ( prefixstrcopy.   empty(),      false ) ;
        EXPECT_EQ( prefixintcopy.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixstrcopy.capacity(), CUSTOM_CAP ) ;

        EXPECT_EQ( prefixint.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixstr.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixint.   empty(),      false ) ;
        EXPECT_EQ( prefixstr.   empty(),      false ) ;
        EXPECT_EQ( prefixint.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixstr.capacity(), CUSTOM_CAP ) ;

        for( ssize_t i = 0; i < prefixintcopy.size(); ++i )
        {
                EXPECT_EQ( prefixintcopy.at( i ), i + 1 ) ;
                EXPECT_EQ( prefixstrcopy.at( i ).starts_with( "copy_c_test" ), true ) ;

                EXPECT_EQ( prefixintcopy.at( i ), prefixint.at( i ) ) ;
                EXPECT_EQ( prefixstrcopy.at( i ), prefixstr.at( i ) ) ;
        }
}

TEST( PrefixTest, MoveConstruct )
{
        uti::prefix_array<         int > prefixint( CUSTOM_CAP, CUSTOM_VAL ) ;
        uti::prefix_array< std::string > prefixstr( CUSTOM_CAP, std::string( "move_c_test" ) ) ;

        uti::prefix_array<         int > prefixintmove( UTI_MOVE( prefixint ) ) ;
        uti::prefix_array< std::string > prefixstrmove( UTI_MOVE( prefixstr ) ) ;

        EXPECT_EQ( prefixintmove.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixstrmove.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixintmove.   empty(),      false ) ;
        EXPECT_EQ( prefixstrmove.   empty(),      false ) ;
        EXPECT_EQ( prefixintmove.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixstrmove.capacity(), CUSTOM_CAP ) ;

        EXPECT_EQ( prefixint.    size(),    0 ) ;
        EXPECT_EQ( prefixstr.    size(),    0 ) ;
        EXPECT_EQ( prefixint.   empty(), true ) ;
        EXPECT_EQ( prefixstr.   empty(), true ) ;
        EXPECT_EQ( prefixint.capacity(),    0 ) ;
        EXPECT_EQ( prefixstr.capacity(),    0 ) ;

        for( ssize_t i = 0; i < prefixintmove.size(); ++i )
        {
                EXPECT_EQ( prefixintmove.at( i ), i + 1 ) ;
                EXPECT_EQ( prefixstrmove.at( i ).starts_with( "move_c_test" ), true ) ;
        }
}

TEST( PrefixTest, CopyAssign )
{
        uti::prefix_array<         int > prefixint( CUSTOM_CAP, CUSTOM_VAL ) ;
        uti::prefix_array< std::string > prefixstr( CUSTOM_CAP, std::string( "copy_a_test" ) ) ;

        uti::prefix_array<         int > prefixintcopy ( CUSTOM_CAP * 2, CUSTOM_VAL * 2 ) ;
        uti::prefix_array< std::string > prefixstrcopy0( CUSTOM_CAP    , std::string( "random" ) ) ;
        uti::prefix_array< std::string > prefixstrcopy1( CUSTOM_CAP * 2, std::string( "random" ) ) ;
        uti::prefix_array< std::string > prefixstrcopy2( CUSTOM_CAP / 2, std::string( "random" ) ) ;

        prefixintcopy  = prefixint ;
        prefixstrcopy0 = prefixstr ;
        prefixstrcopy1 = prefixstr ;
        prefixstrcopy2 = prefixstr ;

        EXPECT_EQ( prefixintcopy .    size(), CUSTOM_CAP     ) ;
        EXPECT_EQ( prefixstrcopy0.    size(), CUSTOM_CAP     ) ;
        EXPECT_EQ( prefixstrcopy1.    size(), CUSTOM_CAP     ) ;
        EXPECT_EQ( prefixstrcopy2.    size(), CUSTOM_CAP     ) ;
        EXPECT_EQ( prefixintcopy .   empty(),      false     ) ;
        EXPECT_EQ( prefixstrcopy0.   empty(),      false     ) ;
        EXPECT_EQ( prefixstrcopy1.   empty(),      false     ) ;
        EXPECT_EQ( prefixstrcopy2.   empty(),      false     ) ;
        EXPECT_EQ( prefixintcopy .capacity(), CUSTOM_CAP * 2 ) ;
        EXPECT_EQ( prefixstrcopy0.capacity(), CUSTOM_CAP     ) ;
        EXPECT_EQ( prefixstrcopy1.capacity(), CUSTOM_CAP * 2 ) ;
        EXPECT_EQ( prefixstrcopy2.capacity(), CUSTOM_CAP     ) ;

        EXPECT_EQ( prefixint.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixstr.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixint.   empty(),      false ) ;
        EXPECT_EQ( prefixstr.   empty(),      false ) ;
        EXPECT_EQ( prefixint.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixstr.capacity(), CUSTOM_CAP ) ;

        for( ssize_t i = 0; i < prefixintcopy.size(); ++i )
        {
                EXPECT_EQ( prefixintcopy .at( i ), i + 1 ) ;
                EXPECT_EQ( prefixstrcopy0.at( i ).starts_with( "copy_a_test" ), true ) ;
                EXPECT_EQ( prefixstrcopy1.at( i ).starts_with( "copy_a_test" ), true ) ;
                EXPECT_EQ( prefixstrcopy2.at( i ).starts_with( "copy_a_test" ), true ) ;

                EXPECT_EQ( prefixintcopy .at( i ), prefixint.at( i ) ) ;
                EXPECT_EQ( prefixstrcopy0.at( i ), prefixstr.at( i ) ) ;
                EXPECT_EQ( prefixstrcopy1.at( i ), prefixstr.at( i ) ) ;
                EXPECT_EQ( prefixstrcopy2.at( i ), prefixstr.at( i ) ) ;
        }
}

TEST( PrefixTest, MoveAssign )
{
        uti::prefix_array<         int > prefixint ( CUSTOM_CAP, CUSTOM_VAL ) ;
        uti::prefix_array< std::string > prefixstr1( CUSTOM_CAP, std::string( "move_a_test" ) ) ;
        uti::prefix_array< std::string > prefixstr2( CUSTOM_CAP, std::string( "move_a_test" ) ) ;
        uti::prefix_array< std::string > prefixstr3( CUSTOM_CAP, std::string( "move_a_test" ) ) ;

        uti::prefix_array<         int > prefixintmove ( CUSTOM_CAP * 2, CUSTOM_VAL * 2 ) ;
        uti::prefix_array< std::string > prefixstrmove0( CUSTOM_CAP    , std::string( "random" ) ) ;
        uti::prefix_array< std::string > prefixstrmove1( CUSTOM_CAP * 2, std::string( "random" ) ) ;
        uti::prefix_array< std::string > prefixstrmove2( CUSTOM_CAP / 2, std::string( "random" ) ) ;

        prefixintmove  = UTI_MOVE( prefixint  ) ;
        prefixstrmove0 = UTI_MOVE( prefixstr1 ) ;
        prefixstrmove1 = UTI_MOVE( prefixstr2 ) ;
        prefixstrmove2 = UTI_MOVE( prefixstr3 ) ;

        EXPECT_EQ( prefixintmove .    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixstrmove0.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixstrmove1.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixstrmove2.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixintmove .   empty(),      false ) ;
        EXPECT_EQ( prefixstrmove0.   empty(),      false ) ;
        EXPECT_EQ( prefixstrmove1.   empty(),      false ) ;
        EXPECT_EQ( prefixstrmove2.   empty(),      false ) ;
        EXPECT_EQ( prefixintmove .capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixstrmove0.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixstrmove1.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixstrmove2.capacity(), CUSTOM_CAP ) ;

        EXPECT_EQ( prefixint .    size(),    0 ) ;
        EXPECT_EQ( prefixstr1.    size(),    0 ) ;
        EXPECT_EQ( prefixstr2.    size(),    0 ) ;
        EXPECT_EQ( prefixstr3.    size(),    0 ) ;
        EXPECT_EQ( prefixint .   empty(), true ) ;
        EXPECT_EQ( prefixstr1.   empty(), true ) ;
        EXPECT_EQ( prefixstr2.   empty(), true ) ;
        EXPECT_EQ( prefixstr3.   empty(), true ) ;
        EXPECT_EQ( prefixint .capacity(),    0 ) ;
        EXPECT_EQ( prefixstr1.capacity(),    0 ) ;
        EXPECT_EQ( prefixstr2.capacity(),    0 ) ;
        EXPECT_EQ( prefixstr3.capacity(),    0 ) ;

        for( ssize_t i = 0; i < prefixintmove.size(); ++i )
        {
                EXPECT_EQ( prefixintmove .at( i ), i + 1 ) ;
                EXPECT_EQ( prefixstrmove0.at( i ).starts_with( "move_a_test" ), true ) ;
                EXPECT_EQ( prefixstrmove1.at( i ).starts_with( "move_a_test" ), true ) ;
                EXPECT_EQ( prefixstrmove2.at( i ).starts_with( "move_a_test" ), true ) ;
        }
}

TEST( PrefixTest, ElementAt )
{
        uti::prefix_array< int >                                           vec1d( CUSTOM_CAP, CUSTOM_VAL ) ;
        uti::prefix_array< uti::prefix_array< int > >                      vec2d( CUSTOM_CAP             ) ;
        uti::prefix_array< uti::prefix_array< uti::prefix_array< int > > > vec3d( CUSTOM_CAP             ) ;

        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                vec2d.push_back( vec1d );
        }
        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                vec3d.push_back( vec2d );
        }
        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                EXPECT_EQ( vec1d.element_at( i ), CUSTOM_VAL ) ;

                for( ssize_t j = 0; j < CUSTOM_CAP; ++j )
                {
                        EXPECT_EQ( vec2d.element_at( i, j ), vec1d.element_at( j ) ) ;

                        for( ssize_t k = 0; k < CUSTOM_CAP; ++k )
                        {
                                EXPECT_EQ( vec3d.element_at( i, j, k ), vec1d.element_at( k ) ) ;
                        }
                }
        }
}

TEST( PrefixTest, PushBack )
{
        uti::prefix_array< int > vec ;

        for( ssize_t i = 0; i < 1024; ++i )
        {
                vec.push_back( i );
        }
        for( ssize_t i = 0; i < 1024; ++i )
        {
                EXPECT_EQ( vec.element_at( i ), i ) ;
        }
}

TEST( PrefixTest, EmplaceBack )
{
        uti::prefix_array< std::string              > prefixstr ;
        uti::prefix_array< uti::prefix_array< int > > prefix2d  ;

        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                prefix2d .emplace_back( CUSTOM_CAP, i ) ;
                prefixstr.emplace_back( std::to_string( i ) ) ;
        }
        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                EXPECT_EQ( prefixstr.at( i ).starts_with( std::to_string( i ) ), true ) ;

                for( auto const & val : prefix2d.element_at( i ) )
                {
                        ( void ) val ;
//                      EXPECT_EQ( val, i ) ;
                }
        }
}

TEST( PrefixTest, Pop )
{
        uti::prefix_array< int > vec ;

        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                vec.push_back( CUSTOM_VAL ) ;
        }

        EXPECT_EQ( vec. size(), CUSTOM_CAP ) ;
        EXPECT_EQ( vec.front(),          1 ) ;
        EXPECT_EQ( vec. back(), CUSTOM_CAP ) ;

        auto val = vec.pop_back_val();

        EXPECT_EQ( val        , CUSTOM_VAL     ) ;
        EXPECT_EQ( vec. size(), CUSTOM_CAP - 1 ) ;
        EXPECT_EQ( vec.front(),              1 ) ;
        EXPECT_EQ( vec. back(), CUSTOM_CAP - 1 ) ;

        val = vec.pop_front_val();

        EXPECT_EQ( val        ,              1 ) ;
        EXPECT_EQ( vec. size(), CUSTOM_CAP - 2 ) ;
        EXPECT_EQ( vec.front(),              1 ) ;
        EXPECT_EQ( vec. back(), CUSTOM_CAP - 2 ) ;
}

TEST( PrefixTest, Reserve )
{
        uti::prefix_array< int > vec1               ;
        uti::prefix_array< int > vec2( CUSTOM_CAP ) ;

        EXPECT_EQ( vec1.capacity(),          0 ) ;
        EXPECT_EQ( vec2.capacity(), CUSTOM_CAP ) ;

        vec1.reserve( 0 ) ;
        vec2.reserve( 0 ) ;

        EXPECT_EQ( vec1.capacity(),          0 ) ;
        EXPECT_EQ( vec2.capacity(), CUSTOM_CAP ) ;

        vec1.reserve( CUSTOM_CAP * 2 ) ;
        vec2.reserve( CUSTOM_CAP * 2 ) ;

        EXPECT_EQ( vec1.capacity(), CUSTOM_CAP * 2 ) ;
        EXPECT_EQ( vec2.capacity(), CUSTOM_CAP * 2 ) ;

        vec1.reserve( CUSTOM_CAP / 2 ) ;
        vec2.reserve( CUSTOM_CAP / 2 ) ;

        EXPECT_EQ( vec1.capacity(), CUSTOM_CAP * 2 ) ;
        EXPECT_EQ( vec2.capacity(), CUSTOM_CAP * 2 ) ;
}

TEST( PrefixTest, Shrink )
{
        {
                uti::prefix_array<         int > prefixint( CUSTOM_CAP,    CUSTOM_VAL ) ;
                uti::prefix_array< std::string > prefixstr( CUSTOM_CAP, "shrink_test" ) ;

                EXPECT_EQ( prefixint.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( prefixint.capacity(), CUSTOM_CAP ) ;

                EXPECT_EQ( prefixstr.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( prefixstr.capacity(), CUSTOM_CAP ) ;

                prefixint.shrink_size( CUSTOM_CAP / 2 ) ;
                prefixstr.shrink_size( CUSTOM_CAP / 2 ) ;

                EXPECT_EQ( prefixint.    size(), CUSTOM_CAP / 2 ) ;
                EXPECT_EQ( prefixint.capacity(), CUSTOM_CAP     ) ;

                EXPECT_EQ( prefixstr.    size(), CUSTOM_CAP / 2 ) ;
                EXPECT_EQ( prefixstr.capacity(), CUSTOM_CAP     ) ;
        }
        {
                uti::prefix_array<         int > prefixint( CUSTOM_CAP,    CUSTOM_VAL ) ;
                uti::prefix_array< std::string > prefixstr( CUSTOM_CAP, "shrink_test" ) ;

                EXPECT_EQ( prefixint.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( prefixint.capacity(), CUSTOM_CAP ) ;

                EXPECT_EQ( prefixstr.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( prefixstr.capacity(), CUSTOM_CAP ) ;

                prefixint.reserve( CUSTOM_CAP * 2 ) ;
                prefixstr.reserve( CUSTOM_CAP * 2 ) ;

                EXPECT_EQ( prefixint.    size(), CUSTOM_CAP     ) ;
                EXPECT_EQ( prefixint.capacity(), CUSTOM_CAP * 2 ) ;

                EXPECT_EQ( prefixstr.    size(), CUSTOM_CAP     ) ;
                EXPECT_EQ( prefixstr.capacity(), CUSTOM_CAP * 2 ) ;

                prefixint.shrink_to_fit();
                prefixstr.shrink_to_fit();

                EXPECT_EQ( prefixint.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( prefixint.capacity(), CUSTOM_CAP ) ;

                EXPECT_EQ( prefixstr.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( prefixstr.capacity(), CUSTOM_CAP ) ;
        }
        {
                uti::prefix_array<         int > prefixint( CUSTOM_CAP,    CUSTOM_VAL ) ;
                uti::prefix_array< std::string > prefixstr( CUSTOM_CAP, "shrink_test" ) ;

                EXPECT_EQ( prefixint.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( prefixint.capacity(), CUSTOM_CAP ) ;

                EXPECT_EQ( prefixstr.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( prefixstr.capacity(), CUSTOM_CAP ) ;

                prefixint.shrink( CUSTOM_CAP / 2 ) ;
                prefixstr.shrink( CUSTOM_CAP / 2 ) ;

                EXPECT_EQ( prefixint.    size(), CUSTOM_CAP / 2 ) ;
                EXPECT_EQ( prefixint.capacity(), CUSTOM_CAP / 2 ) ;

                EXPECT_EQ( prefixstr.    size(), CUSTOM_CAP / 2 ) ;
                EXPECT_EQ( prefixstr.capacity(), CUSTOM_CAP / 2 ) ;
        }
}

TEST( PrefixTest, Insert )
{
        uti::prefix_array<         int > prefixint( CUSTOM_CAP,    CUSTOM_VAL ) ;
        uti::prefix_array< std::string > prefixstr( CUSTOM_CAP, "insert_test" ) ;

        EXPECT_EQ( prefixint.size(), CUSTOM_CAP ) ;
        EXPECT_EQ( prefixstr.size(), CUSTOM_CAP ) ;

        prefixint.insert( CUSTOM_VAL * 2, 0 ) ;
        prefixstr.insert(    "inserted" , 0 ) ;

        EXPECT_EQ( prefixint.size(), CUSTOM_CAP + 1 ) ;
        EXPECT_EQ( prefixstr.size(), CUSTOM_CAP + 1 ) ;

        prefixint.insert( CUSTOM_VAL * 2, CUSTOM_CAP / 2 ) ;
        prefixstr.insert(     "inserted", CUSTOM_CAP / 2 ) ;

        EXPECT_EQ( prefixint.size(), CUSTOM_CAP + 2 ) ;
        EXPECT_EQ( prefixstr.size(), CUSTOM_CAP + 2 ) ;

        prefixint.insert( CUSTOM_VAL * 2, prefixint.size() ) ;
        prefixstr.insert(     "inserted", prefixstr.size() ) ;

        EXPECT_EQ( prefixint.size(), CUSTOM_CAP + 3 ) ;
        EXPECT_EQ( prefixstr.size(), CUSTOM_CAP + 3 ) ;

        for( ssize_t i = 0; i < prefixint.size(); ++i )
        {
                if( i == 0 || i == CUSTOM_CAP / 2 || i == prefixint.size() - 1 )
                {
//                      EXPECT_EQ( prefixint.at( i ), CUSTOM_VAL * 2 ) ;
//                      EXPECT_EQ( prefixstr.at( i ).starts_with( "inserted" ), true ) ;
                }
                else
                {
//                      EXPECT_EQ( prefixint.at( i ), CUSTOM_VAL ) ;
//                      EXPECT_EQ( prefixstr.at( i ).starts_with( "insert_test" ), true ) ;
                }
        }
}

TEST( PrefixTest, Erase )
{
        {
                uti::prefix_array<         int > prefixint( CUSTOM_CAP,   CUSTOM_VAL ) ;
//              uti::prefix_array< std::string > prefixstr( CUSTOM_CAP, "erase_test" ) ;

                EXPECT_EQ( prefixint.size(), CUSTOM_CAP ) ;
//              EXPECT_EQ( prefixstr.size(), CUSTOM_CAP ) ;

                prefixint.erase( 0 ) ;
//              prefixstr.erase( 0 ) ;

                EXPECT_EQ( prefixint.size(), CUSTOM_CAP - 1 ) ;
//              EXPECT_EQ( prefixstr.size(), CUSTOM_CAP - 1 ) ;

                prefixint.erase( prefixint.size() / 2 ) ;
//              prefixstr.erase( prefixstr.size() / 2 ) ;

                EXPECT_EQ( prefixint.size(), CUSTOM_CAP - 2 ) ;
//              EXPECT_EQ( prefixstr.size(), CUSTOM_CAP - 2 ) ;

                prefixint.erase( prefixint.size() - 1 ) ;
//              prefixstr.erase( prefixstr.size() - 1 ) ;

                EXPECT_EQ( prefixint.size(), CUSTOM_CAP - 3 ) ;
//              EXPECT_EQ( prefixstr.size(), CUSTOM_CAP - 3 ) ;
        }
        {
                uti::prefix_array<         int > prefixint( CUSTOM_CAP,   CUSTOM_VAL ) ;
//              uti::prefix_array< std::string > prefixstr( CUSTOM_CAP, "erase_test" ) ;

                EXPECT_EQ( prefixint.size(), CUSTOM_CAP ) ;
//              EXPECT_EQ( prefixstr.size(), CUSTOM_CAP ) ;

                prefixint.erase_stable( 0 ) ;
//              prefixstr.erase_stable( 0 ) ;

                EXPECT_EQ( prefixint.size(), CUSTOM_CAP - 1 ) ;
//              EXPECT_EQ( prefixstr.size(), CUSTOM_CAP - 1 ) ;

                prefixint.erase_stable( prefixint.size() / 2 ) ;
//              prefixstr.erase_stable( prefixstr.size() / 2 ) ;

                EXPECT_EQ( prefixint.size(), CUSTOM_CAP - 2 ) ;
//              EXPECT_EQ( prefixstr.size(), CUSTOM_CAP - 2 ) ;

                prefixint.erase_stable( prefixint.size() - 1 ) ;
//              prefixstr.erase_stable( prefixstr.size() - 1 ) ;

                EXPECT_EQ( prefixint.size(), CUSTOM_CAP - 3 ) ;
//              EXPECT_EQ( prefixstr.size(), CUSTOM_CAP - 3 ) ;
        }
}

TEST( PrefixTest, Clear )
{
        uti::prefix_array<         int > vec1                                        ;
        uti::prefix_array<         int > vec2( CUSTOM_CAP,            CUSTOM_VAL   ) ;
        uti::prefix_array< std::string > vec3( CUSTOM_CAP, std::string( "random" ) ) ;

        EXPECT_EQ( vec1.size(),          0 ) ;
        EXPECT_EQ( vec2.size(), CUSTOM_CAP ) ;
        EXPECT_EQ( vec3.size(), CUSTOM_CAP ) ;

        vec1.clear() ;
        vec2.clear() ;
        vec3.clear() ;

        EXPECT_EQ( vec1.size(), 0 ) ;
        EXPECT_EQ( vec2.size(), 0 ) ;
        EXPECT_EQ( vec3.size(), 0 ) ;
}

TEST( PrefixTest, Iterate )
{
        uti::prefix_array< int > vec( CUSTOM_CAP, CUSTOM_VAL ) ;

        int pos = 1 ;

        for( auto const & val : vec )
        {
                EXPECT_EQ( val, pos++ ) ;
        }
}

TEST( PrefixTest, NoDoubleFree )
{
        uti::prefix_array< uti::prefix_array< std::string > > prefix2d;

        for( int i = 0; i < 4; ++i )
        {
                uti::prefix_array< std::string > prefix1d;
                for( int i = 0; i < 4; ++i )
                {
                        prefix1d.insert( std::to_string( i ), 0 );
                }
                prefix2d.insert( UTI_MOVE( prefix1d ), 0 );
        }
        uti::prefix_array< uti::prefix_array< std::string > > vec2d2;

        for( int i = 0; i < 4; ++i )
        {
                if( i % 2 == 0 )
                {
                        vec2d2.insert( UTI_MOVE( prefix2d.at( i ) ), 0 );
                }
                else
                {
                        vec2d2.insert( prefix2d.at( i ), 0 );
                }
        }
        ssize_t dummy_counter { 0 } ;

        for( auto const & row : vec2d2 )
        {
                for( auto const & val : row )
                {
                        dummy_counter += val.length();
                }
        }
        EXPECT_EQ( dummy_counter, dummy_counter ) ;
}
