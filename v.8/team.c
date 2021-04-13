#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

# define BUF_SIZE 32768

#include <stdio.h>

char g_full_char;
char g_empty_char;
char g_obstacle_char;
int g_row_size;
int g_col_size;

int ft_mv_nextline(int fd, int size)
{
	char *line;
	int i;
	
	i = 0;
	if (!(line = (char *)malloc((size + 1) * sizeof(char))))
	{
		write(2, "MAP ERROR\n", 10); 							// malloc 실패 에러메시지로 수정
		return (0);
	}
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break ;
		i++;
	}
	free(line);
	return (1);													// return 값의 쓰임새  찾아보기
}

void ft_count_row_size(int fd)
{
	char c;
	int i;
	
	i = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			break ;
		i++;
	}
	g_row_size = i;
}

int ft_set_charset(char *file, int size)
{
	char *line;
	int i;
	int fd;
	int result;
	
	i = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		write(2, "MAP ERROR\n", 10); 			//  2번째 파일오픈 에러체크 중복됨,   
		return (0);
	}
	if (!(line = malloc((size + 1) * sizeof(char))))
	{
		write(2, "MAP ERROR\n", 10);			//   malloc에러인데 맵 에러 메시지  
		return (0);
	}
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break ;
		i++;
	}
	g_empty_char = line[i - 3];
	g_obstacle_char = line[i - 2];
	g_full_char = line[i - 1];
	i = 0;
	result = 0;
	while (line[i])
	{
		if (line[i] != g_empty_char && '0' <= line[i] && line[i] <= '9')
		{
			result *= 10; 									// result = result * 10 + line[i] - '0';
			result += line[i] - '0';
		}
		else
			break ;
		i++;
	}
	g_col_size = result;
	ft_count_row_size(fd);
	close(fd);
	return (line[i] == g_empty_char ? 1 : 0);      			// 반대로 아닌가   왜 잘 작동하는거지
}

int ft_count_file_size(char *file)
{
	char c;
	int i;
	int fd;
	int size;
	
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		write(2, "Error\n", 6);            // 첫번째 파일 오픈 에러체크,  에러메시지 구체적으로
		return (0);
	}
	size = 0;
	while (read(fd, &c, 1))
		size++;
	close(fd);
	return (size);
}

// 
//
//
//      여기부터 수정한다. 표준입력 받은것을 ft_set_input_map()에 인자로 줄것
//
//
//
//


//char **ft_set_input_map
char *ft_push_array(int fd, int size)
{
	char *array;
	int i;
	
	if (!(array = malloc((g_row_size + 1) * sizeof(char))))
		return (0);														// malloc 실패 에러같은데 0으로 리턴하는 이유가 어떤것인가요
	i = 0;																// map[?] 에 0이 들어가게 된다. 
	while (read(fd, &array[i], 1))
	{
		if (array[i] == '\n')
		{
			array[i] = 0;											// 개행 제외하고 모두 0을 넣어준다.
			break ;
		}
		i++;
	}
	return (array);
}

char *ft_push_array_keyboard(char *keyboard_array, int *i)
{
	if (*i == 0)
		return (keyboard_array);
	keyboard_array += *i * g_row_size;
	while (*keyboard_array != '\0')
	{
		if (*keyboard_array == '\n')
		{
			*keyboard_array = 0;
			break ;
		}
		keyboard_array++;
	}
	keyboard_array++;
	printf("\n   			now :  %c\n", *keyboard_array);
	return (keyboard_array);
}

char **ft_set_input_map(char *file, int size, char *keyboard_array)
{
	int fd;
	int i;
	char **map;
	
	map = NULL;
	i = 0;
	if (!(map = (char **)malloc((g_col_size + 1) * sizeof(char *))))   		
		return (0);

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		while (i < g_col_size)
			map[i++] = ft_push_array_keyboard(keyboard_array, &i);
	
		return (map);
	}

	ft_mv_nextline(fd, size);
	while (i < g_col_size)
		map[i++] = ft_push_array(fd, size);
	close(fd);
	return (map);												
}	



