SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
cmake_minimum_required(VERSION 3.1)
add_executable(hooya-viewer)

project(hooya-viewer VERSION 0.0.1
	DESCRIPTION "Simple GTK image viewer ported from the HooYa! network client"
	LANGUAGES CXX)
set(PROJECT_VERSION_PRERELEASE "hyperalpha")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -pedantic -Wstrict-aliasing -Werror)

# LeakSanitizer
set(CMAKE_CXX_FLAGS_LEAKSANITIZER
	"-fsanitize=leak -fno-omit-frame-pointer -g -O1"
	CACHE STRING "Flags used by the C++ compiler during LeakSanitizer builds."
	FORCE)

# AddressSanitizer
set(CMAKE_CXX_FLAGS_ADDRESSSANITIZER
	"-fsanitize=address -fno-optimize-sibling-calls -fsanitize-address-use-after-scope -fno-omit-frame-pointer -g -O1"
	CACHE STRING "Flags used by the C++ compiler during AddressSanitizer builds."
	FORCE)

# MemorySanitizer
set(CMAKE_CXX_FLAGS_MEMORYSANITIZER
	"-fsanitize=memory -fno-optimize-sibling-calls -fsanitize-memory-track-origins=2 -fno-omit-frame-pointer -g -O2"
	CACHE STRING "Flags used by the C++ compiler during MemorySanitizer builds."
	FORCE)

# ThreadSanitizer
set(CMAKE_CXX_FLAGS_THREADSANITIZER
	"-fsanitize=thread -g -O1"
	CACHE STRING "Flags used by the C++ compiler during ThreadSanitizer builds."
	FORCE)

# Debug
set(CMAKE_CXX_FLAGS_DEBUG
	"-g -O0"
	CACHE STRING "Flags used for Debug builds"
	FORCE)

# Required libs
find_package(gflags REQUIRED)
find_package(PkgConfig)
find_package(Threads)
pkg_check_modules(GTKMM gtkmm-3.0)

INCLUDE_DIRECTORIES(${GTKMM_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

target_sources(hooya-viewer PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc
	${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindow.cc
	${CMAKE_CURRENT_SOURCE_DIR}/src/SingleImageWindow.cc
	${CMAKE_CURRENT_SOURCE_DIR}/src/ImageBrick.cc
	${CMAKE_CURRENT_SOURCE_DIR}/src/ImageBrickData.cc
	${CMAKE_CURRENT_SOURCE_DIR}/src/MasonRow.cc
	${CMAKE_CURRENT_SOURCE_DIR}/src/MasonLayout.cc
)

target_include_directories(hooya-viewer PUBLIC include)
target_link_libraries(hooya-viewer gflags ${GTKMM_LIBRARIES})
install(TARGETS hooya-viewer DESTINATION bin)
