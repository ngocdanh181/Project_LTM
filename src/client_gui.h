#ifndef __CLIENT_GUI_H__
#define __CLIENT_GUI_H__

#include <gtk/gtk.h>
#include <gtk/gtkx.h>

#define TEXT_SIZE 4096
#define NEWLINE "\n"
#define SPLITER ": "
#define HELLO_USER_MSG "Hello, "
#define MYSELF_INDICATOR "You"
#define GROUP_NAME_INDICATOR "Group Name:"
#define GROUP_MEM_NUMBER_INDICATOR "Number of members: "
#define GROUP_MEM_USERNAME_INDICATOR "Member username is: "
#define DEFAULT_CUR_CHAT_LABEL "#none#"

#define INCORRECT_ACC_NOTIF "Login failed!\nUsername or password is incorrect."
#define SIGNED_IN_ACC_NOTIF "Login failed!\nThe account has been logged in by someone else."
#define INVALID_RECEIVER_NOTIF "Failed!\nThe recipient is not online or does not exist."
#define MAKE_GROUP_SUCC_NOTIF "Successfully created new room!\nYour new room name is: "
#define GROUP_NOT_FOUND_NOTIF "Failed to enter room!\n"
#define NOT_IN_GROUP_ROOM_NOTIF "Failed!\nYou are not in any room"
#define INVITE_MYSELF_NOTIF "Failed!\nCannot invite yourself to the group."
#define USER_NOT_FOUND_NOTIF "Failed!\nUser is not online or does not exist."
#define FULL_MEM_NOTIF "Failed!\nThe room's member limit has been reached. Cannot invite more."
#define IS_MEM_NOTIF "Failed!\nThe person you invited is already a member of the group."
#define INVITE_FRIEND_SUCC_NOTIF "Success!\nUser \"%s\" is now a member of the room \"%s\"."
#define INVITE_FRIEND_NOTIF "Attention!\nUser \"%s\" has added you to the room \"%s\"."
#define LEAVE_GROUP_SUCC_NOTIF "Successfully left the room!"
#define NEW_MESSAGES_NOTIF "------------New Messages------------"


//* builder for loading views
GtkBuilder *builder;




//* login window widgets
GtkWidget *login_window;
GtkWidget *login_fixed;
GtkWidget *login_acc_entry;
GtkWidget *login_pwd_entry;
GtkWidget *login_btn;
GtkWidget *login_exit_btn;

//* main window widgets
GtkWidget *main_window;
GtkWidget *main_fixed;
GtkWidget *online_sw;
GtkWidget *online_tv;
GtkWidget *group_sw;
GtkWidget *group_tv;
GtkWidget *private_chat_btn;
GtkWidget *group_chat_btn;
GtkWidget *refresh_list_btn;
GtkWidget *cur_user_label;
GtkWidget *logout_btn;
GtkWidget *group_invite_btn;
GtkWidget *group_info_btn;
GtkWidget *group_leave_btn;
GtkWidget *cur_chat_label;
GtkWidget *recv_msg_sw;
GtkWidget *recv_msg_tv;
GtkWidget *send_entry;
GtkWidget *send_btn;
GtkWidget *start_btn;

//* receiver username dialog
GtkWidget *receiver_username_dialog;
GtkWidget *receiver_username_box;
GtkWidget *receiver_username_entry;
GtkWidget *receiver_username_btn_box;
GtkWidget *receiver_username_confirm_btn;
GtkWidget *receiver_username_exit_btn;

//* join group dialog
GtkWidget *join_group_dialog;
GtkWidget *join_group_box;
GtkWidget *join_group_entry;
GtkWidget *join_group_btn_box;
GtkWidget *join_group_join_btn;
GtkWidget *join_group_create_btn;
GtkWidget *join_group_exit_btn;

//* invite to group dialog
GtkWidget *invite_to_group_dialog;
GtkWidget *invite_to_group_box;
GtkWidget *invite_to_group_entry;
GtkWidget *invite_to_group_btn_box;
GtkWidget *invite_to_group_confirm_btn;
GtkWidget *invite_to_group_exit_btn;

