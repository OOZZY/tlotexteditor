qt5_wrap_ui(uiheaders texteditor.ui)
add_library(tlotexteditorcore STATIC ${uiheaders} texteditor.cpp)
# linking to Qt5::Widgets causes cmake to use the appropriate include
# directories and compile definitions needed to use Qt Widgets when building
# the target
target_link_libraries(tlotexteditorcore Qt5::Widgets)
