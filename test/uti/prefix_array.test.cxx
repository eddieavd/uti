//
//
//      uti.test
//      prefix_array.test.cxx
//

#include <snitch/snitch.hpp>

#include "uti.test.hxx"

#include <allocator/new.hxx>
#include <container/prefix_array.hxx>


template< typename T >
using container_type = uti::prefix_array< T > ;


TEMPLATE_LIST_TEST_CASE( "prefix::ctor_default", "[prefix][ctor][ctor_default]", all_test_types )
{
        constexpr auto prefix = []{ return container_type< TestType >() ; } ;

        CONSTEXPR_CHECK( prefix().    size() ==    0 ) ;
        CONSTEXPR_CHECK( prefix().   empty() == true ) ;
        CONSTEXPR_CHECK( prefix().capacity() ==    0 ) ;
}

TEMPLATE_LIST_TEST_CASE( "prefix::ctor_reserve", "[prefix][ctor][ctor_reserve]", all_test_types )
{
        constexpr auto prefix = []{ return container_type< TestType >( CUSTOM_CAP ) ; } ;

        CONSTEXPR_CHECK( prefix().    size() ==          0 ) ;
        CONSTEXPR_CHECK( prefix().   empty() ==       true ) ;
        CONSTEXPR_CHECK( prefix().capacity() == CUSTOM_CAP ) ;
}

TEMPLATE_LIST_TEST_CASE( "prefix::ctor_fill", "[prefix][ctor][ctor_fill]", trivial_types )
{
        constexpr auto prefix = []{ return container_type< TestType >( CUSTOM_CAP, 1 ) ; } ;

        CONSTEXPR_CHECK( prefix().    size() == CUSTOM_CAP ) ;
        CONSTEXPR_CHECK( prefix().   empty() ==      false ) ;
        CONSTEXPR_CHECK( prefix().capacity() == CUSTOM_CAP ) ;

        if constexpr( uti::meta::equality_comparable< TestType > )
        {
                INFO( "prefix::ctor_fill::equal_elements" ) ;
                CONSTEXPR_CHECK( []
                {
                container_type< TestType > vec( CUSTOM_CAP, 1 ) ;

                for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
                {
                        if( vec.at( i ) != i + 1 ) return false ;
                }
                return true ;
                }() ) ;
        }
}

TEMPLATE_LIST_TEST_CASE( "prefix::ctor_iter", "[prefix][ctor][ctor_iter]", trivial_types )
{
        {
                INFO( "prefix::ctor_iter::c_style_array" ) ;
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
                                if( vec.at( i ) != arr[ i ] + i ) return false ;
                        }
                }
                return true ;
                }() ) ;
        }
        {
                INFO( "prefix::ctor_iter::vector" ) ;
                CONSTEXPR_CHECK( []
                {
                uti::vector< TestType > vec( 4, 1 ) ;

                container_type< TestType > vec2( vec.begin(), vec.end() ) ;

                if( vec.size() != 4 ) return false ;

                if constexpr( uti::meta::equality_comparable< TestType > )
                {
                        for( ssize_t i = 0; i < vec.size(); ++i )
                        {
                                if( vec.at( i ) != vec2.element_at( i ) ) return false ;
                        }
                }
                return true ;
                }() ) ;
        }
        {
                INFO( "prefix::ctor_iter::prefix_array" ) ;
                CONSTEXPR_CHECK( []
                {
                uti::prefix_array< int > prefix( 4, 1 ) ;

                container_type< int > vec( prefix.begin(), prefix.end() ) ;

                if( vec.size() != 4 ) return false ;

                if constexpr( uti::meta::equality_comparable< TestType > )
                {
                        for( ssize_t i = 0; i < prefix.size(); ++i )
                        {
                                if( vec.at( i ) != prefix.at( i ) ) return false ;
                        }
                }
                return true ;
                }() ) ;
        }
}

