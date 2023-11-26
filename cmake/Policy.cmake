macro(neschess_policy)
    #MSVC Runtime Library policy
    if (POLICY CMP0091)
        cmake_policy(SET CMP0091 NEW)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "" CACHE STRING "" FORCE)
        set(MSVC_RUNTIME_LIBRARY "" CACHE STRING "" FORCE)
    endif()
    #DOWNLOAD_EXTRACT_TIMESTAMP policy
    if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
        cmake_policy(SET CMP0135 NEW)
    endif()
endmacro()