//
//
//      uti.test
//      segment_tree.test.cxx
//

#include <snitch/snitch.hpp>

#include "uti.test.hxx"

#include <uti/container/prefix_array.hxx>
#include <uti/container/segment_tree.hxx>

#define CUSTOM_CAP_OLD CUSTOM_CAP
#undef  CUSTOM_CAP
#define CUSTOM_CAP 4


template< typename T >
using container_type = uti::segment_tree< T, uti::compare::sum > ;


TEMPLATE_LIST_TEST_CASE( "segment::ctor_default", "[segment][ctor][ctor_default]", trivial_types )
{
        constexpr auto segment = []{ return container_type< TestType >() ; } ;

        CONSTEXPR_CHECK( segment().    size() ==    0 ) ;
        CONSTEXPR_CHECK( segment().   empty() == true ) ;
        CONSTEXPR_CHECK( segment().capacity() ==    0 ) ;
}

TEMPLATE_LIST_TEST_CASE( "segment::ctor_reserve", "[segment][ctor][ctor_reserve]", trivial_types )
{
        constexpr auto segment = []{ return container_type< TestType >( CUSTOM_CAP ) ; } ;

        CONSTEXPR_CHECK( segment().    size() ==          0 ) ;
        CONSTEXPR_CHECK( segment().   empty() ==       true ) ;
        CONSTEXPR_CHECK( segment().capacity() == CUSTOM_CAP ) ;
}

TEMPLATE_LIST_TEST_CASE( "segment::ctor_fill", "[segment][ctor][ctor_fill]", trivial_types )
{
        constexpr auto segment = []{ return container_type< TestType >( CUSTOM_CAP, 1 ) ; } ;

        CONSTEXPR_CHECK( segment().    size() == CUSTOM_CAP ) ;
        CONSTEXPR_CHECK( segment().   empty() ==      false ) ;
        CONSTEXPR_CHECK( segment().capacity() == CUSTOM_CAP ) ;

        if constexpr( uti::meta::equality_comparable< TestType > )
        {
                INFO( "segment::ctor_fill::equal_elements" ) ;
                CONSTEXPR_CHECK( []
                {
                container_type< TestType > vec( CUSTOM_CAP, 1 ) ;

                for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
                {
                        if( vec.at( i ) != 1 ) return false ;
                }
                return true ;
                }() ) ;
        }
}

TEMPLATE_LIST_TEST_CASE( "segment::ctor_iter", "[segment][ctor][ctor_iter]", trivial_types )
{
        {
                INFO( "segment::ctor_iter::c_style_array" ) ;
                CONSTEXPR_CHECK( []
                {
                TestType arr[] = { 1, 1, 1, 1 } ;

                TestType * begin = arr ;
                TestType *   end = arr + ( sizeof( arr ) / sizeof( TestType ) ) ;

                container_type< TestType > vec( begin, end ) ;

                if( vec.size() != 4 ) return false ;

                if constexpr( uti::meta::equality_comparable< TestType > )
                {
                        for( ssize_t i = 0; i < 4; ++i )
                        {
                                if( vec.at( i ) != arr[ i ] ) return false ;
                        }
                }
                return true ;
                }() ) ;
        }
        {
                INFO( "segment::ctor_iter::vector" ) ;
                CONSTEXPR_CHECK( []
                {
                uti::vector< TestType > vec( 4, 1 ) ;

                container_type< TestType > vec2( vec.begin(), vec.end() ) ;

                if( vec.size() != 4 ) return false ;

                if constexpr( uti::meta::equality_comparable< TestType > )
                {
                        for( ssize_t i = 0; i < vec.size(); ++i )
                        {
                                if( vec.at( i ) != vec2.at( i ) ) return false ;
                        }
                }
                return true ;
                }() ) ;
        }
        {
                INFO( "segment::ctor_iter::prefix_array" ) ;
                CONSTEXPR_CHECK( []
                {
                uti::prefix_array< int > prefix( 4, 1 ) ;

                container_type< int > vec( prefix.begin(), prefix.end() ) ;

                if( vec.size() != 4 ) return false ;

                if constexpr( uti::meta::equality_comparable< TestType > )
                {
                        for( ssize_t i = 0; i < prefix.size(); ++i )
                        {
                                if( vec.at( i ) != prefix.element_at( i ) ) return false ;
                        }
                }
                return true ;
                }() ) ;
        }
}

