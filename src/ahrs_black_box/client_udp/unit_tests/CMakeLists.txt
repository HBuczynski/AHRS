file(GLOB source_list *.cpp)

foreach(file ${source_list})
    add_boost_test(SOURCE ${file} LINK client_udp PREFIX client_udp)
endforeach()
