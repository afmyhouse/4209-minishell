/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:21:17 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/03/25 17:21:15 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* ************************************************************************** */
///	CONSTANTS
/* ************************************************************************** */
# ifndef ERROR
#  define ERROR 1
# endif
# ifndef SUCCESS
#  define SUCCESS 0
# endif
# ifndef TRUE
#  define TRUE 1
# endif
# ifndef FALSE
#  define FALSE 0
# endif

/// Var sizes

# ifndef __LONG_LONG_MAX__
#  define __LONG_LONG_MAX__ 9223372036854775807
# endif
# ifndef __LONG_LONG_MIN__
#  define __LONG_LONG_MIN__ -9223372036854775808
# endif

/**********************
	LIBS
**********************/

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>

/**********************
	BONUS TYPEDEF
**********************/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* ************************************************************************** */
///	structure required by printf functions
/* ************************************************************************** */

typedef struct s_printf
{
	va_list	args;
	int		f_hash;
	int		f_align;
	char	f_stype;
	int		f_zpad;
	int		w_num;
	int		p_dot;
	int		p_num;
	char	e_sign;
	int		e_val;
	char	e_symb;
	char	e_radix;
	char	at;
	char	arg_len1;
	char	arg_len2;
	int		arg_zero;
	int		res_len;
	int		pf_len;
}	t_printf;

/* ************************************************************************** */
///	LIBFT BASE FUNCTIONS
/* ************************************************************************** */

void			ft_free_arr(char **str);
void			ft_free(char *str);

/// @see		ft_isspace, ft_issign, ft_isdigit
/// @brief 		Converts the initial portion of the string pointed to by nptr
/// @param nptr	Pointer to string
/// @return		The converted integer
int				ft_atoi(const char *nptr);

/// @see		ft_isspace, ft_issign, ft_isdigit
/// @brief 		Converts the initial portion of the string pointed to by nptr
///				to long int
/// @param nptr	The string to convert
/// @return		The converted long int
long			ft_atol(const char *nptr);

/// @see		ft_isspace, ft_issign, ft_isdigit
/// @brief 		Converts the initial portion of the string pointed to by nptr
///				to long int
/// @param nptr	The string to convert
/// @return		The converted long int
long double		ft_atoll(const char *nptr);

/// @see		malloc
/// @brief 		Converts a decimal to a string
/// @param n	The decimal to be converted
/// @param p	The precision of the decimal
/// @return		The string representation of the decimal
char			*ft_ftoa(float f, int p);

/// @brief 		Converts the integer n to a string
/// @param n	The integer to convert
///
/// @return		The string representation of the integer
char			*ft_itoa_base(const long int n, char base);

/// @see		ft_memset
/// @brief 		Fills a byte string with zeros.
/// @param s	Pointer to string
/// @param n	Number of bytes to fill
void			ft_bzero(void *s, size_t n);

/// @brief 		Converts the integer n to a string
/// @param n	The integer to convert
/// @return		The string representation of the integer
char			*ft_itoa(int n);

/// @see				malloc, ft_bzero
/// @brief 				Allocates memory for an array of Number of elements
///						of size item_size (bytes) each and returns a pointer to
///						the begin of allocated memory
/// @param item_qty		Number of elements
/// @param item_size	Size of each element
/// @return				Pointer to allocated memory
void			*ft_calloc(size_t nmemb, size_t size);

