add_library(culina_simulation STATIC sim_board.cpp thermal_model.cpp motor_model.cpp
                                     scale_model.cpp socket_transport.cpp sim_control_server.cpp)
target_link_libraries(culina_simulation PUBLIC culina_hal)
culina_set_warnings(culina_simulation)
