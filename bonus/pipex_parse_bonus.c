/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parse_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:11:18 by amahla            #+#    #+#             */
/*   Updated: 2022/05/25 12:31:49 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_heredoc(char *line)
{
	perror("write ");
	free(line);
	exit(EXIT_FAILURE);
}

void	clear_all(t_list **cmd, int	*fd_file, char *file_out)
{
	if (file_out)
		unlink(file_out);
	close(fd_file[0]);
	close(fd_file[1]);
	ft_lstclear(cmd, &free_array);
	exit(EXIT_FAILURE);
}

int	open_heredoc(char *limiter)
{
	int		fd;
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
		return (-1);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(line) == ft_strlen(limiter) + 1
			&& line[ft_strlen(line) - 1] == '\n')
			break ;
		if (write(fds[1], line, ft_strlen(line)) == -1)
			error_heredoc(line);
		free(line);
	}
	free(line);
	close(fds[1]);
	fd = dup(fds[0]);
	close(fds[0]);
	return (fd);
}

void	open_file(int ac, char **av, int *fd_in, int *fd_out)
{
	if (ft_strcmp(av[1], "here_doc") != 0)
		*fd_in = open(av[1], O_RDONLY, 0644);
	else
		*fd_in = open_heredoc(av[2]);
	if (*fd_in == -1)
	{
		perror("error ");
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(av[1], "here_doc") != 0)
		*fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		*fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
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
	if (ft_strcmp(av[1], "here_doc") == 0)
		i++;
	open_file(ac, av, fd_file, fd_file + 1);
	while (i < ac - 1)
	{
		if ((ft_strcmp(av[1], "here_doc") == 0 && i == 3) || i == 2)
			ft_lstadd_back(cmd, ft_lstnew(ft_split(av[i], ' ')));
		else if (i == ac - 2)
			ft_lstadd_back(cmd, ft_lstnew(ft_split(av[i], ' ')));
		else
			ft_lstadd_back(cmd, ft_lstnew(ft_split(av[i], ' ')));
		if (ft_lstsize(*cmd) != y++)
			clear_all(cmd, fd_file, NULL);
		i++;
	}
}
