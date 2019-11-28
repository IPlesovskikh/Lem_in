//
// Created by Peggie Donnie on 2019-11-24.
//

#ifndef INC_42_LEM_IN_VALIDATOR_H
#define INC_42_LEM_IN_VALIDATOR_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>

# define BUFF_SIZE 100


typedef struct		s_child
{
	int 			num;
	struct s_child 	*next;
}					t_child;

typedef struct		s_room
{
	int 			num;
	char			*name;
	int 			x;
	int 			y;
	int 			level;
	int 			input;
	int 			output;
	struct s_room 	*next;
	t_child 		*child;
}					t_room;

typedef	struct		s_link
{
	int 			a;
	int 			b;
	struct s_link 	*next;
	struct s_link 	*prev;
}					t_link;

typedef struct		s_data
{
	int				ants;
	t_link			*links;
	t_room			*rooms;
	t_room			*start;
	t_room			*end;
	int				total_rooms;
}					t_data;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_lines
{
	char 			*line;
	struct s_lines	*next;
}					t_lines;

int		            validator(t_data *data, int fd);
int					check_links(t_link *link, t_link *temp_link);
t_link				*ft_create_link(t_link *temp_link, t_data *data);
int					ft_fill_link(t_link *temp_link, t_data *data, t_lines *lines);
int					get_links(t_data *data, t_lines *lines);
int 				get_commande(t_data *data, t_lines **lines);
int 				get_rooms(int i, int i2, t_data *data, t_lines *lines);
int					bfs(t_data *data, t_room **array);
void				fill_array_rooms(t_data *data, t_room **array);

int					get_next_line(const int fd, char **line);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *s);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
t_list				*ft_lstnew(void const *content, size_t content_size);
char				*ft_strchr(const char *s, int c);
void				*ft_memcpy(void *restrict dst, const void *restrict src, size_t n);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_check_comment(t_lines **lines);
int					create_array_rooms(t_data *data, t_room ***array);

#endif //INC_42_LEM_IN_VALIDATOR_H
