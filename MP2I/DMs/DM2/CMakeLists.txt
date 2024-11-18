# Je trouvais intéressant d’essayer d’utiliser CMake

cmake_minimum_required(VERSION 3.10)

project(vlc++)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror --pedantic-errors -lm -g")

set(SRCS
    main.c
    src/file_management.c
    src/run_tests.c
    src/sound.c
    src/wav.c
    )

set (HEADERS
     src/file_management.h
     src/run_tests.h
     src/sound.h
     src/wav.h
     )

add_executable(vlc++ ${SRCS} ${HEADERS})

