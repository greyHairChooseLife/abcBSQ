/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_keyboard_input_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangykim <sangykim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 02:17:37 by sangykim          #+#    #+#             */
/*   Updated: 2021/04/14 02:25:18 by sangykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*malloc_for_keyboard(char *map_keyboard, int *i);
int		get_3_simbols(int i, char *map_keyboard);
void	get_col_size(char *map_keyboard);
int		read_keyboard(char *map_keyboard);

char	*malloc_for_keyboard(char *map_keyboard, int *i)
{
	if (!(map_keyboard = (char *)malloc(sizeof(char) * 50000)))
		printf("malloc fail_Error\n");
	read(0, map_keyboard, 50000);
	*i = get_3_simbols(*i, map_keyboard);
	return (map_keyboard);
}

int		get_3_simbols(int i, char *map_keyboard)
{
	i = 0;
	while (map_keyboard[i] != '\n')
		i++;
	g_empty_char = map_keyboard[i - 3];
	g_obstacle_char = map_keyboard[i - 2];
	g_full_char = map_keyboard[i - 1];
	return (i);
}

void	get_col_size(char *m_kbd)
{
	int i;
	int temp;

	i = 0;
	temp = 0;
	while (map_keybd[i] != g_empty_char)
	{
		if (m_kbd[i] != g_empty_char && '0' <= m_kbd[i] && m_kbd[i] <= '9')
			temp = temp * 10 + m_kbd[i] - '0';
		else
			break ;
		i++;
	}
	g_col_size = temp;
}

int		read_keyboard(char *map_keyboard)
{
	int i;
	int temp;
	int temp2;

	i = 0;
	while (i < g_col_size)
	{
		temp = read(0, map_keyboard, 50000);
		map_keyboard += temp;
		i++;
		if (i == 1)
			temp2 = temp;
		if (i >= 2 && temp2 != temp)
		{
			write(2, "Map Error_diff_length\n", 22);
			return (1);
		}
		if (temp == 1)
		{
			write(2, "Map Error_empty_map\n", 20);
			return (1);
		}
	}
	g_row_size = temp - 1;
	return (temp);
}
