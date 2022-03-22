/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosu <ehosu@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 21:20:04 by ehosu             #+#    #+#             */
/*   Updated: 2022/03/22 12:12:23 by ehosu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../phil.h"

t_bool	number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' && str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	phil_atoi(const char *str)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + str[i] - '0';
		i++;
	}
	return (res);
}

t_bool	config_data(t_config *config, char **argv)
{
	if (!number(argv[1]) || !number(argv[2]) || !number(argv[3]) || \
		!number(argv[4]) || !number(argv[4]))
		return (false);
	if (argv[5])
	{
		if (number(argv[5]))
			config->times_to_eat = phil_atoi(argv[5]);
		else
			return (false);
	}
	else
		config->times_to_eat = 0;
	config->n_philo = phil_atoi(argv[1]);
	if (config->n_philo == 0)
		return (false);
	config->time_to_die = phil_atoi(argv[2]);
	config->time_to_eat = phil_atoi(argv[3]);
	config->time_to_sleep = phil_atoi(argv[4]);
	return (true);
}
