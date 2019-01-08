add_executable(test_runner
    main.cpp
    test_signature.cpp)
target_link_libraries(test_runner
    PRIVATE
    cppjni
    ${JNI_LIBRARIES})
add_test(test test_runner)
