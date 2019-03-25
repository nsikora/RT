/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 12:40:27 by dtheo             #+#    #+#             */
/*   Updated: 2018/08/20 00:08:35 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <math.h>

# include "get_next_line.h"

# define FT_INT_MIN -2147483648
# define FT_INT_MAX 2147483647

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_vector2
{
	float			x;
	float			y;
}					t_vector2;

typedef struct		s_vector3
{
	float			x;
	float			y;
	float			z;
}					t_vector3;

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memrchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

t_list				*ft_lstnew(const void *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstpush(t_list *alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
size_t				ft_lstlen(t_list *lst);

t_vector2			ft_vector2_new(double x, double y);
double				ft_vector2_mag(t_vector2 v);
t_vector2			ft_vector2_mult(t_vector2 u, t_vector2 v);
t_vector2			ft_vector2_scl(t_vector2 v, double s);
t_vector2			ft_vector2_div(t_vector2 v, double s);
t_vector2			ft_vector2_add(t_vector2 u, t_vector2 v);
t_vector2			ft_vector2_sub(t_vector2 u, t_vector2 v);
t_vector2			ft_vector2_norm(t_vector2 v);

t_vector3			ft_vector3_new(double x, double y, double z);
double				ft_vector3_mag(t_vector3 v);
double				ft_vector3_dot(t_vector3 u, t_vector3 v);
t_vector3			ft_vector3_scl(t_vector3 v, double s);
t_vector3			ft_vector3_div(t_vector3 v, double s);
t_vector3			ft_vector3_cross(t_vector3 u, t_vector3 v);
t_vector3			ft_vector3_sub(t_vector3 u, t_vector3 v);
t_vector3			ft_vector3_add(t_vector3 u, t_vector3 v);
t_vector3			ft_vector3_norm(t_vector3 v);
t_vector3			ft_vector3_rodrigues(t_vector3 v, t_vector3 k, double t);

void				ft_strclr(char *s);
char				*ft_strnew(size_t size);
void				ft_strdel(char **s);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				**ft_strsplit(const char *s, char c);

void				ft_putendl_fd(const char *s, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_error(char *str);

void				ft_putchar(char c);
void				ft_putstr(const char *s);
void				ft_putendl(const char *s);
void				ft_putnbr(int n);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(const char *s, char (*f)(char));
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char				*ft_strsub(const char *s, unsigned int start, size_t len);

size_t				ft_strlen(const char *s);
char				*ft_strtrim(const char *s);
char				*ft_stralloc(const char *s);
char				*ft_strdup(const char *s);
int					ft_atoi(const char *nptr);
float				ft_fatoi(const char *str);

char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dest, const char *src, size_t n);

int					ft_strcmp(char const *s1, char const *s2);
int					ft_strncmp(char const *s1, char const *s2, size_t n);
int					ft_strequ(const char *s1, const char *s2);
int					ft_strnequ(const char *s1, const char *s2, size_t n);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big, const char *little, size_t n);

char				*ft_itoa(int n);
char				*ft_ftoa(float n, size_t precision);
int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

int					ft_abs(int n);
int					ft_factorial(int n);
int					ft_pow(int a, int b);

#endif