TEMPLATE_LIST_TEST_CASE( "segment::ctor_copy", "[segment][ctor][ctor_copy]", trivial_types )
{
        constexpr auto segment = []{ container_type< TestType > vec( CUSTOM_CAP, 1 ) ; return uti::segment_tree( vec ) ; } ;

        CONSTEXPR_CHECK( segment().    size() == CUSTOM_CAP ) ;
        CONSTEXPR_CHECK( segment().   empty() ==      false ) ;
        CONSTEXPR_CHECK( segment().capacity() == CUSTOM_CAP ) ;

        if constexpr( uti::meta::equality_comparable< TestType > )
        {
                INFO( "segment::ctor_copy::equal_elements" ) ;
                CONSTEXPR_CHECK( [ & ]
                {
                auto vec_copy = segment() ;
                for( ssize_t i = 0; i < vec_copy.size(); ++i )
                {
                        if( vec_copy.at( i ) != 1 ) return false ;
                }
                return true ;
                }() ) ;
        }
}

TEMPLATE_LIST_TEST_CASE( "segment::ctor_move", "[segment][ctor][ctor_move]", trivial_types )
{
        constexpr auto moved_to   = []{ container_type< TestType > vec( CUSTOM_CAP, 1 ) ; return uti::segment_tree( UTI_MOVE( vec ) ) ; } ;
        constexpr auto moved_from = []{ container_type< TestType > vec( CUSTOM_CAP, 1 ) ; uti::segment_tree move( UTI_MOVE( vec ) ) ; return vec ; } ;

        CONSTEXPR_CHECK( moved_to().    size() == CUSTOM_CAP ) ;
        CONSTEXPR_CHECK( moved_to().   empty() ==      false ) ;
        CONSTEXPR_CHECK( moved_to().capacity() == CUSTOM_CAP ) ;

        CONSTEXPR_CHECK( moved_from().    size() ==    0 ) ;
        CONSTEXPR_CHECK( moved_from().   empty() == true ) ;
        CONSTEXPR_CHECK( moved_from().capacity() ==    0 ) ;

        if constexpr( uti::meta::equality_comparable< TestType > )
        {
                INFO( "segment::ctor_move::equal_elements" ) ;
                CONSTEXPR_CHECK( [ & ]
                {
                auto vecmove = moved_to() ;

                for( ssize_t i = 0; i < vecmove.size(); ++i )
                {
                        if( vecmove.at( i ) != 1 ) return false ;
                }
                return true ;
                }() ) ;
        }
}

TEMPLATE_LIST_TEST_CASE( "segment::assign_copy", "[segment][assign_copy]", trivial_types )
{
        static constexpr auto seg_src = []{ return container_type< TestType >( CUSTOM_CAP, 1 ) ; } ;

        constexpr auto seg_copy0 = [ & ]{ container_type< TestType > vec_copy_0( CUSTOM_CAP    , {} ); vec_copy_0 = seg_src(); return vec_copy_0 ; } ;
        constexpr auto seg_copy1 = [ & ]{ container_type< TestType > vec_copy_1( CUSTOM_CAP * 2, {} ); vec_copy_1 = seg_src(); return vec_copy_1 ; } ;
        constexpr auto seg_copy2 = [ & ]{ container_type< TestType > vec_copy_2( CUSTOM_CAP / 2, {} ); vec_copy_2 = seg_src(); return vec_copy_2 ; } ;

        CONSTEXPR_CHECK( seg_copy0().    size() == CUSTOM_CAP     ) ;
        CONSTEXPR_CHECK( seg_copy1().    size() == CUSTOM_CAP     ) ;
        CONSTEXPR_CHECK( seg_copy2().    size() == CUSTOM_CAP     ) ;
        CONSTEXPR_CHECK( seg_copy0().   empty() ==      false     ) ;
        CONSTEXPR_CHECK( seg_copy1().   empty() ==      false     ) ;
        CONSTEXPR_CHECK( seg_copy2().   empty() ==      false     ) ;
        CONSTEXPR_CHECK( seg_copy0().capacity() == CUSTOM_CAP     ) ;
        CONSTEXPR_CHECK( seg_copy1().capacity() == CUSTOM_CAP     ) ;
//      CONSTEXPR_CHECK( vec_copy1().capacity() == CUSTOM_CAP * 2 ) ;
        CONSTEXPR_CHECK( seg_copy2().capacity() == CUSTOM_CAP     ) ;

        if constexpr( uti::meta::equality_comparable< TestType > )
        {
                INFO( "segment::assign_copy::equal_elements" ) ;
                CONSTEXPR_CHECK( [ & ]
                {
                auto vec = seg_src() ;
                auto vec_copy_0 = seg_copy0() ;
                auto vec_copy_1 = seg_copy1() ;
                auto vec_copy_2 = seg_copy2() ;

                for( ssize_t i = 0; i < vec.size(); ++i )
                {
                        if( vec_copy_0.at( i ) != seg_src().at( i ) ) return false ;
                        if( vec_copy_1.at( i ) != seg_src().at( i ) ) return false ;
                        if( vec_copy_2.at( i ) != seg_src().at( i ) ) return false ;
                }
                return true ;
                }() ) ;
        }
}

