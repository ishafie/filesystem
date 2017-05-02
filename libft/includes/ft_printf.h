/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 13:02:20 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/26 10:27:40 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <limits.h>

# define KCYN "\033[0;36m"
# define KRESET "\033[0m"
# define KRED "\033[0;31m"
# define KWHI "\033[1;37m"

typedef struct	s_struct
{
	char		flag;
	char		clong;
	int			prec;
	int			min;
}				t_struct;

int				ft_printf(char const *format, ...);
int				noflag(va_list ap, char conv);
int				pf_print_var(t_struct data, char conv, va_list ap);
void			fill_data_flag(char c, t_struct *data);
int				fill_data_clong(char c, char d, t_struct *data);
int				fill_data_prec(char const *str, size_t *i, va_list ap);
int				fill_data_min(char const *str, size_t *i, va_list ap);
int				pf_isconver(char c);
t_struct		init_data(void);
int				pf_isclong(char c, char d);
int				pf_isflag(char c);
int				pf_isnum(char c);
int				pf_print_line(va_list ap, char const *str);
int				pf_putstr(char const *str);
int				put_prec_nbr(int nbr);
int				pf_putchar(char c);
void			pf_fill_struct(char *str, size_t *i, t_struct *data, va_list a);
int				pf_until_conv(size_t *i, va_list ap, char const *str);
int				percent_conv(t_struct data);
int				conv_any(char conv, t_struct data, va_list ap);
size_t			ft_strlen(char const *str);
void			ft_putchar(char c);
void			ft_putstr(char const *str);
void			*ft_memalloc(size_t size);
void			ftp_putnbr(int n, int flag);
void			ft_bzero(void *s, size_t n);
int				ft_atoi(const char *str);
int				pf_retbin(size_t nbr);
void			ft_putnbr_bin(size_t nbr);
char			*ft_strncpy(char *dst, const char *src, size_t n);
int				hexa_conv(t_struct data, va_list ap, int lower);
int				pf_rethexa_noclong(unsigned int nbr, int lower);
int				pf_rethexa_h(unsigned short nbr, int lower);
int				pf_rethexa_hh(unsigned char nbr, int lower);
int				pf_rethexa_j(uintmax_t nbr, int lower);
int				pf_rethexa_l(unsigned long nbr, int lower);
int				pf_rethexa_ll(unsigned long long nbr, int lower);
int				pf_rethexa_z(size_t nbr, int lower);
void			pf_puthexa_noflag(unsigned int nbr, int lower);
void			pf_puthexa_noflag_h(unsigned short nbr, int lower);
void			pf_puthexa_noflag_hh(unsigned char nbr, int lower);
void			pf_puthexa_noflag_j(uintmax_t nbr, int lower);
void			pf_puthexa_noflag_l(unsigned long nbr, int lower);
void			pf_puthexa_noflag_ll(unsigned long long nbr, int lower);
void			pf_puthexa_noflag_z(size_t nbr, int lower);
int				hexa_conv_noclong(t_struct data, unsigned int nbr, int lower);
int				hexa_conv_h(t_struct data, unsigned short nbr, int lower);
int				hexa_conv_hh(t_struct data, unsigned char nbr, int lower);
int				hexa_conv_j(t_struct data, uintmax_t nbr, int lower);
int				hexa_conv_l(t_struct data, unsigned long nbr, int lower);
int				hexa_conv_ll(t_struct data, unsigned long long nbr, int lower);
int				hexa_conv_z(t_struct data, size_t nbr, int lower);
int				string_conv(t_struct data, va_list ap, int lower);
int				string_conv_noclong(t_struct data, char *str);
int				ft_strwlen(wchar_t *str);
int				string_conv_l(t_struct data, wchar_t *str);
int				pf_putstruni(wchar_t *str);
int				char_conv(t_struct data, va_list ap, int lower);
int				char_conv_noclong(t_struct data, char c);
int				char_conv_l(t_struct data, wchar_t c);
int				pf_putcharuni(wchar_t c);
int				octal_conv(t_struct data, va_list ap, int lower);
int				pf_retoctal_noclong(unsigned int nbr, int lower);
int				pf_retoctal_l(unsigned long nbr, int lower);
int				pf_retoctal_ll(unsigned long long nbr, int lower);
int				pf_retoctal_h(unsigned short nbr, int lower);
int				pf_retoctal_hh(unsigned char nbr, int lower);
int				pf_retoctal_j(uintmax_t nbr, int lower);
int				pf_retoctal_z(size_t nbr, int lower);
void			pf_putoctal_noflag(unsigned int nbr);
void			pf_putoctal_noflag_l(unsigned long nbr);
void			pf_putoctal_noflag_ll(unsigned long long nbr);
void			pf_putoctal_noflag_h(unsigned short nbr);
void			pf_putoctal_noflag_hh(unsigned char nbr);
void			pf_putoctal_noflag_j(uintmax_t nbr);
void			pf_putoctal_noflag_z(size_t nbr);
int				octal_conv_noclong(t_struct data, unsigned int nbr);
int				octal_conv_hh(t_struct data, unsigned char nbr);
int				octal_conv_ll(t_struct data, unsigned long long nbr);
int				octal_conv_h(t_struct data, unsigned short nbr);
int				octal_conv_l(t_struct data, unsigned long nbr);
int				octal_conv_j(t_struct data, uintmax_t nbr);
int				octal_conv_z(t_struct data, size_t nbr);
int				deci_conv(t_struct data, va_list ap);
int				pf_retdeci_noclong(int n, int flag);
int				pf_retdeci_h(short n, int flag);
int				pf_retdeci_hh(char n, int flag);
int				pf_retdeci_l(long n, int flag);
int				pf_retdeci_ll(long long n, int flag);
int				pf_retdeci_j(uintmax_t n, int flag);
int				pf_retdeci_z(size_t n, int flag);
int				deci_conv_noclong(t_struct data, int nbr);
int				deci_conv_h(t_struct data, short nbr);
int				deci_conv_hh(t_struct data, char nbr);
int				deci_conv_l(t_struct data, long nbr);
int				deci_conv_ll(t_struct data, long long nbr);
int				deci_conv_j(t_struct data, uintmax_t nbr);
int				deci_conv_z(t_struct data, size_t nbr);
void			ft_putnbr(int nbr, int flag);
void			ft_putnbr_h(short n, int flag);
void			ft_putnbr_hh(char n, int flag);
void			ft_putnbr_l(long n, int flag);
void			ft_putnbr_ll(long long n, int flag);
void			ft_putnbr_j(uintmax_t n, int flag);
void			ft_putnbr_z(size_t n, int flag);
int				unsigned_conv(t_struct data, va_list ap, int lower);
int				unsigned_conv_noclong(t_struct data, unsigned int nbr);
int				unsigned_conv_hh(t_struct data, unsigned char nbr);
int				unsigned_conv_h(t_struct data, unsigned short nbr);
int				unsigned_conv_ll(t_struct data, unsigned long long nbr);
int				unsigned_conv_l(t_struct data, unsigned long nbr);
int				unsigned_conv_j(t_struct data, uintmax_t nbr);
int				unsigned_conv_z(t_struct data, size_t nbr);
int				pf_retunsigned_noclong(unsigned int n, int flag);
int				pf_retunsigned_h(unsigned short n, int flag);
int				pf_retunsigned_hh(unsigned char n, int flag);
int				pf_retunsigned_l(unsigned long n, int flag);
int				pf_retunsigned_ll(unsigned long long n, int flag);
int				pf_retunsigned_j(uintmax_t n, int flag);
int				pf_retunsigned_z(size_t n, int flag);
void			ft_putunsigned_noclong(unsigned int n, int flag);
void			ft_putunsigned_h(unsigned short n, int flag);
void			ft_putunsigned_hh(unsigned char n, int flag);
void			ft_putunsigned_l(unsigned long n, int flag);
void			ft_putunsigned_ll(unsigned long long n, int flag);
void			ft_putunsigned_j(uintmax_t n, int flag);
void			ft_putunsigned_z(size_t n, int flag);
int				pf_retmem_noclong(size_t n, int flag);
void			pf_putmem_noflag(size_t nbr);
int				mem_conv_noclong(t_struct data, size_t nbr);
int				mem_conv(t_struct data, va_list ap);

#endif
