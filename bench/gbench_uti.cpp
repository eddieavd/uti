//
//
//      uti
//      gbench_uti.cpp
//

#include "gbench_uti.hpp"

#include <container/vector.hpp>
#include <allocator/static_bump.hpp>


using namespace uti::bench ;


using stdvecint = std::vector<         int > ;
using stdvecstr = std::vector< std::string > ;

using utivecint = uti::vector<         int, uti::allocator<         int > > ;
using utivecstr = uti::vector< std::string, uti::allocator< std::string > > ;

using utivecintstat = uti::vector<         int, uti::static_bump_allocator<         int, UTI_STATIC_MEM_SIZE > > ;
using utivecstrstat = uti::vector< std::string, uti::static_bump_allocator< std::string, UTI_STATIC_MEM_SIZE > > ;


BENCHMARK( bm_push_back_trivial< stdvecint     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_trivial< utivecint     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_trivial< utivecintstat > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_push_back_nontrivial< stdvecstr     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_nontrivial< utivecstr     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_nontrivial< utivecstrstat > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_push_back_reserved_trivial< stdvecint     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_reserved_trivial< utivecint     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_reserved_trivial< utivecintstat > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_push_back_reserved_nontrivial< stdvecstr     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_reserved_nontrivial< utivecstr     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_reserved_nontrivial< utivecstrstat > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_copy_container_trivial< stdvecint     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_copy_container_trivial< utivecint     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_copy_container_trivial< utivecintstat > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_copy_container_nontrivial< stdvecstr     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_copy_container_nontrivial< utivecstr     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_copy_container_nontrivial< utivecstrstat > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