TEMPLATE_LIST_TEST_CASE( "prefix::ctor_copy", "[prefix][ctor][ctor_copy]", trivial_types )
{
        constexpr auto prefix = []{ container_type< TestType > vec( CUSTOM_CAP, 1 ) ; return uti::prefix_array( vec ) ; } ;

        CONSTEXPR_CHECK( prefix().    size() == CUSTOM_CAP ) ;
        CONSTEXPR_CHECK( prefix().   empty() ==      false ) ;
        CONSTEXPR_CHECK( prefix().capacity() == CUSTOM_CAP ) ;

        if constexpr( uti::meta::equality_comparable< TestType > )
        {
                INFO( "prefix::ctor_copy::equal_elements" ) ;
                CONSTEXPR_CHECK( [ & ]
                {
                auto vec_copy = prefix() ;
                for( ssize_t i = 0; i < vec_copy.size(); ++i )
                {
                        if( vec_copy.at( i ) != i + 1 ) return false ;
                }
                return true ;
                }() ) ;
        }
}

TEMPLATE_LIST_TEST_CASE( "prefix::ctor_move", "[prefix][ctor][ctor_move]", trivial_types )
{
        constexpr auto moved_to   = []{ container_type< TestType > vec( CUSTOM_CAP, 1 ) ; return uti::prefix_array( UTI_MOVE( vec ) ) ; } ;
        constexpr auto moved_from = []{ container_type< TestType > vec( CUSTOM_CAP, 1 ) ; uti::prefix_array move( UTI_MOVE( vec ) ) ; return vec ; } ;

        CONSTEXPR_CHECK( moved_to().    size() == CUSTOM_CAP ) ;
        CONSTEXPR_CHECK( moved_to().   empty() ==      false ) ;
        CONSTEXPR_CHECK( moved_to().capacity() == CUSTOM_CAP ) ;

        CONSTEXPR_CHECK( moved_from().    size() ==    0 ) ;
        CONSTEXPR_CHECK( moved_from().   empty() == true ) ;
        CONSTEXPR_CHECK( moved_from().capacity() ==    0 ) ;

        if constexpr( uti::meta::equality_comparable< TestType > )
        {
                INFO( "prefix::ctor_move::equal_elements" ) ;
                CONSTEXPR_CHECK( [ & ]
                {
                auto vecmove = moved_to() ;

                for( ssize_t i = 0; i < vecmove.size(); ++i )
                {
                        if( vecmove.at( i ) != i + 1 ) return false ;
                }
                return true ;
                }() ) ;
        }
}

TEMPLATE_LIST_TEST_CASE( "prefix::assign_copy", "[prefix][assign_copy]", trivial_types )
{
        static constexpr auto vec_src = []{ return container_type< TestType >( CUSTOM_CAP, 1 ) ; } ;

        constexpr auto vec_copy0 = [ & ]{ container_type< TestType > vec_copy_0( CUSTOM_CAP    , {} ); vec_copy_0 = vec_src(); return vec_copy_0 ; } ;
        constexpr auto vec_copy1 = [ & ]{ container_type< TestType > vec_copy_1( CUSTOM_CAP * 2, {} ); vec_copy_1 = vec_src(); return vec_copy_1 ; } ;
        constexpr auto vec_copy2 = [ & ]{ container_type< TestType > vec_copy_2( CUSTOM_CAP / 2, {} ); vec_copy_2 = vec_src(); return vec_copy_2 ; } ;

        CONSTEXPR_CHECK( vec_copy0().    size() == CUSTOM_CAP     ) ;
        CONSTEXPR_CHECK( vec_copy1().    size() == CUSTOM_CAP     ) ;
        CONSTEXPR_CHECK( vec_copy2().    size() == CUSTOM_CAP     ) ;
        CONSTEXPR_CHECK( vec_copy0().   empty() ==      false     ) ;
        CONSTEXPR_CHECK( vec_copy1().   empty() ==      false     ) ;
        CONSTEXPR_CHECK( vec_copy2().   empty() ==      false     ) ;
        CONSTEXPR_CHECK( vec_copy0().capacity() == CUSTOM_CAP     ) ;
        CONSTEXPR_CHECK( vec_copy1().capacity() == CUSTOM_CAP     ) ;
//      CONSTEXPR_CHECK( vec_copy1().capacity() == CUSTOM_CAP * 2 ) ;
        CONSTEXPR_CHECK( vec_copy2().capacity() == CUSTOM_CAP     ) ;

        if constexpr( uti::meta::equality_comparable< TestType > )
        {
                INFO( "prefix::assign_copy::equal_elements" ) ;
                CONSTEXPR_CHECK( [ & ]
                {
                auto vec = vec_src() ;
                auto vec_copy_0 = vec_copy0() ;
                auto vec_copy_1 = vec_copy1() ;
                auto vec_copy_2 = vec_copy2() ;

                for( ssize_t i = 0; i < vec.size(); ++i )
                {
                        if( vec_copy_0.at( i ) != vec_src().at( i ) ) return false ;
                        if( vec_copy_1.at( i ) != vec_src().at( i ) ) return false ;
                        if( vec_copy_2.at( i ) != vec_src().at( i ) ) return false ;
                }
                return true ;
                }() ) ;
        }
}

