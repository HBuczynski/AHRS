file(GLOB source_list *.cpp)

foreach(file ${source_list})
    add_boost_test(SOURCE ${file} LINK database_manager PREFIX database_manager)
endforeach()
