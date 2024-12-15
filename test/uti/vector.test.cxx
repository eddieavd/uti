//
//
//      uti.test
//      vector.test.cxx
//

#include <snitch/snitch.hpp>

#include "uti.test.hxx"


using namespace uti::test ;


template< typename T >
using container_type = uti::vector< T > ;


TEMPLATE_LIST_TEST_CASE( "vector::ctor_default", "[vector][ctor][ctor_default]", uti_test_types )
{
        constexpr auto vector = []{ return container_type< TestType >() ; } ;

        CONSTEXPR_CHECK( vector().    size() ==    0 ) ;
        CONSTEXPR_CHECK( vector().   empty() == true ) ;
        CONSTEXPR_CHECK( vector().capacity() ==    0 ) ;
}

TEMPLATE_LIST_TEST_CASE( "vector::ctor_reserve", "[vector][ctor][ctor_reserve]", uti_test_types )
{
        constexpr auto vector = []{ return container_type< TestType >( CUSTOM_CAP ) ; } ;

        CONSTEXPR_CHECK( vector().    size() ==          0 ) ;
        CONSTEXPR_CHECK( vector().   empty() ==       true ) ;
        CONSTEXPR_CHECK( vector().capacity() == CUSTOM_CAP ) ;
}

TEMPLATE_LIST_TEST_CASE( "vector::ctor_fill", "[vector][ctor][ctor_fill]", trivial_types )
{
        constexpr auto vector = []{ return container_type< TestType >( CUSTOM_CAP, 1 ) ; } ;

        CONSTEXPR_CHECK( vector().    size() == CUSTOM_CAP ) ;
        CONSTEXPR_CHECK( vector().   empty() ==      false ) ;
        CONSTEXPR_CHECK( vector().capacity() == CUSTOM_CAP ) ;

        if constexpr( uti::meta::equality_comparable< TestType > )
        {
                INFO( "vector::ctor_fill::equal_elements" ) ;
                CONSTEXPR_CHECK( []
                {
                container_type< TestType > vec( CUSTOM_CAP, {} ) ;

                for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
                {
                        if( vec.at( i ) != TestType{} ) return false ;
                }
                return true ;
                }() ) ;
        }
}