TEMPLATE_LIST_TEST_CASE( "prefix::assign_move", "[prefix][assign_move]", trivial_types )
{
        container_type< TestType > vec0 ( CUSTOM_CAP, 1 ) ;
        container_type< TestType > vec1 ( CUSTOM_CAP, 1 ) ;
        container_type< TestType > vec2 ( CUSTOM_CAP, 1 ) ;
        container_type< TestType > vec3 ( CUSTOM_CAP, 1 ) ;

        container_type< TestType > vec_move0( CUSTOM_CAP * 2, 1 ) ;
        container_type< TestType > vec_move1( CUSTOM_CAP    , 1 ) ;
        container_type< TestType > vec_move2( CUSTOM_CAP * 2, 1 ) ;
        container_type< TestType > vec_move3( CUSTOM_CAP / 2, 1 ) ;

        vec_move0 = UTI_MOVE( vec0 ) ;
        vec_move1 = UTI_MOVE( vec1 ) ;
        vec_move2 = UTI_MOVE( vec2 ) ;
        vec_move3 = UTI_MOVE( vec3 ) ;

        CHECK( vec_move0.    size() == CUSTOM_CAP ) ;
        CHECK( vec_move1.    size() == CUSTOM_CAP ) ;
        CHECK( vec_move2.    size() == CUSTOM_CAP ) ;
        CHECK( vec_move3.    size() == CUSTOM_CAP ) ;
        CHECK( vec_move0.   empty() ==      false ) ;
        CHECK( vec_move1.   empty() ==      false ) ;
        CHECK( vec_move2.   empty() ==      false ) ;
        CHECK( vec_move3.   empty() ==      false ) ;
        CHECK( vec_move0.capacity() == CUSTOM_CAP ) ;
        CHECK( vec_move1.capacity() == CUSTOM_CAP ) ;
        CHECK( vec_move2.capacity() == CUSTOM_CAP ) ;
        CHECK( vec_move3.capacity() == CUSTOM_CAP ) ;

        CHECK( vec0.    size() ==    0 ) ;
        CHECK( vec1.    size() ==    0 ) ;
        CHECK( vec2.    size() ==    0 ) ;
        CHECK( vec3.    size() ==    0 ) ;
        CHECK( vec0.   empty() == true ) ;
        CHECK( vec1.   empty() == true ) ;
        CHECK( vec2.   empty() == true ) ;
        CHECK( vec3.   empty() == true ) ;
        CHECK( vec0.capacity() ==    0 ) ;
        CHECK( vec1.capacity() ==    0 ) ;
        CHECK( vec2.capacity() ==    0 ) ;
        CHECK( vec3.capacity() ==    0 ) ;

        if constexpr( uti::meta::equality_comparable< TestType > )
        {
                for( ssize_t i = 0; i < vec_move0.size(); ++i )
                {
                        CHECK( vec_move0.at( i ) == i + 1 ) ;
                        CHECK( vec_move1.at( i ) == i + 1 ) ;
                        CHECK( vec_move2.at( i ) == i + 1 ) ;
                        CHECK( vec_move3.at( i ) == i + 1 ) ;
                }
        }
}

