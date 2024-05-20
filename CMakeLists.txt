cmake_minimum_required(VERSION 3.28)
project(OSGNotes)

set(CMAKE_CXX_STANDARD 17)


set(OSG_DIR D:/lib/osg365)
#set(ENV{OSG_FILE_PATH} D:/lib/OpenSceneGraph-Data)
# 改为在clion 配置中直接设置OSG_FILE_PATH=D:\lib\OpenSceneGraph-Data
add_subdirectory(OSGGuide)
