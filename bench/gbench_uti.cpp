//
//
//      uti
//      gbench_uti.cpp
//

#include "gbench_uti.hpp"

#include <container/vector.hpp>


using namespace uti::bench ;


BENCHMARK( bm_push_back< std::vector< int > > )->RangeMultiplier( 2 )->Range( 256, 256 << 8 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back< uti::vector< int > > )->RangeMultiplier( 2 )->Range( 256, 256 << 8 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_push_back_reserved< std::vector< int > > )->RangeMultiplier( 2 )->Range( 256, 256 << 8 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_reserved< uti::vector< int > > )->RangeMultiplier( 2 )->Range( 256, 256 << 8 )->Unit( benchmark::kMicrosecond );