TEMPLATE_LIST_TEST_CASE( "vector::ctor_iter", "[vector][ctor][ctor_iter]", uti_test_types )
{
        {
                INFO( "vector::ctor_iter::c_style_array" ) ;
                CONSTEXPR_CHECK( []
                {
                TestType arr[] = { {}, {}, {}, {} } ;

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
                INFO( "vector::ctor_iter::vector" ) ;
                CONSTEXPR_CHECK( []
                {
                container_type< TestType > vec( 4, TestType{} ) ;

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
                INFO( "vector::ctor_iter::prefix_array" ) ;
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

TEMPLATE_LIST_TEST_CASE( "vector::ctor_copy", "[vector][ctor][ctor_copy]", uti_test_types )
{
        constexpr auto vector = []{ container_type< TestType > vec( CUSTOM_CAP, {} ) ; return uti::vector( vec ) ; } ;

        CONSTEXPR_CHECK( vector().    size() == CUSTOM_CAP ) ;
        CONSTEXPR_CHECK( vector().   empty() ==      false ) ;
        CONSTEXPR_CHECK( vector().capacity() == CUSTOM_CAP ) ;

        if constexpr( uti::meta::equality_comparable< TestType > )
        {
                INFO( "vector::ctor_copy::equal_elements" ) ;
                CONSTEXPR_CHECK( [ & ]
                {
                auto vec_copy = vector() ;
                for( ssize_t i = 0; i < vec_copy.size(); ++i )
                {
                        if( vec_copy.at( i ) != TestType{} ) return false ;
                }
                return true ;
                }() ) ;
        }
}

TEMPLATE_LIST_TEST_CASE( "vector::ctor_move", "[vector][ctor][ctor_move]", uti_test_types )
{
        constexpr auto moved_to   = []{ container_type< TestType > vec( CUSTOM_CAP, {} ) ; return uti::vector( UTI_MOVE( vec ) ) ; } ;
        constexpr auto moved_from = []{ container_type< TestType > vec( CUSTOM_CAP, {} ) ; uti::vector move( UTI_MOVE( vec ) ) ; return vec ; } ;

        CONSTEXPR_CHECK( moved_to().    size() == CUSTOM_CAP ) ;
        CONSTEXPR_CHECK( moved_to().   empty() ==      false ) ;
        CONSTEXPR_CHECK( moved_to().capacity() == CUSTOM_CAP ) ;

        CONSTEXPR_CHECK( moved_from().    size() ==    0 ) ;
        CONSTEXPR_CHECK( moved_from().   empty() == true ) ;
        CONSTEXPR_CHECK( moved_from().capacity() ==    0 ) ;

        if constexpr( uti::meta::equality_comparable< TestType > )
        {
                INFO( "vector::ctor_move::equal_elements" ) ;
                CONSTEXPR_CHECK( [ & ]
                {
                auto vecmove = moved_to() ;

                for( ssize_t i = 0; i < vecmove.size(); ++i )
                {
                        if( vecmove.at( i ) != TestType{} ) return false ;
                }
                return true ;
                }() ) ;
        }
}

TEMPLATE_LIST_TEST_CASE( "vector::assign_copy", "[vector][assign_copy]", uti_test_types )
{
        static constexpr auto vec_src = []{ return container_type< TestType >( CUSTOM_CAP, {} ) ; } ;

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
                INFO( "vector::assign_copy::equal_elements" ) ;
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

TEMPLATE_LIST_TEST_CASE( "vector::assign_move", "[vector][assign_move]", uti_test_types )
{
        container_type< TestType > vec0 ( CUSTOM_CAP, {} ) ;
        container_type< TestType > vec1 ( CUSTOM_CAP, {} ) ;
        container_type< TestType > vec2 ( CUSTOM_CAP, {} ) ;
        container_type< TestType > vec3 ( CUSTOM_CAP, {} ) ;

        container_type< TestType > vec_move0( CUSTOM_CAP * 2, {} ) ;
        container_type< TestType > vec_move1( CUSTOM_CAP    , {} ) ;
        container_type< TestType > vec_move2( CUSTOM_CAP * 2, {} ) ;
        container_type< TestType > vec_move3( CUSTOM_CAP / 2, {} ) ;

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
                        CHECK( vec_move0.at( i ) == TestType{} ) ;
                        CHECK( vec_move1.at( i ) == TestType{} ) ;
                        CHECK( vec_move2.at( i ) == TestType{} ) ;
                        CHECK( vec_move3.at( i ) == TestType{} ) ;
                }
        }
}

TEMPLATE_LIST_TEST_CASE( "vector::at", "[vector][access][at]", comparable_types )
{
        static constexpr uti::u32_t cap { 4 } ;

        CONSTEXPR_CHECK( []
        {
        container_type< TestType >                               vec1d( cap, {} ) ;
        container_type< container_type< TestType > >                vec2d( cap     ) ;
        container_type< container_type< container_type< TestType > > > vec3d( cap     ) ;

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
                if( vec1d.at( i ) != TestType{} ) return false ;

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

TEMPLATE_LIST_TEST_CASE( "vector::push_back", "[vector][modify][push_back]", trivial_types )
{
        CONSTEXPR_CHECK( []
        {
        container_type< TestType > vec ;

        for( ssize_t i = 0; i < 1024; ++i )
        {
                vec.push_back( TestType( i ) );
        }
        if constexpr( uti::meta::equality_comparable< TestType > )
        {
                for( ssize_t i = 0; i < 1024; ++i )
                {
                        if( vec.at( i ) != TestType( i ) ) return false ;
                }
        }
        return true ;
        }() ) ;
}

TEST_CASE( "vector::emplace_back", "[vector][modify][emplace_back]" )
{
        container_type< std::string        > vecstr ;
        container_type< container_type< int > > vec2d  ;

        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                vec2d .emplace_back( CUSTOM_CAP, i ) ;
                vecstr.emplace_back( std::to_string( i ) ) ;
        }
        for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
        {
                CHECK( vecstr.at( i ) == std::to_string( i ) ) ;

                for( auto const & val : vec2d.at( i ) )
                {
                        CHECK( val == i ) ;
                }
        }
}

TEST_CASE( "vector::pop", "[vector][modify][pop]" )
{
        static constexpr auto vec_src = []
        {
                container_type< int > vec ;

                for( ssize_t i = 0; i < CUSTOM_CAP; ++i )
                {
                        vec.push_back( i ) ;
                }
                return vec ;
        } ;

        CONSTEXPR_CHECK( vec_src(). size() == CUSTOM_CAP     ) ;
        CONSTEXPR_CHECK( vec_src().front() ==              0 ) ;
        CONSTEXPR_CHECK( vec_src(). back() == CUSTOM_CAP - 1 ) ;

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

        CONSTEXPR_CHECK( vec_pop_back_val()     == CUSTOM_CAP - 1 ) ;
        CONSTEXPR_CHECK( vec_pop_back(). size() == CUSTOM_CAP - 1 ) ;
        CONSTEXPR_CHECK( vec_pop_back().front() ==              0 ) ;
        CONSTEXPR_CHECK( vec_pop_back(). back() == CUSTOM_CAP - 2 ) ;

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

        CONSTEXPR_CHECK( vec_pop_back_front_val()     ==              0 ) ;
        CONSTEXPR_CHECK( vec_pop_back_front(). size() == CUSTOM_CAP - 2 ) ;
        CONSTEXPR_CHECK( vec_pop_back_front().front() ==              1 ) ;
        CONSTEXPR_CHECK( vec_pop_back_front(). back() == CUSTOM_CAP - 2 ) ;
}

TEMPLATE_LIST_TEST_CASE( "vector::reserve", "[vector][modify][reserve]", uti_test_types )
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

TEMPLATE_LIST_TEST_CASE( "vector::shrink", "[vector][modify][shrink]", uti_test_types )
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

TEST_CASE( "vector::insert", "[vector][modify][insert]" )
{
        container_type< int > vecint( CUSTOM_CAP, {} ) ;

        for( ssize_t i = 0; i < vecint.size(); ++i )
        {
                vecint.at( i ) = i ;
        }

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
                        CHECK( vecint.at( i ) == i - 1 ) ;
                }
                else
                {
                        CHECK( vecint.at( i ) == i - 2 ) ;
                }
        }
}

TEMPLATE_LIST_TEST_CASE( "vector::erase", "[vector][modify][erase]", uti_test_types )
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

TEST_CASE( "vector::clear", "[vector][modify][clear]" )
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

TEST_CASE( "vector::iterate", "[vector][access][iterate]" )
{
        container_type< int > vec( CUSTOM_CAP ) ;

        for( auto const & val : vec )
        {
                CHECK( val == 0 ) ;
        }
}

TEST_CASE( "vector::no_double_free", "[vector][dtor]" )
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
