file(GLOB source_list *.cpp)

foreach(file ${source_list})
    add_boost_test(SOURCE ${file} LINK hm_interface PREFIX hm_interface)
endforeach()
