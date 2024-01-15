/**
 * Account manager
*/
#include "account_manager.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_to_file(Account *list) {

    FILE *fp = fopen("../assets/account.txt", "w");

    if (fp) {
        Account *acc = list;
        while (acc) {
            fprintf(fp, "%s %s %d %d\n", acc->username, acc->password, acc->status, acc->score);
            acc = acc->next;
        }

        fclose(fp);
    } else {
        report_err(ERR_OPEN_FILE);
        exit(0);
    }
}

Account* read_account_list() {

    FILE *fp = fopen("../assets/account.txt", "r");

    Account *list = NULL;
    Account *prev_acc, *acc;

    char username[USERNAME_SIZE + 1];
    char password[PASSWORD_SIZE + 1];
    int status;
    int score;

    if (fp) {
        while (!feof(fp)) {
            fscanf(fp, "%s", username);
            fscanf(fp, "%s", password);
            fscanf(fp, "%d", &status);
            fscanf(fp, "%d", &score);

            if (strlen(username) == 0) {
                continue;
            }

            acc = (Account *) malloc(sizeof(Account));
            strcpy(acc->username, username);
            strcpy(acc->password, password);
            acc->status = status;
            acc->score = score;
            acc->consecutive_failed_sign_in = 0;
            acc->is_signed_in = 0;

            if (list == NULL) {
                list = acc;
                prev_acc = acc;
            } else {
                prev_acc->next = acc;
                prev_acc = acc;
            }

            strcpy(username, "");
            strcpy(password, "");
        }

        fclose(fp);
    } else {
        report_err(ERR_OPEN_FILE);
        exit(0);
    }

    return list;
}


void get_top_5_players(Account *acc_list, char *msg) {
    int account_count = 0;
    Account *current = acc_list;
    while (current != NULL) {
        account_count++;
        current = current->next;
    }

    if (account_count == 0) {
        strcpy(msg, "Have not anyone.");
        return;
    }

    Account accounts[account_count];
    current = acc_list;
    for (int i = 0; i < account_count; i++) {
        accounts[i] = *current;
        current = current->next;
    }

    for (int i = 0; i < account_count - 1; i++) {
        for (int j = 0; j < account_count - i - 1; j++) {
            if (accounts[j].score < accounts[j + 1].score) {
                Account temp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = temp;
            }
        }
    }

    int top_users_count = 5 < account_count ? 5 : account_count;
    char line[512];
    strcpy(msg, "Top 5 users score:\n");
    for (int i = 0; i < top_users_count; i++) {
        sprintf(line, "%d- %s - %d Score\n",i+1, accounts[i].username, accounts[i].score);
        strcat(msg, line);
    }
}



void write_to_file1(Question *list1) {

    FILE *fp = fopen("../assets/question.txt", "w");

    if (fp) {
        Question *que = list1;
        while (que) {
            fprintf(fp, "%s %d %d %d %d\n", que->question, que->answer_a, que->answer_b,que->answer_c,que->correct_index);
            que = que->next;
        }

        fclose(fp);
    } else {
        report_err(ERR_OPEN_FILE);
        exit(0);
    }
}

Question* read_question_list() {

    FILE *fp = fopen("../assets/question.txt", "r");

    Question *list1 = NULL;
    Question *prev_que, *que;

    char question[USERNAME_SIZE + 1];
    int answer_a, answer_b, answer_c;
    int correct_index;

    if (fp) {
        while (!feof(fp)) {
            fscanf(fp, "%s", question);
            fscanf(fp, "%d", &answer_a);
            fscanf(fp, "%d", &answer_b);
			fscanf(fp, "%d", &answer_c);
			fscanf(fp, "%d", &correct_index);

            que = (Question *) malloc(sizeof(Question));
            strcpy(que->question, question);
            que->answer_a= answer_a;
            que->answer_b= answer_b;
            que->answer_c= answer_c;
            que->correct_index= correct_index;

            if (list1 == NULL) {
                list1 = que;
                prev_que = que;
            } else {
                prev_que->next = que;
                prev_que = que;
            }

            strcpy(question, "");
        }

        fclose(fp);
    } else {
        report_err(ERR_OPEN_FILE);
        exit(0);
    }

    return list1;
}


Account* find_account(Account *list, char *username) {

    Account *acc = list;

    while (acc) {
        if (strcmp(acc->username, username) == 0) {
            return acc;
        }
        acc = acc->next;
    }

    return NULL;
}


int is_active_account(Account *list, char *username) {
    Account *acc = find_account(list, username);
    if (acc) {
        return acc->status;
    }
    return 1;
}
