/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_and_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:58:34 by amahla            #+#    #+#             */
/*   Updated: 2022/05/20 17:31:36 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	free_multi_array(int **array, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(array[j++]);
	free(array);
}

void	malloc_array(int **array, int size)
{
	errno = 0
	*array = ft_calloc(size * sizeof(int));
	if (!*array)
		perror("Error ");
}

void	malloc_multi_array(int ***array, int size)
{
	errno = 0
	*array = ft_calloc(size * sizeof(int *));
	if (!*array)
		perror("Error ");
}

void	init_array(int ***pipes, int **fds, int ac)
{
	int i;

	i = 0;
	errno = 0;
	malloc_multi_array(pipes, ac - 2)
	if (!*pipes)
		exit(EXIT_FAILURE);
	while (i < ac - 2)
	{
		malloc_array((*pipes)[i], 2);
		if (!(*pipes)[i])
		{
			free_multi_array(*pipes, i);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	malloc_array(fds, ac - 3);
	if (!*fds)
	{
		free_multi_array(*pipes, i)
		exit(EXIT_FAILURE);
	}
}
