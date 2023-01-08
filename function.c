#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "header.h"
#define HEART_CODE 3
#define OTHER_ACCOUNT_INFO 0/*for info function that onfo is for other accounts*/
#define ACCOUNT_TXT "accounts.txt"
#define POSTS_TXT "posts.txt"
/*operations defines*/
#define SIGNUP "signup"
#define LOGOUT "logout"
#define LOGIN "login"
#define LIST "list"
#define EXIT "exit"
#define SEARCH "find_user"
#define POST "post"
#define INFO "info"
#define LIKE "like"
#define DELETE_POST "delete"
/*this function read from buffer anad return to array of array which is dynamic*/
char *read_instruction(int *len_instruction)/*first malloc and makee it null then put char in it if it was true char*/
{
    int len = 0;
    char temp = ' ';
    char *instruction = (char *)malloc(sizeof(char));
    *(instruction) = '\0';
    int flag = 1;
    temp = getchar();
    if (temp != '\n')
    {
        len++;
        instruction[len - 1] = temp;
        while (flag)
        {
            temp = getchar();
            len++;
            instruction = (char *)realloc(instruction, len * (sizeof(char)));
            instruction[len - 1] = '\0';
            switch (temp)
            {
            case '\n':
                flag = 0;
                break;
            default:
                instruction[len - 1] = temp;
                break;
            }
        }
        *len_instruction = len;
        return instruction;
    }
    else
    {
        return NULL;
    }
}

/*using instruction array for recognizing the function*/
char *recognize_operation(char *instruction, int len_instruction, int *code_operation)
{
    int index_instruction = 0;
    char *operation = (char *)malloc(sizeof(char));
    int len = 1;
    int draft = 0;
    while ((instruction[index_instruction] != ' ') && (instruction[index_instruction] != '\n') && (instruction[index_instruction] != '\0'))
    {
        if (draft == 0)
        {
            operation[len - 1] = instruction[index_instruction];
            index_instruction++;
            draft = 1;
        }
        else
        {
            len++;
            operation = (char *)realloc(operation, len * sizeof(char));
            operation[len - 1] = instruction[index_instruction];
            index_instruction++;
        }
    }
    len++;
    operation[len - 1] = '\0';
    if (index_instruction == len_instruction - 1) /*single instruction/just the name of operation should be written by user*/
    {
        if (!strcmp(operation, LOGOUT))
        {
            *code_operation = 3;
            free(operation);
            free(instruction);
            return NULL;
        }
        else if (!strcmp(operation, LIST))
        {
            *code_operation = 10;
            free(operation);
            free(instruction);
            return NULL;
        }
        else if (!strcmp(operation, EXIT))
        {
            *code_operation = 9;
            free(operation);
            free(instruction);
            return NULL;
        }
        else if (!strcmp(operation, INFO))
        {
            *code_operation = 6;
            free(operation);
            free(instruction);
            return NULL;
        }
        else
        {
            free(operation);
            free(instruction);
            return NULL;
        }
    }
    else/*instruction has more than one word*/
    {
        if (!strcmp(operation, SIGNUP))
        {
            *code_operation = 1;
        }
        else if (!strcmp(operation, LOGIN))
        {
            *code_operation = 2;
        }
        else if (!strcmp(operation, SEARCH))
        {
            *code_operation = 4;
        }
        else if (!strcmp(operation, POST))
        {
            *code_operation = 5;
        }
        else if (!strcmp(operation, LIKE))
        {
            *code_operation = 7;
        }
        else if (!strcmp(operation, DELETE_POST))
        {
            *code_operation = 8;
        }
        else
        {
            return NULL;
        }
        index_instruction++;
        int len_input = len_instruction - len;
        int index_input = 0;
        char *input = (char *)malloc(len_input * sizeof(char));
        while (index_instruction < len_instruction)
        {
            input[index_input] = instruction[index_instruction];
            index_instruction++;
            index_input++;
        }
        free(operation);
        free(instruction);
        return input;
    }
}

/*recognizing that the operation is true or no*/
int count_space(char *instruction)
{
    int counter_space = 0;
    int index_instruction = 0;
    while (instruction[index_instruction] != '\0')
    {
        if (instruction[index_instruction] == ' ')
        {
            counter_space++;
        }
        index_instruction++;
    }
    return counter_space;
}

