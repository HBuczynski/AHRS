file(GLOB source_list *.cpp)

foreach(file ${source_list})
    add_boost_test(SOURCE ${file} LINK time_manager PREFIX time_manager)
endforeach()
