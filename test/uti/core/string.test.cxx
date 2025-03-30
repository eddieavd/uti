//
//
//      uti.core.test
//      string.test.cxx
//

#include <snitch/snitch.hpp>

#include "uti.core.test.hxx"


TEST_CASE( "string::ctor_default", "[string][ctor][ctor_default]" )
{
        CONSTEXPR_CHECK( uti::string().    size() ==                         0 ) ;
        CONSTEXPR_CHECK( uti::string().capacity() == uti::string::sso_capacity ) ;
        CONSTEXPR_CHECK( uti::string().   empty() ==                      true ) ;
}

TEST_CASE( "string::ctor_reserve", "[string][ctor][ctor_reserve]" )
{
        for( uti::ssize_t i = 0; i <= uti::string::sso_capacity; ++i )
        {
                uti::string str( i ) ;

                CHECK( str.    size() ==                         0 ) ;
                CHECK( str.capacity() == uti::string::sso_capacity ) ;
                CHECK( str.   empty() ==                      true ) ;
        }
        for( uti::ssize_t i = uti::string::sso_capacity + 1; i < 1024; ++i )
        {
                uti::string str( i ) ;

                CHECK( str.    size() ==     0 ) ;
                CHECK( str.capacity() == i + 1 ) ;
                CHECK( str.   empty() ==  true ) ;
        }
}

TEST_CASE( "string::ctor_cstr", "[string][ctor][ctor_cstr]" )
{
        char const * cstr1 = "hello world from stack" ;
        char const * cstr2 = "hello world from the heap!" ;

        auto len1 = ::uti::strlen( cstr1 ) ;
        auto len2 = ::uti::strlen( cstr2 ) ;

        uti::string str1( cstr1 ) ;
        uti::string str2( cstr2 ) ;

        CHECK( str1.    size() ==        len1 ) ;
        CHECK( str1.capacity() == UTI_SSO_CAP ) ;
        CHECK( str1.   empty() ==       false ) ;

        CHECK( str2.    size() ==  len2     ) ;
        CHECK( str2.capacity() ==  len2 + 1 ) ;
        CHECK( str2.   empty() == false     ) ;
}

TEST_CASE( "string::ctor_ptr", "[string][ctor][ctor_ptr]" )
{
        char const * cstr1 = "hello world from stack" ;
        char const * cstr2 = "hello world from the heap!" ;

        auto len1 =  5 ;
        auto len2 = 24 ;

        uti::string str1( cstr1, len1 ) ;
        uti::string str2( cstr2, len2 ) ;

        CHECK( str1.    size() ==        len1 ) ;
        CHECK( str1.capacity() == UTI_SSO_CAP ) ;
        CHECK( str1.   empty() ==       false ) ;

        CHECK( str2.    size() ==  len2     ) ;
        CHECK( str2.capacity() ==  len2 + 1 ) ;
        CHECK( str2.   empty() == false     ) ;
}

TEST_CASE( "string::ctor_iter", "[string][ctor][ctor_iter]" )
{
        uti::string src1( "hello world from stack" ) ;
        uti::string src2( "hello world from the heap!" ) ;

        uti::string str1( src1.begin(), src1.end() ) ;
        uti::string str2( src2.begin(), src2.end() ) ;

        CHECK( str1. size() == src1.size() ) ;
        CHECK( str1.empty() ==       false ) ;

        CHECK( str2. size() == src2.size() ) ;
        CHECK( str2.empty() ==       false ) ;
}

TEST_CASE( "string::copy", "[string][ctor][ctor_copy][assign_copy]" )
{
        uti::string src1( "hello world from stack" ) ;
        uti::string src2( "hello world from the heap!" ) ;

        uti::string str1( src1 ) ;
        uti::string str2( src2 ) ;

        CHECK( str1.    size() == src1.size() ) ;
        CHECK( str1.capacity() == UTI_SSO_CAP ) ;
        CHECK( str1.   empty() ==       false ) ;

        CHECK( str2.    size() == src2.size()     ) ;
        CHECK( str2.capacity() == src2.size() + 1 ) ;
        CHECK( str2.   empty() == false           ) ;

        str1 = src2 ;
        str2 = src1 ;

        CHECK( str1.    size() == src2.size()     ) ;
        CHECK( str1.capacity() == src2.size() + 1 ) ;
        CHECK( str1.   empty() == false           ) ;

        CHECK( str2. size() == src1.size() ) ;
        CHECK( str2.empty() ==       false ) ;
}