/*creating an account*/
int signup(account *head, char *instrution)
{
    int status = count_space(instrution);
    if (status == 1)
    {
        char *username = (char *)malloc(sizeof(char));
        char *password = (char *)malloc(sizeof(char));
        int len_username = 1;
        int pass_len = 1;
        int index_instruction = 0;
        username[len_username - 1] = instrution[index_instruction];
        index_instruction++;
        while (instrution[index_instruction] != ' ')
        {
            len_username++;
            username = (char *)realloc(username, len_username * sizeof(char));
            username[len_username - 1] = instrution[index_instruction];
            index_instruction++;
        }
        len_username++;
        username = (char *)realloc(username, len_username * sizeof(char));
        username[len_username - 1] = '\0';
        account *temp1;
        temp1 = head->next;
        while (temp1 != NULL)
        {
            if (!strcmp(username, temp1->username))/*checking duplicated username*/
            {
                free(instrution);
                free(username);
                free(password);
                return 2;
            }
            else
            {
                temp1 = temp1->next;
            }
        }
        index_instruction++;
        password[pass_len - 1] = instrution[index_instruction];
        index_instruction++;
        while (instrution[index_instruction] != '\0')
        {
            pass_len++;
            password = (char *)realloc(password, pass_len * sizeof(char));
            password[pass_len - 1] = instrution[index_instruction];
            index_instruction++;
        }
        pass_len++;
        password = (char *)realloc(password, pass_len * sizeof(char));
        password[pass_len - 1] = '\0';
        /*put data in user struct*/
        account *new_user = (account *)malloc(sizeof(account));
        account *temp;
        temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_user;
        new_user->username = username;
        new_user->password = password;
        new_user->next = NULL;
        new_user->num_liked_posts = 0;
        new_user->num_user_posts = 0;
        post *dummy = (post *)malloc(sizeof(post));
        new_user->first_post = dummy;
        dummy->next = NULL;
        dummy->like = -1;
        free(instrution);
        return 1;
    }
    else
    {
        free(instrution);
        return 0;
    }
}

/*printing users with usernames and passwords*/
void show_list_users(account *head)
{
    account *temp;
    temp = head->next;
    while (temp != NULL)
    {
        printf("%s\n%s\n", temp->username, temp->password);
        printf("------------------------\n");
        temp = temp->next;
    }
}

/*using instruction array/checking the username and pass to be existed/changing the amount of login status for rest of program/retuening the account pointer*/
int login(account *head, int *status_login, char *instruction, account **current_account)
{
    int counter_space = count_space(instruction);
    if (counter_space == 1)
    {
        char *username = (char *)malloc(sizeof(char));
        int username_len = 1;
        int index_instruction = 0;
        username[username_len - 1] = instruction[index_instruction];
        index_instruction++;
        while (instruction[index_instruction] != ' ')
        {
            username_len++;
            username = (char *)realloc(username, username_len * sizeof(char));
            username[username_len - 1] = instruction[index_instruction];
            index_instruction++;
        }
        username_len++;
        username = (char *)realloc(username, username_len * sizeof(char));
        username[username_len - 1] = '\0';
        account *temp;
        temp = head->next;
        int flag = 0;
        while (temp != NULL)
        {
            if (!strcmp(username, temp->username))/*checking if username existed*/
            {
                flag = 1;
                break;
            }
            else
            {
                temp = temp->next;
            }
        }
        if (flag == 1)
        {
            char *password = (char *)malloc(sizeof(char));
            int pass_len = 1;
            index_instruction++;
            password[pass_len - 1] = instruction[index_instruction];
            index_instruction++;
            while (instruction[index_instruction] != '\0')
            {
                pass_len++;
                password = (char *)realloc(password, pass_len * sizeof(char));
                password[pass_len - 1] = instruction[index_instruction];
                index_instruction++;
            }
            pass_len++;
            password = (char *)realloc(password, pass_len * sizeof(char));
            password[pass_len - 1] = '\0';
            if (!strcmp(password, temp->password))
            {
                *status_login = 1;
                *current_account = temp;
                free(instruction);
                free(username);
                free(password);
                return 1;
            }
            else
            {
                free(instruction);
                free(username);
                free(password);
                return 0;
            }
        }
        else
        {
            free(username);
            free(instruction);
            return 0;
        }
    }
    else
    {
        free(instruction);
        return 0;
    }
}

/*leaving current account/change the amount of login status and make the current account null*/
int logout(account **current_account, int *status_login)
{
    *current_account = NULL;
    *status_login = 0;
    return 1;
}

