cmake_minimum_required (VERSION 2.6)
project (InsertDB)
#include(CTest)
 
# The version number.
#set (Tutorial_VERSION_MAJOR 1)
#set (Tutorial_VERSION_MINOR 0)
 
# 用于检查函数是否存在
#include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
 
#check_function_exists (log HAVE_LOG)
#check_function_exists (exp HAVE_EXP)
 
# should we use our own math functions
#option(USE_MYMATH "Use tutorial provided math implementation" ON)
 
# configure a header file to pass some of the CMake settings to the source code
#configure_file (
#  "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
#  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
#  )
 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories (/mnt/winshared/myyb/product/Linux64/opt/oracle.oci.Linux64/include)
 
# add the MathFunctions library?
#if (USE_MYMATH)
#  include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
#  add_subdirectory (MathFunctions)
#  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
#endif (USE_MYMATH)
 
# add the executable
add_executable (insertDB occi.cpp)
FIND_LIBRARY(lIBXXX1 clntsh /mnt/winshared/myyb/product/Linux64/opt/oracle.oci.Linux64/lib)
FIND_LIBRARY(lIBXXX2 occi /mnt/winshared/myyb/product/Linux64/opt/oracle.oci.Linux64/lib)
set (EXTRA_LIBS ${EXTRA_LIBS} ${lIBXXX1} ${lIBXXX2})
target_link_libraries (insertDB ${EXTRA_LIBS})
 
#添加编译选项
set(CMAKE_CXX_FLAGS, "-pg -g -Wall")
# add the install targets
#install (TARGETS Tutorial DESTINATION bin)
#install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)
 
# does the application run
#add_test (TutorialRuns Tutorial 25)
# 
## does the usage message work?
#add_test (TutorialUsage Tutorial)
#set_tests_properties (TutorialUsage
#  PROPERTIES 
#  PASS_REGULAR_EXPRESSION "Usage:.*number"
#  )
# 
# 
##define a macro to simplify adding tests
#macro (do_test arg result)
#  add_test (TutorialComp${arg} Tutorial ${arg})
#  set_tests_properties (TutorialComp${arg}
#    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
#    )
#endmacro (do_test)
# 
## do a bunch of result based tests
#do_test (4 "4 is 2")
#do_test (9 "9 is 3")
#do_test (5 "5 is 2.236")
#do_test (7 "7 is 2.645")
#do_test (25 "25 is 5")
#do_test (-25 "-25 is 0")
#do_test (0.0001 "0.0001 is 0.01")

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
#set (CPACK_RESOURCE_FILE_LICENSE  
#     "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
#set (CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
#set (CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include (CPack)

