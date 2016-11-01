cmake_minimum_required(VERSION 3.2)
project(blocks_the_game)
find_package(Qt4 REQUIRED)



INCLUDE(${QT_USE_FILE})

# add definitions
ADD_DEFINITIONS(
  ${QT_DEFINITIONS} 
)

include_directories(
  src
  include
  )

set(HEADERS
  include/mygui.hpp
  include/keyvalues.hpp
  )

set(SOURCES
  src/mygui.cpp
  )

qt4_wrap_cpp(HEADERS_MOC ${HEADERS})

add_executable(blocks
  src/main.cpp
  ${SOURCES}
  ${HEADERS_MOC}
  )

target_link_libraries(blocks
  Qt4::QtGui
  Qt4::QtXml
  )
install(FILES
	src/block.png
	src/block2.png
	src/blue.png
	src/green.png
	src/black.png
	src/rosa.png
	src/orange.png
	src/red.png
	src/red_selected.png
	src/yellow.png
	src/yellow_selected.png
	DESTINATION ${PROJECT_BINARY_DIR}
)

