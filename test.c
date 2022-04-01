#include "minishell.h"

void sig_hand(int sig)
{
	rl_on_new_line();
}

int main()
{
	char *input;
	signal(SIGINT, sig_hand);
	while (1)
	{
		input = readline("input > ");
		// printf("%s", input);
	}
	return (0);
}