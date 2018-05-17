file(GLOB source_list *.cpp)

foreach(file ${source_list})
    add_boost_test(SOURCE ${file} LINK wireless_responses PREFIX wireless_responses)
endforeach()
