# Copyright (c) 2020 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.19.0 FATAL_ERROR)

set(MBED_PATH ${CMAKE_CURRENT_SOURCE_DIR}/mbed-os CACHE INTERNAL "")
set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")
set(APP_TARGET micro_ros_mbed)

include(${MBED_PATH}/tools/cmake/app.cmake)

add_subdirectory(${MBED_PATH})

add_executable(${APP_TARGET})

mbed_configure_app_target(${APP_TARGET})

include(ExternalProject)

externalproject_add(libmicroros_project
    PREFIX     ${CMAKE_BINARY_DIR}/libmicroros-prefix
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND
        make -j -f ${CMAKE_CURRENT_SOURCE_DIR}/libmicroros.mk
            X_CC=${CMAKE_C_COMPILER}
            X_AR=${CMAKE_AR}
            X_STRIP=${CMAKE_STRIP}
            X_CFLAGS=${CMAKE_C_FLAGS}
            X_CXX=${CMAKE_CXX_COMPILER}
            X_CXXFLAGS=${CMAKE_CXX_FLAGS}
            BUILD_DIR=${CMAKE_BINARY_DIR}
            EXTENSIONS_DIR=${CMAKE_CURRENT_SOURCE_DIR}
    INSTALL_COMMAND ""
    BUILD_BYPRODUCTS ${CMAKE_CURRENT_SOURCE_DIR}/libmicroros.a
    )

project(${APP_TARGET})

target_sources(${APP_TARGET}
    PRIVATE
        main.cpp
        transports.cpp
)

add_dependencies(${APP_TARGET} libmicroros_project)
target_include_directories(${APP_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${APP_TARGET}
    PRIVATE
        mbed-os
        ${CMAKE_CURRENT_SOURCE_DIR}/libmicroros.a
)

mbed_set_post_build(${APP_TARGET})

option(VERBOSE_BUILD "Have a verbose build process")
if(VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()
