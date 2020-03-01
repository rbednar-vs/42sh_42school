/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbednar <rbednar@sdudent.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 11:48:24 by sschmele          #+#    #+#             */
/*   Updated: 2020/03/01 14:59:33 by rbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include "ft_printf.h"
# include "get_next_line.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_lstsize(t_list *begin_list);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
int					ft_atoi(const char *str);
char				*ft_strcpy(char *dest, const char *src);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
char				*ft_strncpy(char *dst, const char *src, size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strchri(char *s, int c);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack,
		const char *needle, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				**ft_strsplit(char const *s, char c);
char				*ft_strtrim(char const *s);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				ft_strdel(char **as);
char				*ft_strnew(size_t size);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char*));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strndup(const char *s1, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
void				ft_putnbr(int n);
char				*ft_makerevstr(char *s);
void				ft_putendl(char const *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
long				ft_nb_root(long nb, size_t root);
char				*ft_itoa(int ni);
long long			ft_atoll(const char *str);
void				ft_bubble_sort(char *s);
void				ft_choice_sort(char *s);
void				ft_nputstr(char const *s, int len);
void				ft_insertive_sort(char *s);
size_t				ft_strchrlen(const char *s, int c);
char				*ft_strchrnew(char *s, int c);
char				*ft_strrejoin(char *s1, char *s2);
void				ft_lstdelcont(void *content, size_t size);
void				ft_mapdel(char **map, int i);
void				ft_printmap(char **map, int side);
char				*ft_ltoa_base(long nb, int base);
char				*ft_utoa_base(unsigned long nb, int base);
char				*ft_strnewsetchar(size_t size, char c);
char				*ft_strremerge(char *s1, size_t len_s1, char *s2, size_t n);
char				*ft_restrsub(char *s, int start, int len);
char				*ft_utoa_base(unsigned long nb, int base);
void				ft_arrdel(char **arr);

#endif
