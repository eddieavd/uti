//
//
//      uti.test
//      allocator.test.cxx
//

#include <snitch/snitch.hpp>

#include <uti.hxx>


TEST_CASE( "allocator::malloc_resource::string", "[allocator][malloc][string]" )
{
        using resource = uti::malloc_resource ;

        using string = uti::generic_string< char, uti::allocator< char, resource > > ;

        auto void_block = resource::allocate( sizeof( string ) * 4, alignof( string ) ) ;
        auto string_block = static_cast< uti::block_t< string > >( void_block ) ;

        for( int i = 0; i < 4; ++i )
        {
                uti::construct( string_block.begin() + i, '0' + i, 32 ) ;
        }
        for( int i = 0; i < 4; ++i )
        {
                CHECK( *( string_block.begin() + i ) == string( '0' + i, 32 ) ) ;
        }
        for( int i = 0; i < 4; ++i )
        {
                uti::destroy( string_block.begin() + i ) ;
        }
        resource::deallocate( void_block ) ;
}

TEST_CASE( "allocator::malloc_resource::vector", "[allocator][malloc][vector]" )
{
        using resource = uti::malloc_resource ;

        using string = uti::generic_string< char, uti::allocator< char, resource > > ;

        using vector_int = uti::vector<    int, uti::allocator<    int, resource > > ;
        using vector_str = uti::vector< string, uti::allocator< string, resource > > ;

        auto void_block_vi = resource::allocate( sizeof( vector_int ), alignof( vector_int ) ) ;
        auto void_block_vs = resource::allocate( sizeof( vector_str ), alignof( vector_str ) ) ;

        auto type_block_vi = static_cast< uti::block_t< vector_int > >( void_block_vi ) ;
        auto type_block_vs = static_cast< uti::block_t< vector_str > >( void_block_vs ) ;

        uti::construct( type_block_vi.begin() ) ;
        uti::construct( type_block_vs.begin() ) ;

        vector_int & vec_int = *type_block_vi.begin() ;
        vector_str & vec_str = *type_block_vs.begin() ;

        for( int i = 0; i < 26; ++i )
        {
                vec_int.push_back( i ) ;
                vec_str.emplace_back( '0' + i, 32 ) ;
        }
        for( int i = 0; i < 26; ++i )
        {
                CHECK( vec_int.at( i ) == i ) ;
                CHECK( vec_str.at( i ) == string( '0' + i, 32 ) ) ;
        }

        uti::destroy( type_block_vi.begin() ) ;
        uti::destroy( type_block_vs.begin() ) ;

        resource::deallocate( void_block_vi ) ;
        resource::deallocate( void_block_vs ) ;
}

TEST_CASE( "allocator::static_bump_resource::string", "[allocator][static_bump][string]" )
{
        using resource = uti::static_bump_resource< 1024 * 1024 > ;

        using string = uti::generic_string< char, uti::allocator< char, resource > > ;

        auto void_block = resource::allocate( sizeof( string ) * 4, alignof( string ) ) ;
        auto string_block = static_cast< uti::block_t< string > >( void_block ) ;

        for( int i = 0; i < 4; ++i )
        {
                uti::construct( string_block.begin() + i, '0' + i, 32 ) ;
        }
        for( int i = 0; i < 4; ++i )
        {
                CHECK( *( string_block.begin() + i ) == string( '0' + i, 32 ) ) ;
        }
        for( int i = 0; i < 4; ++i )
        {
                uti::destroy( string_block.begin() + i ) ;
        }
        resource::deallocate( void_block ) ;
}

