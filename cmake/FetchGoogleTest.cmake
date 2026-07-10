include(FetchContent)

# The first configure needs network access to download GoogleTest. For offline
# machines, pre-populate with -DFETCHCONTENT_SOURCE_DIR_GOOGLETEST=/path/to/googletest.
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
    URL_HASH SHA256=7b42b4d6ed48810c5362c265a17faebe90dc2373c885e5216439d37927f02926
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
