#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "qt_ui_test" for configuration "Release"
set_property(TARGET qt_ui_test APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(qt_ui_test PROPERTIES
  IMPORTED_LOCATION_RELEASE "/home/zhang/c-_algorithm/install/bin/qt_ui_test"
  )

list(APPEND _IMPORT_CHECK_TARGETS qt_ui_test )
list(APPEND _IMPORT_CHECK_FILES_FOR_qt_ui_test "/home/zhang/c-_algorithm/install/bin/qt_ui_test" )

# Import target "qt_ui" for configuration "Release"
set_property(TARGET qt_ui APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(qt_ui PROPERTIES
  IMPORTED_LOCATION_RELEASE "/home/zhang/c-_algorithm/install/lib/libqt_ui.so"
  IMPORTED_SONAME_RELEASE "libqt_ui.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS qt_ui )
list(APPEND _IMPORT_CHECK_FILES_FOR_qt_ui "/home/zhang/c-_algorithm/install/lib/libqt_ui.so" )

# Import target "common" for configuration "Release"
set_property(TARGET common APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(common PROPERTIES
  IMPORTED_LOCATION_RELEASE "/home/zhang/c-_algorithm/install/lib/libcommon.so"
  IMPORTED_SONAME_RELEASE "libcommon.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS common )
list(APPEND _IMPORT_CHECK_FILES_FOR_common "/home/zhang/c-_algorithm/install/lib/libcommon.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
