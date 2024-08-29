//
//
//      uti
//      gtest_string.cpp
//

#include "gtest_string.hpp"


TEST( StringTest, DefaultConstruct )
{
        uti::string str ;

        EXPECT_EQ( str.    size(),    0 ) ;
        EXPECT_EQ( str.capacity(),    0 ) ;
        EXPECT_EQ( str.   empty(), true ) ;
}

TEST( StringTest, ReserveConstruct )
{
        for( uti::ssize_t i = 0; i <= UTI_SSO_CAP; ++i )
        {
                uti::string str( i ) ;

                EXPECT_EQ( str.    size(),           0 ) ;
                EXPECT_EQ( str.capacity(), UTI_SSO_CAP ) ;
                EXPECT_EQ( str.   empty(),        true ) ;
        }
        for( uti::ssize_t i = UTI_SSO_CAP + 1; i < 1024; ++i )
        {
                uti::string str( i ) ;

                EXPECT_EQ( str.    size(),    0 ) ;
                EXPECT_EQ( str.capacity(),    i ) ;
                EXPECT_EQ( str.   empty(), true ) ;
        }
}

TEST( StringTest, CStrConstruct )
{
        char const * cstr1 = "hello world from stack" ;
        char const * cstr2 = "hello world from the heap!" ;

        auto len1 = ::uti::strlen( cstr1 ) ;
        auto len2 = ::uti::strlen( cstr2 ) ;

        uti::string str1( cstr1 ) ;
        uti::string str2( cstr2 ) ;

        EXPECT_EQ( str1.    size(),        len1 ) ;
        EXPECT_EQ( str1.capacity(), UTI_SSO_CAP ) ;
        EXPECT_EQ( str1.   empty(),       false ) ;

        EXPECT_EQ( str2.    size(),  len2     ) ;
        EXPECT_EQ( str2.capacity(),  len2 + 1 ) ;
        EXPECT_EQ( str2.   empty(), false     ) ;
}

TEST( StringTest, PtrConstruct )
{
        char const * cstr1 = "hello world from stack" ;
        char const * cstr2 = "hello world from the heap!" ;

        auto len1 =  5 ;
        auto len2 = 24 ;

        uti::string str1( cstr1, len1 ) ;
        uti::string str2( cstr2, len2 ) ;

        EXPECT_EQ( str1.    size(),        len1 ) ;
        EXPECT_EQ( str1.capacity(), UTI_SSO_CAP ) ;
        EXPECT_EQ( str1.   empty(),       false ) ;

        EXPECT_EQ( str2.    size(),  len2     ) ;
        EXPECT_EQ( str2.capacity(),  len2 + 1 ) ;
        EXPECT_EQ( str2.   empty(), false     ) ;
}

TEST( StringTest, IteratorConstruct )
{
        uti::string src1( "hello world from stack" ) ;
        uti::string src2( "hello world from the heap!" ) ;

        uti::string str1( src1.begin(), src1.end() ) ;
        uti::string str2( src2.begin(), src2.end() ) ;

        EXPECT_EQ( str1. size(), src1.size() ) ;
        EXPECT_EQ( str1.empty(),       false ) ;

        EXPECT_EQ( str2. size(), src2.size() ) ;
        EXPECT_EQ( str2.empty(),       false ) ;
}

TEST( StringTest, Copy )
{
        uti::string src1( "hello world from stack" ) ;
        uti::string src2( "hello world from the heap!" ) ;

        uti::string str1( src1 ) ;
        uti::string str2( src2 ) ;

        EXPECT_EQ( str1.    size(), src1.size() ) ;
        EXPECT_EQ( str1.capacity(), UTI_SSO_CAP ) ;
        EXPECT_EQ( str1.   empty(),       false ) ;

        EXPECT_EQ( str2.    size(), src2.size()     ) ;
        EXPECT_EQ( str2.capacity(), src2.size() + 1 ) ;
        EXPECT_EQ( str2.   empty(), false           ) ;

        str1 = src2 ;
        str2 = src1 ;

        EXPECT_EQ( str1.    size(), src2.size()     ) ;
        EXPECT_EQ( str1.capacity(), src2.size() + 1 ) ;
        EXPECT_EQ( str1.   empty(), false           ) ;

        EXPECT_EQ( str2. size(), src1.size() ) ;
        EXPECT_EQ( str2.empty(),       false ) ;
}