char			*ft_charjoin(char const *s1, char const c);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_issign(char c);
int				ft_isspace(int c);
/// @brief 			Builtin 'exit' command argument checker
/// @param str		Builtin 'exit' argument string
/// @return			SUCSESS or ERROR
int				ft_isnum(char *str);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			ft_putchar_fd(char c, int fd);
void			ft_putchar(char c);
void			ft_putendl_fd(const char *s, int fd);
void			ft_putendl(const char *s);
void			ft_putnbr_fd(int n, int fd);
void			ft_putnbr(int n);
void			ft_putstr_fd(const char *s, int fd);
void			ft_putstr(const char *str);
void			ft_strswap(char **s1, char **s2);
char			*ft_strrev(char *str, int j);
char			**ft_split(char const *s, char c);
char			**ft_split_set(char *str, char *charset);
/// @brief 		Locates the first occurrence of char `c` in the string `s`
/// @param s	String to search
/// @param c	Character to search for
/// @return		Pointer to the located character, or NULL if not found
char			*ft_strchr(const char *s, int c);
/// @brief 		Locates the first occurrence of char `c` in the string `s`
/// @param s	String to search
/// @param c	Character to search for
/// @return		Pointer to the located character, or NULL if not found
int				ft_strchr_i(const char *s, int c);
/// @brief 		Detects the occurrence of char from set in string s
/// @param str	string to process
/// @param set	set of chars
/// @return		char found or 0
char			ft_strset(const char *s, const char *set);
char			*ft_strdup(const char *s);
char			*ft_strjoin_free(char *s1, char *s2);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strtrim_free(char *line, char const *set);
char			*ft_strtrim_leading(char const *s1, char const *set);
char			*ft_strtrim_trailing(char const *s1, char const *set);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
int				ft_tolower(int c);
int				ft_toupper(int c);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
				void (*del)(void *));
/* ************************************************************************** */
///	FT_PRINTF SPECIFIC FUNCTIONS
/* ************************************************************************** */
/**********ft_pf_all2s_1.c**********/
int				ft_pf_tools_d2s(t_printf *f, unsigned int n, char *str);
int				ft_pf_tools_i2s(char arg_type, unsigned int n, char *str);
int				ft_pf_f2s(t_printf *f, char *str);
int				ft_pf_f2s_power(t_printf *f, char *arg_arr, \
				char *str, void *arg);
void			ft_pf_f2s_exp(t_printf *f, long double *arg);
/**********ft_pf_all2s_2.c**********/
int				ft_pf_tools_f2s_fill_arr(char base, char *arg_arr, void *arg);
int				ft_pf_tools_f2s_round(t_printf *f, int k, char *arg_arr);
int				ft_pf_tools_f2s_round_offset(t_printf *f);
int				ft_pf_tools_f2s_mantissa(t_printf *f, char dot, \
				char *arg_arr, char *str);
/* ft_pf_fwp2f.c - prepare t_printf for each new arg */
const char		*ft_pf_all2f(t_printf *flgs, const char *s);
const char		*ft_pf_f2f(t_printf *flgs, const char *s);
const char		*ft_pf_w2f(t_printf *flgs, const char *s);
const char		*ft_pf_p2f(t_printf *f, const char *s);
const char		*ft_pf_l2f(t_printf *flgs, const char *s);
/*	ft_pf_fwp2s.c */
int				ft_pf_fwp_p2s(t_printf *f, char *digit, int i);
int				ft_pf_fwp_war2s(t_printf *f, char *ds, int i);
int				ft_pf_fwp_wal2s(t_printf *f, char *ds, int i);
int				ft_pf_fwp_hash2s(t_printf *f, char *digit, int i);
void			ft_pf_write(t_printf *f, char *res);
/* ft_pf_tools1.c */
void			ft_pf_fwp_u(t_printf *f, void *arg);
char			ft_itoc_base(const int n, char radix);
char			*ft_pf_tools_strrev(char *str, int j);
char			ft_pf_base2radix(char base);
int				ft_isdigit(int c);
/* ft_pf_type_numbers.c*/
void			ft_pf_type_fega(t_printf *f);
void			ft_pf_type_fega_flags(t_printf *f);
void			ft_pf_type_g(t_printf *f);
void			ft_pf_type_iduox(t_printf *f);
void			ft_pf_type_n(t_printf *f);
/* ft_pf_type_scp.c*/
void			ft_pf_type_s(t_printf *f);
int				ft_pf_type_s2s(t_printf *f, char *res, char *ds, int ds_len);
void			ft_pf_type_c(t_printf *f);
void			ft_pf_type_p(t_printf *f);
int				ft_pf_type_p2s(t_printf *f, char *res, unsigned long long arg);
/*	ft_printf.c -  where the printf and most directly functions reside */
int				ft_printf(const char *format, ...);
const char		*ft_pf_type(t_printf *flgs, const char *s);
void			ft_pf_f_init(t_printf *f);
/* ************************************************************************** */
int				ft_min(int a, int b);
int				ft_max(int a, int b);
unsigned int	ft_abs(int n);
int				ft_intcmp(int a, int b);
/* ************************************************************************** */

#endif
