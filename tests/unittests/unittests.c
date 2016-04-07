#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <sys/stat.h>

#include "config.h"
#include "chat_session.h"
#include "helpers.h"
#include "test_autocomplete.h"
#include "test_chat_session.h"
#include "test_common.h"
#include "test_contact.h"
#include "test_cmd_connect.h"
#include "test_cmd_account.h"
#include "test_cmd_rooms.h"
#include "test_cmd_sub.h"
#include "test_cmd_statuses.h"
#include "test_cmd_otr.h"
#include "test_cmd_pgp.h"
#include "test_jid.h"
#include "test_parser.h"
#include "test_roster_list.h"
#include "test_preferences.h"
#include "test_server_events.h"
#include "test_cmd_alias.h"
#include "test_cmd_bookmark.h"
#include "test_cmd_join.h"
#include "test_muc.h"
#include "test_cmd_roster.h"
#include "test_cmd_disconnect.h"
#include "test_form.h"

int main(int argc, char* argv[]) {
    const UnitTest all_tests[] = {

        unit_test(replace_one_substr),
        unit_test(replace_one_substr_beginning),
        unit_test(replace_one_substr_end),
        unit_test(replace_two_substr),
        unit_test(replace_char),
        unit_test(replace_when_none),
        unit_test(replace_when_match),
        unit_test(replace_when_string_empty),
        unit_test(replace_when_string_null),
        unit_test(replace_when_sub_empty),
        unit_test(replace_when_sub_null),
        unit_test(replace_when_new_empty),
        unit_test(replace_when_new_null),
        unit_test(compare_win_nums_less),
        unit_test(compare_win_nums_equal),
        unit_test(compare_win_nums_greater),
        unit_test(compare_0s_equal),
        unit_test(compare_0_greater_than_1),
        unit_test(compare_1_less_than_0),
        unit_test(compare_0_less_than_11),
        unit_test(compare_11_greater_than_0),
        unit_test(compare_0_greater_than_9),
        unit_test(compare_9_less_than_0),
        unit_test(next_available_when_only_console),
        unit_test(next_available_3_at_end),
        unit_test(next_available_9_at_end),
        unit_test(next_available_0_at_end),
        unit_test(next_available_2_in_first_gap),
        unit_test(next_available_9_in_first_gap),
        unit_test(next_available_0_in_first_gap),
        unit_test(next_available_11_in_first_gap),
        unit_test(next_available_24_first_big_gap),
        unit_test(test_online_is_valid_resource_presence_string),
        unit_test(test_chat_is_valid_resource_presence_string),
        unit_test(test_away_is_valid_resource_presence_string),
        unit_test(test_xa_is_valid_resource_presence_string),
        unit_test(test_dnd_is_valid_resource_presence_string),
        unit_test(test_available_is_not_valid_resource_presence_string),
        unit_test(test_unavailable_is_not_valid_resource_presence_string),
        unit_test(test_blah_is_not_valid_resource_presence_string),
        unit_test(test_p_sha1_hash1),
        unit_test(test_p_sha1_hash2),
        unit_test(test_p_sha1_hash3),
        unit_test(test_p_sha1_hash4),
        unit_test(test_p_sha1_hash5),
        unit_test(test_p_sha1_hash6),
        unit_test(test_p_sha1_hash7),
        unit_test(utf8_display_len_null_str),
        unit_test(utf8_display_len_1_non_wide),
        unit_test(utf8_display_len_1_wide),
        unit_test(utf8_display_len_non_wide),
        unit_test(utf8_display_len_wide),
        unit_test(utf8_display_len_all_wide),
        unit_test(strip_quotes_does_nothing_when_no_quoted),
        unit_test(strip_quotes_strips_first),
        unit_test(strip_quotes_strips_last),
        unit_test(strip_quotes_strips_both),

        unit_test(clear_empty),
        unit_test(reset_after_create),
        unit_test(find_after_create),
        unit_test(get_after_create_returns_null),
        unit_test(add_one_and_complete),
        unit_test(add_two_and_complete_returns_first),
        unit_test(add_two_and_complete_returns_second),
        unit_test(add_two_adds_two),
        unit_test(add_two_same_adds_one),
        unit_test(add_two_same_updates),

        unit_test(create_jid_from_null_returns_null),
        unit_test(create_jid_from_empty_string_returns_null),
        unit_test(create_jid_from_full_returns_full),
        unit_test(create_jid_from_full_returns_bare),
        unit_test(create_jid_from_full_returns_resourcepart),
        unit_test(create_jid_from_full_returns_localpart),
        unit_test(create_jid_from_full_returns_domainpart),
        unit_test(create_jid_from_full_nolocal_returns_full),
        unit_test(create_jid_from_full_nolocal_returns_bare),
        unit_test(create_jid_from_full_nolocal_returns_resourcepart),
        unit_test(create_jid_from_full_nolocal_returns_domainpart),
        unit_test(create_jid_from_full_nolocal_returns_null_localpart),
        unit_test(create_jid_from_bare_returns_null_full),
        unit_test(create_jid_from_bare_returns_null_resource),
        unit_test(create_jid_from_bare_returns_bare),
        unit_test(create_jid_from_bare_returns_localpart),
        unit_test(create_jid_from_bare_returns_domainpart),
        unit_test(create_room_jid_returns_room),
        unit_test(create_room_jid_returns_nick),
        unit_test(create_with_slash_in_resource),
        unit_test(create_with_at_in_resource),
        unit_test(create_with_at_and_slash_in_resource),
        unit_test(create_full_with_trailing_slash),
        unit_test(returns_fulljid_when_exists),
        unit_test(returns_barejid_when_fulljid_not_exists),

        unit_test(parse_null_returns_null),
        unit_test(parse_empty_returns_null),
        unit_test(parse_space_returns_null),
        unit_test(parse_cmd_no_args_returns_null),
        unit_test(parse_cmd_with_space_returns_null),
        unit_test(parse_cmd_with_too_few_returns_null),
        unit_test(parse_cmd_with_too_many_returns_null),
        unit_test(parse_cmd_one_arg),
        unit_test(parse_cmd_two_args),
        unit_test(parse_cmd_three_args),
        unit_test(parse_cmd_three_args_with_spaces),
        unit_test(parse_cmd_with_freetext),
        unit_test(parse_cmd_one_arg_with_freetext),
        unit_test(parse_cmd_two_args_with_freetext),
        unit_test(parse_cmd_min_zero),
        unit_test(parse_cmd_min_zero_with_freetext),
        unit_test(parse_cmd_with_quoted),
        unit_test(parse_cmd_with_quoted_and_space),
        unit_test(parse_cmd_with_quoted_and_many_spaces),
        unit_test(parse_cmd_with_many_quoted_and_many_spaces),
        unit_test(parse_cmd_freetext_with_quoted),
        unit_test(parse_cmd_freetext_with_quoted_and_space),
        unit_test(parse_cmd_freetext_with_quoted_and_many_spaces),
        unit_test(parse_cmd_freetext_with_many_quoted_and_many_spaces),
        unit_test(parse_cmd_with_quoted_freetext),
        unit_test(parse_cmd_with_third_arg_quoted_0_min_3_max),
        unit_test(parse_cmd_with_second_arg_quoted_0_min_3_max),
        unit_test(parse_cmd_with_second_and_third_arg_quoted_0_min_3_max),
        unit_test(count_one_token),
        unit_test(count_one_token_quoted_no_whitespace),
        unit_test(count_one_token_quoted_with_whitespace),
        unit_test(count_two_tokens),
        unit_test(count_two_tokens_first_quoted),
        unit_test(count_two_tokens_second_quoted),
        unit_test(count_two_tokens_both_quoted),
        unit_test(get_first_of_one),
        unit_test(get_first_of_two),
        unit_test(get_first_two_of_three),
        unit_test(get_first_two_of_three_first_quoted),
        unit_test(get_first_two_of_three_second_quoted),
        unit_test(get_first_two_of_three_first_and_second_quoted),
        unit_test(parse_options_when_none_returns_empty_hasmap),
        unit_test(parse_options_when_opt1_no_val_sets_error),
        unit_test(parse_options_when_one_returns_map),
        unit_test(parse_options_when_opt2_no_val_sets_error),
        unit_test(parse_options_when_two_returns_map),
        unit_test(parse_options_when_opt3_no_val_sets_error),
        unit_test(parse_options_when_three_returns_map),
        unit_test(parse_options_when_unknown_opt_sets_error),
        unit_test(parse_options_with_duplicated_option_sets_error),

        unit_test(empty_list_when_none_added),
        unit_test(contains_one_element),
        unit_test(first_element_correct),
        unit_test(contains_two_elements),
        unit_test(first_and_second_elements_correct),
        unit_test(contains_three_elements),
        unit_test(first_three_elements_correct),
        unit_test(add_twice_at_beginning_adds_once),
        unit_test(add_twice_in_middle_adds_once),
        unit_test(add_twice_at_end_adds_once),
        unit_test(find_first_exists),
        unit_test(find_second_exists),
        unit_test(find_third_exists),
        unit_test(find_returns_null),
        unit_test(find_on_empty_returns_null),
        unit_test(find_twice_returns_second_when_two_match),
        unit_test(find_five_times_finds_fifth),
        unit_test(find_twice_returns_first_when_two_match_and_reset),
        unit_test(add_contact_with_no_group),
        unit_test(add_contact_with_group),
        unit_test(add_contact_with_two_groups),
        unit_test(add_contact_with_three_groups),
        unit_test(add_contact_with_three_groups_update_adding_two),
        unit_test(add_contact_with_three_groups_update_removing_one),
        unit_test(add_contact_with_three_groups_update_removing_two),
        unit_test(add_contact_with_three_groups_update_removing_three),
        unit_test(add_contact_with_three_groups_update_two_new),
        unit_test(add_remove_contact_groups),
        unit_test(add_contacts_with_different_groups),
        unit_test(add_contacts_with_same_groups),
        unit_test(add_contacts_with_overlapping_groups),
        unit_test(remove_contact_with_remaining_in_group),

        unit_test_setup_teardown(returns_false_when_chat_session_does_not_exist,
            init_chat_sessions,
            close_chat_sessions),
        unit_test_setup_teardown(creates_chat_session_on_recipient_activity,
            init_chat_sessions,
            close_chat_sessions),
        unit_test_setup_teardown(replaces_chat_session_on_recipient_activity_with_different_resource,
            init_chat_sessions,
            close_chat_sessions),
        unit_test_setup_teardown(removes_chat_session,
            init_chat_sessions,
            close_chat_sessions),

        unit_test_setup_teardown(cmd_connect_shows_message_when_disconnecting,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_shows_message_when_connecting,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_shows_message_when_connected,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_shows_message_when_undefined,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_when_no_account,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_fail_message,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_lowercases_argument,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_asks_password_when_not_in_account,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_shows_usage_when_no_server_value,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_shows_message_when_connecting_with_account,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_connects_with_account,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_shows_usage_when_server_no_port_value,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_shows_usage_when_no_port_value,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_shows_usage_when_port_no_server_value,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_shows_message_when_port_0,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_shows_message_when_port_minus1,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_shows_message_when_port_65536,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_shows_message_when_port_contains_chars,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_with_server_when_provided,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_with_port_when_provided,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_with_server_and_port_when_provided,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_shows_usage_when_server_provided_twice,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_shows_usage_when_port_provided_twice,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_shows_usage_when_invalid_first_property,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_connect_shows_usage_when_invalid_second_property,
            load_preferences,
            close_preferences),

        unit_test(cmd_rooms_shows_message_when_disconnected),
        unit_test(cmd_rooms_shows_message_when_disconnecting),
        unit_test(cmd_rooms_shows_message_when_connecting),
        unit_test(cmd_rooms_shows_message_when_started),
        unit_test(cmd_rooms_shows_message_when_undefined),
        unit_test(cmd_rooms_uses_account_default_when_no_arg),
        unit_test(cmd_rooms_arg_used_when_passed),

        unit_test(cmd_account_shows_usage_when_not_connected_and_no_args),
        unit_test(cmd_account_shows_account_when_connected_and_no_args),
        unit_test(cmd_account_list_shows_accounts),
        unit_test(cmd_account_show_shows_usage_when_no_arg),
        unit_test(cmd_account_show_shows_message_when_account_does_not_exist),
        unit_test(cmd_account_show_shows_account_when_exists),
        unit_test(cmd_account_add_shows_usage_when_no_arg),
        unit_test(cmd_account_add_adds_account),
        unit_test(cmd_account_enable_shows_usage_when_no_arg),
        unit_test(cmd_account_enable_enables_account),
        unit_test(cmd_account_enable_shows_message_when_account_doesnt_exist),
        unit_test(cmd_account_disable_shows_usage_when_no_arg),
        unit_test(cmd_account_disable_disables_account),
        unit_test(cmd_account_disable_shows_message_when_account_doesnt_exist),
        unit_test(cmd_account_rename_shows_usage_when_no_args),
        unit_test(cmd_account_rename_shows_usage_when_one_arg),
        unit_test(cmd_account_rename_renames_account),
        unit_test(cmd_account_rename_shows_message_when_not_renamed),
        unit_test(cmd_account_set_shows_usage_when_no_args),
        unit_test(cmd_account_set_shows_usage_when_one_arg),
        unit_test(cmd_account_set_shows_usage_when_two_args),
        unit_test(cmd_account_set_shows_message_when_account_doesnt_exist),
        unit_test(cmd_account_set_jid_shows_message_for_malformed_jid),
        unit_test(cmd_account_set_jid_sets_barejid),
        unit_test(cmd_account_set_jid_sets_resource),
        unit_test(cmd_account_set_server_sets_server),
        unit_test(cmd_account_set_resource_sets_resource),
        unit_test(cmd_account_set_resource_sets_resource_with_online_message),
        unit_test(cmd_account_set_password_sets_password),
        unit_test(cmd_account_set_eval_password_sets_eval_password),
        unit_test(cmd_account_set_password_when_eval_password_set),
        unit_test(cmd_account_set_eval_password_when_password_set),
        unit_test(cmd_account_set_muc_sets_muc),
        unit_test(cmd_account_set_nick_sets_nick),
#ifdef HAVE_LIBOTR
        unit_test(cmd_account_show_message_for_missing_otr_policy),
        unit_test(cmd_account_show_message_for_invalid_otr_policy),
        unit_test(cmd_account_set_otr_sets_otr),
#endif
        unit_test(cmd_account_set_status_shows_message_when_invalid_status),
        unit_test(cmd_account_set_status_sets_status_when_valid),
        unit_test(cmd_account_set_status_sets_status_when_last),
        unit_test(cmd_account_set_invalid_presence_string_priority_shows_message),
        unit_test(cmd_account_set_last_priority_shows_message),
        unit_test(cmd_account_set_online_priority_sets_preference),
        unit_test(cmd_account_set_chat_priority_sets_preference),
        unit_test(cmd_account_set_away_priority_sets_preference),
        unit_test(cmd_account_set_xa_priority_sets_preference),
        unit_test(cmd_account_set_dnd_priority_sets_preference),
        unit_test(cmd_account_set_priority_too_low_shows_message),
        unit_test(cmd_account_set_priority_too_high_shows_message),
        unit_test(cmd_account_set_priority_when_not_number_shows_message),
        unit_test(cmd_account_set_priority_when_empty_shows_message),
        unit_test(cmd_account_set_priority_updates_presence_when_account_connected_with_presence),
        unit_test(cmd_account_clear_shows_usage_when_no_args),
        unit_test(cmd_account_clear_shows_usage_when_one_arg),
        unit_test(cmd_account_clear_shows_message_when_account_doesnt_exist),
        unit_test(cmd_account_clear_shows_message_when_invalid_property),

        unit_test(cmd_sub_shows_message_when_not_connected),
        unit_test(cmd_sub_shows_usage_when_no_arg),

        unit_test(contact_in_group),
        unit_test(contact_not_in_group),
        unit_test(contact_name_when_name_exists),
        unit_test(contact_jid_when_name_not_exists),
        unit_test(contact_string_when_name_exists),
        unit_test(contact_string_when_name_not_exists),
        unit_test(contact_string_when_default_resource),
        unit_test(contact_presence_offline),
        unit_test(contact_presence_uses_highest_priority),
        unit_test(contact_presence_chat_when_same_prioroty),
        unit_test(contact_presence_online_when_same_prioroty),
        unit_test(contact_presence_away_when_same_prioroty),
        unit_test(contact_presence_xa_when_same_prioroty),
        unit_test(contact_presence_dnd),
        unit_test(contact_subscribed_when_to),
        unit_test(contact_subscribed_when_both),
        unit_test(contact_not_subscribed_when_from),
        unit_test(contact_not_subscribed_when_no_subscription_value),
        unit_test(contact_not_available),
        unit_test(contact_not_available_when_highest_priority_away),
        unit_test(contact_not_available_when_highest_priority_xa),
        unit_test(contact_not_available_when_highest_priority_dnd),
        unit_test(contact_available_when_highest_priority_online),
        unit_test(contact_available_when_highest_priority_chat),

        unit_test(cmd_statuses_shows_usage_when_bad_subcmd),
        unit_test(cmd_statuses_shows_usage_when_bad_console_setting),
        unit_test(cmd_statuses_shows_usage_when_bad_chat_setting),
        unit_test(cmd_statuses_shows_usage_when_bad_muc_setting),
        unit_test_setup_teardown(cmd_statuses_console_sets_all,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_statuses_console_sets_online,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_statuses_console_sets_none,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_statuses_chat_sets_all,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_statuses_chat_sets_online,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_statuses_chat_sets_none,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_statuses_muc_sets_all,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_statuses_muc_sets_online,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_statuses_muc_sets_none,
            load_preferences,
            close_preferences),

        unit_test_setup_teardown(statuses_console_defaults_to_all,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(statuses_chat_defaults_to_all,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(statuses_muc_defaults_to_all,
            load_preferences,
            close_preferences),

        unit_test_setup_teardown(console_shows_online_presence_when_set_online,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(console_shows_online_presence_when_set_all,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(console_shows_dnd_presence_when_set_all,
            load_preferences,
            close_preferences),
        unit_test(handle_offline_removes_chat_session),
        unit_test(lost_connection_clears_chat_sessions),

        unit_test(cmd_alias_add_shows_usage_when_no_args),
        unit_test(cmd_alias_add_shows_usage_when_no_value),
        unit_test(cmd_alias_remove_shows_usage_when_no_args),
        unit_test(cmd_alias_show_usage_when_invalid_subcmd),
        unit_test_setup_teardown(cmd_alias_add_adds_alias,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_alias_add_shows_message_when_exists,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_alias_remove_removes_alias,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_alias_remove_shows_message_when_no_alias,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_alias_list_shows_all_aliases,
            load_preferences,
            close_preferences),

        unit_test_setup_teardown(test_muc_invites_add, muc_before_test, muc_after_test),
        unit_test_setup_teardown(test_muc_remove_invite, muc_before_test, muc_after_test),
        unit_test_setup_teardown(test_muc_invites_count_0, muc_before_test, muc_after_test),
        unit_test_setup_teardown(test_muc_invites_count_5, muc_before_test, muc_after_test),
        unit_test_setup_teardown(test_muc_room_is_not_active, muc_before_test, muc_after_test),
        unit_test_setup_teardown(test_muc_active, muc_before_test, muc_after_test),

        unit_test(cmd_bookmark_shows_message_when_disconnected),
        unit_test(cmd_bookmark_shows_message_when_disconnecting),
        unit_test(cmd_bookmark_shows_message_when_connecting),
        unit_test(cmd_bookmark_shows_message_when_started),
        unit_test(cmd_bookmark_shows_message_when_undefined),
        unit_test(cmd_bookmark_shows_usage_when_no_args),
        unit_test(cmd_bookmark_list_shows_bookmarks),
        unit_test(cmd_bookmark_add_shows_message_when_invalid_jid),
        unit_test(cmd_bookmark_add_adds_bookmark_with_jid),
        unit_test(cmd_bookmark_add_adds_bookmark_with_jid_nick),
        unit_test(cmd_bookmark_add_adds_bookmark_with_jid_autojoin),
        unit_test(cmd_bookmark_add_adds_bookmark_with_jid_nick_autojoin),
        unit_test(cmd_bookmark_remove_removes_bookmark),
        unit_test(cmd_bookmark_remove_shows_message_when_no_bookmark),

#ifdef HAVE_LIBOTR
        unit_test(cmd_otr_shows_usage_when_no_args),
        unit_test(cmd_otr_shows_usage_when_invalid_subcommand),
        unit_test(cmd_otr_log_shows_usage_when_no_args),
        unit_test(cmd_otr_log_shows_usage_when_invalid_subcommand),
        unit_test_setup_teardown(cmd_otr_log_on_enables_logging,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_otr_log_off_disables_logging,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_otr_redact_redacts_logging,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_otr_log_on_shows_warning_when_chlog_disabled,
            load_preferences,
            close_preferences),
        unit_test_setup_teardown(cmd_otr_log_redact_shows_warning_when_chlog_disabled,
            load_preferences,
            close_preferences),
        unit_test(cmd_otr_libver_shows_libotr_version),
        unit_test(cmd_otr_gen_shows_message_when_not_connected),
        unit_test(cmd_otr_gen_generates_key_for_connected_account),
        unit_test(cmd_otr_gen_shows_message_when_disconnected),
        unit_test(cmd_otr_gen_shows_message_when_undefined),
        unit_test(cmd_otr_gen_shows_message_when_started),
        unit_test(cmd_otr_gen_shows_message_when_connecting),
        unit_test(cmd_otr_gen_shows_message_when_disconnecting),
        unit_test(cmd_otr_myfp_shows_message_when_disconnected),
        unit_test(cmd_otr_myfp_shows_message_when_undefined),
        unit_test(cmd_otr_myfp_shows_message_when_started),
        unit_test(cmd_otr_myfp_shows_message_when_connecting),
        unit_test(cmd_otr_myfp_shows_message_when_disconnecting),
        unit_test(cmd_otr_myfp_shows_message_when_no_key),
        unit_test(cmd_otr_myfp_shows_my_fingerprint),
        unit_test(cmd_otr_theirfp_shows_message_when_in_console),
        unit_test(cmd_otr_theirfp_shows_message_when_in_muc),
        unit_test(cmd_otr_theirfp_shows_message_when_in_private),
        unit_test(cmd_otr_theirfp_shows_message_when_non_otr_chat_window),
        unit_test(cmd_otr_theirfp_shows_fingerprint),
        unit_test(cmd_otr_start_shows_message_when_in_console),
        unit_test(cmd_otr_start_shows_message_when_in_muc),
        unit_test(cmd_otr_start_shows_message_when_in_private),
        unit_test(cmd_otr_start_shows_message_when_already_started),
        unit_test(cmd_otr_start_shows_message_when_no_key),
        unit_test_setup_teardown(cmd_otr_start_sends_otr_query_message_to_current_recipeint,
            load_preferences,
            close_preferences),
#else
        unit_test(cmd_otr_shows_message_when_otr_unsupported),
#endif

#ifdef HAVE_LIBGPGME
        unit_test(cmd_pgp_shows_usage_when_no_args),
        unit_test(cmd_pgp_start_shows_message_when_disconnected),
        unit_test(cmd_pgp_start_shows_message_when_disconnecting),
        unit_test(cmd_pgp_start_shows_message_when_connecting),
        unit_test(cmd_pgp_start_shows_message_when_undefined),
        unit_test(cmd_pgp_start_shows_message_when_started),
        unit_test(cmd_pgp_start_shows_message_when_no_arg_in_console),
        unit_test(cmd_pgp_start_shows_message_when_no_arg_in_muc),
        unit_test(cmd_pgp_start_shows_message_when_no_arg_in_mucconf),
        unit_test(cmd_pgp_start_shows_message_when_no_arg_in_private),
        unit_test(cmd_pgp_start_shows_message_when_no_arg_in_xmlconsole),
#else
        unit_test(cmd_pgp_shows_message_when_pgp_unsupported),
#endif

        unit_test(cmd_join_shows_message_when_disconnecting),
        unit_test(cmd_join_shows_message_when_connecting),
        unit_test(cmd_join_shows_message_when_disconnected),
        unit_test(cmd_join_shows_message_when_undefined),
        unit_test(cmd_join_shows_error_message_when_invalid_room_jid),
        unit_test(cmd_join_uses_account_mucservice_when_no_service_specified),
        unit_test(cmd_join_uses_supplied_nick),
        unit_test(cmd_join_uses_account_nick_when_not_supplied),
        unit_test(cmd_join_uses_password_when_supplied),

        unit_test(cmd_roster_shows_message_when_disconnecting),
        unit_test(cmd_roster_shows_message_when_connecting),
        unit_test(cmd_roster_shows_message_when_disconnected),
        unit_test(cmd_roster_shows_message_when_undefined),
        unit_test(cmd_roster_shows_roster_when_no_args),
        unit_test(cmd_roster_add_shows_message_when_no_jid),
        unit_test(cmd_roster_add_sends_roster_add_request),
        unit_test(cmd_roster_remove_shows_message_when_no_jid),
        unit_test(cmd_roster_remove_sends_roster_remove_request),
        unit_test(cmd_roster_nick_shows_message_when_no_jid),
        unit_test(cmd_roster_nick_shows_message_when_no_nick),
        unit_test(cmd_roster_nick_shows_message_when_no_contact_exists),
        unit_test(cmd_roster_nick_sends_name_change_request),
        unit_test(cmd_roster_clearnick_shows_message_when_no_jid),
        unit_test(cmd_roster_clearnick_shows_message_when_no_contact_exists),
        unit_test(cmd_roster_clearnick_sends_name_change_request_with_empty_nick),

        unit_test(get_form_type_field_returns_null_no_fields),
        unit_test(get_form_type_field_returns_null_when_not_present),
        unit_test(get_form_type_field_returns_value_when_present),
        unit_test(get_field_type_returns_unknown_when_no_fields),
        unit_test(get_field_type_returns_correct_type),
        unit_test(set_value_adds_when_none),
        unit_test(set_value_updates_when_one),
        unit_test(add_unique_value_adds_when_none),
        unit_test(add_unique_value_does_nothing_when_exists),
        unit_test(add_unique_value_adds_when_doesnt_exist),
        unit_test(add_value_adds_when_none),
        unit_test(add_value_adds_when_some),
        unit_test(add_value_adds_when_exists),
        unit_test(remove_value_does_nothing_when_none),
        unit_test(remove_value_does_nothing_when_doesnt_exist),
        unit_test(remove_value_removes_when_one),
        unit_test(remove_value_removes_when_many),
        unit_test(remove_text_multi_value_does_nothing_when_none),
        unit_test(remove_text_multi_value_does_nothing_when_doesnt_exist),
        unit_test(remove_text_multi_value_removes_when_one),
        unit_test(remove_text_multi_value_removes_when_many),

        unit_test_setup_teardown(clears_chat_sessions,
            load_preferences,
            close_preferences),

        unit_test(prof_partial_occurrences_tests),
        unit_test(prof_whole_occurrences_tests),
    };

    return run_tests(all_tests);
}
