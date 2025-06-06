/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:57:08 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/06 18:25:35 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Updates PWD and OLDPWD environment variables after changing directory
 * @param mini Pointer to the shell structure
 * @param cwd New current working directory
 * @param owd Previous working directory

static void	update_pwd_vars(t_ms *mini, char *cwd, char *owd)
{
	t_envlst	*pwd_node;
	t_envlst	*oldpwd_node;

	pwd_node = mini->myenv;
	while (pwd_node && ft_strcmp(pwd_node->key, "PWD") != 0)
		pwd_node = pwd_node->next;
	oldpwd_node = mini->myenv;
	while (oldpwd_node && ft_strcmp(oldpwd_node->key, "OLDPWD") != 0)
		oldpwd_node = oldpwd_node->next;
	if (pwd_node)
	{
		free(pwd_node->value);
		pwd_node->value = ft_strdup(cwd);
	}
	if (oldpwd_node)
	{
		free(oldpwd_node->value);
		oldpwd_node->value = ft_strdup(owd);
	}
}*/
static void	update_pwd_vars(t_ms *mini, char *cwd, char *owd)
{
	t_envlst	*pwd_node;
	t_envlst	*oldpwd_node;
	char		*temp;

	temp = NULL;
	pwd_node = env_get_node(&mini->myenv, "PWD");
	oldpwd_node = env_get_node(&mini->myenv, "OLDPWD");
	if (pwd_node)
	{
		free(pwd_node->value);
		pwd_node->value = ft_strdup(cwd);
	}
	if (oldpwd_node)
	{
		free(oldpwd_node->value);
		oldpwd_node->value = ft_strdup(owd);
	}
	else if (!oldpwd_node)
	{
		temp = ft_strjoin("OLDPWD=", owd);
		env_append_node(&mini->myenv, env_new_node(temp));
		free (temp);
	}
}

/**
 * Gets home directory from environment variables
 * @param mini Pointer to the shell structure
 * @return Home directory path or NULL if not found
 */
static char	*get_home_dir(t_ms *mini)
{
	t_envlst	*home_node;

	home_node = mini->myenv;
	while (home_node)
	{
		if (ft_strcmp(home_node->key, "HOME") == 0)
			return (home_node->value);
		home_node = home_node->next;
	}
	return (NULL);
}

static char	*get_target_directory(char **cmd, t_ms *mini)
{
	char	*target_dir;

	if (cmd[1] == NULL)
	{
		target_dir = get_home_dir(mini);
		if (!target_dir)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			mini->exit_status = 1;
			return (NULL);
		}
	}
	else
		target_dir = cmd[1];
	return (target_dir);
}

