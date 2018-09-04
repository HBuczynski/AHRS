file(GLOB source_list *.cpp)

foreach(file ${source_list})
    add_boost_test(SOURCE ${file} LINK gui_interface PREFIX gui_interface)
endforeach()
