//
//
//      uti
//      gbench_uti.cpp
//

#include "gbench_uti.hpp"

#include <container/vector.hpp>


using namespace uti::bench ;


BENCHMARK( bm_push_back_trivial< std::vector< int > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 12 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_trivial< uti::vector< int > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 12 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_push_back_nontrivial< std::vector< std::string > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 12 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_nontrivial< uti::vector< std::string > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 12 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_push_back_reserved_trivial< std::vector< int > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 12 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_reserved_trivial< uti::vector< int > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 12 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_push_back_reserved_nontrivial< std::vector< std::string > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 12 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_reserved_nontrivial< uti::vector< std::string > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 12 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_copy_container_trivial< std::vector< int > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 12 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_copy_container_trivial< uti::vector< int > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 12 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_copy_container_nontrivial< std::vector< std::string > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 12 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_copy_container_nontrivial< uti::vector< std::string > > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 12 )->Unit( benchmark::kMicrosecond );
