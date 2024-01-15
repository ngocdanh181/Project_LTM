#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

char my_username[USERNAME_SIZE];
char curr_group_name[GROUP_NAME_SIZE];
int curr_group_id = -1;
int join_succ = 0;

char *PRIME_SOURCE_FILE = "../assets/primes.txt";

struct public_key_class my_pub[1];
struct private_key_class my_priv[1];

Public_key_users user_pub[1];

int doing = 0;

int connect_to_server()
{

    int client_socket;
    struct sockaddr_in server_addr;

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        report_err(ERR_SOCKET_INIT);
        exit(0);
    }

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        report_err(ERR_CONNECT_TO_SERVER);
        exit(0);
    }

    return client_socket;
}


int login(int client_socket, char *username, char *password)
{

    Package pkg;

    strcpy(pkg.msg, username);
    send(client_socket, &pkg, sizeof(pkg), 0);

    recv(client_socket, &pkg, sizeof(pkg), 0);

    strcpy(pkg.msg, password);
    send(client_socket, &pkg, sizeof(pkg), 0);

    recv(client_socket, &pkg, sizeof(pkg), 0);
    // sleep(1);
    if (pkg.ctrl_signal == LOGIN_SUCC){
        strcpy(my_username, username);
        if(my_priv->exponent == 0)
            rsa_gen_keys(my_pub, my_priv, PRIME_SOURCE_FILE);
        
        printf("Private Key:\n Modulus: %lld\n Exponent: %lld\n", (long long)my_priv->modulus, (long long)my_priv->exponent);
        printf("Public Key:\n Modulus: %lld\n Exponent: %lld\n\n", (long long)my_pub->modulus, (long long)my_pub->exponent);
        // pubkey_count = 0;
        send_my_public_key(client_socket);
    }
    return pkg.ctrl_signal;
}

void send_my_public_key(int client_socket) {
    Package pkg;
    pkg.ctrl_signal = SEND_PUBLIC_KEY;
    strcpy(pkg.sender, my_username);
    memcpy(pkg.msg, &my_pub->modulus, sizeof(my_pub->modulus));
    memcpy(pkg.msg + sizeof my_pub->modulus, &my_pub->exponent, sizeof(my_pub->exponent));
    send(client_socket, &pkg, sizeof(pkg), 0);
}

void receive_public_key(int client_socket, Package* pkg) {
    strcpy(user_pub->username, pkg->receiver);
    user_pub->public_key->exponent = ((struct public_key_class*)pkg->msg)->exponent;
    user_pub->public_key->modulus = ((struct public_key_class*)pkg->msg)->modulus;
    printf("receive pubkey of %s: %lld %lld\n", user_pub->username, (long long)user_pub->public_key->exponent, (long long)user_pub->public_key->modulus);
}

int check_public_key(int client_socket, char* username) {
    // printf("Key of %s, require %s\n", user_pub->username, username);
    if(strcmp(user_pub->username, username) == 0) return 1;
    else {
        Package pkg;
        strcpy(pkg.sender, my_username);
        strcpy(pkg.receiver, username);
        pkg.ctrl_signal = SEND_PUBLIC_KEY_REQ;
        send(client_socket, &pkg, sizeof(pkg), 0);
        return 0;
    }
}


void see_active_user(int client_socket)
{
    Package pkg;
    pkg.ctrl_signal = SHOW_USER;
    send(client_socket, &pkg, sizeof(pkg), 0);

}

void make_done(int msg) {
    doing = msg;
}

int check_receiver(int client_socket, char* receiver) {
    int res;
    Package pkg;
    
    strcpy(pkg.receiver, receiver);
    strcpy(pkg.sender, my_username);
    strcpy(pkg.msg, TESTING_MSG);
    pkg.ctrl_signal = PRIVATE_CHAT;
    doing = 0;
    send(client_socket, &pkg, sizeof(pkg), 0);
    printf("ccc\n");
    while(!doing);
    printf("dd\n");
    return doing;
    // sleep(1);
}