/*searching user and showing their posts*/
int search(account *head, char *instruction)
{
    int counter_space = count_space(instruction);
    if (counter_space == 0)
    {
        char *username = (char *)malloc(sizeof(char));
        int username_len = 1;
        int index_instruction = 0;
        username[username_len - 1] = instruction[index_instruction];
        index_instruction++;
        while (instruction[index_instruction] != '\0')
        {
            username_len++;
            username = (char *)realloc(username, username_len * sizeof(char));
            username[username_len - 1] = instruction[index_instruction];
            index_instruction++;
        }
        username_len++;
        username = (char *)realloc(username, username_len * sizeof(char));
        username[username_len - 1] = '\0';
        int flag = 0;
        account *temp;
        temp = head->next;
        while (temp != NULL)
        {
            if (!strcmp(username, temp->username))/*searching in linked list of account*/
            {
                flag = 1;
                break;
            }
            else
            {
                temp = temp->next;
            }
        }
        if (flag == 1)
        {
            int status = info(temp, OTHER_ACCOUNT_INFO);
            if (status == 1)
            {
                free(instruction);
                free(username);
                return 1;
            }
            else
            {
                free(instruction);
                free(username);
                return 0;
            }
        }
        else
        {
            free(instruction);
            free(username);
            return 0;
        }
    }
    else
    {
        free(instruction);
        return 0;
    }
}

/*adding a post and connect another liked list to each account*/
int add_post(account *current_account, char *instruction, int *num_posts)
{
    char *text = (char *)malloc(sizeof(char));
    int text_len = 1;
    int index_instruction = 0;
    text[text_len - 1] = instruction[index_instruction];
    index_instruction++;
    while (instruction[index_instruction] != '\0')
    {
        text_len++;
        text = (char *)realloc(text, text_len * sizeof(char));
        text[text_len - 1] = instruction[index_instruction];
        index_instruction++;
    }
    text_len++;
    text = (char *)realloc(text, text_len * sizeof(char));
    text[text_len - 1] = '\0';
    post *new_post = (post *)malloc(sizeof(post));
    post *temp;
    temp = current_account->first_post;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_post;
    new_post->text = text;
    int draft = *num_posts;
    draft++;/*converting post id from int to char for using strcmp*/
    *num_posts = draft;
    new_post->id = draft;
    int digit = 0, len_id = 1;
    char *id = (char *)malloc(sizeof(char));
    if (draft < 10)
    {
        id[len_id - 1] = draft + '0';
        len_id++;
        id = (char *)realloc(id, len_id * sizeof(char));
        id[len_id - 1] = '\0';
    }
    else
    {
        int *num = (int *)malloc(sizeof(int));
        int len = 1;
        digit = draft % 10;
        draft = draft / 10;
        num[len - 1] = digit;
        while (draft != 0)
        {
            digit = draft % 10;
            draft /= 10;
            len++;
            num = (int *)realloc(num, len * sizeof(int));
            num[len - 1] = digit;
        }
        id = (char *)realloc(id, sizeof(char) * len);
        len_id = 0;
        int counter_while = len;
        while (counter_while > 0)
        {
            id[len_id] = num[len - 1] + '0';
            len--;
            len_id++;
            counter_while--;
        }
        len_id++;
        id = (char *)realloc(id, sizeof(char) * len_id);
        id[len_id - 1] = '\0';
    }
    new_post->post_id = id;
    new_post->like = 0;
    current_account->num_user_posts += 1;
    new_post->next = NULL;
    return 1;
}

/*printing posts anf username of users/status login is for recognizing whether the password should be printed or no*/
int info(account *current_account, int status_account)
{
    post *temp;
    int i = 0;
    for (i = 0; i < 15; i++)
    {
        printf("-");
    }
    printf("\n");
    printf("account info:\nusername: %s\n", current_account->username);
    if (status_account == 1)
    {
        printf("password: %s\n", current_account->password);
    }

    for (i = 0; i < 15; i++)
    {
        printf("-");
    }
    printf("\n");
    temp = current_account->first_post->next;
    while (temp != NULL)
    {
        for (i = 0; i < 15; i++)
        {
            printf("-");
        }
        printf("\n");
        printf("post id :%s\n%s\n%d%c\n", temp->post_id, temp->text, temp->like, HEART_CODE);
        for (i = 0; i < 15; i++)
        {
            printf("-");
        }
        printf("\n\n");
        temp = temp->next;
    }
    return 1;
}