TEST( StringTest, Move )
{
        uti::string src1( "hello world from stack" ) ;
        uti::string src2( "hello world from the heap!" ) ;

        auto src11( src1 ) ;
        auto src22( src2 ) ;

        auto len1 = ::uti::strlen( src1.c_str() ) ;
        auto len2 = ::uti::strlen( src2.c_str() ) ;

        uti::string str1( UTI_MOVE( src1 ) ) ;
        uti::string str2( UTI_MOVE( src2 ) ) ;

        EXPECT_EQ( str1. size(),  len1 ) ;
        EXPECT_EQ( str1.empty(), false ) ;

        EXPECT_EQ( str2. size(),  len2 ) ;
        EXPECT_EQ( str2.empty(), false ) ;

        EXPECT_EQ( src1.    size(),    0 ) ;
        EXPECT_EQ( src1.capacity(),    0 ) ;
        EXPECT_EQ( src1.   empty(), true ) ;

        EXPECT_EQ( src2.    size(),    0 ) ;
        EXPECT_EQ( src2.capacity(),    0 ) ;
        EXPECT_EQ( src2.   empty(), true ) ;

        str1 = UTI_MOVE( src22 ) ;
        str2 = UTI_MOVE( src11 ) ;

        EXPECT_EQ( str1. size(),  len2 ) ;
        EXPECT_EQ( str1.empty(), false ) ;

        EXPECT_EQ( str2. size(),  len1 ) ;
        EXPECT_EQ( str2.empty(), false ) ;

        EXPECT_EQ( src11.    size(),    0 ) ;
        EXPECT_EQ( src11.capacity(),    0 ) ;
        EXPECT_EQ( src11.   empty(), true ) ;

        EXPECT_EQ( src22.    size(),    0 ) ;
        EXPECT_EQ( src22.capacity(),    0 ) ;
        EXPECT_EQ( src22.   empty(), true ) ;
}

TEST( StringTest, PushBack )
{
        uti::string str1 ;
        uti::string str2( 4 ) ;
        uti::string str3( UTI_SSO_CAP * 2 ) ;
        uti::string str4( "hello world from stack" ) ;
        uti::string str5( "hello world from the heap!" ) ;

        auto len1 = str1.size() ;
        auto len2 = str4.size() ;
        auto len3 = str5.size() ;

        EXPECT_EQ( str4.back(), 'k' ) ;
        EXPECT_EQ( str5.back(), '!' ) ;

        str1.push_back( 'x' ) ;
        str2.push_back( 'x' ) ;
        str3.push_back( 'x' ) ;
        str4.push_back( 'x' ) ;
        str5.push_back( 'x' ) ;

        EXPECT_EQ( str1.size(), len1 + 1 ) ;
        EXPECT_EQ( str2.size(), len1 + 1 ) ;
        EXPECT_EQ( str3.size(), len1 + 1 ) ;
        EXPECT_EQ( str4.size(), len2 + 1 ) ;
        EXPECT_EQ( str5.size(), len3 + 1 ) ;

        EXPECT_EQ( str1.back(), 'x' ) ;
        EXPECT_EQ( str2.back(), 'x' ) ;
        EXPECT_EQ( str3.back(), 'x' ) ;
        EXPECT_EQ( str4.back(), 'x' ) ;
        EXPECT_EQ( str5.back(), 'x' ) ;

        str1.push_back( 'y' ) ;
        str2.push_back( 'y' ) ;
        str3.push_back( 'y' ) ;
        str4.push_back( 'y' ) ;
        str5.push_back( 'y' ) ;

        EXPECT_EQ( str1.size(), len1 + 2 ) ;
        EXPECT_EQ( str2.size(), len1 + 2 ) ;
        EXPECT_EQ( str3.size(), len1 + 2 ) ;
        EXPECT_EQ( str4.size(), len2 + 2 ) ;
        EXPECT_EQ( str5.size(), len3 + 2 ) ;

        EXPECT_EQ( str1.back(), 'y' ) ;
        EXPECT_EQ( str2.back(), 'y' ) ;
        EXPECT_EQ( str3.back(), 'y' ) ;
        EXPECT_EQ( str4.back(), 'y' ) ;
        EXPECT_EQ( str5.back(), 'y' ) ;
}

