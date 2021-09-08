include(FetchContent)

FetchContent_Declare(range-v3_src
  GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
  GIT_TAG 0487cca29e352e8f16bbd91fda38e76e39a0ed28
)
FetchContent_MakeAvailable(range-v3_src)

# for better error messages
target_compile_options(range-v3 INTERFACE $<$<COMPILE_LANG_AND_ID:CXX,GNU>:-fconcepts>)
