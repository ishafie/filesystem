/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 17:13:03 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/27 20:12:39 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "tos.h"
# include <dirent.h>
# include <fcntl.h>
# include <time.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# define YELLOW "\e[1;33m"
# define BLUE "\e[0;36m"
# define RED "\e[0;31m"
# define WHITE "\e[1;37m"
# define PURPLE "\e[1;35m"
# define STOP "\e[0m"
# define CYAN "\e[1;36m"
# define GREEN "\e[1;32m"

char					*g_name_prog;

t_env					*create_env(void);
int						my_exit(char **args);
void					display_prompt(t_env *e);
void					safe_exit(int a);


#endif
