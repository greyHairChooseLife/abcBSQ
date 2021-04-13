char *malloc_for_keyboard(char *map_keyboard, int *i);
int get_3_simbols(int i, char *map_keyboard);
void    get_col_size(char *map_keyboard);
int read_keyboard(char *map_keyboard);
int     check_exceptions_argc_1(char *map_keyboard, int i);
int check_exceptions_argc_2(int i, char *map_keyboard);


char *malloc_for_keyboard(char *map_keyboard, int *i)
{
    if (!(map_keyboard = (char *)malloc(sizeof(char) * 50000)))
        printf("malloc fail_Error\n");
    read(0, map_keyboard, 50000);

    *i = get_3_simbols(*i, map_keyboard);
    return (map_keyboard);
}

int get_3_simbols(int i, char *map_keyboard)
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

void    get_col_size(char *map_keyboard)
{
    int i;
    int temp;

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


int read_keyboard(char *map_keyboard)
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
    g_row_size = temp - 1;
    return (temp);
}

int     check_exceptions_argc_1(char *map_keyboard, int i)
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


int check_exceptions_argc_2(int i, char *map_keyboard)
{
    i = 0;
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





