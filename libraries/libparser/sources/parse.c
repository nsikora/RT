/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 12:23:52 by nsikora           #+#    #+#             */
/*   Updated: 2018/08/21 15:00:11 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_parse	*init_parse(void)
{
	t_parse		*parse;

	if ((parse = ft_memalloc(sizeof(t_parse))) == 0)
		ft_error(MALLOC_ERROR);
	parse->comma = 0;
	parse->bracket = 0;
	parse->array = 0;
	parse->cpy = 0;
	parse->double_quote = 0;
	return (parse);
}

static t_error	*init_error(void)
{
	t_error		*error;

	if ((error = ft_memalloc(sizeof(t_error))) == 0)
		ft_error(MALLOC_ERROR);
	error->id = 0;
	error->line = 1;
	return (error);
}

static int		parse(char *str, t_json_obj **obj)
{
	t_parse		*parse;
	t_error		*error;
	int			nb;

	parse = init_parse();
	error = init_error();
	check_parse_error(parse, error, str);
	store_info(str, obj, 0);
	nb = error->id;
	free(parse);
	free(error);
	return (nb);
}

t_json_obj		*ft_parse_file(char *path, int *error, t_json_obj *obj, int fd)
{
	ssize_t		ret;
	char		buf[READ_BUF_SIZE + 1];
	char		*str;
	char		*tmp;

	check_ext(path);
	if ((fd = open(path, O_RDONLY)) == -1)
		ft_error("Error opening file");
	if ((str = ft_strnew(1)) == NULL)
		ft_error(MALLOC_ERROR);
	while ((ret = read(fd, buf, READ_BUF_SIZE)) > 0)
	{
		buf[ret] = 0;
		if ((tmp = ft_strjoin(str, buf)) == NULL)
			ft_error(MALLOC_ERROR);
		free(str);
		str = tmp;
	}
	if (close(fd) == -1 || ret == -1 || buf[0] == '\0')
		ft_error("Error: reading file");
	*error = parse(str, &obj);
	free(tmp);
	return (obj);
}
