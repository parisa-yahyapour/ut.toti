#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "header.h"
#define MY_ACCOUNT_INFO 1/*for info function, that the info is for user or others*/
int main()
{
    account *head = (account *)malloc(sizeof(account));
    account *current_account = NULL;
    head->next = NULL;
    int len_instruction, code_operation = -1, proccess = 1, status = -1, status_login = 0, num_posts = 0;
    /*code operation for recognizing operation
    process for while condition
    status for checking all functions
    status login for showing user is in an account or no
    num posts for post id*/
    while (proccess)
    {
        status = -1;
        code_operation = -1;
        char *instruction = read_instruction(&len_instruction);
        if (instruction != NULL)
        {
            instruction = recognize_operation(instruction, len_instruction, &code_operation);
            switch (code_operation)
            {
            case 1:/*signup*/
                if (status_login == 1)
                {
                    printf("you are in your account!\n");
                    free(instruction);
                }
                else
                {
                    status = signup(head, instruction);
                    if (status == 1)
                    {
                        printf("signup was successful\n");
                    }
                    else if (status == 0)
                    {
                        printf("signup failed\n");
                    }
                    else if (status == 2)
                    {
                        printf("this username existed\n");
                    }

                    else
                    {
                        printf("signup did'nt work\n");
                    }
                }
                break;
            case 2:/*login*/
                if (status_login == 1)
                {
                    printf("you are in your account!\n");
                    free(instruction);
                }
                else
                {
                    status = login(head, &status_login, instruction, &current_account);
                    if (status == 1)
                    {
                        printf("you logged in\n");
                    }
                    else
                    {
                        printf("login failed\n");
                    }
                }
                break;
            case 3:/*logout*/
                if (status_login == 1)
                {
                    status = logout(&current_account, &status_login);
                    if (status == 1)
                    {
                        printf("you logged out\n");
                    }
                    else
                    {
                        printf("logout didn't work\n");
                    }
                }
                else
                {
                    printf("you haven't logged in!\n");
                    free(instruction);
                }
                break;
            case 4:/*search*/
                if (status_login == 0)
                {
                    printf("you haven't logged in\n");
                    free(instruction);
                }
                else
                {
                    status = search(head, instruction);
                    if (status == 1)
                    {
                        printf("user found\n");
                    }
                    else
                    {
                        printf("no user found\n");
                    }
                }
                break;
            case 5:/*post*/
                if (status_login == 1)
                {
                    status = add_post(current_account, instruction, &num_posts);
                    if (status == 1)
                    {
                        printf("post added\n");
                    }
                    else
                    {
                        printf("post didn't add\n");
                    }
                }
                else
                {
                    printf("you haven't logged in\n");
                }
                break;
            case 6:/*info*/
                if (status_login == 1)
                {
                    status = info(current_account, MY_ACCOUNT_INFO);
                }
                else
                {
                    printf("you haven't logged in!\n");
                }
                break;
            case 7:/*like*/
                if (status_login == 1)
                {
                    status = like(head, instruction, current_account);
                    if (status == 1)
                    {
                        printf("your chosen post was liked successfully!\n");
                    }
                    else
                    {
                        printf("like process failed!\n");
                    }
                }
                else
                {
                    printf("you haven't logged in!\n");
                }
                free(instruction);
                break;
            case 8:/*delete post*/
                if (status_login == 1)
                {
                    status = delete_post(current_account, instruction);
                    if (status == 1)
                    {
                        printf("post was deleted successfully!\n");
                        free(instruction);
                    }
                    else
                    {
                        printf("deleting post failed\n");
                        free(instruction);
                    }
                }
                else
                {
                    printf("you haven't logged in!\n");
                }
                break;
            case -1:/*instruction wasn't same as any of them*/
                printf("wrong input\n");
                break;
            case 9:/*exit*/
                proccess = 0;
                break;
            case 10:/*list of users*/
                show_list_users(head);
                break;
            default:
                printf("something wrong has happened!\n");
                break;
            }
        }
        else
        {
            printf("error\n");
        }
        output_accounts(head);/*output accounts*/
        if (num_posts != 0)
        {
            output_posts(head);/*output posts*/
        }
    }

    return 0;
}
