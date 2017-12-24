file(GLOB source_list *.cpp)

foreach(file ${source_list})
    add_boost_test(SOURCE ${file} LINK config_reader PREFIX config_reader)
endforeach()
