/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:45:14 by yguaye            #+#    #+#             */
/*   Updated: 2017/12/09 12:05:21 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
#include <stdlib.h>

int		main(int argc, char **argv)
{
	int		i;
	int		fds[argc - 1][2];
	int		c;
	char	*line;

	if (argc-- > 1)
	{
		i = 0;
		++argv;
		while (i < argc)
		{
			fds[i][1] = 1;
			if(!(fds[i][0] = open(argv[i], O_RDONLY)))
				printf("Could not open file %s for reading!\n", argv[i]);
			else
				printf("Opening file %s for reading...\n", argv[i]);
			++i;
		}
		c = 0;
		int out = open("result.log", O_WRONLY | O_CREAT, 0640);
		while (c < argc)
		{
			i = -1;
			while (++i < argc)
			{
				if ((fds[i][1] = get_next_line(fds[i][0], &line)) == 1)
				{
					if (argc > 1)
						printf("[%s]: ", argv[i]);
					printf("%s\n", line);
					dprintf(out, "%s\n", line);
					free(line);
				}
				if (fds[i][1] != 1)
					++c;
			}
		}
		close(out);
		i = -1;
		while (++i < argc)
		{
			close(fds[i][0]);
			printf("fds[%d][1]: %d\n", i, fds[i][1]);
		}
	}
	return (0);
}
