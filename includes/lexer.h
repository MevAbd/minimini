/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "struct.h"

int		is_pipe(char c);
int		is_space(char c);
int		is_redir(char c);
int		is_simple_quote(char c);
int		is_double_quote(char c);
int		line_simple(const char *s, int i, int j);
int		line_double(const char *s, int i, int j);
int		line_pipe(const char *s, int i, t_lexer **lexer);
int		line_redir(const char *s, int i, t_lexer **lexer);
int		line_word(const char *s, int i, int j, t_lexer **lexer);

void	free_lexer(t_lexer **lexer);
void	addback_lexer(t_lexer **alst, t_lexer *add);

t_lexer	*cut_line(const char *str);
t_lexer	*new_lexer(char *s, t_type type);

#endif
