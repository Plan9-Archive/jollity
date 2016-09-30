</$objtype/mkfile

jollity:	free_structs.$0 handle_away.$0 handle_ctcp.$0 handle_invite.$0 handle_join.$0 handle_kick.$0 handle_list.$0 handle_misc.$0 handle_mode.$0 handle_nick.$0 handle_notice.$0 handle_part.$0 handle_privmsg.$0 handle_quit.$0 handle_servmsg.$0 handle_topic.$0 handle_who.$0 handle_whois.$0 init_structs.$0 main.$0 input_network.$0 parse_network.$0 parse_user.$0 read_line_user.$0 read_line_net.$0 input_user.$0 util.$0
		$LD $LDFLAGS -o $target free_structs.8 handle_away.8 handle_ctcp.8 handle_invite.8 handle_join.8 handle_kick.8 handle_list.8 handle_misc.8 handle_mode.8 handle_nick.8 handle_notice.8 handle_part.8 handle_privmsg.8 handle_quit.8 handle_servmsg.8 handle_topic.8 handle_who.8 handle_whois.8 init_structs.8 main.8 input_network.8 parse_network.8 parse_user.8 read_line_user.8 read_line_net.8 input_user.8 util.8

clean:
		rm *.8 jollity

%.$0:	%.c
		$CC $CFLAGS $stem.c
