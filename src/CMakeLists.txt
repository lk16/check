find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-2.4) # look into FindPkgConfig.cmake, 



link_directories(
  ${GTKMM_LIBRARY_DIRS}
)

set(DEBUG_FLAGS
  "-I .. -std=c++0x -Wall -Wextra -g  -Wfloat-equal -Wno-unused-result -Wshadow -Wstrict-aliasing"
)

set(OPTIMIZING_FLAGS
  "-I .. -std=c++0x -Wall -DNDEBUG -Wextra -O3 -pipe -msse2 -fforce-addr -ftree-vectorize -funroll-loops" 
)


set(CMAKE_CXX_FLAGS 
  #${OPTIMIZING_FLAGS}
  #${DEBUG_FLAGS} 
) 

SET(objects
  bots/bot_ali.cpp
  game/board.cpp
  game/game_control.cpp
  gui_base/clickable_image.cpp
  gui/main_window.cpp
  main/check.cpp
)


include_directories(.)
include_directories(${GTKMM_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})


ADD_EXECUTABLE(../check
  ${objects}
)

target_link_libraries(../check
  ${GTKMM_LIBRARIES}
)


