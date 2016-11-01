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
  images
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
	images/block.png
	images/block2.png
	images/blue.png
	images/green.png
	images/black.png
	images/rosa.png
	images/orange.png
	images/red.png
	images/red_selected.png
	images/yellow.png
	images/yellow_selected.png
	DESTINATION ${PROJECT_BINARY_DIR}/images
)

