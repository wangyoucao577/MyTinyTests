
# find source files here
aux_source_directory(. DIR_LIB_SRCS)

# add headers also into the visual studio project
file(GLOB HEADER_FILES "*.h")
message(${HEADER_FILES})
source_group("headers" FILES ${HEADER_FILES})

# target (static lib)
add_library(math ${DIR_LIB_SRCS} ${HEADER_FILES})


