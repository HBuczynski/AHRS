file(GLOB source_list *.cpp)

foreach(file ${source_list})
    add_boost_test(SOURCE ${file} LINK external_feeder_communication PREFIX external_feeder_communication)
endforeach()
