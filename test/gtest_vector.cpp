//
//
//      uti
//      gtest_vector.cpp
//

#include "gtest_vector.hpp"


TEST( VectorTest, DefaultConstruct )
{
        uti::vector<         int > vecint ;
        uti::vector< std::string > vecstr ;

        EXPECT_EQ( vecint.    size(),    0 ) ;
        EXPECT_EQ( vecstr.    size(),    0 ) ;
        EXPECT_EQ( vecint.   empty(), true ) ;
        EXPECT_EQ( vecstr.   empty(), true ) ;
        EXPECT_EQ( vecint.capacity(),    0 ) ;
        EXPECT_EQ( vecstr.capacity(),    0 ) ;
}

TEST( VectorTest, ReserveConstruct )
{
        uti::vector<         int > vecint( CUSTOM_CAP ) ;
        uti::vector< std::string > vecstr( CUSTOM_CAP ) ;

        EXPECT_EQ( vecint.    size(),          0 ) ;
        EXPECT_EQ( vecstr.    size(),          0 ) ;
        EXPECT_EQ( vecint.   empty(),       true ) ;
        EXPECT_EQ( vecstr.   empty(),       true ) ;
        EXPECT_EQ( vecint.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecstr.capacity(), CUSTOM_CAP ) ;
}

TEST( VectorTest, FillConstruct )
{
        uti::vector< int > vecint( CUSTOM_CAP, CUSTOM_VAL ) ;

        uti::vector< std::string > vecstr( CUSTOM_CAP, std::string( "fill_test" ) ) ;

        EXPECT_EQ( vecint.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecstr.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecint.   empty(),      false ) ;
        EXPECT_EQ( vecstr.   empty(),      false ) ;
        EXPECT_EQ( vecint.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecstr.capacity(), CUSTOM_CAP ) ;

        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                EXPECT_EQ( vecint.at( i ),  CUSTOM_VAL ) ;
                EXPECT_EQ( vecstr.at( i ), "fill_test" ) ;
        }
}

TEST( VectorTest, IteratorConstruct )
{
        {
                int arr[] = { 0, 1, 2, 3 } ;

                int * begin = arr ;
                int *   end = arr + ( sizeof( arr ) / sizeof( int ) ) ;

                uti::vector< int > vec( begin, end ) ;

                for( ssize_t i = 0; i < 4; ++i )
                {
                        EXPECT_EQ( vec.at( i ), i ) ;
                }
        }
        {
                uti::vector< int > vec( 4, 1 ) ;

                uti::vector< int > vec2( vec.begin(), vec.end() ) ;

                for( ssize_t i = 0; i < vec.size(); ++i )
                {
                        EXPECT_EQ( vec.at( i ), vec2.at( i ) ) ;
                }
        }
        {
                uti::prefix_array< int > prefix( 4, 1 ) ;

                uti::vector< int > vec( prefix.begin(), prefix.end() ) ;

                for( ssize_t i = 0; i < prefix.size(); ++i )
                {
                        EXPECT_EQ( vec.at( i ), prefix.element_at( i ) ) ;
                }
        }
}

TEST( VectorTest, CopyConstruct )
{
        uti::vector<         int > vecint( CUSTOM_CAP, CUSTOM_VAL ) ;
        uti::vector< std::string > vecstr( CUSTOM_CAP, std::string( "copy_c_test" ) ) ;

        uti::vector<         int > vecintcopy( vecint ) ;
        uti::vector< std::string > vecstrcopy( vecstr ) ;

        EXPECT_EQ( vecintcopy.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecstrcopy.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecintcopy.   empty(),      false ) ;
        EXPECT_EQ( vecstrcopy.   empty(),      false ) ;
        EXPECT_EQ( vecintcopy.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecstrcopy.capacity(), CUSTOM_CAP ) ;

        EXPECT_EQ( vecint.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecstr.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecint.   empty(),      false ) ;
        EXPECT_EQ( vecstr.   empty(),      false ) ;
        EXPECT_EQ( vecint.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecstr.capacity(), CUSTOM_CAP ) ;

        for( ssize_t i = 0; i < vecintcopy.size(); ++i )
        {
                EXPECT_EQ( vecintcopy.at( i ),    CUSTOM_VAL ) ;
                EXPECT_EQ( vecstrcopy.at( i ), "copy_c_test" ) ;

                EXPECT_EQ( vecintcopy.at( i ), vecint.at( i ) ) ;
                EXPECT_EQ( vecstrcopy.at( i ), vecstr.at( i ) ) ;
        }
}

