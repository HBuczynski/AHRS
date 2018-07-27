file(GLOB source_list *.cpp)

foreach(file ${source_list})
    add_boost_test(SOURCE ${file} LINK cockpit_gui PREFIX cockpit_gui)
endforeach()
