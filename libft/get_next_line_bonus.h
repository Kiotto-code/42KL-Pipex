/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 22:10:30 by yichan            #+#    #+#             */
/*   Updated: 2022/11/07 20:56:21 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

/* inside compile configuration */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char	*ft_strchr2(char *str, int c);
char	*ft_strjoin2(char *s1, char *s2);
size_t	ft_strlen2(char *str);
char	*get_next_line(int fd);
char	*joinfree(char *str1, char *str2);

#endif