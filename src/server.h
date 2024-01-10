#ifndef __SERVER_H__
#define __SERVER_H__

#include "network.h"
#include "db.h"
#include "error.h"
#include "account_manager.h"

#include "rsa.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define MAX_USER 1024
#define MAX_GROUP 10
#define NULL_STRING "#NULL_STRING#"
#define SERVER_SYSTEM_USERNAME "#server_system#"
#define GROUP_NAME_SIZE 30

typedef struct Active_user_ {
    char username[USERNAME_SIZE]; 
    int socket; 
    int group_id[MAX_GROUP]; 
} Active_user;

//* Group
typedef struct Member_{
    char username[USERNAME_SIZE]; 
    int socket; 
} Member;

typedef struct Group_ {
    Member group_member[MAX_USER]; 
    int curr_num; 
    char group_name[GROUP_NAME_SIZE]; 
} Group;

typedef struct public_key_users_ {
    char username[USERNAME_SIZE];
    struct public_key_class public_key[1];
}Public_key_users;

void send_public_key(int client_socket, char* receiver);
void save_public_key(char* sender, char* msg);

int create_listen_socket();

int accept_conn(int listen_socket);

void make_server();

void *pre_login_srv(void *param);

void handle_login(int conn_socket, Account *acc_list);

int search_user(int conn_socket);

void sv_user_use(int conn_socket);

void sv_active_user(int conn_socket, Package *pkg);

void sv_private_chat(int conn_socket, Package *pkg);

void sv_chat_all(int conn_socket, Package *pkg);

void sv_group_chat_init(int conn_socket, Package *pkg);

void sv_show_group(int conn_socket, Package *pkg);

void sv_new_group(int conn_socket, Package *pkg);

int sv_add_group_user(Active_user *user, int group_id);

int sv_leave_group_user(Active_user *user, int group_id);

int sv_add_user(Active_user user, Group *group);

void sv_join_group(int conn_socket, Package *pkg);

int  sv_search_id_group(Group group[],Active_user user, char *group_name);

int  sv_search_id_user(Active_user user[], char *user_name);

int  sv_search_id_user_group(Group group, char *user_name);

void sv_invite_friend(int conn_socket, Package *pkg);

void sv_group_chat(int conn_socket, Package *pkg);

void handle_start_activity(int conn_socket, Package *pkg);

void send_start_activity_to_group(Group *group, Package *pkg);

void get_next_question(int conn_socket, Package *pkg); 

void sv_show_group_info(int conn_socket, Package *pkg);

void sv_leave_group(int conn_socket, Package *pkg);

void sv_update_port_group(Active_user *user, Group *group);

void print_members(Group group);

int check_user_in_group(Active_user user, int group_id);

void sv_logout(int conn_socket, Package *pkg);

#endif
