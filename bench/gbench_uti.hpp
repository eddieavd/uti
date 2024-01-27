//
//
//      uti
//      gbench_uti.hpp
//

#pragma once

#include <benchmark/benchmark.h>


namespace uti::bench
{


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


} // namespace uti::bench
