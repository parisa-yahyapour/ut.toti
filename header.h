#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
typedef struct post_struct
{
    char *post_id;
    int id;
    char *text;
    int like;
    struct post_struct *next;
}post;
typedef struct users
{
    char *username;
    char *password;
    struct users *next;
    int *liked_posts_id;
    int num_liked_posts;
    int num_user_posts;
    post *first_post;
}account;
char *read_instruction(int *len_instruction);
char *recognize_operation(char *instruction, int len_instruction, int *code_operation);
int signup(account *head, char *instrution);
void show_list_users(account *head);
int login(account *head, int *status_login, char *instruction, account **current_account);
int logout(account **current_account, int *status_login);
int search(account *head, char *instruction);
int add_post(account *current_account, char *instruction, int *num_posts);
int info(account *current_account, int status_account);
int like(account *head, char *instruction, account *current_account);
int delete_post(account *current_account, char *instruction);
int output_accounts(account *head);
int output_posts(account *head);
