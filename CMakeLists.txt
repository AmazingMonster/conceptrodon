cmake_minimum_required(VERSION 3.28)

# Generate compile_commands.json for clangd
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    Conceptrodon
    VERSION 1.0.0.0
    LANGUAGES CXX
)

option(CONCEPTRODON_COMPARE_WITH_BOOST OFF)

# cache variables for installation destinations
include(GNUInstallDirs)

add_library(ConceptrodonFacilities INTERFACE)

set_target_properties(ConceptrodonFacilities PROPERTIES
    OUTPUT_NAME ConceptrodonFacilities
    EXPORT_NAME Facilities
)

target_include_directories(ConceptrodonFacilities INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


if(CMAKE_SOURCE_DIR STREQUAL Conceptrodon_SOURCE_DIR OR TEST_CONCEPTRODON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TestConceptrodon
    ${CMAKE_CURRENT_LIST_DIR}/tests/tests.cpp
)


target_include_directories(TestConceptrodon
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}
)

target_compile_options(TestConceptrodon
    PRIVATE -ftime-trace
)

find_package(Macaron REQUIRED CONFIG)
target_link_libraries(TestConceptrodon PRIVATE Macaron::Facilities)

if(CONCEPTRODON_COMPARE_WITH_BOOST)
find_package(Boost REQUIRED CONFIG)
target_include_directories(TestConceptrodon
    PRIVATE ${Boost_INCLUDE_DIRS}
)
endif()

endif()


install(
    TARGETS ConceptrodonFacilities
    EXPORT Conceptrodon
)

install(
    DIRECTORY conceptrodon
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT Conceptrodon
    FILE Conceptrodon.cmake
    NAMESPACE Conceptrodon::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/conceptrodon
)

# include the package config helpers and generate the file below
include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/ConceptrodonConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/conceptrodon
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/ConceptrodonConfig.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/conceptrodon
)