set(BINARY ${CMAKE_PROJECT_NAME})

#file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.hpp *.cpp)
#set(SOURCES ${SOURCES})

#file(GLOB_RECURSE MODULES LIST_DIRECTORIES true *.cxx)
#SET(MODULES ${MODULES})

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)

set(LLVM_ENABLE_THREADS TRUE)
set(LLVM_PARALLEL_COMPILE_JOBS, 8)
set(LLVM_PARALLEL_LINK_JOBS, 8)

add_library(team)
target_sources(
    team PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
    modules/team.cxx
)

add_library(player)
target_sources(
    player PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
    modules/player.cxx
)

add_library(point)
target_sources(
    point PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
    modules/point.cxx
)

add_executable(${BINARY} modules/main.cxx)
#${SOURCES})


#add_library(${BINARY}_lib STATIC ${SOURCES})

#set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_link_libraries(${PROJECT_NAME} "${CMAKE_THREAD_LIBS_INIT}")

target_link_libraries(${PROJECT_NAME} team player point)

#target_compile_options(${PROJECT_NAME} PRIVATE -fmodules-ts -xc++-system-header)

#target_compile_options(${PROJECT_NAME} PRIVATE -fmodules-ts)
#target_link_options(${PROJECT_NAME} PUBLIC -fmodules-ts)

#if(${BUILD_FOR_CUDA})
#    target_compile_options(${PROJECT_NAME} PRIVATE -fsycl -fsycl-targets=nvptx64-nvidia-cuda -fsycl-unnamed-lambda)
#    target_link_options(${PROJECT_NAME} PUBLIC -fsycl -fsycl-targets=nvptx64-nvidia-cuda -fsycl-unnamed-lambda)
#endif ()

