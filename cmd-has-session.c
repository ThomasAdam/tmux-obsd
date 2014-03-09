/* $OpenBSD$ */

/*
 * Copyright (c) 2007 Nicholas Marriott <nicm@users.sourceforge.net>
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
 * Cause client to report an error and exit with 1 if session doesn't exist.
 */

enum cmd_retval	 cmd_has_session_exec(struct cmd *, struct cmd_q *);
void		 cmd_has_session_prepare(struct cmd *, struct cmd_q *);

const struct cmd_entry cmd_has_session_entry = {
	"has-session", "has",
	"t:", 0, 0,
	CMD_TARGET_SESSION_USAGE,
	CMD_PREPAREWINDOW,
	NULL,
	cmd_has_session_exec,
	NULL
};

enum cmd_retval
cmd_has_session_exec(unused struct cmd *self, struct cmd_q *cmdq)
{
	if (cmdq->state.s == NULL)
		return (CMD_RETURN_ERROR);

	return (CMD_RETURN_NORMAL);
}
