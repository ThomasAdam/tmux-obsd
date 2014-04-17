/* $OpenBSD$ */

/*
 * Copyright (c) 2009 Nicholas Marriott <nicm@users.sourceforge.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF MIND, USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/types.h>

#include "tmux.h"

/*
 * Select pane.
 */

void		 cmd_select_pane_key_binding(struct cmd *, int);
enum cmd_retval	 cmd_select_pane_exec(struct cmd *, struct cmd_q *);

const struct cmd_entry cmd_select_pane_entry = {
	"select-pane", "selectp",
	"ClDLMRt:U", 0, 0,
	"[-ClDLMRU] " CMD_TARGET_PANE_USAGE,
	0,
	cmd_select_pane_key_binding,
	cmd_select_pane_exec
};

const struct cmd_entry cmd_last_pane_entry = {
	"last-pane", "lastp",
	"t:", 0, 0,
	CMD_TARGET_WINDOW_USAGE,
	0,
	NULL,
	cmd_select_pane_exec
};

void
cmd_select_pane_key_binding(struct cmd *self, int key)
{
	self->args = args_create(0);
	if (key == KEYC_UP)
		args_set(self->args, 'U', NULL);
	if (key == KEYC_DOWN)
		args_set(self->args, 'D', NULL);
	if (key == KEYC_LEFT)
		args_set(self->args, 'L', NULL);
	if (key == KEYC_RIGHT)
		args_set(self->args, 'R', NULL);
	if (key == 'o')
		args_set(self->args, 't', ":.+");
	if (key == 'M')
		args_set(self->args, 'C', NULL);
	if (key == 'm')
		args_set(self->args, 'M', NULL);
}

enum cmd_retval
cmd_select_pane_exec(struct cmd *self, struct cmd_q *cmdq)
{
	struct args		*args = self->args;
	struct winlink		*wl;
	struct window_pane	*wp, *lastwp;
	struct session		*s;

	if (self->entry == &cmd_last_pane_entry || args_has(args, 'l')) {
		wl = cmd_find_window(cmdq, args_get(args, 't'), NULL, 0);
		if (wl == NULL)
			return (CMD_RETURN_ERROR);

		if (wl->window->last == NULL) {
			cmdq_error(cmdq, "no last pane");
			return (CMD_RETURN_ERROR);
		}

		server_unzoom_window(wl->window);
		window_set_active_pane(wl->window, wl->window->last);
		server_status_window(wl->window);
		server_redraw_window_borders(wl->window);

		return (CMD_RETURN_NORMAL);
	}

	if ((wl = cmd_find_pane(cmdq, args_get(args, 't'), &s, &wp, 0)) == NULL)
		return (CMD_RETURN_ERROR);

	if (args_has(args, 'C') || args_has(args, 'M')) {
		if (args_has(args, 'M') && !window_pane_visible(wp))
			return (CMD_RETURN_NORMAL);
		lastwp = marked_window_pane;

		if (args_has(args, 'C') || server_is_marked(s, wl, wp))
			server_clear_marked();
		else
			server_set_marked(s, wl, wp);

		if (lastwp != NULL)
			server_redraw_window_borders(lastwp->window);
		if (marked_window_pane != NULL)
			server_redraw_window_borders(marked_window_pane->window);
		return (CMD_RETURN_NORMAL);
	}

	server_unzoom_window(wp->window);
	if (!window_pane_visible(wp)) {
		cmdq_error(cmdq, "pane not visible");
		return (CMD_RETURN_ERROR);
	}

	if (args_has(self->args, 'L'))
		wp = window_pane_find_left(wp);
	else if (args_has(self->args, 'R'))
		wp = window_pane_find_right(wp);
	else if (args_has(self->args, 'U'))
		wp = window_pane_find_up(wp);
	else if (args_has(self->args, 'D'))
		wp = window_pane_find_down(wp);
	if (wp == NULL) {
		cmdq_error(cmdq, "pane not found");
		return (CMD_RETURN_ERROR);
	}

	window_set_active_pane(wl->window, wp);
	server_status_window(wl->window);
	server_redraw_window_borders(wl->window);

	return (CMD_RETURN_NORMAL);
}