TEMPLATE_LIST_TEST_CASE( "prefix::at", "[prefix][access][at]", trivial_types )
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
                if( vec1d.element_at( i ) != 1 ) return false ;

                for( ssize_t j = 0; j < cap; ++j )
                {
                        if( vec2d.element_at( i, j ) != vec1d.element_at( j ) ) return false ;

                        for( ssize_t k = 0; k < cap; ++k )
                        {
                                if( vec3d.element_at( i, j, k ) != vec1d.element_at( k ) ) return false ;
                        }
                }
        }
        return true ;
        }() ) ;
}

TEMPLATE_LIST_TEST_CASE( "prefix::push_back", "[prefix][modify][push_back]", trivial_types )
{
        CONSTEXPR_CHECK( []
        {
        container_type< TestType > vec ;

        for( ssize_t i = 0; i < 1024; ++i )
        {
                vec.push_back( 1 );
        }
        if constexpr( uti::meta::equality_comparable< TestType > )
        {
                for( ssize_t i = 0; i < 1024; ++i )
                {
                        if( vec.at( i ) != TestType( i + 1 ) ) return false ;
                }
        }
        return true ;
        }() ) ;
}

TEST_CASE( "prefix::emplace_back", "[prefix][modify][emplace_back]" )
{
        container_type< container_type< int > > vec2d ;

        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                vec2d.emplace_back( CUSTOM_CAP, i ) ;
        }
        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                for( ssize_t j = 0; j < vec2d.at( i ).size(); ++j )
                {
                        CHECK( vec2d.element_at( i, j ) == i ) ;
                }
        }
}

TEST_CASE( "prefix::pop", "[prefix][modify][pop]" )
{
        static constexpr auto vec_src = []
        {
                container_type< int > vec ;

                for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
                {
                        vec.push_back( 1 ) ;
                }
                return vec ;
        } ;

        CONSTEXPR_CHECK( vec_src(). size() == CUSTOM_CAP ) ;
        CONSTEXPR_CHECK( vec_src().front() ==          1 ) ;
        CONSTEXPR_CHECK( vec_src(). back() == CUSTOM_CAP ) ;

        constexpr auto vec_pop_back = [ & ]
        {
                auto vec = vec_src() ;
                vec.pop_back() ;
                return vec ;
        } ;
        constexpr auto vec_pop_back_val = [ & ]
        {
                auto vec = vec_src() ;
                return vec.pop_back_val() ;
        } ;

        CONSTEXPR_CHECK( vec_pop_back_val()     ==              1 ) ;
        CONSTEXPR_CHECK( vec_pop_back(). size() == CUSTOM_CAP - 1 ) ;
        CONSTEXPR_CHECK( vec_pop_back().front() ==              1 ) ;
        CONSTEXPR_CHECK( vec_pop_back(). back() == CUSTOM_CAP - 1 ) ;

        constexpr auto vec_pop_back_front = [ & ]
        {
                auto vec = vec_src() ;
                vec.pop_back() ;
                vec.pop_front() ;
                return vec ;
        } ;
        constexpr auto vec_pop_back_front_val = [ & ]
        {
                auto vec = vec_src() ;
                vec.pop_back() ;
                return vec.pop_front_val() ;
        } ;

        CONSTEXPR_CHECK( vec_pop_back_front_val()     ==              1 ) ;
        CONSTEXPR_CHECK( vec_pop_back_front(). size() == CUSTOM_CAP - 2 ) ;
        CONSTEXPR_CHECK( vec_pop_back_front().front() ==              1 ) ;
        CONSTEXPR_CHECK( vec_pop_back_front(). back() == CUSTOM_CAP - 2 ) ;
}

