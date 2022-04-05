/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "struct.h"

int		ft_strlen(const char *str);
int		ft_strncmp(char const *s1, char const *s2, int n);

char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s1, size_t n);
char	*strdup_len(const char *s, int i, int j);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnjoin(char const *s1, char const *s2, size_t n);
char	*ft_strjoinn(char const *s1, char const *s2, size_t n);

void	*ft_calloc(int nb, int size);
void	ft_memdel(void **ap);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);


#endif
