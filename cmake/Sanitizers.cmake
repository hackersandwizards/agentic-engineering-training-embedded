set(CULINA_SANITIZE
    ""
    CACHE STRING "Comma-separated sanitizers to enable (e.g. address,undefined or thread)")

if(CULINA_SANITIZE)
    add_compile_options(-fsanitize=${CULINA_SANITIZE} -fno-omit-frame-pointer)
    add_link_options(-fsanitize=${CULINA_SANITIZE})
endif()
