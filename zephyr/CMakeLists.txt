if(CONFIG_MICROCBOR)

zephyr_include_directories(../include)

zephyr_library()
zephyr_library_sources(
    ../src/dataitem.c
    ../src/decoder.c
    ../src/encoder.c
    ../src/exp2_uint.c
)

endif()
