//
//
//      uti
//      copy_counter.hpp
//

#pragma once

#include <traits/traits.hpp>

#include <ostream>


namespace uti::test
{


struct copy_stats
{
        i32_t n_default_constructs { 0 } ;
        i32_t n_copies             { 0 } ;
        i32_t n_moves              { 0 } ;

        constexpr bool operator== ( copy_stats const & _other_ ) const noexcept = default ;
};

inline std::ostream & operator<< ( std::ostream & stream, copy_stats const & stats )
{
        stream << "copy_stats: {\n\tdefault constructs: " << stats.n_default_constructs
                            << "\n\tcopy    constructs: " << stats.n_copies
                            << "\n\tmove    constructs: " << stats.n_moves << "\n}\n";
        return stream;
}

struct copy_counter
{
        inline static copy_stats stats ;

        copy_counter () noexcept { ++stats.n_default_constructs; }

        copy_counter             ( copy_counter const & ) { ++stats.n_copies;               }
        copy_counter & operator= ( copy_counter const & ) { ++stats.n_copies; return *this; }

        copy_counter             ( copy_counter && ) { ++stats.n_moves;               }
        copy_counter & operator= ( copy_counter && ) { ++stats.n_moves; return *this; }

        static copy_stats reset ()
        {
                copy_stats old_stats = stats;

                stats.n_default_constructs = 0 ;
                stats.n_copies             = 0 ;
                stats.n_moves              = 0 ;

                return old_stats;
        }
};


} // namespace uti::test
