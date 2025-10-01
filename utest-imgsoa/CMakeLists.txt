#Executable for all unit tests with list of sources
# For example, you may have one ∗_test.cpp for each ∗.cpp in img−aos
add_executable(utest-imgsoa
        maxlevel_unittest.cpp
        cutfreq_unittest.cpp
        resize_unittest.cpp
        compress_unittest.cpp
)
# Library dependencies
target_link_libraries (utest-imgsoa
        PRIVATE
        imgsoa
        GTest::gtest_main
        Microsoft.GSL::GSL)