static int	perform_cd(char *target_dir, t_ms *mini, char *old_dir)
{
	char	cwd[1024];

	if (chdir(target_dir) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(target_dir, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		mini->exit_status = 1;
		return (1);
	}	
	if (getcwd(cwd, 1024) == NULL)
		return (ft_putstr_fd("minishell: cd: getcwd error\n", 2), 1);
	update_pwd_vars(mini, cwd, old_dir);
	if (mini->cwd)
		free(mini->cwd);
	mini->cwd = ft_strdup(cwd);
	if (!mini->cwd)
	{
		ft_putstr_fd("cd: memory allocation error\n", 2);
		return (mini->exit_status = 1, 1);
	}
	return (0);
}

int	ft_cd(char **cmd, t_ms *mini)
{
	char	owd[1024];
	char	*target_dir;

	if (getcwd(owd, 1024) == NULL)
		return (ft_putstr_fd("minishell: cd: getcwd error\n", 2), 1);
	target_dir = get_target_directory(cmd, mini);
	if (!target_dir)
		return (1);
	if (perform_cd(target_dir, mini, owd))
		return (1);
	mini->exit_status = 0;
	return (0);
}

/* 

 * Change directory command implementation
 * @param data Command block containing cd command and arguments
 * @param mini Pointer to the shell structure
 * @return Exit status (0 for success, 1 for error)
 
int ft_cd(char **cmd, t_ms *mini)
{
    char cwd[1024];
    char owd[1024];
    char *target_dir;
    
    if (getcwd(owd, 1024) == NULL)
        return (ft_putstr_fd("minishell: cd: getcwd error\n", 2), 1);
    if (cmd[1] == NULL)
    {
        target_dir = get_home_dir(mini);
        if (!target_dir)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            mini->exit_status = 1;
            return (1);
        }
    }
    else
        target_dir = cmd[1];
    if (chdir(target_dir) != 0)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(target_dir, 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
        mini->exit_status = 1;
        return (1);
    }

    if (getcwd(cwd, 1024) == NULL)
        return (ft_putstr_fd("minishell: cd: getcwd error\n", 2), 1);

    update_pwd_vars(mini, cwd, owd);
    if (mini->cwd)
    {
        free(mini->cwd);
        mini->cwd = NULL;
    }
    mini->cwd = ft_strdup(cwd);
    if (!mini->cwd)
    {
        ft_putstr_fd("cd: memory allocation error\n", 2);
        mini->exit_status = 1;
        return (1);
    }
    mini->exit_status = 0;
    return (0);
}
 */
/* //--------------------------------TESTING OONLY

char *ft_strdup(const char *s)
{
    char *dup;
    size_t len = strlen(s) + 1;
    
    dup = malloc(len);
    if (dup)
        memcpy(dup, s, len);
    return (dup);
}

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void ft_putstr_fd(char *s, int fd)
{
    if (s)
        write(fd, s, strlen(s));
}

t_envlst *create_env_node(char *key, char *value)
{
    t_envlst *node = malloc(sizeof(t_envlst));
    if (!node)
        return (NULL);
    
    node->key = ft_strdup(key);
    node->value = ft_strdup(value);
    node->next = NULL;
    
    return (node);
}
t_envlst *init_env(void)
{
    t_envlst *env_head = NULL;
    t_envlst *temp;
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        return (NULL);
    }
    env_head = create_env_node("PWD", cwd);
    if (!env_head)
        return (NULL);
    temp = create_env_node("OLDPWD", cwd);
    if (!temp)
    {
        free(env_head->key);
        free(env_head->value);
        free(env_head);
        return (NULL);
    }
    env_head->next = temp;
    char *home = getenv("HOME");
    if (!home)
        home = "/";
    
    temp->next = create_env_node("HOME", home);
    
    return (env_head);
}
void display_env(t_envlst *env)
{
    t_envlst *current = env;
    
    printf("\n--- Environment Variables ---\n");
    while (current)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
    printf("---------------------------\n\n");
}
t_cmdblock *create_test_cmd(char **args)
{
    t_cmdblock *cmd = malloc(sizeof(t_cmdblock));
    if (!cmd)
        return (NULL);
    
    cmd->cmd = args;
    cmd->redir = NULL;
    cmd->next = NULL;
    
    return (cmd);
}
void free_env(t_envlst *env)
{
    t_envlst *current;
    t_envlst *next;
    
    current = env;
    while (current)
    {
        next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
}
void free_cmd(t_cmdblock *cmd)
{
    if (cmd)
        free(cmd);
    // not freeing cmd->cmd as it's statically allocated in this test
}
int main(int argc, char *argv[])
{
    t_ms mini;
    t_cmdblock *cmd;
    char *cd_cmd[] = {"cd", NULL, NULL};
    char cwd[1024];
    mini.myenv = init_env();
    if (!mini.myenv)
    {
        fprintf(stderr, "Failed to initialize environment\n");
        return (1);
    }
    
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        free_env(mini.myenv);
        return (1);
    }
    mini.cwd = ft_strdup(cwd);
    mini.exit_status = 0;
    printf("Initial working directory: %s\n", mini.cwd);
    display_env(mini.myenv);
    // Test 1: cd to parent directory
    printf("Test 1: cd ..\n");
    cd_cmd[1] = "..";
    cmd = create_test_cmd(cd_cmd);
    ft_cd(cmd, &mini);
    printf("New working directory: %s\n", mini.cwd);
    display_env(mini.myenv);
    free_cmd(cmd);
    // Test 2: cd to home directory
    printf("Test 2: cd (to home)\n");
    cd_cmd[1] = NULL;
    cmd = create_test_cmd(cd_cmd);
    ft_cd(cmd, &mini);
    printf("New working directory: %s\n", mini.cwd);
    display_env(mini.myenv);
    free_cmd(cmd);
    // Test 3: cd to invalid directory
    printf("Test 3: cd to invalid directory\n");
    cd_cmd[1] = "/non_existent_directory";
    cmd = create_test_cmd(cd_cmd);
    int result = ft_cd(cmd, &mini);
    printf("Result: %d (exit status: %d)\n", result, mini.exit_status);
    printf("Working directory remains: %s\n", mini.cwd);
    display_env(mini.myenv);
    free_cmd(cmd);
    // Test 4: cd back to original directory (if provided)
    if (argc > 1)
    {
        printf("Test 4: cd back to %s\n", argv[1]);
        cd_cmd[1] = argv[1];
        cmd = create_test_cmd(cd_cmd);
        ft_cd(cmd, &mini);
        printf("New working directory: %s\n", mini.cwd);
        display_env(mini.myenv);
        free_cmd(cmd);
    }
    free(mini.cwd);
    free_env(mini.myenv);
    
    return (0);
} */