TEST_CASE( "allocator::static_bump_resource::vector", "[allocator][static_bump][vector]" )
{
        using resource = uti::static_bump_resource< 1024 * 1024 > ;

        using string = uti::generic_string< char, uti::allocator< char, resource > > ;

        using vector_int = uti::vector<    int, uti::allocator<    int, resource > > ;
        using vector_str = uti::vector< string, uti::allocator< string, resource > > ;

        auto void_block_vi = resource::allocate( sizeof( vector_int ), alignof( vector_int ) ) ;
        auto void_block_vs = resource::allocate( sizeof( vector_str ), alignof( vector_str ) ) ;

        auto type_block_vi = static_cast< uti::block_t< vector_int > >( void_block_vi ) ;
        auto type_block_vs = static_cast< uti::block_t< vector_str > >( void_block_vs ) ;

        uti::construct( type_block_vi.begin() ) ;
        uti::construct( type_block_vs.begin() ) ;

        vector_int & vec_int = *type_block_vi.begin() ;
        vector_str & vec_str = *type_block_vs.begin() ;

        for( int i = 0; i < 26; ++i )
        {
                vec_int.push_back( i ) ;
                vec_str.emplace_back( '0' + i, 32 ) ;
        }
        for( int i = 0; i < 26; ++i )
        {
                CHECK( vec_int.at( i ) == i ) ;
                CHECK( vec_str.at( i ) == string( '0' + i, 32 ) ) ;
        }

        uti::destroy( type_block_vi.begin() ) ;
        uti::destroy( type_block_vs.begin() ) ;

        resource::deallocate( void_block_vi ) ;
        resource::deallocate( void_block_vs ) ;
}
TEST_CASE( "allocator::static_freelist_resource::string", "[allocator][static_freelist][string]" )
{
        using resource = uti::static_freelist_resource< 1024 * 1024 > ;

        using string = uti::generic_string< char, uti::allocator< char, resource > > ;

        auto void_block = resource::allocate( sizeof( string ) * 4, alignof( string ) ) ;
        auto string_block = static_cast< uti::block_t< string > >( void_block ) ;

        for( int i = 0; i < 4; ++i )
        {
                uti::construct( string_block.begin() + i, '0' + i, 32 ) ;
        }
        for( int i = 0; i < 4; ++i )
        {
                CHECK( *( string_block.begin() + i ) == string( '0' + i, 32 ) ) ;
        }
        for( int i = 0; i < 4; ++i )
        {
                uti::destroy( string_block.begin() + i ) ;
        }
        resource::deallocate( void_block ) ;
}

TEST_CASE( "allocator::static_freelist_resource::vector", "[allocator][static_freelist][vector]" )
{
        using resource = uti::static_freelist_resource< 1024 * 1024 > ;

        using string = uti::generic_string< char, uti::allocator< char, resource > > ;

        using vector_int = uti::vector<    int, uti::allocator<    int, resource > > ;
        using vector_str = uti::vector< string, uti::allocator< string, resource > > ;

        auto void_block_vi = resource::allocate( sizeof( vector_int ), alignof( vector_int ) ) ;
        auto void_block_vs = resource::allocate( sizeof( vector_str ), alignof( vector_str ) ) ;

        auto type_block_vi = static_cast< uti::block_t< vector_int > >( void_block_vi ) ;
        auto type_block_vs = static_cast< uti::block_t< vector_str > >( void_block_vs ) ;

        uti::construct( type_block_vi.begin() ) ;
        uti::construct( type_block_vs.begin() ) ;

        vector_int & vec_int = *type_block_vi.begin() ;
        vector_str & vec_str = *type_block_vs.begin() ;

        for( int i = 0; i < 26; ++i )
        {
                vec_int.push_back( i ) ;
                vec_str.emplace_back( '0' + i, 32 ) ;
        }
        for( int i = 0; i < 26; ++i )
        {
                CHECK( vec_int.at( i ) == i ) ;
                CHECK( vec_str.at( i ) == string( '0' + i, 32 ) ) ;
        }

        uti::destroy( type_block_vi.begin() ) ;
        uti::destroy( type_block_vs.begin() ) ;

        resource::deallocate( void_block_vi ) ;
        resource::deallocate( void_block_vs ) ;
}
