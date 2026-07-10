option(CULINA_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

function(culina_set_warnings target)
    target_compile_options(
        ${target}
        PRIVATE -Wall
                -Wextra
                -Wpedantic
                -Wshadow
                -Wconversion
                -Wsign-conversion
                -Wnon-virtual-dtor
                -Woverloaded-virtual)
    if(CULINA_WARNINGS_AS_ERRORS)
        target_compile_options(${target} PRIVATE -Werror)
    endif()
endfunction()

# Firmware translation units build without exceptions and RTTI, matching the
# constraints of the target toolchain. Host-only code (sim, CLI, tests) keeps both.
function(culina_firmware_target target)
    culina_set_warnings(${target})
    target_compile_options(${target} PRIVATE -fno-exceptions -fno-rtti)
endfunction()
