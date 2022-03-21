#include "../minishell.h"

int n_of_cmd(char *str)
{
    int cmd;
    int i;

    cmd = 0;
    i = 0;
    while (str[i])
    {
        if (*str == '|')
            cmd++;
        else if(str[i] == '<')
        {
            if (str[i + 1] == '<')
                i++;
            cmd++;
        }
        else if(str[i] == '>' && str[i + 1] != '>')
        {
            cmd++;
        }
        else if (str[i] == '|')
            cmd++;
        i++;
    }
    return(++cmd);
}

char    ***l_to_tab(char *str)
{
    int i;
    int j;
    int ncmd;
    char    ***cmds;

    ncmd = n_of_cmd(str);
    cmds = malloc((ncmd + 1) * sizeof(char **));
    i = 0;
    j = 0;
    while (str[i] != '|')
        i++;
    str[i] = 0;
    if (ft_strchr(str, '"'))
    {
        cmds[j] = ft_split(str, '"');
    }
}

