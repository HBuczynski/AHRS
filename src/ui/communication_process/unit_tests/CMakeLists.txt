file(GLOB source_list *.cpp)

foreach(file ${source_list})
    add_boost_test(SOURCE ${file} LINK communication_process_ui PREFIX communication_process_ui)
endforeach()
