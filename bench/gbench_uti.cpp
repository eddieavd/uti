//
//
//      uti
//      gbench_uti.cpp
//

#include "gbench_uti.hpp"

#include <allocator/freelist_resource.hpp>
#include <container/vector.hpp>

#include <vector>
#include <string>


using namespace uti::bench ;


using stdvecint = std::vector<         int > ;
using stdvecstr = std::vector< std::string > ;

using utivecint = uti::vector<         int, uti::allocator<         int, uti::malloc_resource > > ;
using utivecstr = uti::vector< std::string, uti::allocator< std::string, uti::malloc_resource > > ;

using utivecintstat = uti::vector<         int, uti::allocator<         int, uti::static_bump_resource< 8 * 1024 * 1024 > > > ;
using utivecstrstat = uti::vector< std::string, uti::allocator< std::string, uti::static_bump_resource< 8 * 1024 * 1024 > > > ;

using utivecintlist = uti::vector<         int, uti::allocator<         int, uti::static_freelist_resource< 8 * 1024 * 1024 > > > ;
using utivecstrlist = uti::vector< std::string, uti::allocator< std::string, uti::static_freelist_resource< 8 * 1024 * 1024 > > > ;


BENCHMARK( bm_push_back_trivial< stdvecint     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_trivial< utivecint     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_trivial< utivecintstat > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_trivial< utivecintlist > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_push_back_nontrivial< stdvecstr     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_nontrivial< utivecstr     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_nontrivial< utivecstrstat > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_nontrivial< utivecstrlist > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_push_back_reserved_trivial< stdvecint     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_reserved_trivial< utivecint     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_reserved_trivial< utivecintstat > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_reserved_trivial< utivecintlist > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_push_back_reserved_nontrivial< stdvecstr     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_reserved_nontrivial< utivecstr     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_reserved_nontrivial< utivecstrstat > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_reserved_nontrivial< utivecstrlist > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_copy_container_trivial< stdvecint     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_copy_container_trivial< utivecint     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_copy_container_trivial< utivecintstat > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_copy_container_trivial< utivecintlist > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_copy_container_nontrivial< stdvecstr     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_copy_container_nontrivial< utivecstr     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_copy_container_nontrivial< utivecstrstat > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_copy_container_nontrivial< utivecstrlist > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
