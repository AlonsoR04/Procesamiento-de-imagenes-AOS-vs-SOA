#Executable for all unit tests with list of sources
# For example, you may have one ∗_test.cpp for each ∗.cpp in img−aos
add_executable(ftest-soa
        maxlevel_ftest.cpp
        compress_ftest.cpp
        cutfreq_ftest.cpp
        resize_ftest.cpp
)
# Library dependencies
target_link_libraries (ftest-soa
        PRIVATE
        imgsoa
        GTest::gtest_main
)# CMakeLists.txt en el directorio ftest-aos