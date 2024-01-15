#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "account_manager.h"
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sqlite3.h>
#include <string.h>


#define MSG_SIZE 2048 
#define MAX_SQL_SIZE 3072
// chung
// server
#define LOGIN_SUCC 101 
#define INCORRECT_ACC 102 
#define SIGNED_IN_ACC 103 
#define RECV_SUCC 104 
// client
#define LOGIN_REQ 201 
#define QUIT_REQ 202 

#define MSG_SENT_SUCC 301
#define END_CHAT 302

#define SHOW_USER 401
#define CHAT_ALL 403
#define LOG_OUT 404

#define GROUP_CHAT_INIT 405
#define SHOW_GROUP 406
#define NEW_GROUP  407
#define MSG_MAKE_GROUP_SUCC 408
#define MSG_MAKE_GROUP_ERR 409
#define JOIN_GROUP 410
#define JOIN_GROUP_SUCC 411
#define HANDEL_GROUP_MESS 412
#define INVITE_FRIEND 413
#define INVITE_FRIEND_SUCC 414
#define GROUP_CHAT 415
#define GROUP_INFO 416
#define SHOW_GROUP_INFO_START 417
#define SHOW_GROUP_NAME 418
#define SHOW_GROUP_MEM_NUMBER 419
#define SHOW_GROUP_MEM_USERNAME 420
#define SHOW_GROUP_INFO_END 421
#define LEAVE_GROUP 422
#define LEAVE_GROUP_SUCC 423
#define START_GAME 424 
#define QUESTION_2 425 
#define NEXT_QUESTION 426
#define NEXT_QUESTION_REQ2 427
#define NEXT_QUESTION_REQ3 428
#define SEND_QUESTION 429
#define END_GAME 430 
#define SHOW_RANK 431 

#define PRIVATE_CHAT 501
#define SEND_PUBLIC_KEY 502
#define SEND_PUBLIC_KEY_REQ 503
#define RECV_PUB_KEY_SUCCESS 504
#define NO_PUBLIC_KEY -504

#define TESTING_MSG "#sys_testing#"

//* Cau truc tap tin
typedef struct Package_ {
    char msg[MSG_SIZE]; 
    long long encrypted_msg[MSG_SIZE]; 
    char sender[USERNAME_SIZE]; 
    char receiver[USERNAME_SIZE]; 
    int group_id; 
    int ctrl_signal; 
    char question[USERNAME_SIZE];
    int answers[3];               
    int correct_index;
    int score;
} Package;


#endif
