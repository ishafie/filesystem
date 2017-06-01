/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tos.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 23:40:16 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/28 20:30:08 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOS_H
# define TOS_H

# include "libft.h"
# include "colors.h"
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include "dirent.h"

enum
{
	LEFT = 1,
	UP,
	DOWN,
	RIGHT
};

enum
{
	READ_HIST,
	WRITE_HIST,
	NEXT_HIST,
	PREV_HIST,
	FIRST_HIST,
	SECOND_HIST,
	ADD_HIST,
	SAVE_LINE,
	RES_ORI
};

enum
{
	PAIRING,
	HEREDOC,
	NORMAL
};

enum
{
	ADD_SPACE,
	RUP_FOR_HIST
};

enum
{
	GET_HOME = 1,
	GET_TERM
};

/*
***		structs for line editing
*/

typedef struct			s_line_edit
{
	struct s_line_edit	*next;
	struct s_line_edit	*prev;
	int					x;
	int					y;
	int					is_orig;
	char				c;
	int					paired;
}						t_line;

typedef struct			s_le
{
	int					fd;
	int					w_sizex;
	int					w_sizey;
	int					pos_x;
	int					pos_y;
	int					sig;
	t_line				*line;
	char				*prompt;
}						t_le;

typedef struct			s_hist
{
	t_line				*old_line;
	int					len;
	struct s_hist		*next;
	struct s_hist		*prev;
}						t_hist;

typedef struct			s_word
{
	char				*word;
	struct s_word		*next;
}						t_word;

/*
***		structs for command execution and env
*/


typedef struct			s_env
{
	t_le				le;
	int					fd;
	struct termios		reset;
}						t_env;

int						env_sw(void);
int						get_fd(int fd);
t_env					*get_t_env(t_env *env);
char					*get_from_env(char **env, char *to_find);
int						init_term(void);
int						reset_term(struct termios reset);
void					init_env(t_le *e, t_env *env);
void					calc_col(t_le *e);
void					malloc_handling(void);
void					message_handling(void);
int						check_end_window(int winsize);
/*
***
***		LINE EDIT
***
*/
/*
***		line edit : display
*/
void					add_to_line_display(t_le *le, t_line **line);
void					delete_char_display(t_line **line, t_le *le);
void					redisplay_line(t_line *line, t_le *le);
int						redisplay_line_index(t_line *line, t_le *le);
/*
***		line edit : back
*/
t_line					*add_space_between_redir(t_line *line);
void					update_size(int sig);
void					restart_prompt(int sig);
void					stop_heredoc(int sig);
void					show_me_cursor(t_le *le);
t_line					*edit_line(t_le *le);
int						ft_is_arrow(char *buffer);
int						ft_is_del_or_back(char *buffer);
void					get_pos_cursor(int *x, int *y);
int						linelen(t_line *line);
char					*to_string(t_line *line, int space);
int						ft_putint(int c);
void					add_to_line(t_le *le, t_line **line, char n);
t_line					*get_last_line(t_line *line);
t_line					*get_first_line(t_line *line);
void					clipboard_to_line(t_le *le);
void					parse_buffer(char *buffer, t_le *le, int mode);
void					delete_char(t_le *le, t_line **line, char c);
/*
***		line edit : move
*/
void					move_to_first(t_le *le, t_line **line);
void					move_to_last(t_le *le, t_line **line);
void					move_left(t_le *le, t_line **line);
void					move_right(t_le *le, t_line **line);
void					move_to_word(int dir, t_le *le);
void					move_vertically(int dir, t_le *le);
void					move_to_extrem(int dir, t_le *le);
void					move_cursor(t_le *le, int dir, t_line **line, int mode);
/*
***		edit line : pairs, pipe, heredoc
*/
char					*missing_pair(t_line *line, int indquote);
void					edit_line_pairing(t_le *le, char *prompt);
t_line					*get_orig_line(t_line *line);
t_line					*edit_line_heredoc(t_le *le, char *end, int bsn);
void					write_here_in_file(t_word *tmp, char *in_heredoc);
void					prepare_heredoc(t_le *le, t_line *line);
t_word					*rdwr_in_heredocs(char *in_heredoc);
t_word					*clear_words(t_word **word, int *id);
t_word					*get_heredocs_add(void *ad);
void					ignore_heredoc(t_le *le, void *tmp);
int						end_is_not_in_line(t_le *le, char *end);
/*
***		history
*/
t_line					*history(int query, t_line *line);
void					*clear_hist(t_hist *hist);
t_hist					*generate_hist(t_line *cmd, t_hist *next, t_hist *prev);
t_line					*to_line(char *cmd);
t_line					*cpy_line(t_line *line);
void					clear_line(t_line *line);
int						get_hist_fd(void);
t_hist					*get_first_hist(t_hist *hist);
void					create_new_hist(t_hist **history, t_line *line);
t_line					*cut_line_for_hist(t_line *line);
/*
***		completion
*/
void					complete_word(t_line **line, t_le *le);

#endif