TEST( VectorTest, MoveConstruct )
{
        uti::vector<         int > vecint( CUSTOM_CAP, CUSTOM_VAL ) ;
        uti::vector< std::string > vecstr( CUSTOM_CAP, std::string( "move_c_test" ) ) ;

        uti::vector<         int > vecintmove( UTI_MOVE( vecint ) ) ;
        uti::vector< std::string > vecstrmove( UTI_MOVE( vecstr ) ) ;

        EXPECT_EQ( vecintmove.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecstrmove.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecintmove.   empty(),      false ) ;
        EXPECT_EQ( vecstrmove.   empty(),      false ) ;
        EXPECT_EQ( vecintmove.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecstrmove.capacity(), CUSTOM_CAP ) ;

        EXPECT_EQ( vecint.    size(),    0 ) ;
        EXPECT_EQ( vecstr.    size(),    0 ) ;
        EXPECT_EQ( vecint.   empty(), true ) ;
        EXPECT_EQ( vecstr.   empty(), true ) ;
        EXPECT_EQ( vecint.capacity(),    0 ) ;
        EXPECT_EQ( vecstr.capacity(),    0 ) ;

        for( ssize_t i = 0; i < vecintmove.size(); ++i )
        {
                EXPECT_EQ( vecintmove.at( i ),    CUSTOM_VAL ) ;
                EXPECT_EQ( vecstrmove.at( i ), "move_c_test" ) ;
        }
}

TEST( VectorTest, CopyAssign )
{
        uti::vector<         int > vecint( CUSTOM_CAP, CUSTOM_VAL ) ;
        uti::vector< std::string > vecstr( CUSTOM_CAP, std::string( "copy_a_test" ) ) ;

        uti::vector<         int > vecintcopy ( CUSTOM_CAP * 2, CUSTOM_VAL * 2 ) ;
        uti::vector< std::string > vecstrcopy0( CUSTOM_CAP    , std::string( "random" ) ) ;
        uti::vector< std::string > vecstrcopy1( CUSTOM_CAP * 2, std::string( "random" ) ) ;
        uti::vector< std::string > vecstrcopy2( CUSTOM_CAP / 2, std::string( "random" ) ) ;

        vecintcopy  = vecint ;
        vecstrcopy0 = vecstr ;
        vecstrcopy1 = vecstr ;
        vecstrcopy2 = vecstr ;

        EXPECT_EQ( vecintcopy .    size(), CUSTOM_CAP     ) ;
        EXPECT_EQ( vecstrcopy0.    size(), CUSTOM_CAP     ) ;
        EXPECT_EQ( vecstrcopy1.    size(), CUSTOM_CAP     ) ;
        EXPECT_EQ( vecstrcopy2.    size(), CUSTOM_CAP     ) ;
        EXPECT_EQ( vecintcopy .   empty(),      false     ) ;
        EXPECT_EQ( vecstrcopy0.   empty(),      false     ) ;
        EXPECT_EQ( vecstrcopy1.   empty(),      false     ) ;
        EXPECT_EQ( vecstrcopy2.   empty(),      false     ) ;
        EXPECT_EQ( vecintcopy .capacity(), CUSTOM_CAP * 2 ) ;
        EXPECT_EQ( vecstrcopy0.capacity(), CUSTOM_CAP     ) ;
        EXPECT_EQ( vecstrcopy1.capacity(), CUSTOM_CAP * 2 ) ;
        EXPECT_EQ( vecstrcopy2.capacity(), CUSTOM_CAP     ) ;

        EXPECT_EQ( vecint.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecstr.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecint.   empty(),      false ) ;
        EXPECT_EQ( vecstr.   empty(),      false ) ;
        EXPECT_EQ( vecint.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecstr.capacity(), CUSTOM_CAP ) ;

        for( ssize_t i = 0; i < vecintcopy.size(); ++i )
        {
                EXPECT_EQ( vecintcopy .at( i ),    CUSTOM_VAL ) ;
                EXPECT_EQ( vecstrcopy0.at( i ), "copy_a_test" ) ;
                EXPECT_EQ( vecstrcopy1.at( i ), "copy_a_test" ) ;
                EXPECT_EQ( vecstrcopy2.at( i ), "copy_a_test" ) ;

                EXPECT_EQ( vecintcopy .at( i ), vecint.at( i ) ) ;
                EXPECT_EQ( vecstrcopy0.at( i ), vecstr.at( i ) ) ;
                EXPECT_EQ( vecstrcopy1.at( i ), vecstr.at( i ) ) ;
                EXPECT_EQ( vecstrcopy2.at( i ), vecstr.at( i ) ) ;
        }
}

