//
//
//      uti.test
//      iterator.test.cxx
//

#include <snitch/snitch.hpp>

#include "uti.test.hxx"


TEMPLATE_LIST_TEST_CASE( "iterator::traits", "[iterator][traits]", all_test_types )
{
        using   input_iter = uti::iterator_base< TestType, uti::        input_iterator_tag > ;
        using forward_iter = uti::iterator_base< TestType, uti::      forward_iterator_tag > ;
        using    bidi_iter = uti::iterator_base< TestType, uti::bidirectional_iterator_tag > ;
        using  random_iter = uti::iterator_base< TestType, uti::random_access_iterator_tag > ;
        using  prefix_iter = uti::iterator_base< TestType, uti:: prefix_array_iterator_tag > ;

        using pointer = TestType * ;

        CONSTEVAL_CHECK( uti::meta::iterator<   input_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::iterator< forward_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::iterator<    bidi_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::iterator<  random_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::iterator<  prefix_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::iterator<      pointer > ) ;

        CONSTEVAL_CHECK( uti::meta::input_iterator<   input_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::input_iterator< forward_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::input_iterator<    bidi_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::input_iterator<  random_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::input_iterator<  prefix_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::input_iterator<      pointer > ) ;

        CONSTEVAL_CHECK( !uti::meta::forward_iterator<   input_iter > ) ;
        CONSTEVAL_CHECK(  uti::meta::forward_iterator< forward_iter > ) ;
        CONSTEVAL_CHECK(  uti::meta::forward_iterator<    bidi_iter > ) ;
        CONSTEVAL_CHECK(  uti::meta::forward_iterator<  random_iter > ) ;
        CONSTEVAL_CHECK(  uti::meta::forward_iterator<  prefix_iter > ) ;
        CONSTEVAL_CHECK(  uti::meta::forward_iterator<      pointer > ) ;

        CONSTEVAL_CHECK( !uti::meta::bidirectional_iterator<   input_iter > ) ;
        CONSTEVAL_CHECK( !uti::meta::bidirectional_iterator< forward_iter > ) ;
        CONSTEVAL_CHECK(  uti::meta::bidirectional_iterator<    bidi_iter > ) ;
        CONSTEVAL_CHECK(  uti::meta::bidirectional_iterator<  random_iter > ) ;
        CONSTEVAL_CHECK(  uti::meta::bidirectional_iterator<  prefix_iter > ) ;
        CONSTEVAL_CHECK(  uti::meta::bidirectional_iterator<      pointer > ) ;

        CONSTEVAL_CHECK( !uti::meta::random_access_iterator<   input_iter > ) ;
        CONSTEVAL_CHECK( !uti::meta::random_access_iterator< forward_iter > ) ;
        CONSTEVAL_CHECK( !uti::meta::random_access_iterator<    bidi_iter > ) ;
        CONSTEVAL_CHECK(  uti::meta::random_access_iterator<  random_iter > ) ;
        CONSTEVAL_CHECK(  uti::meta::random_access_iterator<  prefix_iter > ) ;
        CONSTEVAL_CHECK(  uti::meta::random_access_iterator<      pointer > ) ;

        CONSTEVAL_CHECK( !uti::meta::prefix_array_iterator<   input_iter > ) ;
        CONSTEVAL_CHECK( !uti::meta::prefix_array_iterator< forward_iter > ) ;
        CONSTEVAL_CHECK( !uti::meta::prefix_array_iterator<    bidi_iter > ) ;
        CONSTEVAL_CHECK( !uti::meta::prefix_array_iterator<  random_iter > ) ;
        CONSTEVAL_CHECK(  uti::meta::prefix_array_iterator<  prefix_iter > ) ;
        CONSTEVAL_CHECK( !uti::meta::prefix_array_iterator<      pointer > ) ;
}

TEMPLATE_LIST_TEST_CASE( "iterator::container", "[iterator][container]", all_test_types )
{
        using     prefix_iter = typename uti::prefix_array< TestType >::              iterator ;
        using   c_prefix_iter = typename uti::prefix_array< TestType >::        const_iterator ;
        using   r_prefix_iter = typename uti::prefix_array< TestType >::      reverse_iterator ;
        using c_r_prefix_iter = typename uti::prefix_array< TestType >::const_reverse_iterator ;

        CONSTEVAL_CHECK( uti::meta::prefix_array_iterator<     prefix_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::prefix_array_iterator<   c_prefix_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::prefix_array_iterator<   r_prefix_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::prefix_array_iterator< c_r_prefix_iter > ) ;

        using     vector_iter = typename uti::vector< TestType >::              iterator ;
        using   c_vector_iter = typename uti::vector< TestType >::        const_iterator ;
        using   r_vector_iter = typename uti::vector< TestType >::      reverse_iterator ;
        using c_r_vector_iter = typename uti::vector< TestType >::const_reverse_iterator ;

        CONSTEVAL_CHECK( !uti::meta::prefix_array_iterator<     vector_iter > ) ;
        CONSTEVAL_CHECK( !uti::meta::prefix_array_iterator<   c_vector_iter > ) ;
        CONSTEVAL_CHECK( !uti::meta::prefix_array_iterator<   r_vector_iter > ) ;
        CONSTEVAL_CHECK( !uti::meta::prefix_array_iterator< c_r_vector_iter > ) ;

        CONSTEVAL_CHECK( uti::meta::random_access_iterator<     vector_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::random_access_iterator<   c_vector_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::random_access_iterator<   r_vector_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::random_access_iterator< c_r_vector_iter > ) ;

        using     segtree_iter = typename uti::segment_tree< TestType >::              iterator ;
        using   c_segtree_iter = typename uti::segment_tree< TestType >::        const_iterator ;
        using   r_segtree_iter = typename uti::segment_tree< TestType >::      reverse_iterator ;
        using c_r_segtree_iter = typename uti::segment_tree< TestType >::const_reverse_iterator ;

        CONSTEVAL_CHECK( !uti::meta::prefix_array_iterator<     segtree_iter > ) ;
        CONSTEVAL_CHECK( !uti::meta::prefix_array_iterator<   c_segtree_iter > ) ;
        CONSTEVAL_CHECK( !uti::meta::prefix_array_iterator<   r_segtree_iter > ) ;
        CONSTEVAL_CHECK( !uti::meta::prefix_array_iterator< c_r_segtree_iter > ) ;

        CONSTEVAL_CHECK( uti::meta::random_access_iterator<     segtree_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::random_access_iterator<   c_segtree_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::random_access_iterator<   r_segtree_iter > ) ;
        CONSTEVAL_CHECK( uti::meta::random_access_iterator< c_r_segtree_iter > ) ;
}

