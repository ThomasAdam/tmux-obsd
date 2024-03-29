# $OpenBSD$

PROG=	tmux
SRCS=	alerts.c \
	arguments.c \
	attributes.c \
	cfg.c \
	client.c \
	cmd-attach-session.c \
	cmd-bind-key.c \
	cmd-break-pane.c \
	cmd-capture-pane.c \
	cmd-choose-tree.c \
	cmd-command-prompt.c \
	cmd-confirm-before.c \
	cmd-copy-mode.c \
	cmd-detach-client.c \
	cmd-display-menu.c \
	cmd-display-message.c \
	cmd-display-panes.c \
	cmd-find-window.c \
	cmd-find.c \
	cmd-if-shell.c \
	cmd-join-pane.c \
	cmd-kill-pane.c \
	cmd-kill-server.c \
	cmd-kill-session.c \
	cmd-kill-window.c \
	cmd-list-buffers.c \
	cmd-list-clients.c \
	cmd-list-keys.c \
	cmd-list-panes.c \
	cmd-list-sessions.c \
	cmd-list-windows.c \
	cmd-load-buffer.c \
	cmd-lock-server.c \
	cmd-move-window.c \
	cmd-new-session.c \
	cmd-new-window.c \
	cmd-parse.y \
	cmd-paste-buffer.c \
	cmd-pipe-pane.c \
	cmd-queue.c \
	cmd-refresh-client.c \
	cmd-rename-session.c \
	cmd-rename-window.c \
	cmd-resize-pane.c \
	cmd-resize-window.c \
	cmd-respawn-pane.c \
	cmd-respawn-window.c \
	cmd-rotate-window.c \
	cmd-run-shell.c \
	cmd-save-buffer.c \
	cmd-select-layout.c \
	cmd-select-pane.c \
	cmd-select-window.c \
	cmd-send-keys.c \
	cmd-server-access.c \
	cmd-set-buffer.c \
	cmd-set-environment.c \
	cmd-set-option.c \
	cmd-show-environment.c \
	cmd-show-messages.c \
	cmd-show-options.c \
	cmd-show-prompt-history.c \
	cmd-source-file.c \
	cmd-split-window.c \
	cmd-swap-pane.c \
	cmd-swap-window.c \
	cmd-switch-client.c \
	cmd-unbind-key.c \
	cmd-wait-for.c \
	cmd.c \
	colour.c \
	control-notify.c \
	control.c \
	environ.c \
	file.c \
	format.c \
	format-draw.c \
	grid-reader.c \
	grid-view.c \
	grid.c \
	hyperlinks.c \
	input-keys.c \
	input.c \
	job.c \
	key-bindings.c \
	key-string.c \
	layout-custom.c \
	layout-set.c \
	layout.c \
	log.c \
	menu.c \
	mode-tree.c \
	names.c \
	notify.c \
	options-table.c \
	options.c \
	paste.c \
	popup.c \
	proc.c \
	procname.c \
	regsub.c \
	resize.c \
	screen-redraw.c \
	screen-write.c \
	screen.c \
	server-acl.c \
	server-client.c \
	server-fn.c \
	server.c \
	session.c \
	spawn.c \
	status.c \
	style.c \
	tmux.c \
	tty-acs.c \
	tty-features.c \
	tty-keys.c \
	tty-term.c \
	tty.c \
	utf8.c \
	utf8-combined.c \
	window-buffer.c \
	window-client.c \
	window-clock.c \
	window-copy.c \
	window-customize.c \
	window-tree.c \
	window.c \
	xmalloc.c

CDIAGFLAGS+= -Wno-long-long -Wall -W -Wnested-externs -Wformat=2
CDIAGFLAGS+= -Wmissing-prototypes -Wstrict-prototypes -Wmissing-declarations
CDIAGFLAGS+= -Wwrite-strings -Wshadow -Wpointer-arith -Wsign-compare
CDIAGFLAGS+= -Wundef -Wbad-function-cast -Winline -Wcast-align

CFLAGS += -I${.CURDIR}

LDADD=  -lutil -lcurses -levent -lm
DPADD=  ${LIBUTIL} ${LIBCURSES} ${LIBEVENT} ${LIBM}

.include <bsd.prog.mk>