TEST( VectorTest, MoveAssign )
{
        uti::vector<         int > vecint ( CUSTOM_CAP, CUSTOM_VAL ) ;
        uti::vector< std::string > vecstr1( CUSTOM_CAP, std::string( "move_a_test" ) ) ;
        uti::vector< std::string > vecstr2( CUSTOM_CAP, std::string( "move_a_test" ) ) ;
        uti::vector< std::string > vecstr3( CUSTOM_CAP, std::string( "move_a_test" ) ) ;

        uti::vector<         int > vecintmove ( CUSTOM_CAP * 2, CUSTOM_VAL * 2 ) ;
        uti::vector< std::string > vecstrmove0( CUSTOM_CAP    , std::string( "random" ) ) ;
        uti::vector< std::string > vecstrmove1( CUSTOM_CAP * 2, std::string( "random" ) ) ;
        uti::vector< std::string > vecstrmove2( CUSTOM_CAP / 2, std::string( "random" ) ) ;

        vecintmove  = UTI_MOVE( vecint  ) ;
        vecstrmove0 = UTI_MOVE( vecstr1 ) ;
        vecstrmove1 = UTI_MOVE( vecstr2 ) ;
        vecstrmove2 = UTI_MOVE( vecstr3 ) ;

        EXPECT_EQ( vecintmove .    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecstrmove0.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecstrmove1.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecstrmove2.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecintmove .   empty(),      false ) ;
        EXPECT_EQ( vecstrmove0.   empty(),      false ) ;
        EXPECT_EQ( vecstrmove1.   empty(),      false ) ;
        EXPECT_EQ( vecstrmove2.   empty(),      false ) ;
        EXPECT_EQ( vecintmove .capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecstrmove0.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecstrmove1.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecstrmove2.capacity(), CUSTOM_CAP ) ;

        EXPECT_EQ( vecint .    size(),    0 ) ;
        EXPECT_EQ( vecstr1.    size(),    0 ) ;
        EXPECT_EQ( vecstr2.    size(),    0 ) ;
        EXPECT_EQ( vecstr3.    size(),    0 ) ;
        EXPECT_EQ( vecint .   empty(), true ) ;
        EXPECT_EQ( vecstr1.   empty(), true ) ;
        EXPECT_EQ( vecstr2.   empty(), true ) ;
        EXPECT_EQ( vecstr3.   empty(), true ) ;
        EXPECT_EQ( vecint .capacity(),    0 ) ;
        EXPECT_EQ( vecstr1.capacity(),    0 ) ;
        EXPECT_EQ( vecstr2.capacity(),    0 ) ;
        EXPECT_EQ( vecstr3.capacity(),    0 ) ;

        for( ssize_t i = 0; i < vecintmove.size(); ++i )
        {
                EXPECT_EQ( vecintmove .at( i ),    CUSTOM_VAL ) ;
                EXPECT_EQ( vecstrmove0.at( i ), "move_a_test" ) ;
                EXPECT_EQ( vecstrmove1.at( i ), "move_a_test" ) ;
                EXPECT_EQ( vecstrmove2.at( i ), "move_a_test" ) ;
        }
}

