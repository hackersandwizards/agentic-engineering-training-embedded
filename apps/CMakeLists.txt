add_executable(culina_sim culina_sim_main.cpp)
target_link_libraries(culina_sim PRIVATE culina_cli)
culina_set_warnings(culina_sim)

add_executable(culina_mcu culina_mcu_main.cpp)
target_link_libraries(culina_mcu PRIVATE culina_mcu_lib culina_simulation)
culina_set_warnings(culina_mcu)

add_executable(culina_app culina_app_main.cpp)
target_link_libraries(culina_app PRIVATE culina_app_lib culina_simulation)
culina_set_warnings(culina_app)

if(CULINA_BUILD_UI)
    qt_standard_project_setup(REQUIRES 6.5)
    qt_policy(SET QTP0004 NEW)
    qt_add_executable(culina_ui ui/culina_ui_main.cpp ui/device_view_model.cpp)
    target_include_directories(culina_ui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ui)
    target_link_libraries(culina_ui PRIVATE culina_app_lib culina_simulation Qt6::Quick
                                            Qt6::QuickControls2 Qt6::Qml Qt6::Network)
    culina_set_warnings(culina_ui)
    if(APPLE AND CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
        # Qt 6.11's generated QML cache loader invokes an empty variadic macro.
        target_compile_options(culina_ui PRIVATE -Wno-variadic-macro-arguments-omitted)
    endif()
    set_target_properties(culina_ui PROPERTIES MACOSX_BUNDLE TRUE
                                               MACOSX_BUNDLE_GUI_IDENTIFIER
                                               com.hackersandwizards.culina.ui)

    qt_add_qml_module(culina_ui
                      URI Culina
                      VERSION 1.0
                      QML_FILES ui/qml/Main.qml)
endif()