TEST_CASE( "string::move", "[string][ctor][ctor_move][assign_move]" )
{
        uti::string src1( "hello world from stack" ) ;
        uti::string src2( "hello world from the heap!" ) ;

        auto src11( src1 ) ;
        auto src22( src2 ) ;

        auto len1 = ::uti::strlen( src1.c_str() ) ;
        auto len2 = ::uti::strlen( src2.c_str() ) ;

        uti::string str1( UTI_MOVE( src1 ) ) ;
        uti::string str2( UTI_MOVE( src2 ) ) ;

        CHECK( str1. size() ==  len1 ) ;
        CHECK( str1.empty() == false ) ;

        CHECK( str2. size() ==  len2 ) ;
        CHECK( str2.empty() == false ) ;

        CHECK( src1.    size() ==                         0 ) ;
        CHECK( src1.capacity() == uti::string::sso_capacity ) ;
        CHECK( src1.   empty() ==                      true ) ;

        CHECK( src2.    size() ==                         0 ) ;
        CHECK( src2.capacity() == uti::string::sso_capacity ) ;
        CHECK( src2.   empty() ==                      true ) ;

        str1 = UTI_MOVE( src22 ) ;
        str2 = UTI_MOVE( src11 ) ;

        CHECK( str1. size() ==  len2 ) ;
        CHECK( str1.empty() == false ) ;

        CHECK( str2. size() ==  len1 ) ;
        CHECK( str2.empty() == false ) ;

        CHECK( src11.    size() ==                         0 ) ;
        CHECK( src11.capacity() == uti::string::sso_capacity ) ;
        CHECK( src11.   empty() ==                      true ) ;

        CHECK( src22.    size() ==                         0 ) ;
        CHECK( src22.capacity() == uti::string::sso_capacity ) ;
        CHECK( src22.   empty() ==                      true ) ;
}

TEST_CASE( "string::push_back", "[string][modify][push_back]" )
{
        uti::string str1 ;
        uti::string str2( 4 ) ;
        uti::string str3( UTI_SSO_CAP * 2 ) ;
        uti::string str4( "hello world from stack" ) ;
        uti::string str5( "hello world from the heap!" ) ;

        auto len1 = str1.size() ;
        auto len2 = str4.size() ;
        auto len3 = str5.size() ;

        CHECK( str4.back() == 'k' ) ;
        CHECK( str5.back() == '!' ) ;

        str1.push_back( 'x' ) ;
        str2.push_back( 'x' ) ;
        str3.push_back( 'x' ) ;
        str4.push_back( 'x' ) ;
        str5.push_back( 'x' ) ;

        CHECK( str1.size() == len1 + 1 ) ;
        CHECK( str2.size() == len1 + 1 ) ;
        CHECK( str3.size() == len1 + 1 ) ;
        CHECK( str4.size() == len2 + 1 ) ;
        CHECK( str5.size() == len3 + 1 ) ;

        CHECK( str1.back() == 'x' ) ;
        CHECK( str2.back() == 'x' ) ;
        CHECK( str3.back() == 'x' ) ;
        CHECK( str4.back() == 'x' ) ;
        CHECK( str5.back() == 'x' ) ;

        str1.push_back( 'y' ) ;
        str2.push_back( 'y' ) ;
        str3.push_back( 'y' ) ;
        str4.push_back( 'y' ) ;
        str5.push_back( 'y' ) ;

        CHECK( str1.size() == len1 + 2 ) ;
        CHECK( str2.size() == len1 + 2 ) ;
        CHECK( str3.size() == len1 + 2 ) ;
        CHECK( str4.size() == len2 + 2 ) ;
        CHECK( str5.size() == len3 + 2 ) ;

        CHECK( str1.back() == 'y' ) ;
        CHECK( str2.back() == 'y' ) ;
        CHECK( str3.back() == 'y' ) ;
        CHECK( str4.back() == 'y' ) ;
        CHECK( str5.back() == 'y' ) ;
}