int private_chat(int client_socket, char *receiver, char *msg)
{
    Package pkg;
    strcpy(pkg.receiver, receiver);
    strcpy(pkg.sender, my_username);
    printf("check key\n");
    int check = check_public_key(client_socket, receiver);
    if(check == 0) {
        user_pub->public_key->exponent = 0;
        printf("nnn\n");
        while( !user_pub->public_key->exponent);
        printf("mmm\n");
    }

    printf("Start chatting with %s\n", receiver);
    
    pkg.ctrl_signal = PRIVATE_CHAT;

    if(strcmp(msg, TESTING_MSG) == 0)
        strcpy(pkg.msg, msg);
    else {
        long long *encrypted = rsa_encrypt(msg, strlen(msg), user_pub->public_key);
        memset(pkg.encrypted_msg, '\0', sizeof(pkg.encrypted_msg));
        int i = 0;
        printf("Encrypted!\n");
        // printf("%s %ld\n", msg, strlen(msg));
        for(i = 0; i < strlen(msg); i++) {
            pkg.encrypted_msg[i] = (long long)encrypted[i];
            printf("%lld ", (long long)pkg.encrypted_msg[i]);
        }
        printf("\n");
        i = 0;
        while (pkg.encrypted_msg[i] != 0) {
            printf("%lld\n", pkg.encrypted_msg[i]);
            i++;
        }
        printf("\n");
    }
    send(client_socket, &pkg, sizeof(pkg), 0);
    printf("sent chat\n");

        // sleep(1);
    // }
}

void chat_all(int client_socket)
{
    Package pkg;
    pkg.ctrl_signal = CHAT_ALL;
    strcpy(pkg.sender, my_username);
    char msg[MSG_SIZE];
    while (1)
    {
        printf("Message(leave blank to exit group chat): \n");
        fgets(msg, MSG_SIZE, stdin);
        msg[strlen(msg) - 1] = '\0';
        if (strlen(msg) == 0)
        {
            break;
        }

        strcpy(pkg.msg, msg);
        send(client_socket, &pkg, sizeof(pkg), 0);

        // sleep(1);
    }
}

char* group_msg_encrypt(char* msg, char* key) {

}

char* group_msg_decrypt(char* msg, char* key) {

}

// hien thi nhom hien tai
void show_group(int client_socket)
{
    Package pkg;
    pkg.ctrl_signal = SHOW_GROUP;
    send(client_socket, &pkg, sizeof(pkg), 0);
    // sleep(1);
}

// tao group moi
void new_group(int client_socket)
{
    Package pkg;
    pkg.ctrl_signal = NEW_GROUP;
    send(client_socket, &pkg, sizeof(pkg), 0);
}

// vao group cua minh

void join_group(int client_socket, char *group_name)
{
    // show_group(client_socket);
    // sleep(1);
    Package pkg;
    pkg.ctrl_signal = JOIN_GROUP;
    strcpy(pkg.sender, my_username);
    strcpy(pkg.msg, group_name);
    send(client_socket, &pkg, sizeof(pkg), 0);
}



// moi ban
void invite_friend(int client_socket, char *friend_username)
{
    // see_active_user(client_socket);
    Package pkg;

    strcpy(pkg.sender, my_username);
    strcpy(pkg.receiver, friend_username);
    strcpy(pkg.msg, my_username);
    strcat(pkg.msg, " Added you to ");
    strcat(pkg.msg, curr_group_name);
    pkg.ctrl_signal = INVITE_FRIEND;
    pkg.group_id = curr_group_id;
    send(client_socket, &pkg, sizeof(pkg), 0);
}

// chat trong nhom
void group_chat(int client_socket, char *msg)
{
    Package pkg;
    pkg.ctrl_signal = GROUP_CHAT;
    pkg.group_id = curr_group_id;
    strcpy(pkg.sender, my_username);

        strcpy(pkg.msg, msg);
        save_chat(&pkg);
        send(client_socket, &pkg, sizeof(pkg), 0);

}

// hien thi thong tin phong
void show_group_info(int client_socket)
{
    Package pkg;
    pkg.ctrl_signal = GROUP_INFO;
    pkg.group_id = curr_group_id;
    send(client_socket, &pkg, sizeof(pkg), 0);
}
// Thoat nhom
void leave_group(int client_socket)
{
    Package pkg;
    pkg.ctrl_signal = LEAVE_GROUP;
    pkg.group_id = curr_group_id;
    strcpy(pkg.sender, my_username);
    // curr_group_id = -1;
    send(client_socket, &pkg, sizeof(pkg), 0);
}

