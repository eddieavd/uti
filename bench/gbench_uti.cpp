//
//
//      uti
//      gbench_uti.cpp
//

#include "gbench_uti.hpp"

#include <container/vector.hpp>


using namespace uti::bench ;


BENCHMARK( bm_push_back< std::vector< int > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 8 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back< uti::vector< int > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 8 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_push_back_nontrivial< std::vector< std::string > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 8 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_nontrivial< uti::vector< std::string > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 8 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_push_back_reserved< std::vector< int > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 8 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_reserved< uti::vector< int > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 8 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_push_back_reserved_nontrivial< std::vector< std::string > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 8 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_reserved_nontrivial< uti::vector< std::string > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 8 )->Unit( benchmark::kMicrosecond );
