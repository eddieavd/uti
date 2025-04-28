# uti - universal template implementations

### a humble attempt at a modern c++ standard library

# components

## containers

- array
- vector
- list
- prefix_array
- segment_tree
- tuple
- variant_vector
- view
- buffer

## allocators

- allocator traits interface
- new/delete allocator
- default allocator
- resource traits interface
- malloc memory resource
- static bump memory resource
- static freelist memory resource

## string

- string
- string_view
- string_switch

## meta

- type_list
- fast join
- fast algos
- random

# usage

`uti` requires at least `c++23` (for `deducing this` among other things).  
for full compile-time support, we require `c++26` to be able to cast `void` pointers at compile time.  

side note: clang-18 frontend crashes when parsing some of the heavily-templated `variant_vector` code. the issue is fixed in clang-19

## cmake

```cmake
...
include( FetchContent )

# build tests by setting:
set( UTI_TEST ON )

# build benchmarks by setting:
set( UTI_BENCH ON )

FetchContent_Declare(
        uti
        GIT_REPOSITORY https://github.com/eddieavd/uti.git
)
FetchContent_MakeAvailable( uti )

target_link_libraries( <your_target> PRIVATE uti_core::uti_core uti_sys::uti_sys )
...
```
