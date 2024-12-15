# uti - universal template implementations

### a humble attempt at a standard library

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

## cmake

```cmake
...
include( FetchContent )

FetchContent_Declare(
        uti
        GIT_REPOSITORY https://github.com/eddieavd/uti.git
)
FetchContent_MakeAvailable( uti )

target_link_libraries( <your_target> PRIVATE uti::uti )
...
```
