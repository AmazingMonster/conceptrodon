cmake_minimum_required(VERSION 3.28)

project(
    Conceptrodon
    VERSION 1.0.0.0
    LANGUAGES CXX
)

# cache variables for installation destinations
include(GNUInstallDirs)

add_library(ConceptrodonContents INTERFACE)

set_target_properties(ConceptrodonContents PROPERTIES
    OUTPUT_NAME ConceptrodonContents
    EXPORT_NAME Contents
)

target_include_directories(ConceptrodonContents INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


install(
    TARGETS ConceptrodonContents
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