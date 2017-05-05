
# find source files here
aux_source_directory(. DIR_LIB_SRCS)

# target (static lib)
add_library(math ${DIR_LIB_SRCS})

