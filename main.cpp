//
//
//	uti
//	main.cpp
//

#include <container/variant_vector.hpp>


using resource = uti::static_bump_resource< 1 * 1024 * 1024 > ;

constexpr void print_all ( auto const & vv ) noexcept
{
        std::cout << "\n================================================================================\n" ;

        for( int i = 0; i < vv.size(); ++i )
        {
                vv.visit( i, uti::visitor{
                        []( int         const & val ){ std::cout << "int    : " << val << "\n" ; } ,
                        []( char        const & val ){ std::cout << "char   : " << val << "\n" ; } ,
                        []( double      const & val ){ std::cout << "double : " << val << "\n" ; } ,
                        []( std::string const & val ){ std::cout << "string : " << val << "\n" ; } ,
                } ) ;
        }
        std::cout << "================================================================================\n" ;
}

constexpr void dump_memory ( void const * _ptr_, uti::ssize_t const _len_ ) noexcept ;

int main ()
{
        uti::variant_vector< resource, int, char, double, std::string > vv ;

        for( int i = 0; i < 12; ++i )
        {
                int offset = i / 4 ;

                if( i % 4 == 0 )
                {
                        vv.push_back< int >( 128 + offset ) ;
                }
                else if( i % 4 == 1 )
                {
                        vv.push_back< char >( 'a' + offset ) ;
                }
                else if( i % 4 == 2 )
                {
                        vv.push_back< double >( 1.1 + offset * 0.1 ) ;
                }
                else
                {
                        vv.push_back< std::string >( std::string( "hello" ).append( std::to_string( offset ) ) ) ;
                }
                print_all( vv ) ;
        }


        return 0 ;
}

constexpr void dump_memory ( void const * _ptr_, uti::ssize_t const _len_ ) noexcept
{
        printf( "\n========================================================================================\n" ) ;

        uti::u8_t const * buff = static_cast< uti::u8_t const * >( _ptr_ ) ;

        for( uti::i32_t i = 0; i < _len_; i += 16 )
        {
                printf( "%06x : ", i ) ;
                printf( "%p : ", static_cast< void const * >( buff + i ) ) ;

                for( uti::i32_t j = 0; j < 16; ++j )
                {
                        if( i + j < _len_ )
                        {
                                printf( "%02x ", buff[ i + j ] ) ;
                        }
                        else
                        {
                                printf( "    " ) ;
                        }
                }
                printf( " " ) ;

                for( uti::i32_t j = 0; j < 16; ++j )
                {
                        if( i + j < _len_ )
                        {
                                printf( "%c", isprint( buff[ i + j ] ) ? buff[ i + j ] : '.' ) ;
                        }
                }
                printf( "\n" ) ;
        }
        printf( "========================================================================================\n\n" ) ;
}
