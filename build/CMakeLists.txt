#project name 
PROJECT(test)
#head file path 
#INCLUDE_DIRECTORIES(include)
#source directory
AUX_SOURCE_DIRECTORY(./  DIR_SRCS)
#set environment variable
SET(TEST ${DIR_SRCS})
#set extern libraies
#SET(LIBRARIES libm.so)
#add executable file
ADD_EXECUTABLE(./build ${TEST})
#add link library 
#TARGET_LINK_LIBRARIES(./build ${LIBRARIES})

