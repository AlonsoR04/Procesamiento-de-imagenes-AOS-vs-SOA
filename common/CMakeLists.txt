#Add to this lisy all files related to common library
add_library(common
        progars.cpp
        binaryio.hpp
        progars.hpp
        info.cpp
        info.hpp
)

#Use this line only if you have dependencies from this library to GSL
target_link_libraries (common PRIVATE Microsoft.GSL::GSL)