TEMPLATE_LIST_TEST_CASE( "iterator::convertibility", "[iterator][convertibility]", all_test_types )
{
        using iter_u8  = uti::iterator_base< uti::  u8_t, uti::random_access_iterator_tag > ;
        using iter_u64 = uti::iterator_base< uti:: u64_t, uti::random_access_iterator_tag > ;
        using iter_t   = uti::iterator_base<    TestType, uti::random_access_iterator_tag > ;

        using const_iter_u8  = uti::iterator_base< uti::  u8_t const, uti::random_access_iterator_tag > ;
        using const_iter_u64 = uti::iterator_base< uti:: u64_t const, uti::random_access_iterator_tag > ;
        using const_iter_t   = uti::iterator_base<    TestType const, uti::random_access_iterator_tag > ;

        /// self
        {
                CONSTEVAL_CHECK(  uti::is_convertible_v<       iter_u8,       iter_u8 > ) ;
                CONSTEVAL_CHECK(  uti::is_convertible_v<       iter_u8, const_iter_u8 > ) ;
                CONSTEVAL_CHECK( !uti::is_convertible_v< const_iter_u8,       iter_u8 > ) ;
                CONSTEVAL_CHECK(  uti::is_convertible_v< const_iter_u8, const_iter_u8 > ) ;

                CONSTEVAL_CHECK(  uti::is_convertible_v<       iter_u64,       iter_u64 > ) ;
                CONSTEVAL_CHECK(  uti::is_convertible_v<       iter_u64, const_iter_u64 > ) ;
                CONSTEVAL_CHECK( !uti::is_convertible_v< const_iter_u64,       iter_u64 > ) ;
                CONSTEVAL_CHECK(  uti::is_convertible_v< const_iter_u64, const_iter_u64 > ) ;

                CONSTEVAL_CHECK(  uti::is_convertible_v<       iter_u64,       iter_u64 > ) ;
                CONSTEVAL_CHECK(  uti::is_convertible_v<       iter_u64, const_iter_u64 > ) ;
                CONSTEVAL_CHECK( !uti::is_convertible_v< const_iter_u64,       iter_u64 > ) ;
                CONSTEVAL_CHECK(  uti::is_convertible_v< const_iter_u64, const_iter_u64 > ) ;
        }
        /// to and from u8
        {
                CONSTEVAL_CHECK(  uti::is_convertible_v<       iter_u64,       iter_u8 > ) ;
                CONSTEVAL_CHECK(  uti::is_convertible_v<       iter_u64, const_iter_u8 > ) ;
                CONSTEVAL_CHECK( !uti::is_convertible_v< const_iter_u64,       iter_u8 > ) ;
                CONSTEVAL_CHECK(  uti::is_convertible_v< const_iter_u64, const_iter_u8 > ) ;

                CONSTEVAL_CHECK(  uti::is_convertible_v<       iter_u8,       iter_u64 > ) ;
                CONSTEVAL_CHECK(  uti::is_convertible_v<       iter_u8, const_iter_u64 > ) ;
                CONSTEVAL_CHECK( !uti::is_convertible_v< const_iter_u8,       iter_u64 > ) ;
                CONSTEVAL_CHECK(  uti::is_convertible_v< const_iter_u8, const_iter_u64 > ) ;

                CONSTEVAL_CHECK(  uti::is_convertible_v<       iter_t,       iter_u8 > ) ;
                CONSTEVAL_CHECK(  uti::is_convertible_v<       iter_t, const_iter_u8 > ) ;
                CONSTEVAL_CHECK( !uti::is_convertible_v< const_iter_t,       iter_u8 > ) ;
                CONSTEVAL_CHECK(  uti::is_convertible_v< const_iter_t, const_iter_u8 > ) ;

                CONSTEVAL_CHECK(  uti::is_convertible_v<       iter_u8,       iter_t > ) ;
                CONSTEVAL_CHECK(  uti::is_convertible_v<       iter_u8, const_iter_t > ) ;
                CONSTEVAL_CHECK( !uti::is_convertible_v< const_iter_u8,       iter_t > ) ;
                CONSTEVAL_CHECK(  uti::is_convertible_v< const_iter_u8, const_iter_t > ) ;
        }
        /// between different types
        {
                CONSTEVAL_CHECK( !uti::is_convertible_v<       iter_u64,       iter_t > ) ;
                CONSTEVAL_CHECK( !uti::is_convertible_v<       iter_u64, const_iter_t > ) ;
                CONSTEVAL_CHECK( !uti::is_convertible_v< const_iter_u64,       iter_t > ) ;
                CONSTEVAL_CHECK( !uti::is_convertible_v< const_iter_u64, const_iter_t > ) ;
        }
}
