# DO NOT EDIT! This file was automatically generated by `dbt buildgen`
# External but in-source libraries
add_library(fatfs STATIC
    ff.c
    ffsystem.c
    ffunicode.c
    fatfs.cpp
)
target_include_directories(fatfs PUBLIC ${CMAKE_CURRENT_LIST_DIR})
set_target_properties(fatfs
    PROPERTIES
        C_STANDARD ${DELUGE_C_STANDARD}
        C_STANDARD_REQUIRED ON
        CXX_STANDARD ${DELUGE_CXX_STANDARD}
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON
)