TEMPLATE_LIST_TEST_CASE( "segment::assign_move", "[segment][assign_move]", trivial_types )
{
        container_type< TestType > seg0 ( CUSTOM_CAP, 1 ) ;
        container_type< TestType > seg1 ( CUSTOM_CAP, 1 ) ;
        container_type< TestType > seg2 ( CUSTOM_CAP, 1 ) ;
        container_type< TestType > seg3 ( CUSTOM_CAP, 1 ) ;

        container_type< TestType > seg_move0( CUSTOM_CAP * 2, 1 ) ;
        container_type< TestType > seg_move1( CUSTOM_CAP    , 1 ) ;
        container_type< TestType > seg_move2( CUSTOM_CAP * 2, 1 ) ;
        container_type< TestType > seg_move3( CUSTOM_CAP / 2, 1 ) ;

        seg_move0 = UTI_MOVE( seg0 ) ;
        seg_move1 = UTI_MOVE( seg1 ) ;
        seg_move2 = UTI_MOVE( seg2 ) ;
        seg_move3 = UTI_MOVE( seg3 ) ;

        CHECK( seg_move0.    size() == CUSTOM_CAP ) ;
        CHECK( seg_move1.    size() == CUSTOM_CAP ) ;
        CHECK( seg_move2.    size() == CUSTOM_CAP ) ;
        CHECK( seg_move3.    size() == CUSTOM_CAP ) ;
        CHECK( seg_move0.   empty() ==      false ) ;
        CHECK( seg_move1.   empty() ==      false ) ;
        CHECK( seg_move2.   empty() ==      false ) ;
        CHECK( seg_move3.   empty() ==      false ) ;
        CHECK( seg_move0.capacity() == CUSTOM_CAP ) ;
        CHECK( seg_move1.capacity() == CUSTOM_CAP ) ;
        CHECK( seg_move2.capacity() == CUSTOM_CAP ) ;
        CHECK( seg_move3.capacity() == CUSTOM_CAP ) ;

        CHECK( seg0.    size() ==    0 ) ;
        CHECK( seg1.    size() ==    0 ) ;
        CHECK( seg2.    size() ==    0 ) ;
        CHECK( seg3.    size() ==    0 ) ;
        CHECK( seg0.   empty() == true ) ;
        CHECK( seg1.   empty() == true ) ;
        CHECK( seg2.   empty() == true ) ;
        CHECK( seg3.   empty() == true ) ;
        CHECK( seg0.capacity() ==    0 ) ;
        CHECK( seg1.capacity() ==    0 ) ;
        CHECK( seg2.capacity() ==    0 ) ;
        CHECK( seg3.capacity() ==    0 ) ;

        if constexpr( uti::meta::equality_comparable< TestType > )
        {
                for( ssize_t i = 0; i < seg_move0.size(); ++i )
                {
                        CHECK( seg_move0.at( i ) == 1 ) ;
                        CHECK( seg_move1.at( i ) == 1 ) ;
                        CHECK( seg_move2.at( i ) == 1 ) ;
                        CHECK( seg_move3.at( i ) == 1 ) ;
                }
        }
}

