
cmake_minimum_required (VERSION 3.12)
project ("Jamb")

include(GenerateExportHeader)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include_directories("include/jamb")

set(JAMB_VERSION 0.0.1)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")



#----------------------#
#  PLATFORM DETECTION  #
#----------------------#
if(NOT PLATFORM)
	if(WIN32)
		set(PLATFORM "win32")
	elseif(UNIX AND NOT APPLE)
		set(PLATFORM "libx11")
	else()
		message(FATAL_ERROR "Platform is unsuppored")
	endif()
	message(STATUS "Platform detected: ${PLATFORM}")
	add_compile_definitions(${PLATFORM})
endif()



#--------------------#
#  LIBRARY CREATION  #
#--------------------#

# get the relevent source files
file(GLOB_RECURSE jamb_src "src/*.h" "src/*.cpp")
message(STATUS ${jamb_src})

# create the libjamb library
add_library(jamb STATIC ${jamb_src})

# set include directory for header files
target_include_directories(jamb 
	PUBLIC
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/jamb>"
	"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/jamb>"
)

# add platform definition to targets file
target_compile_definitions(jamb PUBLIC ${PLATFORM})

# set c++ version to 17
target_compile_features(jamb PUBLIC cxx_std_17)
target_compile_options(jamb PUBLIC "-std=c++17")



#----------------------#
#  INSTALLATION RULES  #
#----------------------#

# install libraries and binaries
install(TARGETS jamb EXPORT jambTargets
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

# install header files
install(
	DIRECTORY "include/jamb"
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# install cmake config files
install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_DATADIR}/jambConfigVersion.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_DATADIR}/jambConfig.cmake"
	DESTINATION "${CMAKE_INSTALL_DATADIR}/jamb"
)

# install cmake targets file
install(EXPORT jambTargets
	FILE "jambTargets.cmake"
	DESTINATION "${CMAKE_INSTALL_DATADIR}/jamb"
	NAMESPACE jamb::
)



#--------------------------#
#  CONFIG FILE GENERATION  #
#--------------------------#

# export jambConfigVersion
write_basic_package_version_file(
	"${CMAKE_INSTALL_DATADIR}/jambConfigVersion.cmake"
	VERSION ${JAMB_VERSION}
	COMPATIBILITY AnyNewerVersion
)

# export jambConfig
configure_package_config_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/config/jambConfig.cmake.in"
	"${CMAKE_INSTALL_DATADIR}/jambConfig.cmake"
	INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}"
)

# export jambTargets
export(TARGETS jamb
	FILE "${CMAKE_INSTALL_DATADIR}/jambTargets.cmake"
	NAMESPACE jamb::
)



#-----------------------#
#  EXAMPLE EXECUTABLES  #
#-----------------------#
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	add_subdirectory("examples")
endif()
