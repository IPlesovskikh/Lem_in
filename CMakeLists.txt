cmake_minimum_required(VERSION 3.14)
project(Lem_in C)

set(CMAKE_C_STANDARD 99)

add_executable(Lem_in main.c ft_strsub.c ft_strlen.c ft_strjoin.c ft_strcmp.c ft_strchr.c ft_memcpy.c ft_isdigit.c ft_lstnew.c
        ft_atoi.c validator.h validator.c get_next_line.c validator_links.c validator_rooms.c validator_free.c algo_array_of_rooms.c bfs.c algo_prepare.c search_path.c)