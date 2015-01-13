set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)

SET( TARGET_BASE_NAME bomfilefinder )

SET(BASE_SOURCE_PATH ".")
include_directories(${BASE_SOURCE_PATH}/resources)

#-----------------------------------------------------------------------------

SET( EXE_NAME "${TARGET_BASE_NAME}" )

# Add any source files here.
SET( EXE_SRCS
	${BASE_SOURCE_PATH}/MainWindow.cpp
	${BASE_SOURCE_PATH}/BOMDetector.cpp
)


# Add any include files here.
SET( EXE_INCS
	${BASE_INCLUDE_PATH}/BOMFileFinder/MainWindow.h 
	${BASE_INCLUDE_PATH}/BOMFileFinder/BOMDetector.h 
)

SET( EXE_RCCS ${BASE_SOURCE_PATH}/resources/bomfilefinder.qrc )

if (WIN32)
	SET( EXE_INCS ${EXE_INCS} ${BASE_SOURCE_PATH}/resources/resources.h )
	SET( EXE_SRCS ${EXE_SRCS} ${BASE_SOURCE_PATH}/resources/bomfilefinder.rc )
endif()

#-----------------------------------------------------------------------------


FILE(GLOB SG_ROOT ${BASE_INCLUDE_PATH}/BOMFileFinder/* ${BASE_SOURCE_PATH}/*.cpp ${BASE_SOURCE_PATH}/*.cxx)

source_group(src FILES ${SG_ROOT})
source_group(src\\resources REGULAR_EXPRESSION resources/.*)

SET(BASE_SRCS
		main.cpp
)
SET(BASE_INCS
)

# qt wrap
QT5_ADD_RESOURCES(EXE_RCC_SRCS ${EXE_RCCS})

ADD_EXECUTABLE(${EXE_NAME} WIN32 ${BASE_SRCS} ${BASE_INCS_MOC} ${EXE_SRCS} ${EXE_INCS} ${EXE_INCS_MOC} ${EXE_RCC_SRCS})

TARGET_LINK_LIBRARIES ( ${EXE_NAME}
  ${CMAKE_THREAD_LIBS_INIT}
  ${CMAKE_DL_LIBS}
)

qt5_use_modules(${EXE_NAME} Widgets)

install (TARGETS ${EXE_NAME}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)

# installer
get_target_property(QtCore_location Qt5::Core LOCATION)
get_filename_component(QtRootPathBin ${QtCore_location} PATH)
get_filename_component(QtRootPath ${QtRootPathBin} DIRECTORY)

message(status "MSVC: ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}")

list(GET CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS 0 MSVCDep1)
list(GET CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS 1 MSVCDep2)

set(SetupPlatform "unknown")
set(SetupArch "")
if (WIN32)
  if (CMAKE_CL_64) 
	set(SetupPlatform "win64")
	set(SetupArch "x64")
  else()
	set(SetupPlatform "win32")
  endif() 
endif()


configure_file(${CMAKE_SOURCE_DIR}/bomfilefinder.iss.in ${PROJECT_BINARY_DIR}/bomfilefinder.iss )