TEST( VectorTest, At )
{
        uti::vector< int >                               vec1d( CUSTOM_CAP, CUSTOM_VAL ) ;
        uti::vector< uti::vector< int > >                vec2d( CUSTOM_CAP             ) ;
        uti::vector< uti::vector< uti::vector< int > > > vec3d( CUSTOM_CAP             ) ;

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
                EXPECT_EQ( vec1d.at( i ), CUSTOM_VAL ) ;

                for( ssize_t j = 0; j < CUSTOM_CAP; ++j )
                {
                        EXPECT_EQ( vec2d.at( i, j ), vec1d.at( j ) ) ;

                        for( ssize_t k = 0; k < CUSTOM_CAP; ++k )
                        {
                                EXPECT_EQ( vec3d.at( i, j, k ), vec1d.at( k ) ) ;
                        }
                }
        }
}

TEST( VectorTest, PushBack )
{
        uti::vector< int > vec ;

        for( ssize_t i = 0; i < 1024; ++i )
        {
                vec.push_back( i );
        }
        for( ssize_t i = 0; i < 1024; ++i )
        {
                EXPECT_EQ( vec.at( i ), i ) ;
        }
}

TEST( VectorTest, EmplaceBack )
{
        uti::vector< std::string        > vecstr ;
        uti::vector< uti::vector< int > > vec2d  ;

        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                vec2d .emplace_back( CUSTOM_CAP, i ) ;
                vecstr.emplace_back( std::to_string( i ) ) ;
        }
        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                EXPECT_EQ( vecstr.at( i ), std::to_string( i ) ) ;

                for( auto const & val : vec2d.at( i ) )
                {
                        EXPECT_EQ( val, i ) ;
                }
        }
}

TEST( VectorTest, Pop )
{
        uti::vector< int > vec ;

        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                vec.push_back( i ) ;
        }

        EXPECT_EQ( vec. size(), CUSTOM_CAP     ) ;
        EXPECT_EQ( vec.front(),              0 ) ;
        EXPECT_EQ( vec. back(), CUSTOM_CAP - 1 ) ;

        auto val = vec.pop_back_val();

        EXPECT_EQ( val        , CUSTOM_CAP - 1 ) ;
        EXPECT_EQ( vec. size(), CUSTOM_CAP - 1 ) ;
        EXPECT_EQ( vec.front(),              0 ) ;
        EXPECT_EQ( vec. back(), CUSTOM_CAP - 2 ) ;

        val = vec.pop_front_val();

        EXPECT_EQ( val        ,              0 ) ;
        EXPECT_EQ( vec. size(), CUSTOM_CAP - 2 ) ;
        EXPECT_EQ( vec.front(),              1 ) ;
        EXPECT_EQ( vec. back(), CUSTOM_CAP - 2 ) ;
}

