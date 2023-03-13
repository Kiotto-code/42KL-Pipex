/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 23:00:15 by yichan            #+#    #+#             */
/*   Updated: 2023/03/14 02:36:22 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

// void	func(void)
// {
// 	char	buffer[39];

// 	snprintf(buffer, sizeof(buffer), "leaks -q %d >&2", getpid());
// 	system(buffer);
// }

int	main(int ac, char **av, char**envp)
{
	if (ac < 5)
		ft_error("Need More Argument", 1);
	pipex(ac, av, envp);
	return (0);
}
