cmake_minimum_required(VERSION 3.14)
project(Lem_in C)

set(CMAKE_C_STANDARD 99)

add_executable(lem-in main.c ft_strsub.c ft_strlen.c ft_strjoin.c ft_strcmp.c ft_strchr.c ft_memcpy.c ft_isdigit.c ft_lstnew.c
        ft_atoi.c validator.h validator.c get_next_line.c validator_links.c validator_rooms.c algo_array_of_rooms.c bfs.c algo_prepare.c search_path.c algo_move_ants.c free.c print.c create_and_fill_data.c comments.c algo_del_child.c algo_input_fork.c algo_calc_input_output.c)