/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_keyboard_input_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangykim <sangykim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 02:18:57 by sangykim          #+#    #+#             */
/*   Updated: 2021/04/14 02:25:25 by sangykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		check_exceptions_argc_1(char *map_keyboard, int i);
int		check_exceptions_argc_2(int i, char *map_keyboard);

int		check_exceptions_argc_1(char *map_keyboard, int i)
{
	if (i < 4 || g_empty_char < 32 || g_obstacle_char < 32 || g_full_char < 32)
	{
		write(2, "Map Error_not_enough_simbol\n", 29);
		return (1);
	}
	if (map_keyboard[i - 4] > 57 || map_keyboard[i - 4] < 48)
	{
		write(2, "Map Error_too_much_simbol\n", 26);
		return (1);
	}
	return (0);
}

int		check_exceptions_argc_2(int i, char *m)
{
	i = 0;
	while (m[i] != '\n')
		i++;
	while (m[i] != '\0')
	{
		if (m[i] != g_empty_char && m[i] != g_obstacle_char && m[i] != '\n')
		{
			write(2, "Map Error_diff_simbol_on_the_map\n", 33);
			return (1);
		}
		i++;
	}
	if (g_empty_char == g_obstacle_char || g_empty_char == g_full_char)
	{
		write(2, "Map Error_same_simbol\n", 22);
		return (1);
	}
	if (g_obstacle_char == g_full_char)
	{
		write(2, "Map Error_same_simbol\n", 22);
		return (1);
	}
	return (0);
}
