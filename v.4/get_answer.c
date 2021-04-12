/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 17:37:04 by jimikim           #+#    #+#             */
/*   Updated: 2021/04/13 03:58:24 by sangykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int ft_min(int a, int b, int c) //셋중에 젤 작은거 찾아서 반환
{
	return ( (a < b && a < c) ? a : (b < c) ? b : c );
}

int main()
{
	char map[5][5] = {
					{'o', '.', '.', '.'},
					{'.', '.', '.', '.'},
					{'.', '.', '.', '.'},
					{'o', 'o', '.', 'o'}
	};
	int result[5][5];
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			write(1, &map[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	
	
	printf("map print end------------- \n");
	
	
	i = 0;
	j = 0;
	while (i < 5)  // 1행과 1열을 장애물인지 아닌지에 따라 0과 1로 나눈다. 장애물이면 0, 그게 아니면 1로 채우는게 인상적
	{              // 근데 이렇게하면 행과 열의 길이가 서로 다를 때 작동안되지
		if (map[0][i] == 'o')
			result[0][i] = 0;
		else
			result[0][i] = 1;
		if (map[i][0] == 'o')
			result[i][0] = 0;
		else
			result[i][0] = 1;
		i++;
	}
	i = 1;
	j = 1;
	while (i < 5)
	{
		j = 1;
		while (j < 5)
		{
			if (map[i][j] == 'o')
			{
				result[i][j] = 0;
			}
			else
				result[i][j] = 1;
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			printf("%d ", result[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	
	printf("default result map set end---------------\n");
	
	i = 1;
	j = 1;
	while (i < 5)
	{
		j = 1;
		while (j < 5)
		{
			if (map[i][j] != 'o')
				result[i][j] = ft_min(result[i][j - 1], result[i - 1][j], result[i - 1][j - 1]) + 1;
			else
				result[i][j] = 0;
			j++;
		}
		i++;
	}
	
	
	printf("\nresult set end-----------------\n");
	
	
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			printf("%d ", result[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	
	printf("\n last number result set end---------------\n");
	
	i = 0;
	j = 0;
	int max = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			max = (max < result[i][j] ? result[i][j] : max);
			j++;
		}
		i++;
	}
	
	printf("\n larget number : %d --------------------------\n", max);
	
	i = 0;
	j = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			if (result[i][j] == max)
				break;
			j++;
		}
		if (result[i][j] == max)
			break;
		i++;
	}
	
	printf("\nlarget number first index i : %d / j %d / result[i][j] : %d------------\n", i, j, result[i][j]);
	int start_i = i;
	int start_j = j;
	
	i = 0;
	j = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			if (result[i][j] == max && !(i == start_i && j == start_j))
			{
				result[i][j] = 1;
			}
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	while (i < max)
	{
		j = 0;
		while (j < max)
		{
			result[start_i - i][start_j - j] = max;
			j++;
		}
		i++;
	}
	
	i = 0;
	j = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			printf("%d ", result[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	i = 0;
	j = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			if (result[i][j] == 0)
				write(1, "o", 1);
			else if (result[i][j] == max)
				write(1, "x", 1);
			else
				write(1, ".", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
