cmake_minimum_required(VERSION 3.0.2)
project(rviz_lighting)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roslint
  rviz
)

roslint_cpp()

## This plugin includes Qt widgets, so we must include Qt.
## We'll use the version that rviz used so they are compatible.
if(rviz_QT_VERSION VERSION_LESS "5")
  message(STATUS "Using Qt4 based on the rviz_QT_VERSION: ${rviz_QT_VERSION}")
  find_package(Qt4 ${rviz_QT_VERSION} EXACT REQUIRED QtCore QtGui)
  ## pull in all required include dirs, define QT_LIBRARIES, etc.
  include(${QT_USE_FILE})
else()
  message(STATUS "Using Qt5 based on the rviz_QT_VERSION: ${rviz_QT_VERSION}")
  find_package(Qt5 ${rviz_QT_VERSION} EXACT REQUIRED Core Widgets)
  ## make target_link_libraries(${QT_LIBRARIES}) pull in all required dependencies
  set(QT_LIBRARIES Qt5::Widgets)
endif()

catkin_package(
  CATKIN_DEPENDS
  rviz
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

if(rviz_QT_VERSION VERSION_LESS "5")
  qt4_wrap_cpp(MOC_FILES
    include/${PROJECT_NAME}/AmbientLightDisplay.h
    include/${PROJECT_NAME}/LightDisplay.h
  )
else()
  qt5_wrap_cpp(MOC_FILES
    include/${PROJECT_NAME}/AmbientLightDisplay.h
    include/${PROJECT_NAME}/LightDisplay.h
  )
endif()

add_library(${PROJECT_NAME}
  src/AmbientLightDisplay.cpp
  src/LightDisplay.cpp
  src/LightVisual.cpp
  ${MOC_FILES}
)

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  ${QT_LIBRARIES}
)

# install
install(TARGETS
  ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)

install(FILES
  plugin_description.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(DIRECTORY config/ DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/config)
install(DIRECTORY launch/ DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch)
install(DIRECTORY urdf/ DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/urdf)

