/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 21:44:08 by merlich           #+#    #+#             */
/*   Updated: 2022/06/08 22:16:40 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		k;
	int		cmds_num;
	int		p1[2];
	int		p2[2];
	char	**cmd_line;
	int		m;
	static int	opend1 = 0;
	static int	opend2 = 0;

	i = 1;
	k = 1;
	cmds_num = ft_count_cmds(argv);
	printf("cmds_num = %d\n", cmds_num);
	if (cmds_num)
	{
		if (pipe(p1))
			ft_print_error_fatal();
		opend1 = 1;
		if (pipe(p2))
			ft_print_error_fatal();
		opend2 = 1;
		while (argv[i])
		{
			cmd_line = ft_build_cmd_line(argv, &i);
			if (!strcmp(cmd_line[0], "cd"))
				ft_cd(cmd_line);
			// if (pipe(p1))
			// 	ft_print_error_fatal();
			else
			{
				ft_exec_many_cmds(p1, p2, cmd_line, k, cmds_num, envp, opend1, opend2);
				k++;
				if (!strcmp(argv[i - 1], ";"))
				{
					cmds_num -= k;
					// printf("cmds_num = %d\n", cmds_num);
					k = 0;
				}
			}
			// m = 0;
			// while (cmd_line[m])
			// {
			// 	printf("cmd_line[%d] = %s\n", m, cmd_line[m]);
			// 	m++;
			// }
			free(cmd_line);
		}
		k = -1;
		// while (++k < cmds_num)
		// 	waitpid(-1, NULL, 0);
	}
	return (0);
}