TEST( StringTest, Append )
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
                        EXPECT_EQ( x.back(), a.back() ) ;
                        EXPECT_EQ( x.size(), len + 1 ) ;
                }
                if( i % 4 == 1 )
                {
                        x.append( b ) ;
                        EXPECT_EQ( x.back(), b.back() ) ;
                        EXPECT_EQ( x.size(), len + 1 ) ;
                }
                if( i % 4 == 2 )
                {
                        x.append( c ) ;
                        EXPECT_EQ( x.back(), c.back() ) ;
                        EXPECT_EQ( x.size(), len + 1 ) ;
                }
                if( i % 4 == 3 )
                {
                        x.append( big ) ;
                        EXPECT_EQ( x.back(), big.back() ) ;
                        EXPECT_EQ( x.size(), len + big.size() ) ;
                }
                len = x.size() ;
        }
}

TEST( StringTest, Insert )
{
        uti::string str1 ;
        uti::string str2( 4 ) ;
        uti::string str3( UTI_SSO_CAP * 2 ) ;
        uti::string str4( "hello from stack" ) ;
        uti::string str5( "hello world from the heap!!!" ) ;

        auto len1 = 0 ;
        auto len2 = str4.size() ;
        auto len3 = str5.size() ;

        str1.insert( 0, 'x' ) ;
        str2.insert( 0, 'x' ) ;
        str3.insert( 0, 'x' ) ;
        str4.insert( 0, 'x' ) ;
        str5.insert( 0, 'x' ) ;

        EXPECT_EQ( str1.front(), 'x' ) ;
        EXPECT_EQ( str2.front(), 'x' ) ;
        EXPECT_EQ( str3.front(), 'x' ) ;
        EXPECT_EQ( str4.front(), 'x' ) ;
        EXPECT_EQ( str5.front(), 'x' ) ;

        EXPECT_EQ( str1.size(), len1 + 1 ) ;
        EXPECT_EQ( str2.size(), len1 + 1 ) ;
        EXPECT_EQ( str3.size(), len1 + 1 ) ;
        EXPECT_EQ( str4.size(), len2 + 1 ) ;
        EXPECT_EQ( str5.size(), len3 + 1 ) ;

        str1.insert( 99, 'y' ) ;
        str2.insert( 99, 'y' ) ;
        str3.insert( 99, 'y' ) ;
        str4.insert( 99, 'y' ) ;
        str5.insert( 99, 'y' ) ;

        EXPECT_EQ( str1.back(), 'y' ) ;
        EXPECT_EQ( str2.back(), 'y' ) ;
        EXPECT_EQ( str3.back(), 'y' ) ;
        EXPECT_EQ( str4.back(), 'y' ) ;
        EXPECT_EQ( str5.back(), 'y' ) ;

        EXPECT_EQ( str1.size(), len1 + 2 ) ;
        EXPECT_EQ( str2.size(), len1 + 2 ) ;
        EXPECT_EQ( str3.size(), len1 + 2 ) ;
        EXPECT_EQ( str4.size(), len2 + 2 ) ;
        EXPECT_EQ( str5.size(), len3 + 2 ) ;

        str1.insert( str1.size() / 2, 'z' ) ;
        str2.insert( str2.size() / 2, 'z' ) ;
        str3.insert( str3.size() / 2, 'z' ) ;
        str4.insert( str4.size() / 2, 'z' ) ;
        str5.insert( str5.size() / 2, 'z' ) ;

        EXPECT_EQ( str1.at( str1.size() / 2 ), 'z' ) ;
        EXPECT_EQ( str2.at( str2.size() / 2 ), 'z' ) ;
        EXPECT_EQ( str3.at( str3.size() / 2 ), 'z' ) ;
        EXPECT_EQ( str4.at( str4.size() / 2 ), 'z' ) ;
        EXPECT_EQ( str5.at( str5.size() / 2 ), 'z' ) ;

        EXPECT_EQ( str1.size(), len1 + 3 ) ;
        EXPECT_EQ( str2.size(), len1 + 3 ) ;
        EXPECT_EQ( str3.size(), len1 + 3 ) ;
        EXPECT_EQ( str4.size(), len2 + 3 ) ;
        EXPECT_EQ( str5.size(), len3 + 3 ) ;
}