TEST( VectorTest, Reserve )
{
        uti::vector< int > vec1               ;
        uti::vector< int > vec2( CUSTOM_CAP ) ;

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

TEST( VectorTest, Shrink )
{
        {
                uti::vector<         int > vecint( CUSTOM_CAP,    CUSTOM_VAL ) ;
                uti::vector< std::string > vecstr( CUSTOM_CAP, "shrink_test" ) ;

                EXPECT_EQ( vecint.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( vecint.capacity(), CUSTOM_CAP ) ;

                EXPECT_EQ( vecstr.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( vecstr.capacity(), CUSTOM_CAP ) ;

                vecint.shrink_size( CUSTOM_CAP / 2 ) ;
                vecstr.shrink_size( CUSTOM_CAP / 2 ) ;

                EXPECT_EQ( vecint.    size(), CUSTOM_CAP / 2 ) ;
                EXPECT_EQ( vecint.capacity(), CUSTOM_CAP     ) ;

                EXPECT_EQ( vecstr.    size(), CUSTOM_CAP / 2 ) ;
                EXPECT_EQ( vecstr.capacity(), CUSTOM_CAP     ) ;
        }
        {
                uti::vector<         int > vecint( CUSTOM_CAP,    CUSTOM_VAL ) ;
                uti::vector< std::string > vecstr( CUSTOM_CAP, "shrink_test" ) ;

                EXPECT_EQ( vecint.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( vecint.capacity(), CUSTOM_CAP ) ;

                EXPECT_EQ( vecstr.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( vecstr.capacity(), CUSTOM_CAP ) ;

                vecint.reserve( CUSTOM_CAP * 2 ) ;
                vecstr.reserve( CUSTOM_CAP * 2 ) ;

                EXPECT_EQ( vecint.    size(), CUSTOM_CAP     ) ;
                EXPECT_EQ( vecint.capacity(), CUSTOM_CAP * 2 ) ;

                EXPECT_EQ( vecstr.    size(), CUSTOM_CAP     ) ;
                EXPECT_EQ( vecstr.capacity(), CUSTOM_CAP * 2 ) ;

                vecint.shrink_to_fit();
                vecstr.shrink_to_fit();

                EXPECT_EQ( vecint.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( vecint.capacity(), CUSTOM_CAP ) ;

                EXPECT_EQ( vecstr.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( vecstr.capacity(), CUSTOM_CAP ) ;
        }
        {
                uti::vector<         int > vecint( CUSTOM_CAP,    CUSTOM_VAL ) ;
                uti::vector< std::string > vecstr( CUSTOM_CAP, "shrink_test" ) ;

                EXPECT_EQ( vecint.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( vecint.capacity(), CUSTOM_CAP ) ;

                EXPECT_EQ( vecstr.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( vecstr.capacity(), CUSTOM_CAP ) ;

                vecint.shrink( CUSTOM_CAP / 2 ) ;
                vecstr.shrink( CUSTOM_CAP / 2 ) ;

                EXPECT_EQ( vecint.    size(), CUSTOM_CAP / 2 ) ;
                EXPECT_EQ( vecint.capacity(), CUSTOM_CAP / 2 ) ;

                EXPECT_EQ( vecstr.    size(), CUSTOM_CAP / 2 ) ;
                EXPECT_EQ( vecstr.capacity(), CUSTOM_CAP / 2 ) ;
        }
}

TEST( VectorTest, Insert )
{
        uti::vector<         int > vecint( CUSTOM_CAP,            0  ) ;
        uti::vector< std::string > vecstr( CUSTOM_CAP, "insert_test" ) ;

        for( ssize_t i = 0; i < vecint.size(); ++i )
        {
                vecint.at( i ) = i ;
        }

        EXPECT_EQ( vecint.size(), CUSTOM_CAP ) ;
        EXPECT_EQ( vecstr.size(), CUSTOM_CAP ) ;

        vecint.insert( 0,         0  ) ;
        vecstr.insert( 0, "inserted" ) ;

        EXPECT_EQ( vecint.size(), CUSTOM_CAP + 1 ) ;
        EXPECT_EQ( vecstr.size(), CUSTOM_CAP + 1 ) ;

        vecint.insert( CUSTOM_CAP / 2,         0  ) ;
        vecstr.insert( CUSTOM_CAP / 2, "inserted" ) ;

        EXPECT_EQ( vecint.size(), CUSTOM_CAP + 2 ) ;
        EXPECT_EQ( vecstr.size(), CUSTOM_CAP + 2 ) ;

        vecint.insert( vecint.size(),         0  ) ;
        vecstr.insert( vecstr.size(), "inserted" ) ;

        EXPECT_EQ( vecint.size(), CUSTOM_CAP + 3 ) ;
        EXPECT_EQ( vecstr.size(), CUSTOM_CAP + 3 ) ;

        for( ssize_t i = 0; i < vecint.size(); ++i )
        {
                if( i == 0 || i == CUSTOM_CAP / 2 || i == vecint.size() - 1 )
                {
                        EXPECT_EQ( vecint.at( i ),         0  ) ;
                        EXPECT_EQ( vecstr.at( i ), "inserted" ) ;
                }
                else if( i < CUSTOM_CAP / 2 )
                {
                        EXPECT_EQ( vecint.at( i ),        i - 1  ) ;
                        EXPECT_EQ( vecstr.at( i ), "insert_test" ) ;
                }
                else
                {
                        EXPECT_EQ( vecint.at( i ),        i - 2  ) ;
                        EXPECT_EQ( vecstr.at( i ), "insert_test" ) ;
                }
        }
}

TEST( VectorTest, Erase )
{
        {
                uti::vector<         int > vecint( CUSTOM_CAP,   CUSTOM_VAL ) ;
                uti::vector< std::string > vecstr( CUSTOM_CAP, "erase_test" ) ;

                EXPECT_EQ( vecint.size(), CUSTOM_CAP ) ;
                EXPECT_EQ( vecstr.size(), CUSTOM_CAP ) ;

                vecint.erase( 0 ) ;
                vecstr.erase( 0 ) ;

                EXPECT_EQ( vecint.size(), CUSTOM_CAP - 1 ) ;
                EXPECT_EQ( vecstr.size(), CUSTOM_CAP - 1 ) ;

                vecint.erase( vecint.size() / 2 ) ;
                vecstr.erase( vecstr.size() / 2 ) ;

                EXPECT_EQ( vecint.size(), CUSTOM_CAP - 2 ) ;
                EXPECT_EQ( vecstr.size(), CUSTOM_CAP - 2 ) ;

                vecint.erase( vecint.size() - 1 ) ;
                vecstr.erase( vecstr.size() - 1 ) ;

                EXPECT_EQ( vecint.size(), CUSTOM_CAP - 3 ) ;
                EXPECT_EQ( vecstr.size(), CUSTOM_CAP - 3 ) ;
        }
        {
                uti::vector<         int > vecint( CUSTOM_CAP,   CUSTOM_VAL ) ;
                uti::vector< std::string > vecstr( CUSTOM_CAP, "erase_test" ) ;

                EXPECT_EQ( vecint.size(), CUSTOM_CAP ) ;
                EXPECT_EQ( vecstr.size(), CUSTOM_CAP ) ;

                vecint.erase_stable( 0 ) ;
                vecstr.erase_stable( 0 ) ;

                EXPECT_EQ( vecint.size(), CUSTOM_CAP - 1 ) ;
                EXPECT_EQ( vecstr.size(), CUSTOM_CAP - 1 ) ;

                vecint.erase_stable( vecint.size() / 2 ) ;
                vecstr.erase_stable( vecstr.size() / 2 ) ;

                EXPECT_EQ( vecint.size(), CUSTOM_CAP - 2 ) ;
                EXPECT_EQ( vecstr.size(), CUSTOM_CAP - 2 ) ;

                vecint.erase_stable( vecint.size() - 1 ) ;
                vecstr.erase_stable( vecstr.size() - 1 ) ;

                EXPECT_EQ( vecint.size(), CUSTOM_CAP - 3 ) ;
                EXPECT_EQ( vecstr.size(), CUSTOM_CAP - 3 ) ;
        }
}

TEST( VectorTest, Clear )
{
        uti::vector<         int > vec1                                        ;
        uti::vector<         int > vec2( CUSTOM_CAP,            CUSTOM_VAL   ) ;
        uti::vector< std::string > vec3( CUSTOM_CAP, std::string( "random" ) ) ;

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

TEST( VectorTest, Iterate )
{
        uti::vector< int > vec( CUSTOM_CAP, CUSTOM_VAL ) ;

        for( auto const & val : vec )
        {
                EXPECT_EQ( val, CUSTOM_VAL ) ;
        }
}

TEST( VectorTest, NoDoubleFree )
{
        uti::vector< uti::vector< std::string > > vec2d;

        for( int i = 0; i < 4; ++i )
        {
                uti::vector< std::string > vec1d;
                for( int i = 0; i < 4; ++i )
                {
                        vec1d.insert( 0, std::to_string( i ) ) ;
                }
                vec2d.insert( 0, UTI_MOVE( vec1d ) ) ;
        }
        uti::vector< uti::vector< std::string > > vec2d2;

        for( int i = 0; i < 4; ++i )
        {
                if( i % 2 == 0 )
                {
                        vec2d2.insert( 0, UTI_MOVE( vec2d.at( i ) ) ) ;
                }
                else
                {
                        vec2d2.insert( 0, vec2d.at( i ) ) ;
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
        EXPECT_EQ( dummy_counter, 16 ) ;
}
