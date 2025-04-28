//
//
//      uti.core.test
//      algo.test.cxx
//

#include <snitch/snitch.hpp>

#include <uti.core.hxx>


using allocator = uti::new_allocator< int > ;

TEST_CASE( "algo::advance", "[algo][advance]" )
{
        INFO( "algo::advance::input_iter" ) ;
        CONSTEXPR_CHECK( []
        {
                auto block = allocator::allocate( 4 ) ;

                for( int i = 0; i < 4; ++i )
                {
                        *( block.begin() + i ) = i ;
                }
                uti::iterator_base< int, uti::input_iterator_tag > iter( block.begin() ) ;

                if( *iter != 0 ) return false ;

                uti::advance( iter, 2 ) ;

                if( *iter != 2 ) return false ;

                allocator::deallocate( block ) ;

                return true ;
        }() ) ;

        INFO( "algo::advance::bidi_iter" ) ;
        CONSTEXPR_CHECK( []
        {
                auto block = allocator::allocate( 4 ) ;

                for( int i = 0; i < 4; ++i )
                {
                        *( block.begin() + i ) = i ;
                }
                uti::iterator_base< int, uti::bidirectional_iterator_tag > iter( block.begin() ) ;

                if( *iter != 0 ) return false ;

                uti::advance( iter, 2 ) ;

                if( *iter != 2 ) return false ;

                uti::advance( iter, -2 ) ;

                if( *iter != 0 ) return false ;

                allocator::deallocate( block ) ;

                return true ;
        }() ) ;

        INFO( "algo::advance::rand_iter" ) ;
        CONSTEXPR_CHECK( []
        {
                auto block = allocator::allocate( 4 ) ;

                for( int i = 0; i < 4; ++i )
                {
                        *( block.begin() + i ) = i ;
                }
                uti::iterator_base< int, uti::random_access_iterator_tag > iter( block.begin() ) ;

                if( *iter != 0 ) return false ;

                uti::advance( iter, 2 ) ;

                if( *iter != 2 ) return false ;

                uti::advance( iter, -2 ) ;

                if( *iter != 0 ) return false ;

                allocator::deallocate( block ) ;

                return true ;
        }() ) ;
}

TEST_CASE( "algo::distance", "[algo][distance]" )
{
        INFO( "algo::distance::input_iter" ) ;
        CONSTEXPR_CHECK( []
        {
                auto block = allocator::allocate( 4 ) ;

                uti::iterator_base< int, uti::input_iterator_tag > begin( block.begin() ) ;
                uti::iterator_base< int, uti::input_iterator_tag >   end( block.  end() ) ;

                if( uti::distance( begin, end ) != 4 ) return false ;

                allocator::deallocate( block ) ;

                return true ;
        }() ) ;

        INFO( "algo::distance::rand_iter" ) ;
        CONSTEXPR_CHECK( []
        {
                auto block = allocator::allocate( 4 ) ;

                uti::iterator_base< int, uti::random_access_iterator_tag > begin( block.begin() ) ;
                uti::iterator_base< int, uti::random_access_iterator_tag >   end( block.  end() ) ;

                if( uti::distance( begin, end ) != 4 ) return false ;

                allocator::deallocate( block ) ;

                return true ;
        }() ) ;
}

TEST_CASE( "algo::copy", "[algo][copy]" )
{
        CONSTEXPR_CHECK( []
        {
                auto block1 = allocator::allocate( 4 ) ;
                auto block2 = allocator::allocate( 4 ) ;

                for( int i = 0; i < 4; ++i )
                {
                        *( block1.begin() + i ) = i ;
                }
                for( int i = 0; i < 4; ++i )
                {
                        if( *( block1.begin() + i ) != i ) return false ;
                }
                auto  src_begin = block1.begin() ;
                auto  src_end   = block1.  end() ;
                auto dest_begin = block2.begin() ;

                uti::copy( src_begin, src_end, dest_begin ) ;

                for( int i = 0; i < 4; ++i )
                {
                        if( *( src_begin + i ) != *( dest_begin + i ) ) return false ;
                }
                allocator::deallocate( block2 ) ;
                allocator::deallocate( block1 ) ;

                return true ;
        }() ) ;
}
