/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_char_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:51:49 by amahla            #+#    #+#             */
/*   Updated: 2022/05/09 14:24:50 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

int	ft_strlen_gnc(char const *str)
{
	int	i;

	i = 0;
	while (str && *(str + i))
		i++;
	return (i);
}

void	ft_bzero_gnc(char *str)
{
	int	i;

	i = 0;
	while (str && *(str + i))
		*(str + i++) = '\0';
}

void	*calloc_gnc(size_t count, size_t size)
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

char	*ft_strjoin_gnc(char *s1, char *s2, int *y)
{
	char	*dst;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	dst = calloc_gnc((ft_strlen_gnc(s1) + ft_strlen_gnc(s2) + 1), sizeof(char));
	if (!dst)
		return (NULL);
	while (s1 && *(s1 + j))
		*(dst + i++) = *(s1 + j++);
	j = 0;
	while (s2 && *(s2 + j) && *(s2 + j) != '\n')
		*(dst + i++) = *(s2 + j++);
	if (*(s2 + j) == '\n')
		*(dst + i) = *(s2 + j);
	if (s1)
		free(s1);
	if (*(s2 + *y) != '\n')
	{
		*y = 0;
		ft_bzero_gnc(s2);
	}
	return (dst);
}
