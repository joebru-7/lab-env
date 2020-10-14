#--------------------------------------------------------------------------
# Math project
#--------------------------------------------------------------------------

PROJECT(Math)
FILE(GLOB example_headers code/*.h)
FILE(GLOB example_sources code/*.cpp)

SET(files_example ${example_headers} ${example_sources})
SOURCE_GROUP("example" FILES ${files_example})

ADD_EXECUTABLE(Math ${files_example})
TARGET_LINK_LIBRARIES(Math core render)
ADD_DEPENDENCIES(Math core render)