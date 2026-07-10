add_library(culina_protocol STATIC frame_parser.cpp frame_writer.cpp link.cpp)
target_link_libraries(culina_protocol PUBLIC culina_hal)
culina_firmware_target(culina_protocol)
