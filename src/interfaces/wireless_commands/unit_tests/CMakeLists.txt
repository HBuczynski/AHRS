file(GLOB source_list *.cpp)

foreach(file ${source_list})
    add_boost_test(SOURCE ${file} LINK wireless_commands PREFIX wireless_commands)
endforeach()