TEMPLATE_LIST_TEST_CASE( "prefix::reserve", "[prefix][modify][reserve]", trivial_types )
{
        static constexpr auto vec_src_1 = []{ return container_type< TestType >() ; } ;
        static constexpr auto vec_src_2 = []{ return container_type< TestType >( CUSTOM_CAP, {} ) ; } ;

        CONSTEXPR_CHECK( vec_src_1().capacity() ==          0 ) ;
        CONSTEXPR_CHECK( vec_src_2().capacity() == CUSTOM_CAP ) ;

        constexpr auto vec_1_res_0 = []{ auto vec = vec_src_1() ; vec.reserve( 0 ) ; return vec ; } ;
        constexpr auto vec_2_res_0 = []{ auto vec = vec_src_2() ; vec.reserve( 0 ) ; return vec ; } ;

        CONSTEXPR_CHECK( vec_1_res_0().capacity() ==          0 ) ;
        CONSTEXPR_CHECK( vec_2_res_0().capacity() == CUSTOM_CAP ) ;

        constexpr auto vec_1_res_1 = []{ auto vec = vec_src_1() ; vec.reserve( CUSTOM_CAP * 2 ) ; return vec ; } ;
        constexpr auto vec_2_res_1 = []{ auto vec = vec_src_2() ; vec.reserve( CUSTOM_CAP * 2 ) ; return vec ; } ;

        CONSTEXPR_CHECK( vec_1_res_1().capacity() == CUSTOM_CAP * 2 ) ;
        CONSTEXPR_CHECK( vec_2_res_1().capacity() == CUSTOM_CAP * 2 ) ;

        constexpr auto vec_1_res_2 = []{ auto vec = vec_src_1() ; vec.reserve( CUSTOM_CAP * 2 ) ; vec.reserve( CUSTOM_CAP / 2 ) ; return vec ; } ;
        constexpr auto vec_2_res_2 = []{ auto vec = vec_src_2() ; vec.reserve( CUSTOM_CAP * 2 ) ; vec.reserve( CUSTOM_CAP / 2 ) ; return vec ; } ;

        CONSTEXPR_CHECK( vec_1_res_2().capacity() == CUSTOM_CAP * 2 ) ;
        CONSTEXPR_CHECK( vec_2_res_2().capacity() == CUSTOM_CAP * 2 ) ;
}

TEMPLATE_LIST_TEST_CASE( "prefix::shrink", "[prefix][modify][shrink]", trivial_types )
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

TEST_CASE( "prefix::insert", "[prefix][modify][insert]" )
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
                        CHECK( vecint.element_at( i ) ==  0 ) ;
                }
                else if( i < CUSTOM_CAP / 2 )
                {
                        CHECK( vecint.element_at( i ) == 1 ) ;
                }
                else
                {
                        CHECK( vecint.element_at( i ) == 1 ) ;
                }
        }
}

TEMPLATE_LIST_TEST_CASE( "prefix::erase", "[prefix][modify][erase]", trivial_types )
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

TEST_CASE( "prefix::clear", "[prefix][modify][clear]" )
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

TEST_CASE( "prefix::iterate", "[prefix][access][iterate]" )
{
        container_type< int > vec( CUSTOM_CAP ) ;

        for( auto const & val : vec )
        {
                CHECK( val == 0 ) ;
        }
}

TEST_CASE( "prefix::no_double_free", "[prefix][dtor]" )
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

TEST_CASE( "prefix::range", "[prefix][range]" )
{
        container_type< int > prefix( 1024, 1 ) ;

        for( int i = 0; i < prefix.size(); ++i )
        {
                for( int j = i; j < prefix.size(); ++j )
                {
                        CHECK( prefix.range( i, j ) == j - i + 1 ) ;
                }
        }
}
