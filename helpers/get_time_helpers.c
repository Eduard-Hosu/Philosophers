/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosu <ehosu@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:41:35 by ehosu             #+#    #+#             */
/*   Updated: 2022/03/22 11:56:33 by ehosu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../phil.h"

int	get_times_eaten(t_phil *phil)
{
	int	eaten;

	pthread_mutex_lock(&phil->config->m_gameover);
	eaten = phil->t_eaten;
	pthread_mutex_unlock(&phil->config->m_gameover);
	return (eaten);
}

long	get_death_time(t_phil *phil)
{
	long	death_time;

	pthread_mutex_lock(&phil->config->m_gameover);
	death_time = phil->die;
	pthread_mutex_unlock(&phil->config->m_gameover);
	return (death_time);
}
