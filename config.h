/* See LICENSE file for copyright and license details. */

/* special commands */
static const char *dircmd = "xterm -e lf %s";

static const Pair pairs[] = {
	/*  regex                                           action */
	{ "\\.pdf$",                                        "zathura %s" },
	{ "\\.(jpg|jpeg|png|tiff|gif|bmp)$",                "sxiv -a %s" },
	{ "\\.(avi|mp4|m4v|mkv|mp3|ogg|flac|mov|wav|wmv)$", "mpv %s" },
	{ "\\.(html|svg)$",                                 "firefox %s" },
	{ "^(http://|https://)?(www\\.)?(youtube\\.com/watch\?|youtu\\.be/)", "mpv %s" },
	{ "^(http|https)://",                               "firefox %s" },
	{ "(^magnet:\?|\\.torrent$)",                       "torrentadd %s" },
	{ "^mailto:\?",                                     "xterm -e mutt %s" },
	{ ".",                                              "xterm -e nvim %s" },
};
