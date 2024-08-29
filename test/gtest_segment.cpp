//
//
//      uti
//      gtest_segment.cpp
//

#include "gtest_segment.hpp"


TEST( SegmentTreeTest, DefaultConstruct )
{
        uti::segment_tree<         int > segtreeint ;
        uti::segment_tree< std::string > segtreestr ;

        EXPECT_EQ( segtreeint.    size(),    0 ) ;
        EXPECT_EQ( segtreestr.    size(),    0 ) ;
        EXPECT_EQ( segtreeint.   empty(), true ) ;
        EXPECT_EQ( segtreestr.   empty(), true ) ;
        EXPECT_EQ( segtreeint.capacity(),    0 ) ;
        EXPECT_EQ( segtreestr.capacity(),    0 ) ;
}

TEST( SegmentTreeTest, ReserveConstruct )
{
        uti::segment_tree<         int > segtreeint( CUSTOM_CAP ) ;
        uti::segment_tree< std::string > segtreestr( CUSTOM_CAP ) ;

        EXPECT_EQ( segtreeint.    size(),          0 ) ;
        EXPECT_EQ( segtreestr.    size(),          0 ) ;
        EXPECT_EQ( segtreeint.   empty(),       true ) ;
        EXPECT_EQ( segtreestr.   empty(),       true ) ;
        EXPECT_EQ( segtreeint.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreestr.capacity(), CUSTOM_CAP ) ;
}

TEST( SegmentTreeTest, FillConstruct )
{
        uti::segment_tree<         int > segtreeint( CUSTOM_CAP, CUSTOM_VAL ) ;
        uti::segment_tree< std::string > segtreestr( CUSTOM_CAP, std::string( "fill_test" ) ) ;

        EXPECT_EQ( segtreeint.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreestr.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreeint.   empty(),      false ) ;
        EXPECT_EQ( segtreestr.   empty(),      false ) ;
        EXPECT_EQ( segtreeint.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreestr.capacity(), CUSTOM_CAP ) ;

        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                EXPECT_EQ( segtreeint.at( i ), CUSTOM_VAL ) ;
                EXPECT_EQ( segtreestr.at( i ).starts_with( "fill_test" ), true ) ;
        }
}

TEST( SegmentTreeTest, IteratorConstruct )
{
        {
                int arr[] = { 0, 1, 2, 3 } ;

                int * begin = arr ;
                int *   end = arr + ( sizeof( arr ) / sizeof( int ) ) ;

                uti::segment_tree< int > segtree( begin, end ) ;

                for( ssize_t i = 0; i < 4; ++i )
                {
                        EXPECT_EQ( segtree.at( i ), i ) ;
                }
        }
        {
                uti::vector< int > vec( 4, 1 ) ;

                uti::segment_tree< int > segtree( vec.begin(), vec.end() ) ;

                for( ssize_t i = 0; i < vec.size(); ++i )
                {
                        EXPECT_EQ( vec.at( i ), segtree.at( i ) ) ;
                }
        }
        {
                uti::prefix_array< int > prefix( 4, 1 ) ;

                uti::segment_tree< int > segtree( prefix.begin(), prefix.end() ) ;

                for( ssize_t i = 0; i < prefix.size(); ++i )
                {
                        EXPECT_EQ( segtree.at( i ), prefix.element_at( i ) ) ;
                }
        }
        {
                uti::segment_tree< int > segtree( 4, 1 ) ;

                uti::segment_tree< int > segtree2( segtree.begin(), segtree.end() ) ;

                for( ssize_t i = 0; i < segtree.size(); ++i )
                {
                        EXPECT_EQ( segtree.at( i ), segtree2.at( i ) ) ;
                }
        }
}

