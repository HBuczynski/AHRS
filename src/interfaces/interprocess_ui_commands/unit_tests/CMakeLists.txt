file(GLOB source_list *.cpp)

foreach(file ${source_list})
    add_boost_test(SOURCE ${file} LINK interprocess_ui_commands PREFIX interprocess_ui_commands)
endforeach()
