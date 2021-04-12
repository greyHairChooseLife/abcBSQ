#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

char	g_full_char;
char	g_empty_char;
char	g_obstacle_char;
int	g_file_size;
int	g_col_size;

void ft_set_charset(char *file)
{
	char *line;
	char result;
	int i;
	int fd;
	i = 0;

	if ((fd = open(file, O_RDONLY)) == -1)  // 예외처리는 모아서 따로해주는게 좋을듯
	{
		write(2, "Error\n", 6);
		return ;
	}
	if (!(line = malloc(1025 * sizeof(char)))) // 1025는 어디서 온 숫자인가, 이 조건식의 의미 해석이 안됩니다 ㅠㅠ.
	{
		write(2, "Error\n", 6);
		return ;
	}
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break;
		i++;
	}
	g_full_char = line[i - 1];     //이부분 좋은듯. 엉덩이부터 잘라서 3가지 '문자' 찾기. 
	g_empty_char = line[i - 3];
	g_obstacle_char = line[i - 2];
}

void ft_mv_nextline(int fd) // 이 함수의 용도는 무엇인가  음  확인  한줄을 밀어버리는구나 
{
	char *line;
	int i;
	
	i = 0;
	if (!(line = (char *)malloc(1025 * sizeof(char))))  // ft_set_charset 과 중복
	{
		write(2, "Error\n", 6);
		return ;
	}
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break;
		i++;
	}
	free(line);
}

int ft_count_row_size(char *file) 
{
	char *line;
	int i;
	int fd;
	
	if ((fd = open(file, O_RDONLY)) == -1)  // 중복체크
	{
		write(2, "Error\n", 6);
		return (0);
	}
	ft_mv_nextline(fd);
	if (!(line = (char *)malloc((g_file_size + 1) * sizeof(char)))) // 무엇을 확인하는 부분인지 모르겠다!!
	{
		write(2, "Error\n", 6);
		return (0);
	}
	i = 0;
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break ;
		i++;
	}
	close(fd);
	free(line);
	return (i);
}

int ft_get_col(char *file)  // 이 함수 잘 쓸 수 있을듯. atoi따로 할 필요도 없고
{
	char *line;
	int i;
	int fd;
	int col_size;
	
	if ((fd = open(file, O_RDONLY)) == -1)  // 중복체크
	{
		write(2, "Error\n", 6);
		return (0);
	}
	if (!(line = (char *)malloc(1025 * sizeof(char)))) // 중복체크   아  이거 멀록 안되면 안됐다고 체크하는거구나!
	{
		write(2, "Error\n", 6);
		return (0);
	}
	i = 0;
	col_size = 0;
	while (read(fd, &line[i], 1))                          
	{
		if ('0' <= line[i] && line[i] <= '9')
		{
			col_size *= 10;
			col_size += line[i] -'0';
		}
		else if (line[i] == g_empty_char)
			break;
		else
		{
			write(2, "Error\n", 6);
			return (0);
		}
		i++;
	}
	close(fd);
	free(line);
	return (col_size);
}

void ft_count_file_size(char *file)
{
	char c;
	int i;
	int fd;
	int size;
	
	if ((fd = open(file, O_RDONLY)) == -1)  // 중복
	{
		write(2, "Error\n", 6);
		return ;
	}
	size = 0;
	while (read(fd, &c, 1))
		size++;
	close(fd);
	g_file_size = size;
}

int ft_valid_map(char *file)
{
	int i;
	int last_index;
	int fd;
	char *line;
	
	if ((fd = open(file, O_RDONLY)) == -1) //중복
	{
		write(2, "Error\n", 6);
		return (0);
	}
	ft_mv_nextline(fd);
	if (!(line = (char *)malloc((g_file_size + 1) * sizeof(char))))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	last_index = 0;
	while ((last_index = read(fd, &line[0], g_file_size))) // 1 char만큼의 공간에 그이상의 데이터를 저장한대도 오류가 안나네
		line[last_index] = '\0';    		       // 하여간에 이건 어떤 의미가 있는것인가 반복문 조건에 할당이라??
	printf("last_inxdex: ______ %d\n", last_index);        // index값을 구한 의도는 무엇이었을까?
	i = 0;
	while (line[i])  // 이게 숫자가 문자로 주어질 때도 문제가 없을까? 헷갈린다 맑은정신으로 다시 생각하기
	{		 // 그리고 이게  무슨 의미인지 솔찌기 잘 모르겠다... 
		if ((line[i] != g_empty_char && line[i] != g_obstacle_char && line[i] != '\n'))
			return (0);
		i++;
	}
	close(fd);
	free(line);
	return (1);
}

int ft_check_row_newline(char *file)
{
	char *line;
	int i;
	int fd;
	int row_size;
	
	if (!(line = (char *)malloc((g_file_size + 1) * sizeof(char))))  // 멀록 실패인지 확인하는거 좋다. 전에 러쉬때 지적받음
	{
		write(2, "Error\n", 6);
		return (0);
	}
	row_size = ft_count_row_size(file);
	if ((fd = open(file, O_RDONLY)) == -1)  // 중복
	{
		write(2, "Error\n", 6);
		return (0);
	}
	while (read(fd, line, row_size))  // 이렇게 짜면 내부 if조건 만족 못할 시 무한루프에 빠짐
	{
		if (line[row_size] != '\n')   // 여기도 mv_nextline() 해줘야 작동할듯, 찍어보니까 지도파일의 0행 다루고 있음
			return (3);
	}
	close(fd);
	free(line);
	return (1);
}

int ft_get_next_row_size(char *file, int fd)
{
	char *line;
	int i;
	
	i = 0;
	if (!(line = (char *)malloc((g_file_size + 1) * sizeof(char)))) // 중복
	{
		write(2, "Error\n", 6);
		return (0);
	}
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break;
		i++;
	}
	free(line);
	return (i);
}

int ft_valid_row(char *file)  // 모든 행의 길이가 같은지 체크:  이거는 2차원 배열 만들어서 값 넣을 때 겸사겸사 알 수 있지않을까?
{
	int i;
	int j;
	int fd;
	int row_size;
	
	i = 0;
	j = 0;
	row_size = ft_count_row_size(file);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	ft_mv_nextline(fd);
	while (i < g_col_size)
	{
		j = ft_get_next_row_size(file, fd);
		printf("%d / %d \n", j, row_size);
		if (j != row_size)
			return (0);
		i++;
	}
	j = ft_get_next_row_size(file, fd);
	close(fd);
	return (j ? 0 : 1);
}

int main(int argc, char *argv[])   // 코드를 다 보고서 느낀점은 이거 지도 유효성 검사만 해도 양이 엄청 많다는 것이다. main함수 줄 수를 아껴야한다. 또한 전역변수로 무엇무엇을 사용할지 정해야겠다. 
{
	(void)argc;  //뜬금없긴 하지만 이거 왜하시는건가요. 
	(void)argv;
	int row_size = ft_count_row_size("example_file2");
	printf("row_size ? %d \n", row_size);
	ft_set_charset("example_file2");
	printf("g_full : %c / g_empty : %c, g_obstacle : %c \n", g_full_char, g_empty_char, g_obstacle_char);
	g_col_size = ft_get_col("example_file2");
	printf("col_size ? %d \n", g_col_size);
	ft_count_file_size("example_file2");
	printf("g_file_size ? %d \n", g_file_size);
	printf("ft_valid_map ? %d \n", ft_valid_map("example_file2"));
	printf("ft_check_row_newline ? %d \n", ft_check_row_newline("example_file2"));
	printf("valid_col ? : %d \n", ft_valid_row("example_file2"));
	return (0);
}
