/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"

# define SPLQT 39
# define DBLQT 34
# define DOL 36

char			*add_str(char *s1, char *s2);
char			*replace_dol(const char *s, t_cmd *env);
char			*replace(const char *s, t_cmd *env, int *i, int j);
char			*remove_quote(const char *s, int *i, int j, t_cmd *env);
int             find_next_given_char_index(char const *s, int i, char c);
char	        **quote_spliter(char *s);

void			test_quote(int i, int j, char *s);
void			free_cmd(t_cmd **cmd);
void			free_redir(t_redir **redir);
void			word_checker(t_lexer **lexer, t_cmd *env);
void			free_parser(t_parser **parser);
void			parsing(const char *s, t_msh **msh);
void			addback_cmd(t_cmd **cmd, t_cmd *add);
void			addback_redir(t_redir **redir, t_redir *add);
void			addback_pars(t_parser **parser, t_parser *add);
void			parsing_redir(t_parser **parser, t_lexer **lexer);
void			parsing_pipe(t_parser **parser, t_lexer **lexer);


t_cmd			*fill_env(char **envp);
t_cmd			*new_cmd(t_lexer *lexer);
t_redir			*new_redir(t_lexer *lexer);
t_redir			*newredirword(t_lexer *lexer);

t_parser		*new_pars(void);

#endif
