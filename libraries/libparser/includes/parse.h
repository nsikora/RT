/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:41:38 by nsikora           #+#    #+#             */
/*   Updated: 2018/08/21 15:00:40 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define ERR_COMMA			(-1)
# define ERR_OPEN_BRACKET	(-2)
# define ERR_END_BRACKET	(-3)
# define ERR_NBR_BRACKET	(-4)
# define ERR_ARRAY			(-5)
# define ERR_DQUOTE			(-6)
# define ERR_DDOT			(-7)
# define READ_BUF_SIZE		4096
# define MALLOC_ERROR		"Error: Malloc error"

typedef struct				s_error
{
	int						id;
	int						line;
}							t_error;

typedef struct				s_parse
{
	int						cpy;
	int						comma;
	int						array;
	int						bracket;
	int						double_quote;
}							t_parse;

typedef	struct				s_info
{
	char					*str;
	int						length;
	void					*value;
	struct s_info			*next;
}							t_info;

typedef	struct				s_json_obj
{
	char					*str;
	t_info					*info;
	struct s_json_obj		*next;
}							t_json_obj;

void						check_parse_error(t_parse *parse,
							t_error *error, char *str);
t_json_obj					*ft_parse_file(char *path, int *error,
							t_json_obj *obj, int fd);
int							check_ext(char *file);
int							check_useless(char c);
t_error						*check_parse_dquote(t_parse *parse, t_error *error,
							char *str, int i);
t_error						*check_parse_ddot(t_parse *parse,
							t_error *error, char *str, int i);
void						error_message(t_error *error);
void						store_info(char *str, t_json_obj **obj, int cp);
void						get_info(char *str, int *i, t_json_obj **obj);
void						get_info_value_array(char *str, int *i,
							t_info **info);
void						fill_info_value_string(char *tmp, char *str,
							int j, int *i);
void						get_info_value(char *str, int *i, t_info **info);
t_info						*init_info(void);

#endif
