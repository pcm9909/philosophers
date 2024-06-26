/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:14:56 by chunpark          #+#    #+#             */
/*   Updated: 2024/06/14 16:34:22 by chunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_resource	resource;

	if (argc == 5 || argc == 6)
	{
		if (validate_input(argv))
		{
			return (1);
		}
		if (preprocessing(argc, argv, &resource))
		{
			return (1);
		}
		if (create_and_run_philos(&resource))
		{
			return (1);
		}
		checker(&resource);
	}
	else
	{
		print_error(INPUT_ERR_3);
	}
	return (0);
}
