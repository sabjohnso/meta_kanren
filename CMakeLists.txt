cmake_minimum_required( VERSION 2.8.4 )

project( METAKANREN )

option( BUILD_TESTS "Build the test suite?" ON )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

if( BUILD_TESTS )
  
  enable_testing()
  
  macro( add_simple_test name )
    add_executable( ${name}_test test/${name}_test.cpp )
    add_test( ${name} ${name}_test )
  endmacro()

  add_simple_test( easy     )
  add_simple_test( cons     )
  add_simple_test( and      )
  add_simple_test( assp     )
  add_simple_test( unit     )
  add_simple_test( five     )
  add_simple_test( a_and_b  )
  add_simple_test( take2    )
  add_simple_test( take_all )
  
endif()



