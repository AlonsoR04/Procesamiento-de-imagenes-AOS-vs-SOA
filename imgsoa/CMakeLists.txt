 #Add to this list all files related to imgaos library
 add_library(imgsoa
         imgesoa.cpp
         imgesoa.hpp

 )
 # Use this line only if you have dependencies from this library to GSL
 target_link_libraries (imgsoa PRIVATE common Microsoft.GSL::GSL)