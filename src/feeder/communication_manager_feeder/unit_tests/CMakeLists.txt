file(GLOB source_list *.cpp)

foreach(file ${source_list})
    add_boost_test(SOURCE ${file} LINK communication_manager_feeder PREFIX communication_manager_feeder)
endforeach()
