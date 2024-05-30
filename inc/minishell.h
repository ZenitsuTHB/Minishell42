/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:22:28 by deordone          #+#    #+#             */
/*   Updated: 2024/05/30 18:40:34 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../library/dprintf/ft_dprintf.h"
#include "../library/libft/libft.h"
#include "macros.h"
#include "struct.h"
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include "../library/readline/readline.h"
#include "../library/readline/history.h"
// # include <editline/readline.h>

/*
┏━━━━━━━━・▼・━━━━━━━━┓
                LEXER - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/

void	restore_terminal_settings(void);
void	disable_control_chars_echo(void);

extern  sig_atomic_t volatile g_signals;
void	ft_signals(t_shell *sh, t_signal mode);

t_token *generate_tokens(char *line);
int ft_deltoken(t_token **lst);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
                NEW_LEXER - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/

int len_matriz(char *line);
int lex_redir_case(char *s, char redir);
int lex_word_case(char *s);
int lex_quotes_case(char *s, char quote);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
        LEXER_AUX - 4
┗━━━━━━━━・▼・━━━━━━━━┛
*/

char **montage_tokens(char *line);
char *add_between(char *s, char btween);
int cont_meta(char *s);
void token_type(t_token *lst);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
        LEXER_AUX2 - 3
┗━━━━━━━━・▼・━━━━━━━━┛
*/

void redifine_token(t_token *tok);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
                PARSER - 3
┗━━━━━━━━・▼・━━━━━━━━┛
*/
void	find_path(t_words *word);
int parse_all(t_shell *sh);
int parse_input(t_shell *sh);
int parse_redirections(t_shell *sh);
void parse_words(t_shell *sh);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
        WORD_LST - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/

int ft_del_words(t_words **lst);
t_words *generate_words(t_token *tokens);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
        REDIR_LST - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/

int ft_del_redirs(t_redir **lst);
t_redir *generate_redirs(t_token *tokens);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
        EXPANSOR - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/

void expansor(t_shell *sh);
char **split_quotes(char *str);
char *expand_data(t_shell *sh, char *str);
char *expand_string(t_shell *sh, char *str);
char *expansion_final(t_shell *sh, char *str);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
 EXPANSOR_UTILS 1 - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/

char	*aux_trim(char *data);
char **split_env_var(char *str);
char *find_env_part(char *str, int *pos);
char *special_cases(char *special, int exit_status);
char *is_special_dollar(char *data, int num_dollar, int i);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
 EXPANSOR_UTILS 2 - 4
┗━━━━━━━━・▼・━━━━━━━━┛
*/

int count_len(char *str);
int get_len_string(char *str);
int count_len_env_part(char *str);
int count_words(char *str, int count, int is_sq, int is_dq);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
 ExPANSOR_UTILS 3 - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/
char *join_split(char **split);
int found_char(char *data, char c);
char *ft_get_cpy(char *str, int *pos);
char *trimmer_quotes(char *str, int quotes);
int number_of_char(char *str, char charact);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
   PARSER BLOCK - 5
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

void montage_redirections(t_token *tok, t_redir *redir);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
    PARSER CMD - 3
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

t_token *fill_block(t_words **cmd, t_token *token);
t_token *fill_cmd(t_words **cmd, t_token *token);
char *add_space(char *info);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
    PARSER INPUT - 4
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

int syntax_error(t_token *tok);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
    PARSER ENTRY - 4
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

int input_unclosed(t_shell *sh);
void unclosed_entry(t_shell *sh);
int input_incomplete(t_shell *sh);
void incomplete_entry(t_shell *sh);
/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
      MANAGE  - 4
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

int after_exec(t_words *word);
void soft_exit(t_shell *sh);
void hard_exit(t_shell *sh);
void ft_free_array(char **res);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
                EXECUTOR - 5
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

void executor(t_shell *sh);
char	*prompt(int exit_status);
// void execute_cmd(t_block *block);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
                EXEC REDIR  - 5
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

void process_redir(t_shell *sh, t_process *pro);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
                EXEC CMDS  - 5
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

char *ft_check_path(char **paths, char **cmd);
int process_word(t_shell *sh);

/*
┏━━━━━━━━・▼ ・━━━━━━━━┓
        EXEC CONEC  - 5
┗━━━━━━━━・▼ ・━━━━━━━━┛
*/

int process_connector(t_shell *sh, int process);

int manage_signals(t_shell *sh, t_signal mode);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
                AUX ARCH- 7
┗━━━━━━━━・▼・━━━━━━━━┛
*/

int ft_del_env(t_env **lst);
int ft_lstenv_size(t_env *lst);
int is_correct_name(char *name);
void print_lst_env(t_env *lst, int i);
t_token	*quotes_removal(t_token *tokens);
char	*quotes_removal_master(char *cmd_line);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
                AUX DEI - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/
void print_tokens(t_token *lst); // test
void print_words(t_words *lst);  // test
void print_redir(t_redir *lst);  // test
char *ft_imp_strjoin(char const *s1, char const *s2);
char *char2str(char c);
int stock_of(t_shell *sh, int type);
int char_is_inside(const char *str, char c);
char **get_envivar(char *var, char **env);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
        IS SOMETHING - 5
┗━━━━━━━━・▼・━━━━━━━━┛
*/

int is_builtin(char *data);
int is_meta(int type);
int is_charmeta(char c);
int is_redir(int type);
int is_char_redir(char c);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
                ENV
┗━━━━━━━━・▼・━━━━━━━━┛
*/

int ft_del_env(t_env **lst);
t_env *create_envnode(char *envp);
t_env *create_lst_env(char **envp);
char **convert_env_dchar(t_env *lst_env, char **env);
t_env *exporting_var(t_shell sh, t_env **lst_env, t_env *new);

/*
┏━━━━━━━━・▼・━━━━━━━━┓
        BUILTINS
┗━━━━━━━━・▼・━━━━━━━━┛
*/
int token_size(t_token *tokens);
int execute_pwd(void);
void free_matrix(char **sh);
void printlst(t_token *lst);
int ft_del_env(t_env **lst);
int execute_exit(t_shell *sh);
void execute_echo(t_shell *shell);
int check_exp_variable(t_env *tok);
void print_lst_env(t_env *lst, int i);
t_env *found_var(char *var, t_env *lst);
int execute_cd(t_shell *sh, char *path, char **env);
void execute_env(t_shell *sh, char **env);
void execute_export(t_shell *sh, char **env);
int execute_builtins(t_shell *looking, char **env);
void execute_unset(t_shell **sh, t_env *node, char **env);

#endif
