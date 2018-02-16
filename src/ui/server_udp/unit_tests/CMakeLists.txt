file(GLOB source_list *.cpp)

foreach(file ${source_list})
    add_boost_test(SOURCE ${file} LINK server_udp PREFIX server_udp)
endforeach()