// 
//
//
//       여기까지 수정됨. 
//
//
//
//


char **ft_valid_argv(char *file)
{
	int file_size;
	int col_size;
	char **map;
	char *void_;
	
	file_size = ft_count_file_size(file);
	if (!(col_size = ft_set_charset(file, file_size)))
		write(2, "MAP ERROR\n", 10);
	map = NULL;
	map = ft_set_input_map(file, file_size, void_);
	printf("%c %c %c %d %d \n", g_empty_char, g_obstacle_char, g_full_char, g_col_size, g_row_size);
	return (map);
}

int **ft_malloc_solve_map(char **input_map)
{
	int i;
	int j;
	int **resolve_map;
	
	i = 0;
	if (!(resolve_map = (int **)malloc((g_col_size + 1) * sizeof(int *))))    // malloc 실패시 null pointer 반환하는데, 이때 이게 0을 리턴하게 되나
		return (0);
	while (i < g_col_size)
	{
		if (!(resolve_map[i] = (int *)malloc((g_row_size + 1) * sizeof(int))))
			return (0);
		i++;
	}
	printf("%d %d \n", g_col_size, g_row_size);
	return (resolve_map);
}

int ft_min(int a, int b, int c)
{
	return ((a < b && a < c) ? a : (b < c) ? b : c);
}

int **ft_input_solve_map(char **input_map, int *data_store)
{
	int i;
	int j;
	int max_size;
	int pos;
	int **resolve_map;
	
	max_size = 0;
	if (!(resolve_map = ft_malloc_solve_map(input_map)))
		return (0);
	i = 0;
	while (i < g_col_size)
	{
		j = 0;
		while (j < g_row_size)
		{
			if (input_map[i][j] == g_obstacle_char)
				resolve_map[i][j] = 0;
			else if (i == 0 || j == 0)
				resolve_map[i][j] = 1;
			else
				resolve_map[i][j] = ft_min(resolve_map[i - 1][j], resolve_map[i][j - 1], resolve_map[i - 1][j - 1]) + 1;
			if (resolve_map[i][j] > max_size)
			{
				max_size = resolve_map[i][j];
				pos = i * g_row_size + j;
				data_store[0] = max_size;
				data_store[1] = pos;
			}
			j++;
		}
		i++;
	}
	return (resolve_map);
}