TEMPLATE_LIST_TEST_CASE( "segment::at", "[segment][access][at]", trivial_types )
{
        static constexpr uti::u32_t cap { 4 } ;

        CONSTEXPR_CHECK( []
        {
        container_type< TestType >                                     vec1d( cap, 1 ) ;
        container_type< container_type< TestType > >                   vec2d( cap    ) ;
        container_type< container_type< container_type< TestType > > > vec3d( cap    ) ;

        for( ssize_t i = 0; i < cap; ++i )
        {
                vec2d.push_back( vec1d );
        }
        for( ssize_t i = 0; i < cap; ++i )
        {
                vec3d.push_back( vec2d );
        }
        for( ssize_t i = 0; i < cap; ++i )
        {
                if( vec1d.at( i ) != 1 ) return false ;

                for( ssize_t j = 0; j < cap; ++j )
                {
                        if( vec2d.at( i, j ) != vec1d.at( j ) ) return false ;

                        for( ssize_t k = 0; k < cap; ++k )
                        {
                                if( vec3d.at( i, j, k ) != vec1d.at( k ) ) return false ;
                        }
                }
        }
        return true ;
        }() ) ;
}

TEMPLATE_LIST_TEST_CASE( "segment::push_back", "[segment][modify][push_back]", trivial_types )
{
        CONSTEXPR_CHECK( []
        {
        container_type< TestType > seg( 1024 ) ;

        for( ssize_t i = 0; i < 1024; ++i )
        {
                seg.push_back( 1 );
        }
        if constexpr( uti::meta::equality_comparable< TestType > )
        {
                for( ssize_t i = 0; i < 1024; ++i )
                {
                        if( seg.at( i ) != 1 ) return false ;
                }
        }
        return true ;
        }() ) ;
}

TEST_CASE( "segment::emplace_back", "[segment][modify][emplace_back]" )
{
        container_type< container_type< int > > seg2d ;

        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                seg2d.emplace_back( CUSTOM_CAP, i ) ;
        }
        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                for( ssize_t j = 0; j < seg2d.at( i ).size(); ++j )
                {
                        CHECK( seg2d.at( i, j ) == i ) ;
                }
        }
}

TEST_CASE( "segment::pop", "[segment][modify][pop]" )
{
        static constexpr auto seg_src = []
        {
                container_type< int > vec( CUSTOM_CAP ) ;

                for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
                {
                        vec.push_back( 1 ) ;
                }
                return vec ;
        } ;

        CONSTEXPR_CHECK( seg_src(). size() == CUSTOM_CAP ) ;
        CONSTEXPR_CHECK( seg_src().front() ==          1 ) ;
        CONSTEXPR_CHECK( seg_src(). back() ==          1 ) ;

        constexpr auto seg_pop_back = [ & ]
        {
                auto vec = seg_src() ;
                vec.pop_back() ;
                return vec ;
        } ;

        CONSTEXPR_CHECK( seg_pop_back(). size() == CUSTOM_CAP - 1 ) ;
        CONSTEXPR_CHECK( seg_pop_back().front() ==              1 ) ;
        CONSTEXPR_CHECK( seg_pop_back(). back() ==              1 ) ;

        constexpr auto seg_pop_back_front = [ & ]
        {
                auto vec = seg_src() ;
                vec.pop_back() ;
                vec.pop_front() ;
                return vec ;
        } ;

        CONSTEXPR_CHECK( seg_pop_back_front(). size() == CUSTOM_CAP - 2 ) ;
        CONSTEXPR_CHECK( seg_pop_back_front().front() ==              1 ) ;
        CONSTEXPR_CHECK( seg_pop_back_front(). back() ==              1 ) ;
}

