# Je trouvais intéressant d’essayer d’utiliser CMake

cmake_minimum_required(VERSION 3.0)

project(vlc++)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror --pedantic-errors")

set(SRCS
    main.c
    )

set (HEADERS
     )

add_executable(vlc++ ${SRCS} ${HEADERS})

