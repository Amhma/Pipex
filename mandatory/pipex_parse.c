/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:11:18 by amahla            #+#    #+#             */
/*   Updated: 2022/05/24 17:22:41 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clear_all(t_list **cmd, int	*fd_file, char *file_out)
{
	if (file_out)
		unlink(file_out);
	close(fd_file[0]);
	close(fd_file[1]);
	ft_lstclear(cmd, &free_array);
	exit(EXIT_FAILURE);
}

void	open_file(int ac, char **av, int *fd_in, int *fd_out)
{
	*fd_in = open(av[1], O_RDONLY, 0644);
	if (*fd_in == -1)
	{
		perror("error ");
		exit(EXIT_FAILURE);
	}
	*fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fd_out == -1)
	{
		close(*fd_in);
		perror("open ");
		exit(EXIT_FAILURE);
	}
}

void	parse(int ac, char **av, t_list **cmd, int *fd_file)
{
	int	i;
	int	y;

	i = 2;
	y = 1;
	open_file(ac, av, fd_file, fd_file + 1);
	while (i < ac - 1)
	{
		if (i == ac - 2)
			ft_lstadd_back(cmd, ft_lstnew(ft_split(av[i], ' '), 0, fd_file[1]));
		else
			ft_lstadd_back(cmd, ft_lstnew(ft_split(av[i], ' '), 0, 0));
		if (ft_lstsize(*cmd) != y++)
			clear_all(cmd, fd_file, NULL);
		i++;
	}
}
