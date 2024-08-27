//
//
//      uti
//      gtest_iterator.cpp
//

#include "gtest_iterator.hpp"


TEST( IteratorTest, IteratorTraits )
{
        using   input_iter = uti::iterator_base< int, uti::        input_iterator_tag > ;
        using forward_iter = uti::iterator_base< int, uti::      forward_iterator_tag > ;
        using    bidi_iter = uti::iterator_base< int, uti::bidirectional_iterator_tag > ;
        using  random_iter = uti::iterator_base< int, uti::random_access_iterator_tag > ;
        using  prefix_iter = uti::iterator_base< int, uti:: prefix_array_iterator_tag > ;

        using pointer = int * ;

        static_assert( uti::meta::iterator<   input_iter > ) ;
        static_assert( uti::meta::iterator< forward_iter > ) ;
        static_assert( uti::meta::iterator<    bidi_iter > ) ;
        static_assert( uti::meta::iterator<  random_iter > ) ;
        static_assert( uti::meta::iterator<  prefix_iter > ) ;
        static_assert( uti::meta::iterator<      pointer > ) ;

        static_assert( uti::meta::input_iterator<   input_iter > ) ;
        static_assert( uti::meta::input_iterator< forward_iter > ) ;
        static_assert( uti::meta::input_iterator<    bidi_iter > ) ;
        static_assert( uti::meta::input_iterator<  random_iter > ) ;
        static_assert( uti::meta::input_iterator<  prefix_iter > ) ;
        static_assert( uti::meta::input_iterator<      pointer > ) ;

        static_assert( !uti::meta::forward_iterator<   input_iter > ) ;
        static_assert(  uti::meta::forward_iterator< forward_iter > ) ;
        static_assert(  uti::meta::forward_iterator<    bidi_iter > ) ;
        static_assert(  uti::meta::forward_iterator<  random_iter > ) ;
        static_assert(  uti::meta::forward_iterator<  prefix_iter > ) ;
        static_assert(  uti::meta::forward_iterator<      pointer > ) ;

        static_assert( !uti::meta::bidirectional_iterator<   input_iter > ) ;
        static_assert( !uti::meta::bidirectional_iterator< forward_iter > ) ;
        static_assert(  uti::meta::bidirectional_iterator<    bidi_iter > ) ;
        static_assert(  uti::meta::bidirectional_iterator<  random_iter > ) ;
        static_assert(  uti::meta::bidirectional_iterator<  prefix_iter > ) ;
        static_assert(  uti::meta::bidirectional_iterator<      pointer > ) ;

        static_assert( !uti::meta::random_access_iterator<   input_iter > ) ;
        static_assert( !uti::meta::random_access_iterator< forward_iter > ) ;
        static_assert( !uti::meta::random_access_iterator<    bidi_iter > ) ;
        static_assert(  uti::meta::random_access_iterator<  random_iter > ) ;
        static_assert(  uti::meta::random_access_iterator<  prefix_iter > ) ;
        static_assert(  uti::meta::random_access_iterator<      pointer > ) ;

        static_assert( !uti::meta::prefix_array_iterator<   input_iter > ) ;
        static_assert( !uti::meta::prefix_array_iterator< forward_iter > ) ;
        static_assert( !uti::meta::prefix_array_iterator<    bidi_iter > ) ;
        static_assert( !uti::meta::prefix_array_iterator<  random_iter > ) ;
        static_assert(  uti::meta::prefix_array_iterator<  prefix_iter > ) ;
        static_assert( !uti::meta::prefix_array_iterator<      pointer > ) ;

        static_assert( uti::is_constructible_v< uti::iterator_base< int, uti::prefix_array_iterator_tag > > ) ;
}
