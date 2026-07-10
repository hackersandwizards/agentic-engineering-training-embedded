add_library(culina_cli STATIC commands.cpp script_runner.cpp repl.cpp)
target_link_libraries(culina_cli PUBLIC culina_system)
culina_set_warnings(culina_cli)
