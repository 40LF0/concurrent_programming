

# Sources
set(CP_SOURCE_DIR src)
set(CP_SOURCES
  ${CP_SOURCE_DIR}/bpt.cc
  ${CP_SOURCE_DIR}/file.cc
  # Add your sources here
  # ${CP_SOURCE_DIR}/foo/bar/your_source.cc
  )

# Headers
set(CP_HEADER_DIR include)
set(CP_HEADERS
  ${CP_HEADER_DIR}/bpt.h
  ${CP_HEADER_DIR}/file.h
  ${CP_HEADER_DIR}/reg.h
  # Add your headers here
  # ${CP_HEADER_DIR}/foo/bar/your_header.h
  )

add_library(cp STATIC ${CP_HEADERS} ${CP_SOURCES})

target_include_directories(cp
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/${CP_HEADER_DIR}"
  )

