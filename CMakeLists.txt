cmake_minimum_required(VERSION 3.21)
project(GiantsModEditor)

include(FetchContent)
message(STATUS "Fetching Battery...")
FetchContent_Declare(battery
       GIT_REPOSITORY https://github.com/batterycenter/battery
       GIT_TAG        master
)
FetchContent_MakeAvailable(battery)
message(STATUS "Fetching Battery... Done")

message(STATUS "Fetching PugiXML...")
FetchContent_Declare(pugixml
       GIT_REPOSITORY https://github.com/zeux/pugixml
       GIT_TAG        v1.14
)
FetchContent_MakeAvailable(pugixml)
message(STATUS "Fetching PugiXML... Done")

b_add_executable(${PROJECT_NAME}
        src/App.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE battery::core pugixml::static)

b_icon(${PROJECT_NAME} assets/Giants.png)
b_embed(${PROJECT_NAME} src/ui/main.lua)