/*searching in accounts liked list for finding the user/then searching in users posts linked list for post id/put the post id in current account int dynamic array
for restricting liking a post twice*/
int like(account *head, char *instruction, account *current_account)
{
    int counter_space = count_space(instruction);
    if (counter_space == 1)
    {
        char *username = (char *)malloc(sizeof(char));
        int index_instruction = 0;
        int username_len = 1;
        username[username_len - 1] = instruction[index_instruction];
        index_instruction++;
        while (instruction[index_instruction] != ' ')
        {
            username_len++;
            username = (char *)realloc(username, username_len * sizeof(char));
            username[username_len - 1] = instruction[index_instruction];
            index_instruction++;
        }
        index_instruction++;
        username_len++;
        username = (char *)realloc(username, username_len * sizeof(char));
        username[username_len - 1] = '\0';
        account *temp;
        temp = head->next;
        int flag = 0;
        while (temp != NULL)
        {
            if (!strcmp(username, temp->username))
            {
                flag = 1;
                break;
            }
            else
            {
                temp = temp->next;
            }
        }
        if (flag == 1)
        {
            char *post_id = (char *)malloc(sizeof(char));
            int len_id = 1;
            post_id[len_id - 1] = instruction[index_instruction];
            index_instruction++;
            while (instruction[index_instruction] != '\0')
            {
                len_id++;
                post_id = (char *)realloc(post_id, len_id * sizeof(char));
                post_id[len_id - 1] = instruction[index_instruction];
                index_instruction++;
            }
            len_id++;
            post_id = (char *)realloc(post_id, sizeof(char));
            post_id[len_id - 1] = '\0';
            post *temp_post;
            temp_post = temp->first_post->next;
            int post_id_int;
            while (temp_post != NULL)
            {
                if (!strcmp(post_id, temp_post->post_id))
                {
                    flag = 2;
                    post_id_int = temp_post->id;
                    break;
                }
                else
                {
                    temp_post = temp_post->next;
                }
            }
            if (flag == 2)
            {
                int i = 0;
                while (i < current_account->num_liked_posts)
                {
                    if (post_id_int == current_account->liked_posts_id[i])
                    {
                        printf("you liked this post before!\n");
                        free(username);
                        free(post_id);
                        return 0;
                    }
                    else
                    {
                        i++;
                    }
                }
                temp_post->like += 1;
                if (current_account->num_liked_posts == 0)
                {
                    int draft = current_account->num_liked_posts;
                    draft++;
                    current_account->num_liked_posts = draft;
                    current_account->liked_posts_id = (int *)malloc(sizeof(int));
                    current_account->liked_posts_id[draft - 1] = temp_post->id;
                    free(username);
                    free(post_id);
                    return 1;
                }
                else
                {
                    int draft = current_account->num_liked_posts;
                    draft++;
                    current_account->num_liked_posts = draft;
                    current_account->liked_posts_id = (int *)realloc(current_account->liked_posts_id, sizeof(int) * draft);
                    current_account->liked_posts_id[draft - 1] = temp_post->id;
                    free(username);
                    free(post_id);
                    return 1;
                }
            }
            else
            {
                printf("post doesn't exists!\n");
                free(username);
                return 0;
            }
        }
        else
        {
            printf("this username doesn't exists!\n");
            free(username);
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

/*searching in current account post lnked list/connect previus and next node after deleting*/
int delete_post(account *current_account, char *instruction)
{
    post *temp = current_account->first_post->next;
    post *previuos = current_account->first_post;
    post *after = current_account->first_post->next->next;
    char *post_id = (char *)malloc(sizeof(char));
    int post_id_len = 1;
    int index_instruction = 0;
    post_id[post_id_len - 1] = instruction[index_instruction];
    index_instruction++;
    while (instruction[index_instruction != '\0'])
    {
        post_id_len++;
        post_id = (char *)realloc(post_id, sizeof(char) * post_id_len);
        post_id[post_id_len - 1] = instruction[index_instruction];
        index_instruction++;
    }
    post_id_len++;
    post_id = (char *)realloc(post_id, sizeof(char) * post_id_len);
    post_id[post_id_len - 1] = '\0';
    int flag = 0;
    while (temp != NULL)
    {
        if (!strcmp(post_id, temp->post_id))
        {
            previuos->next = after;
            free(temp);
            flag = 1;
            break;
        }
        else
        {
            previuos = temp;
            temp = temp->next;
            after = temp->next;
        }
    }
    if (flag == 1)
    {
        free(post_id);
        return 1;
    }
    else
    {
        return 0;
    }
}

/*wrinting accounts info countaining username pass and num posts in txt file at the end of while*/
int output_accounts(account *head)
{
    FILE *account_txt = fopen(ACCOUNT_TXT, "w");
    account *temp;
    temp = head->next;
    while (temp != NULL)
    {
        fprintf(account_txt, "%s %s %d\n", temp->username, temp->password, temp->num_user_posts);
        temp = temp->next;
    }
    fclose(account_txt);
    return 1;
}

/*writing posts in txt filr including text num likes and username*/
int output_posts(account *head)
{
    FILE *posts_txt = fopen(POSTS_TXT, "w");
    account *temp_account;
    post *temp_post;
    temp_account = head->next;
    while (temp_account != NULL)
    {
        temp_post = temp_account->first_post->next;
        while (temp_post != NULL)
        {
            fprintf(posts_txt, "%s %s %d\n", temp_post->text, temp_account->username, temp_post->like);
            temp_post = temp_post->next;
        }
        temp_account = temp_account->next;
    }
    fclose(posts_txt);
    return 1;
}