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
            fprintf(fp, "%s %s %d\n", acc->username, acc->password, acc->status);
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

    if (fp) {
        while (!feof(fp)) {
            fscanf(fp, "%s", username);
            fscanf(fp, "%s", password);
            fscanf(fp, "%d", &status);

            if (strlen(username) == 0) {
                continue;
            }

            acc = (Account *) malloc(sizeof(Account));
            strcpy(acc->username, username);
            strcpy(acc->password, password);
            acc->status = status;
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
