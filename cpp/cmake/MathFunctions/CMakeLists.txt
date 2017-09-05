# first we add the executable that generates the table
add_executable(MakeTable MakeTable.cpp)
# 使用一下语句生成Table.h文件，其中CMAKE_CURRENT_BINARY_DIR表示cmake当前的执行绝对路径，比如现在是在MathFunctions子目录中
add_custom_command (
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
	DEPENDS MakeTable
	COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
	)
# add the binary tree directory to the search path 
# for include files
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

# add the main library
add_library(MathFunctions mysqrt.cpp ${CMAKE_CURRENT_BINARY_DIR}/Table.h)

install (TARGETS MathFunctions DESTINATION bin)
install (FILES MathFunctions.h DESTINATION include)

