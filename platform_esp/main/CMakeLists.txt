file(GLOB_RECURSE SHARED_SRCS "../../src/*.c")

idf_component_register(
    SRCS
        "platform_esp.c"
        "platform_display.c"
        "platform_input.c"
        "font.c"
        ${SHARED_SRCS}
    INCLUDE_DIRS
        "."
        "../../include"
)
