add_library(culina_sim STATIC sim_board.cpp thermal_model.cpp motor_model.cpp scale_model.cpp)
target_link_libraries(culina_sim PUBLIC culina_hal culina_common)
culina_set_warnings(culina_sim)