TEST_CASE( "string::append", "[string][modify][append]" )
{
        uti::string x( "x" ) ;
        uti::string a( "a" ) ;
        uti::string b( "b" ) ;
        uti::string c( "c" ) ;

        uti::string big( "hello world from the heap!!!" ) ;

        auto len = x.size() ;

        for( int i = 0; i < 1000; ++i )
        {
                if( i % 4 == 0 )
                {
                        x.append( a ) ;
                        CHECK( x.back() == a.back() ) ;
                        CHECK( x.size() == len + 1 ) ;
                }
                if( i % 4 == 1 )
                {
                        x.append( b ) ;
                        CHECK( x.back() == b.back() ) ;
                        CHECK( x.size() == len + 1 ) ;
                }
                if( i % 4 == 2 )
                {
                        x.append( c ) ;
                        CHECK( x.back() == c.back() ) ;
                        CHECK( x.size() == len + 1 ) ;
                }
                if( i % 4 == 3 )
                {
                        x.append( big ) ;
                        CHECK( x.back() == big.back() ) ;
                        CHECK( x.size() == len + big.size() ) ;
                }
                len = x.size() ;
        }
}

TEST_CASE( "string::insert", "[string][modify][insert]" )
{
        uti::string str1 ;
        uti::string str2( 4 ) ;
        uti::string str3( UTI_SSO_CAP * 2 ) ;
        uti::string str4( "hello from stack" ) ;
        uti::string str5( "hello world from the heap!!!" ) ;

        auto len1 = 0 ;
        auto len2 = str4.size() ;
        auto len3 = str5.size() ;

        str1.insert( 'x', 0 ) ;
        str2.insert( 'x', 0 ) ;
        str3.insert( 'x', 0 ) ;
        str4.insert( 'x', 0 ) ;
        str5.insert( 'x', 0 ) ;

        CHECK( str1.front() == 'x' ) ;
        CHECK( str2.front() == 'x' ) ;
        CHECK( str3.front() == 'x' ) ;
        CHECK( str4.front() == 'x' ) ;
        CHECK( str5.front() == 'x' ) ;

        CHECK( str1.size() == len1 + 1 ) ;
        CHECK( str2.size() == len1 + 1 ) ;
        CHECK( str3.size() == len1 + 1 ) ;
        CHECK( str4.size() == len2 + 1 ) ;
        CHECK( str5.size() == len3 + 1 ) ;

        str1.insert( 'y', 99 ) ;
        str2.insert( 'y', 99 ) ;
        str3.insert( 'y', 99 ) ;
        str4.insert( 'y', 99 ) ;
        str5.insert( 'y', 99 ) ;

        CHECK( str1.back() == 'y' ) ;
        CHECK( str2.back() == 'y' ) ;
        CHECK( str3.back() == 'y' ) ;
        CHECK( str4.back() == 'y' ) ;
        CHECK( str5.back() == 'y' ) ;

        CHECK( str1.size() == len1 + 2 ) ;
        CHECK( str2.size() == len1 + 2 ) ;
        CHECK( str3.size() == len1 + 2 ) ;
        CHECK( str4.size() == len2 + 2 ) ;
        CHECK( str5.size() == len3 + 2 ) ;

        str1.insert( 'z', str1.size() / 2 ) ;
        str2.insert( 'z', str2.size() / 2 ) ;
        str3.insert( 'z', str3.size() / 2 ) ;
        str4.insert( 'z', str4.size() / 2 ) ;
        str5.insert( 'z', str5.size() / 2 ) ;

        CHECK( str1.at( str1.size() / 2 ) == 'z' ) ;
        CHECK( str2.at( str2.size() / 2 ) == 'z' ) ;
        CHECK( str3.at( str3.size() / 2 ) == 'z' ) ;
        CHECK( str4.at( str4.size() / 2 ) == 'z' ) ;
        CHECK( str5.at( str5.size() / 2 ) == 'z' ) ;

        CHECK( str1.size() == len1 + 3 ) ;
        CHECK( str2.size() == len1 + 3 ) ;
        CHECK( str3.size() == len1 + 3 ) ;
        CHECK( str4.size() == len2 + 3 ) ;
        CHECK( str5.size() == len3 + 3 ) ;
}
