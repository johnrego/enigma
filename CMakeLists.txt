cmake_minimum_required(VERSION 3.20)
project(enigma C)
set(CMAKE_C_STANDARD 17)
include(FetchContent)
FetchContent_Declare(
    log
    GIT_REPOSITORY https://github.com/rxi/log.c.git
    GIT_TAG master
)
FetchContent_MakeAvailable(log)
if(log_POPULATED)
    message(STATUS "Os arquivos fontes da lib log foram obtidos.")
    message(STATUS "log_SOURCE_DIR: ${log_SOURCE_DIR}")
    set(log_sources
        ${log_SOURCE_DIR}/src/log.c
    )
    add_library(log_lib STATIC ${log_sources})
    target_include_directories(log_lib PUBLIC ${log_SOURCE_DIR}/src)
    target_compile_definitions(log_lib PRIVATE
        LOG_USE_COLOR=TRUE
    )
else()
    message(FATAL_ERROR "Falha ao baixar/configurar log.c")
endif()
set(enigma_sources
    src/main.c
    src/machine/machine.c
)

add_executable(enigma ${enigma_sources})

target_include_directories(enigma PRIVATE
    include
)

target_link_libraries(enigma PRIVATE log_lib)