TEMPLATE_LIST_TEST_CASE( "segment::reserve", "[segment][modify][reserve]", trivial_types )
{
        static constexpr auto seg_src_1 = []{ return container_type< TestType >() ; } ;
        static constexpr auto seg_src_2 = []{ return container_type< TestType >( CUSTOM_CAP, {} ) ; } ;

        CONSTEXPR_CHECK( seg_src_1().capacity() ==          0 ) ;
        CONSTEXPR_CHECK( seg_src_2().capacity() == CUSTOM_CAP ) ;

        constexpr auto seg_1_res_0 = []{ auto vec = seg_src_1() ; vec.reserve( 0 ) ; return vec ; } ;
        constexpr auto seg_2_res_0 = []{ auto vec = seg_src_2() ; vec.reserve( 0 ) ; return vec ; } ;

        CONSTEXPR_CHECK( seg_1_res_0().capacity() ==          0 ) ;
        CONSTEXPR_CHECK( seg_2_res_0().capacity() == CUSTOM_CAP ) ;

        constexpr auto seg_1_res_1 = []{ auto vec = seg_src_1() ; vec.reserve( CUSTOM_CAP * 2 ) ; return vec ; } ;
//      constexpr auto seg_2_res_1 = []{ auto vec = seg_src_2() ; vec.reserve( CUSTOM_CAP * 2 ) ; return vec ; } ;

        CONSTEXPR_CHECK( seg_1_res_1().capacity() == CUSTOM_CAP * 2 ) ;
//      CONSTEXPR_CHECK( seg_2_res_1().capacity() == CUSTOM_CAP * 2 ) ;

        constexpr auto seg_1_res_2 = []{ auto vec = seg_src_1() ; vec.reserve( CUSTOM_CAP * 2 ) ; vec.reserve( CUSTOM_CAP / 2 ) ; return vec ; } ;
//      constexpr auto seg_2_res_2 = []{ auto vec = seg_src_2() ; vec.reserve( CUSTOM_CAP * 2 ) ; vec.reserve( CUSTOM_CAP / 2 ) ; return vec ; } ;

        CONSTEXPR_CHECK( seg_1_res_2().capacity() == CUSTOM_CAP * 2 ) ;
//      CONSTEXPR_CHECK( seg_2_res_2().capacity() == CUSTOM_CAP * 2 ) ;
}

TEMPLATE_LIST_TEST_CASE( "segment::shrink", "[segment][modify][shrink]", trivial_types )
{
        {
                container_type< TestType > vec( CUSTOM_CAP, {} ) ;

                CHECK( vec.    size() == CUSTOM_CAP ) ;
                CHECK( vec.capacity() == CUSTOM_CAP ) ;

                vec.shrink_size( CUSTOM_CAP / 2 ) ;

                CHECK( vec.    size() == CUSTOM_CAP / 2 ) ;
                CHECK( vec.capacity() == CUSTOM_CAP     ) ;
        }
        {
                container_type< TestType > vec( CUSTOM_CAP, {} ) ;

                CHECK( vec.    size() == CUSTOM_CAP ) ;
                CHECK( vec.capacity() == CUSTOM_CAP ) ;

                vec.reserve( CUSTOM_CAP * 2 ) ;

                CHECK( vec.    size() == CUSTOM_CAP     ) ;
                CHECK( vec.capacity() == CUSTOM_CAP * 2 ) ;

                vec.shrink_to_fit();

                CHECK( vec.    size() == CUSTOM_CAP ) ;
                CHECK( vec.capacity() == CUSTOM_CAP ) ;
        }
        {
                container_type< TestType > vec( CUSTOM_CAP, {} ) ;

                CHECK( vec.    size() == CUSTOM_CAP ) ;
                CHECK( vec.capacity() == CUSTOM_CAP ) ;

                vec.shrink( CUSTOM_CAP / 2 ) ;

                CHECK( vec.    size() == CUSTOM_CAP / 2 ) ;
                CHECK( vec.capacity() == CUSTOM_CAP / 2 ) ;
        }
}

