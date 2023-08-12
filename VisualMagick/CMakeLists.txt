cmake_minimum_required(VERSION 3.10)

# SET THE PROJECT NAME
project(configure)

# SET CPP STANDARD
set(CMAKE_CXX_STANDARD_REQUIRED True)
if(MSVC)
  add_compile_options(/W4)
endif()

add_compile_definitions(_AFXDLL WINVER=0x500 _CRT_SECURE_NO_WARNINGS)


if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/ CACHE PATH "Install path that is not program files" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)


#list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/Sdl/include")


# CREATE TARGET EXECUTABLE + INCLUDE DIRECTORIES + LINKING
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/configure/configure.cpp ${PROJECT_SOURCE_DIR}/configure/configure_wizard.cpp
               ${PROJECT_SOURCE_DIR}/configure/finished_page.cpp ${PROJECT_SOURCE_DIR}/configure/stdafx.cpp ${PROJECT_SOURCE_DIR}/configure/system_page.cpp
               ${PROJECT_SOURCE_DIR}/configure/target_page.cpp ${PROJECT_SOURCE_DIR}/configure/WaitDlg.cpp ${PROJECT_SOURCE_DIR}/configure/welcome_page.cpp)

target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/configure/configure.rc)
#${PROJECT_SOURCE_DIR}/configure/configure.rc2

target_include_directories(${PROJECT_NAME} PUBLIC ${EXTRA_INCLUDES} "${PROJECT_SOURCE_DIR}/configure")

target_link_libraries(${PROJECT_NAME} rpcrt4.lib)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")


set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX _d)
install(TARGETS ${PROJECT_NAME} CONFIGURATIONS Debug RUNTIME DESTINATION Debug)
install(TARGETS ${PROJECT_NAME} CONFIGURATIONS Release RUNTIME DESTINATION Release)
install(TARGETS ${PROJECT_NAME} CONFIGURATIONS MinSizeRel RUNTIME DESTINATION MinSizeRel)
install(TARGETS ${PROJECT_NAME} CONFIGURATIONS RelWithDebInfo RUNTIME DESTINATION RelWithDebInfo)

# POST BUILD COMMAND TO COPY EXE TO .. DIR
set(CONFIGURE_API_BIN "${CMAKE_BINARY_DIR}")
ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" ${CONFIGURE_API_BIN}
    COMMENT "Copying configure.exe to ${CONFIGURE_API_BIN}." VERBATIM
)

