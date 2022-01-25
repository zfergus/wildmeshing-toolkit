
if(TARGET lagrange::core)
    return()
endif()

include(FetchContent)
FetchContent_Declare(
    lagrange
    GIT_REPOSITORY https://github.com/adobe/lagrange.git
    GIT_TAG v5.6.0
)
FetchContent_MakeAvailable(lagrange)