TEST( SegmentTreeTest, CopyConstruct )
{
        uti::segment_tree<         int > segtreeint( CUSTOM_CAP, CUSTOM_VAL ) ;
        uti::segment_tree< std::string > segtreestr( CUSTOM_CAP, std::string( "copy_c_test" ) ) ;

        uti::segment_tree<         int > segtreeintcopy( segtreeint ) ;
        uti::segment_tree< std::string > segtreestrcopy( segtreestr ) ;

        EXPECT_EQ( segtreeintcopy.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreestrcopy.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreeintcopy.   empty(),      false ) ;
        EXPECT_EQ( segtreestrcopy.   empty(),      false ) ;
        EXPECT_EQ( segtreeintcopy.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreestrcopy.capacity(), CUSTOM_CAP ) ;

        EXPECT_EQ( segtreeint.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreestr.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreeint.   empty(),      false ) ;
        EXPECT_EQ( segtreestr.   empty(),      false ) ;
        EXPECT_EQ( segtreeint.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreestr.capacity(), CUSTOM_CAP ) ;

        for( ssize_t i = 0; i < segtreeintcopy.size(); ++i )
        {
                EXPECT_EQ( segtreeintcopy.at( i ), CUSTOM_VAL ) ;
                EXPECT_EQ( segtreestrcopy.at( i ).starts_with( "copy_c_test" ), true ) ;

                EXPECT_EQ( segtreeintcopy.at( i ), segtreeint.at( i ) ) ;
                EXPECT_EQ( segtreestrcopy.at( i ), segtreestr.at( i ) ) ;
        }
}

TEST( SegmentTreeTest, MoveConstruct )
{
        uti::segment_tree<         int > segtreeint( CUSTOM_CAP, CUSTOM_VAL ) ;
        uti::segment_tree< std::string > segtreestr( CUSTOM_CAP, std::string( "move_c_test" ) ) ;

        uti::segment_tree<         int > segtreeintmove( UTI_MOVE( segtreeint ) ) ;
        uti::segment_tree< std::string > segtreestrmove( UTI_MOVE( segtreestr ) ) ;

        EXPECT_EQ( segtreeintmove.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreestrmove.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreeintmove.   empty(),      false ) ;
        EXPECT_EQ( segtreestrmove.   empty(),      false ) ;
        EXPECT_EQ( segtreeintmove.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreestrmove.capacity(), CUSTOM_CAP ) ;

        EXPECT_EQ( segtreeint.    size(),    0 ) ;
        EXPECT_EQ( segtreestr.    size(),    0 ) ;
        EXPECT_EQ( segtreeint.   empty(), true ) ;
        EXPECT_EQ( segtreestr.   empty(), true ) ;
        EXPECT_EQ( segtreeint.capacity(),    0 ) ;
        EXPECT_EQ( segtreestr.capacity(),    0 ) ;

        for( ssize_t i = 0; i < segtreeintmove.size(); ++i )
        {
                EXPECT_EQ( segtreeintmove.at( i ), CUSTOM_VAL ) ;
                EXPECT_EQ( segtreestrmove.at( i ).starts_with( "move_c_test" ), true ) ;
        }
}

TEST( SegmentTreeTest, CopyAssign )
{
        uti::segment_tree<         int > segtreeint( CUSTOM_CAP, CUSTOM_VAL ) ;
        uti::segment_tree< std::string > segtreestr( CUSTOM_CAP, std::string( "copy_a_test" ) ) ;

        uti::segment_tree<         int > segtreeintcopy ( CUSTOM_CAP * 2, CUSTOM_VAL * 2 ) ;
        uti::segment_tree< std::string > segtreestrcopy0( CUSTOM_CAP    , std::string( "random" ) ) ;
        uti::segment_tree< std::string > segtreestrcopy1( CUSTOM_CAP * 2, std::string( "random" ) ) ;
        uti::segment_tree< std::string > segtreestrcopy2( CUSTOM_CAP / 2, std::string( "random" ) ) ;

        segtreeintcopy  = segtreeint ;
        segtreestrcopy0 = segtreestr ;
        segtreestrcopy1 = segtreestr ;
        segtreestrcopy2 = segtreestr ;

        EXPECT_EQ( segtreeintcopy .    size(), CUSTOM_CAP     ) ;
        EXPECT_EQ( segtreestrcopy0.    size(), CUSTOM_CAP     ) ;
        EXPECT_EQ( segtreestrcopy1.    size(), CUSTOM_CAP     ) ;
        EXPECT_EQ( segtreestrcopy2.    size(), CUSTOM_CAP     ) ;
        EXPECT_EQ( segtreeintcopy .   empty(),      false     ) ;
        EXPECT_EQ( segtreestrcopy0.   empty(),      false     ) ;
        EXPECT_EQ( segtreestrcopy1.   empty(),      false     ) ;
        EXPECT_EQ( segtreestrcopy2.   empty(),      false     ) ;
        EXPECT_EQ( segtreeintcopy .capacity(), CUSTOM_CAP * 2 ) ;
        EXPECT_EQ( segtreestrcopy0.capacity(), CUSTOM_CAP     ) ;
        EXPECT_EQ( segtreestrcopy1.capacity(), CUSTOM_CAP * 2 ) ;
        EXPECT_EQ( segtreestrcopy2.capacity(), CUSTOM_CAP     ) ;

        EXPECT_EQ( segtreeint.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreestr.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreeint.   empty(),      false ) ;
        EXPECT_EQ( segtreestr.   empty(),      false ) ;
        EXPECT_EQ( segtreeint.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreestr.capacity(), CUSTOM_CAP ) ;

        for( ssize_t i = 0; i < segtreeintcopy.size(); ++i )
        {
                EXPECT_EQ( segtreeintcopy .at( i ), CUSTOM_VAL ) ;
                EXPECT_EQ( segtreestrcopy0.at( i ).starts_with( "copy_a_test" ), true ) ;
                EXPECT_EQ( segtreestrcopy1.at( i ).starts_with( "copy_a_test" ), true ) ;
                EXPECT_EQ( segtreestrcopy2.at( i ).starts_with( "copy_a_test" ), true ) ;

                EXPECT_EQ( segtreeintcopy .at( i ), segtreeint.at( i ) ) ;
                EXPECT_EQ( segtreestrcopy0.at( i ), segtreestr.at( i ) ) ;
                EXPECT_EQ( segtreestrcopy1.at( i ), segtreestr.at( i ) ) ;
                EXPECT_EQ( segtreestrcopy2.at( i ), segtreestr.at( i ) ) ;
        }
}

