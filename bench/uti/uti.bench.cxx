//
//
//      uti.bench
//      uti.bench.cxx
//

#include "uti.bench.hxx"

#include <allocator/freelist_resource.hxx>
#include <container/vector.hxx>
#include <container/variant_vector.hxx>

#include <vector>
#include <string>


using namespace uti::bench ;


using stdvecint = std::vector<         int > ;
using stdvecstr = std::vector< std::string > ;

using utivecint = uti::vector<         int, uti::allocator<         int, uti::malloc_resource > > ;
using utivecstr = uti::vector< std::string, uti::allocator< std::string, uti::malloc_resource > > ;

using utivarvec = uti::variant_vector< uti::malloc_resource, int > ;

using utivecintstat = uti::vector<         int, uti::allocator<         int, uti::static_bump_resource< 16 * 1024 * 1024, 1 > > > ;
using utivecstrstat = uti::vector< std::string, uti::allocator< std::string, uti::static_bump_resource< 16 * 1024 * 1024, 2 > > > ;

using utivarvecstat = uti::variant_vector< uti::static_bump_resource< 32 * 1024 * 1024, 3 >, int > ;

using utivecintlist = uti::vector<         int, uti::allocator<         int, uti::static_freelist_resource< 16 * 1024 * 1024, 4 > > > ;
using utivecstrlist = uti::vector< std::string, uti::allocator< std::string, uti::static_freelist_resource< 16 * 1024 * 1024, 5 > > > ;

using utivarveclist = uti::variant_vector< uti::static_freelist_resource< 32 * 1024 * 1024, 6 >, int > ;


BENCHMARK( bm_push_back_trivial< stdvecint     > )->RangeMultiplier( 4 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_trivial< utivecint     > )->RangeMultiplier( 4 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_trivial< utivecintstat > )->RangeMultiplier( 4 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_trivial< utivecintlist > )->RangeMultiplier( 4 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_push_back_trivial< utivarvec     > )->RangeMultiplier( 4 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );

/*
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
*/

/*
BENCHMARK( bm_copy_container_trivial< stdvecint     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_copy_container_trivial< utivecint     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_copy_container_trivial< utivecintstat > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_copy_container_trivial< utivecintlist > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );

BENCHMARK( bm_copy_container_nontrivial< stdvecstr     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_copy_container_nontrivial< utivecstr     > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_copy_container_nontrivial< utivecstrstat > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
BENCHMARK( bm_copy_container_nontrivial< utivecstrlist > )->RangeMultiplier( 2 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond );
*/

/*
BENCHMARK( bm_sum_vector    < stdvecint     > )->RangeMultiplier( 4 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond ) ;
BENCHMARK( bm_sum_vector    < utivecint     > )->RangeMultiplier( 4 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond ) ;
BENCHMARK( bm_sum_vector    < utivecintstat > )->RangeMultiplier( 4 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond ) ;
BENCHMARK( bm_sum_var_vector< utivarvec     > )->RangeMultiplier( 4 )->Range( 1024, 1024 << 10 )->Unit( benchmark::kMicrosecond ) ;
*/
