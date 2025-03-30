//
//
//      uti.bench
//      uti.bench.hxx
//

#pragma once

#include <benchmark/benchmark.h>


namespace uti::bench
{


template< typename T >
static void bm_sum_vector ( benchmark::State & state )
{
        srand( time( nullptr ) ) ;

        T vector ;

        for( int i = 0; i < state.range( 0 ); ++i )
        {
                vector.push_back( rand() % 1024 ) ;
        }
        long long sum = 0 ;

        for( auto _ : state )
        {
                for( long i = 0; i < ( long )vector.size(); ++i )
                {
                        sum += vector.at( i ) ;
                }
                benchmark::ClobberMemory() ;
                benchmark::DoNotOptimize( sum    ) ;
                benchmark::DoNotOptimize( vector ) ;
        }
}

template< typename T >
static void bm_sum_var_vector ( benchmark::State & state )
{
        srand( time( nullptr ) ) ;

        T vector ;

        for( int i = 0; i < state.range( 0 ); ++i )
        {
                vector.template push_back< int >( rand() % 1024 ) ;
        }
        long long sum = 0 ;

        for( auto _ : state )
        {
                for( long i = 0; i < vector.size(); ++i )
                {
                        vector.visit( i, [ & ]( int const & val ){ sum += val ; } ) ;
                }
                benchmark::ClobberMemory() ;
                benchmark::DoNotOptimize( sum    ) ;
                benchmark::DoNotOptimize( vector ) ;
        }
}


template< typename T >
static void bm_push_back_trivial ( benchmark::State & state )
{
        for( auto _ : state )
        {
                T container;

                for( ssize_t i = 0; i < state.range( 0 ); ++i )
                {
                        container.push_back( 1024 );
                }
                benchmark::ClobberMemory();
                benchmark::DoNotOptimize( container );
        }
}

template< typename T, typename U = T >
static void bm_dual_push_back_trivial ( benchmark::State & state )
{
        for( auto _ : state )
        {
                T container_1 ;
                U container_2 ;

                for( ssize_t i = 0; i < state.range( 0 ); ++i )
                {
                        container_1.push_back( 1024 ) ;
                        container_2.push_back( 1024 ) ;
                }
                benchmark::ClobberMemory() ;
                benchmark::DoNotOptimize( container_1 ) ;
                benchmark::DoNotOptimize( container_2 ) ;
        }
}

template< typename T >
static void bm_push_back_nontrivial ( benchmark::State & state )
{
        for( auto _ : state )
        {
                T container;

                for( ssize_t i = 0; i < state.range( 0 ); ++i )
                {
                        container.emplace_back();
                }
                benchmark::ClobberMemory();
                benchmark::DoNotOptimize( container );
        }
}

template< typename T >
static void bm_push_back_reserved_trivial ( benchmark::State & state )
{
        for( auto _ : state )
        {
                T container;
                container.reserve( state.range( 0 ) );

                for( ssize_t i = 0; i < state.range( 0 ); ++i )
                {
                        container.push_back( 1024 );
                }
                benchmark::ClobberMemory();
                benchmark::DoNotOptimize( container );
        }
}

template< typename T >
static void bm_push_back_var_reserved_trivial ( benchmark::State & state )
{
        for( auto _ : state )
        {
                T container;
                container.template reserve< int >( state.range( 0 ) );

                for( ssize_t i = 0; i < state.range( 0 ); ++i )
                {
                        container.template push_back< int >( 1024 );
                }
                benchmark::ClobberMemory();
                benchmark::DoNotOptimize( container );
        }
}

template< typename T >
static void bm_push_back_reserved_nontrivial ( benchmark::State & state )
{
        for( auto _ : state )
        {
                T container;
                container.reserve( state.range( 0 ) );

                for( ssize_t i = 0; i < state.range( 0 ); ++i )
                {
                        container.emplace_back();
                }
                benchmark::ClobberMemory();
                benchmark::DoNotOptimize( container );
        }
}

template< typename T >
static void bm_copy_container_trivial ( benchmark::State & state )
{
        T container;
        for( ssize_t i = 0; i < state.range( 0 ); ++i )
        {
                container.push_back( i );
        }
        for( auto _ : state )
        {
                T copy( container );

                benchmark::ClobberMemory();
                benchmark::DoNotOptimize( copy );
        }
}

template< typename T >
static void bm_copy_container_nontrivial ( benchmark::State & state )
{
        T container;
        for( ssize_t i = 0; i < state.range( 0 ); ++i )
        {
                container.emplace_back();
        }
        for( auto _ : state )
        {
                T copy( container );

                benchmark::ClobberMemory();
                benchmark::DoNotOptimize( copy );
        }
}


} // namespace uti::bench
