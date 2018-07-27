file(GLOB source_list *.cpp)

foreach(file ${source_list})
    add_boost_test(SOURCE ${file} LINK communication_process_feeder PREFIX communication_process_feeder)
endforeach()
