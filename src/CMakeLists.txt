add_library(tlotexteditor_core STATIC tlo/texteditor.hpp texteditor.cpp)
target_include_directories(tlotexteditor_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tlotexteditor_core PUBLIC Qt5::Widgets)

add_executable(tlotexteditor tlotexteditor.cpp)
target_link_libraries(tlotexteditor PRIVATE tlotexteditor_core)