TEST( SegmentTreeTest, MoveAssign )
{
        uti::segment_tree<         int > segtreeint ( CUSTOM_CAP, CUSTOM_VAL ) ;
        uti::segment_tree< std::string > segtreestr1( CUSTOM_CAP, std::string( "move_a_test" ) ) ;
        uti::segment_tree< std::string > segtreestr2( CUSTOM_CAP, std::string( "move_a_test" ) ) ;
        uti::segment_tree< std::string > segtreestr3( CUSTOM_CAP, std::string( "move_a_test" ) ) ;

        uti::segment_tree<         int > segtreeintmove ( CUSTOM_CAP * 2, CUSTOM_VAL * 2 ) ;
        uti::segment_tree< std::string > segtreestrmove0( CUSTOM_CAP    , std::string( "random" ) ) ;
        uti::segment_tree< std::string > segtreestrmove1( CUSTOM_CAP * 2, std::string( "random" ) ) ;
        uti::segment_tree< std::string > segtreestrmove2( CUSTOM_CAP / 2, std::string( "random" ) ) ;

        segtreeintmove  = UTI_MOVE( segtreeint  ) ;
        segtreestrmove0 = UTI_MOVE( segtreestr1 ) ;
        segtreestrmove1 = UTI_MOVE( segtreestr2 ) ;
        segtreestrmove2 = UTI_MOVE( segtreestr3 ) ;

        EXPECT_EQ( segtreeintmove .    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreestrmove0.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreestrmove1.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreestrmove2.    size(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreeintmove .   empty(),      false ) ;
        EXPECT_EQ( segtreestrmove0.   empty(),      false ) ;
        EXPECT_EQ( segtreestrmove1.   empty(),      false ) ;
        EXPECT_EQ( segtreestrmove2.   empty(),      false ) ;
        EXPECT_EQ( segtreeintmove .capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreestrmove0.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreestrmove1.capacity(), CUSTOM_CAP ) ;
        EXPECT_EQ( segtreestrmove2.capacity(), CUSTOM_CAP ) ;

        EXPECT_EQ( segtreeint .    size(),    0 ) ;
        EXPECT_EQ( segtreestr1.    size(),    0 ) ;
        EXPECT_EQ( segtreestr2.    size(),    0 ) ;
        EXPECT_EQ( segtreestr3.    size(),    0 ) ;
        EXPECT_EQ( segtreeint .   empty(), true ) ;
        EXPECT_EQ( segtreestr1.   empty(), true ) ;
        EXPECT_EQ( segtreestr2.   empty(), true ) ;
        EXPECT_EQ( segtreestr3.   empty(), true ) ;
        EXPECT_EQ( segtreeint .capacity(),    0 ) ;
        EXPECT_EQ( segtreestr1.capacity(),    0 ) ;
        EXPECT_EQ( segtreestr2.capacity(),    0 ) ;
        EXPECT_EQ( segtreestr3.capacity(),    0 ) ;

        for( ssize_t i = 0; i < segtreeintmove.size(); ++i )
        {
                EXPECT_EQ( segtreeintmove .at( i ), CUSTOM_VAL ) ;
                EXPECT_EQ( segtreestrmove0.at( i ).starts_with( "move_a_test" ), true ) ;
                EXPECT_EQ( segtreestrmove1.at( i ).starts_with( "move_a_test" ), true ) ;
                EXPECT_EQ( segtreestrmove2.at( i ).starts_with( "move_a_test" ), true ) ;
        }
}

TEST( SegmentTreeTest, At )
{
        uti::segment_tree< int >                                           vec1d( CUSTOM_CAP, CUSTOM_VAL ) ;
        uti::segment_tree< uti::segment_tree< int > >                      vec2d( CUSTOM_CAP             ) ;
        uti::segment_tree< uti::segment_tree< uti::segment_tree< int > > > vec3d( CUSTOM_CAP             ) ;

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

TEST( SegmentTreeTest, PushBack )
{
        uti::segment_tree< int > vec ;

        for( ssize_t i = 0; i < 1024; ++i )
        {
                vec.push_back( i );
        }
        for( ssize_t i = 0; i < 1024; ++i )
        {
                EXPECT_EQ( vec.at( i ), i ) ;
        }
}

TEST( SegmentTreeTest, EmplaceBack )
{
        uti::segment_tree< std::string              > segtreestr ;
        uti::segment_tree< uti::segment_tree< int > > segtree2d  ;

        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                segtree2d .emplace_back( CUSTOM_CAP, i ) ;
                segtreestr.emplace_back( std::to_string( i ) ) ;
        }
        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                EXPECT_EQ( segtreestr.at( i ).starts_with( std::to_string( i ) ), true ) ;

                for( auto const & val : segtree2d.at( i ) )
                {
                        EXPECT_EQ( val, i ) ;
                }
        }
}

