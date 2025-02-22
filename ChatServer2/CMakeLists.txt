# 设置 Boost 的最小版本要求（根据您的需要调整版本号）
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.74.0 REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

# 链接 Boost 库到您的目标
target_link_libraries(YourTargetName PRIVATE Boost::system) 