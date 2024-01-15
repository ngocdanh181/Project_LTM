#ifndef __ACCOUNT_MANAGER_H__
#define __ACCOUNT_MANAGER_H__

#define USERNAME_SIZE 256
#define PASSWORD_SIZE 256
#define MAX_CONSECUTIVE_FAIL 3

typedef struct Account_ {
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
    int status;
    int score;
    int consecutive_failed_sign_in;
    int is_signed_in;
    struct Account_ *next;
} Account;

typedef struct Question_{
	char question[USERNAME_SIZE];
	int answer_a;
	int answer_b;
	int answer_c;
	int correct_index; 
	struct Question_ *next;
}Question;
 

void write_to_file(Account *list);
Account* read_account_list();
void write_to_file1(Question*list1);
Question* read_question_list();
void get_top_5_players(Account *acc_list, char *msg);

Account* find_account(Account *list, char *username);
int is_active_account(Account *list, char *username);

#endif
