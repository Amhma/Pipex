/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:23:05 by amahla            #+#    #+#             */
/*   Updated: 2022/05/20 17:32:08 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	pipex(int ac, char **av, char **envp)
{
	int	**pipes;
	int	*fds;

	init_array(&pipes, &fds, ac);


int	main(int ac, char **av, char **envp)
{
	if (ac >= 4)
		pipex(ac, av, envp);
	else
		ft_pudendl_fd("Wrong number of arguments\nPlease retry...", 2);
	exit(EXIT_SUCCESS);
}
