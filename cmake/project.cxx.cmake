function(setup_cxx_target target_name)

    # Check if using known CXX compiler
    if(NOT ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")))
        message(FATAL_ERROR "[setup_cxx_target] Can not configure ${target_name} for unknown CXX compiler: ${CMAKE_CXX_COMPILER_ID}")
    endif()
#    else()
#        message (STATUS "${target_name} configured for CXX compiler: ${CMAKE_CXX_COMPILER_ID}")
#    endif()

    # Set CXX Standard to 20
    target_compile_features(${target_name} PRIVATE cxx_std_20)

    # All Builds: Use maximal warning options
    set(warning_flags   "$<$<CXX_COMPILER_ID:GNU>:-Winline;-Wall;-Wextra>$<$<CXX_COMPILER_ID:MSVC>:/Wall>")

    # All Builds: Remove rtti - add "-fno-exceptions" for disabling exceptions
    set(feature_flags   "$<$<CXX_COMPILER_ID:GNU>:-fno-rtti>$<$<CXX_COMPILER_ID:MSVC>:/GR->")

    # Debug Builds: Minimize optimization and add debug flags
    set(debug_flags     "$<$<CXX_COMPILER_ID:GNU>:-O0;-g>$<$<CXX_COMPILER_ID:MSVC>:/Od;/Zi>")

    # Release Builds: Maximal optimization
    set(release_flags   "$<$<CXX_COMPILER_ID:GNU>:-O3;-fomit-frame-pointer;-ffast-math>$<$<CXX_COMPILER_ID:MSVC>:/O2;/fp:fast>")

    target_compile_options(${target_name} PRIVATE ${warning_flags} ${feature_flags})
    target_compile_options(${target_name} PRIVATE "$<$<CONFIG:DEBUG>:${debug_flags}>")
    target_compile_options(${target_name} PRIVATE "$<$<CONFIG:RELEASE>:${release_flags}>")

    # Define DEBUG in preprocessor for debug builds
    target_compile_definitions(${target_name} PRIVATE "$<$<CONFIG:DEBUG>:DEBUG>")

endfunction()