TEST_CASE( "segment::insert", "[segment][modify][insert]" )
{
        container_type< int > vecint( CUSTOM_CAP, 1 ) ;

        CHECK( vecint.size() == CUSTOM_CAP ) ;

        vecint.insert( 0, 0 ) ;

        CHECK( vecint.size() == CUSTOM_CAP + 1 ) ;

        vecint.insert( CUSTOM_CAP / 2, 0 ) ;

        CHECK( vecint.size() == CUSTOM_CAP + 2 ) ;

        vecint.insert( vecint.size(), 0 ) ;

        CHECK( vecint.size() == CUSTOM_CAP + 3 ) ;

        for( ssize_t i = 0; i < vecint.size(); ++i )
        {
                if( i == 0 || i == CUSTOM_CAP / 2 || i == vecint.size() - 1 )
                {
                        CHECK( vecint.at( i ) ==  0 ) ;
                }
                else if( i < CUSTOM_CAP / 2 )
                {
                        CHECK( vecint.at( i ) == 1 ) ;
                }
                else
                {
                        CHECK( vecint.at( i ) == 1 ) ;
                }
        }
}

TEMPLATE_LIST_TEST_CASE( "segment::erase", "[segment][modify][erase]", trivial_types )
{
        {
                container_type< TestType > vecstr( CUSTOM_CAP, {} ) ;

                CHECK( vecstr.size() == CUSTOM_CAP ) ;

                vecstr.erase( 0 ) ;

                CHECK( vecstr.size() == CUSTOM_CAP - 1 ) ;

                vecstr.erase( vecstr.size() / 2 ) ;

                CHECK( vecstr.size() == CUSTOM_CAP - 2 ) ;

                vecstr.erase( vecstr.size() - 1 ) ;

                CHECK( vecstr.size() == CUSTOM_CAP - 3 ) ;
        }
        {
                container_type< TestType > vecstr( CUSTOM_CAP, {} ) ;

                CHECK( vecstr.size() == CUSTOM_CAP ) ;

                vecstr.erase_stable( 0 ) ;

                CHECK( vecstr.size() == CUSTOM_CAP - 1 ) ;

                vecstr.erase_stable( vecstr.size() / 2 ) ;

                CHECK( vecstr.size() == CUSTOM_CAP - 2 ) ;

                vecstr.erase_stable( vecstr.size() - 1 ) ;

                CHECK( vecstr.size() == CUSTOM_CAP - 3 ) ;
        }
}

TEST_CASE( "segment::clear", "[segment][modify][clear]" )
{
        container_type<         int > vec1                                        ;
        container_type<         int > vec2( CUSTOM_CAP,                    {}   ) ;
        container_type< std::string > vec3( CUSTOM_CAP, std::string( "random" ) ) ;

        CHECK( vec1.size() ==          0 ) ;
        CHECK( vec2.size() == CUSTOM_CAP ) ;
        CHECK( vec3.size() == CUSTOM_CAP ) ;

        vec1.clear() ;
        vec2.clear() ;
        vec3.clear() ;

        CHECK( vec1.size() == 0 ) ;
        CHECK( vec2.size() == 0 ) ;
        CHECK( vec3.size() == 0 ) ;
}

TEST_CASE( "segment::iterate", "[segment][access][iterate]" )
{
        container_type< int > vec( CUSTOM_CAP ) ;

        for( auto const & val : vec )
        {
                CHECK( val == 0 ) ;
        }
}

TEST_CASE( "segment::no_double_free", "[segment][dtor]" )
{
        CONSTEXPR_CHECK( []
        {
        container_type< container_type< std::string > > vec2d;

        for( int i = 0; i < 4; ++i )
        {
                container_type< std::string > vec1d;
                for( int i = 0; i < 4; ++i )
                {
                        vec1d.insert( 0, std::string( i + 1, 'x' ) ) ;
                }
                vec2d.insert( 0, UTI_MOVE( vec1d ) ) ;
        }
        container_type< container_type< std::string > > vec2d2;

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
                        dummy_counter += !val.empty();
                }
        }
        return dummy_counter ;
        }() == 16 ) ;
}

TEST_CASE( "segment::range", "[segment][range]" )
{
        uti::segment_tree< int, uti::compare::sum > prefix( 1024, 1 ) ;

        for( int i = 0; i < prefix.size(); ++i )
        {
                for( int j = i; j < prefix.size(); ++j )
                {
                        CHECK( prefix.range( i, j ) == j - i + 1 ) ;
                }
        }
}

#undef  CUSTOM_CAP
#define CUSTOM_CAP CUSTOM_CAP_OLD