TEST( SegmentTreeTest, Pop )
{
        uti::segment_tree< int > vec ;

        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                vec.push_back( i + 1 ) ;
        }

        EXPECT_EQ( vec. size(), CUSTOM_CAP ) ;
        EXPECT_EQ( vec.front(),          1 ) ;
        EXPECT_EQ( vec. back(), CUSTOM_CAP ) ;

        vec.pop_back();

        EXPECT_EQ( vec. size(), CUSTOM_CAP - 1 ) ;
        EXPECT_EQ( vec.front(),              1 ) ;
        EXPECT_EQ( vec. back(), CUSTOM_CAP - 1 ) ;

        vec.pop_front();

        EXPECT_EQ( vec. size(), CUSTOM_CAP - 2 ) ;
        EXPECT_EQ( vec.front(),              2 ) ;
        EXPECT_EQ( vec. back(), CUSTOM_CAP - 1 ) ;
}

TEST( SegmentTreeTest, Reserve )
{
        uti::segment_tree< int > vec1               ;
        uti::segment_tree< int > vec2( CUSTOM_CAP ) ;

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

TEST( SegmentTreeTest, Shrink )
{
        {
                uti::segment_tree<         int > segtreeint( CUSTOM_CAP,    CUSTOM_VAL ) ;
                uti::segment_tree< std::string > segtreestr( CUSTOM_CAP, "shrink_test" ) ;

                EXPECT_EQ( segtreeint.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( segtreeint.capacity(), CUSTOM_CAP ) ;

                EXPECT_EQ( segtreestr.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( segtreestr.capacity(), CUSTOM_CAP ) ;

                segtreeint.shrink_size( CUSTOM_CAP / 2 ) ;
                segtreestr.shrink_size( CUSTOM_CAP / 2 ) ;

                EXPECT_EQ( segtreeint.    size(), CUSTOM_CAP / 2 ) ;
                EXPECT_EQ( segtreeint.capacity(), CUSTOM_CAP     ) ;

                EXPECT_EQ( segtreestr.    size(), CUSTOM_CAP / 2 ) ;
                EXPECT_EQ( segtreestr.capacity(), CUSTOM_CAP     ) ;
        }
        {
                uti::segment_tree<         int > segtreeint( CUSTOM_CAP,    CUSTOM_VAL ) ;
                uti::segment_tree< std::string > segtreestr( CUSTOM_CAP, "shrink_test" ) ;

                EXPECT_EQ( segtreeint.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( segtreeint.capacity(), CUSTOM_CAP ) ;

                EXPECT_EQ( segtreestr.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( segtreestr.capacity(), CUSTOM_CAP ) ;

                segtreeint.reserve( CUSTOM_CAP * 2 ) ;
                segtreestr.reserve( CUSTOM_CAP * 2 ) ;

                EXPECT_EQ( segtreeint.    size(), CUSTOM_CAP     ) ;
                EXPECT_EQ( segtreeint.capacity(), CUSTOM_CAP * 2 ) ;

                EXPECT_EQ( segtreestr.    size(), CUSTOM_CAP     ) ;
                EXPECT_EQ( segtreestr.capacity(), CUSTOM_CAP * 2 ) ;

                segtreeint.shrink_to_fit();
                segtreestr.shrink_to_fit();

                EXPECT_EQ( segtreeint.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( segtreeint.capacity(), CUSTOM_CAP ) ;

                EXPECT_EQ( segtreestr.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( segtreestr.capacity(), CUSTOM_CAP ) ;
        }
        {
                uti::segment_tree<         int > segtreeint( CUSTOM_CAP,    CUSTOM_VAL ) ;
                uti::segment_tree< std::string > segtreestr( CUSTOM_CAP, "shrink_test" ) ;

                EXPECT_EQ( segtreeint.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( segtreeint.capacity(), CUSTOM_CAP ) ;

                EXPECT_EQ( segtreestr.    size(), CUSTOM_CAP ) ;
                EXPECT_EQ( segtreestr.capacity(), CUSTOM_CAP ) ;

                segtreeint.shrink( CUSTOM_CAP / 2 ) ;
                segtreestr.shrink( CUSTOM_CAP / 2 ) ;

                EXPECT_EQ( segtreeint.    size(), CUSTOM_CAP / 2 ) ;
                EXPECT_EQ( segtreeint.capacity(), CUSTOM_CAP / 2 ) ;

                EXPECT_EQ( segtreestr.    size(), CUSTOM_CAP / 2 ) ;
                EXPECT_EQ( segtreestr.capacity(), CUSTOM_CAP / 2 ) ;
        }
}

TEST( SegmentTreeTest, Insert )
{
        uti::segment_tree<         int > segint( CUSTOM_CAP,            0  ) ;
        uti::segment_tree< std::string > segstr( CUSTOM_CAP, "insert_test" ) ;

        for( ssize_t i = 0; i < segint.size(); ++i )
        {
                segint.at( i ) = i ;
        }

        EXPECT_EQ( segint.size(), CUSTOM_CAP ) ;
        EXPECT_EQ( segstr.size(), CUSTOM_CAP ) ;

        segint.insert( 0,         0  ) ;
        segstr.insert( 0, "inserted" ) ;

        EXPECT_EQ( segint.size(), CUSTOM_CAP + 1 ) ;
        EXPECT_EQ( segstr.size(), CUSTOM_CAP + 1 ) ;

        segint.insert( CUSTOM_CAP / 2,         0  ) ;
        segstr.insert( CUSTOM_CAP / 2, "inserted" ) ;

        EXPECT_EQ( segint.size(), CUSTOM_CAP + 2 ) ;
        EXPECT_EQ( segstr.size(), CUSTOM_CAP + 2 ) ;

        segint.insert( segint.size(),         0  ) ;
        segstr.insert( segstr.size(), "inserted" ) ;

        EXPECT_EQ( segint.size(), CUSTOM_CAP + 3 ) ;
        EXPECT_EQ( segstr.size(), CUSTOM_CAP + 3 ) ;

        for( ssize_t i = 0; i < segint.size(); ++i )
        {
                if( i == 0 || i == CUSTOM_CAP / 2 || i == segint.size() - 1 )
                {
                        EXPECT_EQ( segint.at( i ),         0  ) ;
                        EXPECT_EQ( segstr.at( i ), "inserted" ) ;
                }
                else if( i < CUSTOM_CAP / 2 )
                {
                        EXPECT_EQ( segint.at( i ),        i - 1  ) ;
                        EXPECT_EQ( segstr.at( i ), "insert_test" ) ;
                }
                else
                {
                        EXPECT_EQ( segint.at( i ),        i - 2  ) ;
                        EXPECT_EQ( segstr.at( i ), "insert_test" ) ;
                }
        }
}

TEST( SegmentTreeTest, Erase )
{
        {
                uti::segment_tree<         int > segtreeint( CUSTOM_CAP,   CUSTOM_VAL ) ;
                uti::segment_tree< std::string > segtreestr( CUSTOM_CAP, "erase_test" ) ;

                EXPECT_EQ( segtreeint.size(), CUSTOM_CAP ) ;
                EXPECT_EQ( segtreestr.size(), CUSTOM_CAP ) ;

                segtreeint.erase( 0 ) ;
                segtreestr.erase( 0 ) ;

                EXPECT_EQ( segtreeint.size(), CUSTOM_CAP - 1 ) ;
                EXPECT_EQ( segtreestr.size(), CUSTOM_CAP - 1 ) ;

                segtreeint.erase( segtreeint.size() / 2 ) ;
                segtreestr.erase( segtreestr.size() / 2 ) ;

                EXPECT_EQ( segtreeint.size(), CUSTOM_CAP - 2 ) ;
                EXPECT_EQ( segtreestr.size(), CUSTOM_CAP - 2 ) ;

                segtreeint.erase( segtreeint.size() - 1 ) ;
                segtreestr.erase( segtreestr.size() - 1 ) ;

                EXPECT_EQ( segtreeint.size(), CUSTOM_CAP - 3 ) ;
                EXPECT_EQ( segtreestr.size(), CUSTOM_CAP - 3 ) ;
        }
        {
                uti::segment_tree<         int > segtreeint( CUSTOM_CAP,   CUSTOM_VAL ) ;
                uti::segment_tree< std::string > segtreestr( CUSTOM_CAP, "erase_test" ) ;

                EXPECT_EQ( segtreeint.size(), CUSTOM_CAP ) ;
                EXPECT_EQ( segtreestr.size(), CUSTOM_CAP ) ;

                segtreeint.erase_stable( 0 ) ;
                segtreestr.erase_stable( 0 ) ;

                EXPECT_EQ( segtreeint.size(), CUSTOM_CAP - 1 ) ;
                EXPECT_EQ( segtreestr.size(), CUSTOM_CAP - 1 ) ;

                segtreeint.erase_stable( segtreeint.size() / 2 ) ;
                segtreestr.erase_stable( segtreestr.size() / 2 ) ;

                EXPECT_EQ( segtreeint.size(), CUSTOM_CAP - 2 ) ;
                EXPECT_EQ( segtreestr.size(), CUSTOM_CAP - 2 ) ;

                segtreeint.erase_stable( segtreeint.size() - 1 ) ;
                segtreestr.erase_stable( segtreestr.size() - 1 ) ;

                EXPECT_EQ( segtreeint.size(), CUSTOM_CAP - 3 ) ;
                EXPECT_EQ( segtreestr.size(), CUSTOM_CAP - 3 ) ;
        }
}

TEST( SegmentTreeTest, Clear )
{
        uti::segment_tree<         int > vec1                                        ;
        uti::segment_tree<         int > vec2( CUSTOM_CAP,            CUSTOM_VAL   ) ;
        uti::segment_tree< std::string > vec3( CUSTOM_CAP, std::string( "random" ) ) ;

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

TEST( SegmentTreeTest, Iterate )
{
        uti::segment_tree< int > vec( CUSTOM_CAP, CUSTOM_VAL ) ;

        for( auto const & val : vec )
        {
                EXPECT_EQ( val, CUSTOM_VAL ) ;
        }
}

TEST( SegmentTreeTest, NoDoubleFree )
{
        uti::segment_tree< uti::segment_tree< std::string > > segtree2d;

        for( int i = 0; i < 4; ++i )
        {
                uti::segment_tree< std::string > segtree1d;
                for( int i = 0; i < 4; ++i )
                {
                        segtree1d.insert( 0, std::to_string( i ) );
                }
                segtree2d.insert( 0, UTI_MOVE( segtree1d ) );
        }
        uti::segment_tree< uti::segment_tree< std::string > > vec2d2;

        for( int i = 0; i < 4; ++i )
        {
                if( i % 2 == 0 )
                {
                        vec2d2.insert( 0, UTI_MOVE( segtree2d.at( i ) ) );
                }
                else
                {
                        vec2d2.insert( 0, segtree2d.at( i ) );
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
        EXPECT_EQ( dummy_counter, 4 * 4 ) ;
}

TEST( SegmentTreeTest, Range )
{
        uti::segment_tree< int, uti::compare::sum > segtree( 1024, 1 ) ;

        for( int i = 0; i < segtree.size(); ++i )
        {
                for( int j = i; j < segtree.size(); ++j )
                {
                        EXPECT_EQ( segtree.range( i, j ), j - i + 1 ) ;
                }
        }
}

TEST( SegmentTreeTest, Comparators )
{
        EXPECT_EQ( true, true ) ;
}
