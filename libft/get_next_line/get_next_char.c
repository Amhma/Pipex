/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:51:34 by amahla            #+#    #+#             */
/*   Updated: 2022/05/09 14:25:01 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

char	*get_next_line(int fd)
{
	int		rd;
	char	*buffer;
	char	*dst;
	int		i;

	rd = 1;
	i = 0;
	dst = NULL;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = calloc_gnc((BUFFER_SIZE + 1), sizeof(char));
	while (buffer && rd > 0 && *(buffer + i) != '\n')
	{
		rd = read(fd, buffer + i, 1);
		if ((i + 1 == BUFFER_SIZE || *(buffer + i) == '\n' || rd == 0)
			&& ft_strlen_gnc(buffer) > 0)
			dst = ft_strjoin_gnc(dst, buffer, &i);
		else
			i++;
	}
	if (buffer)
		free(buffer);
	return (dst);
}
