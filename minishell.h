/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:45:09 by osarsar           #+#    #+#             */
/*   Updated: 2023/05/06 08:15:12 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdio.h>
#include <unistd.h>
# include <string.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include <dirent.h>
# include <signal.h>
# include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/wait.h>

// #define malloc(sizeof) 0

typedef struct s_env
{
	char 			*value;
	char 			*key;
	char			*line;
	struct s_env	*next;
}t_env;

typedef struct s_cmd
{
	int		ac;
	char	**av;
	char	**env;
	char	**cmd;
	int		fd[2];
	char	*input;
	char	*join;
	int		fd_in;
	int		fd_out;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef enum e_token
{
	PIPE,
	IN,
	OUT,
	HEREDOC,
	APPEND,
	WORD,
	DLR,
	SPC,
	SQU,
	DQU,
	FILENAME,
}	t_token;

typedef struct s_lexer
{
	char			*cmd;
	t_token			token;
	int				fd;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_glb
{
	int		exit_status;
	int		dqu;
	int		sg;
	int		opn_fls;
	t_env	*env;
}	t_glb;

typedef struct s_garbage t_garbage;

struct s_garbage
{
	void				*ptr;
	int					is_freed;
	t_garbage	*next;
};

extern	t_glb g_glb;
//=========================================================//
// int		ft_atoi(char *str);
t_cmd	*ft_lstnew_1(void *content, t_cmd *data);
int		ft_isspace(char *input);
void	ft_lstadd_back_1(t_cmd **lst, t_cmd *new);
t_env	*ft_lstnew_2(void *content, void *key, void *value);
void	ft_lstadd_back_2(t_env **lst, t_env *new);
int		ft_isalpha(int c);
void	echo_cmd(t_cmd **data);
void	cd_cmd(t_cmd **data);
void	env_cmd(void);
void	export_cmd(t_cmd *data);
void	pwd_cmd(void);
int		check_key(char *key);
int		check_error(char *key, t_cmd *head);
void	unset_cmd(t_cmd *data);
void	echo_utils(t_cmd **data, int *i, int *j);
void	add_pwd(void);
int		cd_1(void);
int		cd_2(void);
int		unset_parsing(char *str);
int		is_builting(t_cmd *data);
//=============================================>>>>>>>>>>>>>>>>>>>>
t_env   *duplicate_env(void);
char	**env_to_char(void);
void	affect_value(t_cmd *head, t_env	*headexp, char *value, int i);
char	*ft_value(char *str);
char	*ft_strchr(const char *s, int c);
char	*find_path(void);
int		ft_execve_valid_path(t_cmd *data);
void	ft_execve(t_cmd *data);
void	*ft_calloc(size_t count, size_t size);
t_env	*variable_environnement(char **env);
int		keycmp(t_cmd *head, char *key, char *value);
int		add_key(t_cmd *data, char *key, char *value, int i);
int		keycmp_continue(t_cmd *head, char *key, char *value, int i);
t_env	*lstcmp(void);
void	exec_cmd(t_cmd *data);
void	execution(t_cmd **cmd);
int		redirection(t_cmd *data);
void	ft_process(t_cmd *data, int fd[2]);
/*************************************************/
t_token	which_token(char c1, char c2);
void	ft_lstclear_garbage(t_garbage **lst);
void	ft_lstadd_back_garbage(t_garbage **lst, t_garbage *new);
void	ft_change_dlr_word(t_lexer **head);
t_garbage	*ft_lstnew_garbage(void *ptr);
void	ft_signal(void);
void	ft_putstr_fd(int fd, char *s);
void	redirections(t_lexer **head, t_cmd **cmd, int fd_in_herdc);
void	ft_delete_node(t_lexer **head, t_lexer *node);
char	*ft_itoa(int n);
void	concat_dqu_squ_word(t_lexer *tmp, t_lexer *current);
void	split_cmd(t_lexer **tmp, int i, t_lexer *hold, char ***cmnd);
int		ft_nbr_cmd(t_lexer *tmp);
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void	ft_lstclear_cmd(t_cmd **lst);
t_cmd	*ft_lstnew_cmd(char **cmd);
void	ft_concat_word_dqu_squ(t_lexer **head);
void	print_cmd_linked_list(t_cmd** head);
void	ft_file_redirect(t_lexer **head);
void	assign_fd(t_lexer **tmp, int *fd_in, int *fd_out, int fd_herdc);
void	sig_handl(int sig);
char	*ft_split_concat_dqu_dlr(int i, char *wrd_expd, t_env **env_list);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *key, char *value);
void	ft_lstclear_env(t_env **lst);
void	ft_check_expand_in_line(char **line, t_env **env_list);
t_lexer	*ft_lstnew_lex(char *cmd, t_token token);
void	ft_lstclear_lex(t_lexer **lst);
int		lstsize();
char	**ft_split(char const *s, char c);
void	empty_string(t_lexer **l, t_lexer *hold, t_token tok);
void	ft_lstadd_back_lex(t_lexer **lst, t_lexer *new);
int	 ft_check_quotes(t_lexer **l, t_token tok);
int 	char_in_set(char *set, char c);
t_cmd	*parsing(char *input, char **env);
void	ft_lexer(char *input, t_lexer **head);
int 	ft_strlen(char *str);
void	env_to_map(char **env, t_env **env_list);
void 	concat_words(t_lexer *tmp, t_lexer *current);
char	*ft_strtrim(char *s1, char *set);
char	*concat_var(char *wrd_expd, int i, int j, t_env **env_list, char *var);
char	*ft_substr(char *s, int start, int len);
void	ft_open_files(t_lexer **temp);
char	*ft_strjoin(char *s1, char *s2);
int	 ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(char *source);
t_garbage	*get_garbage_collector(void);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	check_heredoc_delimiter(t_lexer *tmp, t_lexer *hold);
void	concat_word_lexer(t_lexer **l);
void	check_redirect_open(t_lexer **tmp, t_lexer *hold, int *fd);
void	look_for_dlr(t_lexer *tmp, t_env **env_list);
void	delete_spc(t_lexer **head, t_lexer *temp);
void	ft_check_env(t_lexer **head, t_lexer *dlr_ptr, t_env **env_list);
int		ft_syntax_error(t_lexer *tmp);
void	delete_quotes(t_lexer **head);
t_lexer	*find_matching_quote(t_lexer *start, t_token tok);
void	delete_consctv_spaces(t_lexer **head);
void	ft_expand(t_lexer **head, char **env, t_env **env_list);
char	*ft_env_var(char *var, t_env **env_list);
void	tokenize_redirections(t_lexer **head);
int		is_identifier(char c);
void	ft_putstring_fd(int fd, char *s1, char *s2);
int		ft_isalnum(char c);
int		handle_dqu(t_lexer *temp, t_lexer *hold, t_token tok);
t_lexer	*ft_heredoc_delimiter(t_lexer **head);
t_lexer	*find_delimiter(t_lexer **head);
void	free_memo(t_lexer **l, t_env **list_env);
void	*ft_malloc(size_t size);
int 	ft_heredoc(t_lexer **head, char **env, t_env **env_list);
void	concat_between_qu(t_lexer *start, t_lexer *end, t_token tok);
void	ft_free(void *ptr);

#endif