/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:55:47 by amahla            #+#    #+#             */
/*   Updated: 2022/05/07 20:38:21 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

int	ft_strchr_nl(char *str)
{
	while (str && *str)
	{
		if (*str++ == '\n')
			return (1);
	}
	return (0);
}

int	ft_strlen_gnl(char const *str)
{
	int	i;

	i = 0;
	while (str && *(str + i))
		i++;
	return (i);
}

void	*calloc_gnl(size_t count, size_t size)
{
	void	*dst;
	size_t	i;

	i = 0;
	dst = malloc(count * size);
	if (!dst)
		return (NULL);
	while (i < count * size)
		*((unsigned char *)dst + i++) = 0;
	return (dst);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*dst;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	dst = malloc(((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1)) * sizeof(char));
	if (!dst)
		return (NULL);
	while (s1 && *(s1 + j))
		*(dst + i++) = *(s1 + j++);
	j = 0;
	while (s2 && *(s2 + j))
	{
		*(dst + i++) = *(s2 + j++);
		*(s2 + j - 1) = '\0';
	}
	*(dst + i) = '\0';
	if (s1)
		free(s1);
	return (dst);
}