//* group info dialog
GtkWidget *group_info_dialog;
GtkWidget *group_info_box;
GtkWidget *group_info_sw;
GtkWidget *group_info_tv;
GtkWidget *group_info_btn_box;
GtkWidget *group_info_confirm_btn;

GtkWidget *game;
GtkWidget *game_interface;
GtkWidget *question;
GtkWidget *answerA;
GtkWidget *answerB;
GtkWidget *answerC;
GtkWidget *question1;

//* signal handlers
void on_login_btn_clicked(GtkButton *btn, gpointer data);
void on_login_exit_btn_clicked(GtkButton *btn, gpointer data);

void on_logout_btn_clicked(GtkButton *btn, gpointer data);
void on_refresh_list_btn_clicked(GtkButton *btn, gpointer data);
void on_private_chat_btn_clicked(GtkButton *btn, gpointer data);
void on_group_chat_btn_clicked(GtkButton *btn, gpointer data);
void on_group_invite_btn_clicked(GtkButton *btn, gpointer data);
void on_group_info_btn_clicked(GtkButton *btn, gpointer data);
void on_group_leave_btn_clicked(GtkButton *btn, gpointer data);
void on_send_btn_clicked(GtkButton *btn, gpointer data);
void on_start_btn_clicked(GtkButton *btn,gpointer data);
void on_answerA_btn_clicked(GtkButton *button, gpointer data);
void on_answerB_btn_clicked(GtkButton *button, gpointer data);
void on_answerC_btn_clicked(GtkButton *button, gpointer data);

void on_receiver_username_confirm_btn_clicked(GtkButton *btn, gpointer data);

void on_join_group_create_btn_clicked(GtkButton *btn, gpointer data);
void on_join_group_join_btn_clicked(GtkButton *btn, gpointer data);

void on_invite_to_group_confirm_btn_clicked(GtkButton *btn, gpointer data);

//* utility functions
void view_chat_history();
void see_chat(Package *pkg);

void scroll_window_to_bottom(GtkScrolledWindow *sw);

void insert_to_textview(GtkTextView *tv, gchar *text);
void delete_textview_content(GtkTextView *tv);
void delete_lastline_textview(GtkTextView *tv);

void notif_dialog(GtkWindow *parent, gchar *message);

void show_login_window(int *client_socket_pt);
void show_main_window(int *client_socket_pt);
void show_receiver_username_dialog(int *client_socket_pt);
void show_join_group_dialog(int *client_socket_pt);
void show_invite_to_group_dialog(int *client_socket_pt);
void show_group_info_dialog();
void start_game_interface(Package *pkg);


gpointer recv_handler1(gpointer data);
gpointer recv_handler(gpointer data);
gboolean recv_show_user(gpointer data);
gboolean recv_show_group(gpointer data);
gboolean recv_err_invalid_receiver(gpointer data);
gboolean recv_msg_sent_succ(gpointer data);
gboolean recv_private_chat(gpointer data);
gboolean recv_make_group_succ(gpointer data);
gboolean recv_join_group_succ(gpointer data);
gboolean recv_err_group_not_found(gpointer data);
gboolean recv_err_invite_myself(gpointer data);
gboolean recv_err_user_not_found(gpointer data);
gboolean recv_err_full_mem(gpointer data);
gboolean recv_err_is_mem(gpointer data);
gboolean recv_invite_friend_succ(gpointer data);
gboolean recv_invite_friend(gpointer data);
gboolean recv_group_chat(gpointer data);
gboolean recv_show_group_info_start(gpointer data);
gboolean recv_show_group_info_end(gpointer data);
gboolean recv_show_group_name(gpointer data);
gboolean recv_show_group_mem_number(gpointer data);
gboolean recv_show_group_mem_username(gpointer data);
gboolean recv_leave_group_succ(gpointer data);
gboolean recv_start_game(gpointer data);
gboolean update_question_ui(gpointer data);

#endif