char **ft_solve_map(char **input_map)              
{
	int i;
	int j;
	int **resolve_map;
	int length;
	int pos;
	int data_store[3];
	
	resolve_map = ft_input_solve_map(input_map, data_store);
	i = 0;
	j = 0;
	printf("ft_solve_map malloc_solve_map after \n");
	while (i < g_col_size)
	{
		j = 0;
		while (j < g_row_size)
		{
			printf("%d ", resolve_map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("%d %d \n", data_store[0], data_store[1]);
	length = data_store[0];
	pos = data_store[1];
	//i = (pos / g_row_size) - length + 1;
	i = (data_store[1] / g_row_size) - data_store[0] + 1;               // 최대값 위치 기반으로 full char  채우는 과정
	printf("first i ? %d \n", i);										// 근데 도저히 이해가 안된다.
	while (i < (data_store[1] / g_row_size) + 1)
	{
		j = (data_store[1] % g_row_size) - data_store[0] + 1;
		while (j < (data_store[1] % g_row_size) + 1)
		{
			input_map[i][j] = g_full_char;
			j++;
		}
		i++;
	}
	
	i = 0;
	j = 0;
	while (i < g_col_size)
	{
		j = 0;
		while (j < g_row_size)
		{
			printf("%c ", input_map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	return (input_map);
}

void ft_bsq_solution(char **input_map)
{
	int fd;
	int i;
	int j;
	char **map;

	i = 0;
	     												//  체크포인트
	while (i < g_col_size)
	{
		printf("%s inputmap\n", input_map[i]);
		i++;
	}
	map = ft_solve_map(input_map);
	printf("\n------------------------------------end of solution--------------------------------------------------\n");
	     												//  체크포인트
	i = 0;
	j = 0;
	while (i < g_col_size)
	{
		j = 0;
		while (j < g_row_size)
		{
			write(1, &map[i][j], 1);			// 기존에 input map을 출력했다. map으로 바꿔도 마찬가지다. input_map의 내용을 수정하는 방식이란 뜻
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

int		check_exceptions_argc_1(char *map_keyboard, int i)
{
	if (i < 4 || g_empty_char < 32 || g_obstacle_char < 32 || g_full_char < 32)
	{
		write(2, "Map Error_not_enough_simbol\n", 29);
		return (1);
	}
	if (map_keyboard[i-4] > 57 || map_keyboard[i-4] < 48)
	{
		write(2, "Map Error_too_much_simbol\n", 26);
		return (1);
	}
	return (0);
}


int	check_exceptions_argc_2(int i, char *map_keyboard)
{
	while (map_keyboard[i] != '\n')
		i++;
	while (map_keyboard[i] != '\0')
	{
		if (map_keyboard[i] != g_empty_char && map_keyboard[i] != g_obstacle_char && map_keyboard[i] != '\n')
		{
			write(2, "Map Error_diff_simbol_on_the_map\n", 33);
			return (1);

		}
		i++;
	}
	if (g_empty_char == g_obstacle_char || g_empty_char == g_full_char || g_obstacle_char == g_full_char)
		{
			write(2, "Map Error_same_simbol\n", 22);
			return (1);
		}
	return (0);
}


int	get_3_simbols(int i, char *map_keyboard)
{
	i = 0;
	while (map_keyboard[i] != '\n')
	{
		i++;
	}
	g_empty_char = map_keyboard[i - 3];
    g_obstacle_char = map_keyboard[i - 2];
    g_full_char = map_keyboard[i - 1];
	return (i);
}

void	get_col_size(char *map_keyboard)
{
	int	i;
	int	temp;

	i = 0;
	temp = 0;
	while (map_keyboard[i] != g_empty_char)
	{
		if (map_keyboard[i] != g_empty_char && '0' <= map_keyboard[i] && map_keyboard[i] <= '9')
			temp = temp * 10 + map_keyboard[i] - '0';
		else
			break ;
		i++;
	}
	g_col_size = temp;
}



int main(int argc, char *argv[])
{
	int i;
	char **map;
	char *map_keyboard;
	int	temp;

	int	temp2;
	
	i = 1;
	if (argc > 1)
	{
		while (i < argc)
		{
		if((map = ft_valid_argv(argv[i])))       // **map 의 free가 언제 이루어지는지 잘 확인하자   // map이 0이 되는 경우는 ft_push_array가 모든  ccol_size만큼 malloc을 실패하는 경우
				ft_bsq_solution(map);
			i++;
		}
	}
	else if (argc == 1)
	{
		
	if (!(map_keyboard = (char *)malloc(sizeof(char) * 50000)))
		printf("malloc fail_Error\n");
	read(0, map_keyboard, 50000);

	i = get_3_simbols(i, map_keyboard);

	if(check_exceptions_argc_1(map_keyboard, i) == 1)
		return (1);

	get_col_size(map_keyboard);

	i = 0;
	while (i < g_col_size)
	{
		temp = read(0, map_keyboard, 50000);
		map_keyboard += temp;
		i++;
		if(i == 1)
			temp2 = temp;
		if(i >= 2 && temp2 != temp)
		{
			write(2, "Map Error_diff_length\n", 22);
			return (1);
		}
		if(temp == 1)
		{
			write(2, "Map Error_empty_map\n", 20);
			return (1);
		}
	}
	i = 0;
	map_keyboard -= temp * g_col_size;
	g_row_size = temp - 1;

	if(check_exceptions_argc_2(i, map_keyboard) == 1)
			return (1);

	if ((map = ft_set_input_map(map_keyboard, 5, map_keyboard )))
		ft_bsq_solution(map);

	}
	return (0);
}
