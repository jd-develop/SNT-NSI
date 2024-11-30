# Je trouvais intéressant d’essayer d’utiliser CMake

cmake_minimum_required(VERSION 3.10)

project(dm2)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror --pedantic-errors -lm -g")

set(SRCS
    main.c
    src/run_tests.c
    src/sound.c
    src/wav.c
    src/melody.c
)

set (HEADERS
     src/run_tests.h
     src/sound.h
     src/wav.h
     src/melody.h
)

add_executable(dm2 ${SRCS} ${HEADERS})
target_link_libraries(dm2 m)

