/* See LICENSE file for copyright and license details. */

#define OPQ_BAR_ALPHA 0xd0
#define OPQ_BORDER_ALPHA 0x80

/* appearance */
static unsigned int borderpx = 2; /* border pixel of windows */
static unsigned int snap = 32;    /* snap pixel */
/* horiz inner gap between windows */
static unsigned int gappih = 4;
/* vert inner gap between windows */
static unsigned int gappiv = 4;
/* horiz outer gap between windows and screen edge */
static unsigned int gappoh = 8;
/* vert outer gap between windows and screen edge */
static unsigned int gappov = 8;
/* 1 means no outer gap when there is only one window */
static const int smartgaps = 1;
/* 1 means swallow floating windows by default */
static int swallowfloating = 0;
static int showbar = 1; /* 0 means no bar */
static int topbar = 1;  /* 0 means bottom bar */

static const char *fonts[] = {
  "Fantasque Sans Mono:pixelsize=14:antialias=true:autohint=true",
  "NotoSans Nerd Font Mono:pixelsize=14:antialias=true:autohint=true",
	"DejaVu Sans:pixelsize=14:antialias=true:autohint=true",
	"Noto Sans Arabic:pixelsize=14:antialias=true:autohint=true",
	"Amiri Quran Colored:pixelsize=14:antialias=true:autohint=true",
	"Noto Color Emoji:pixelsize=14:antialias=true:autohint=true",
	"JoyPixels:pixelsize=14:antialias=true:autohint=true",
	"Noto Sans Hebrew:pixelsize=18:antialias=true:autohint=true",
	"Noto Sans KR:pixelsize=18:antialias=true:autohint=true",
	"Noto Sans JP:pixelsize=18:antialias=true:autohint=true"
};


static char dmenufont[] =
  "Fantasque Sans Mono:pixelsize=16:antialias=true:autohint=true";

static char normbgcolor[] = "#2B2B2B";
static char normfgcolor[] = "#F0F0F0";
static char selbgcolor[] = "#208C9F";
static char selfgcolor[] = "#E6EDF9";
static char normbordercolor[] = "#FFEDE1";
static char selbordercolor[] = "#C34890";

static const char col_cyan[] = "#005577";
static const char col_black[] = "#2B2B2B";
static const char col_red[] = "#A62525";
static const char col_yellow[] = "#BAAB19";
static const char col_white[] = "#F3DAD0";

static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
    [SchemeWarn] = {col_black, col_yellow, col_red},
    [SchemeUrgent] = {col_white, col_red, col_red},
};

static const unsigned int alphas[][3] = {
    /*               fg      bg        border     */
    [SchemeNorm] = {OPAQUE, OPQ_BAR_ALPHA, OPQ_BORDER_ALPHA},
    [SchemeSel] = {OPAQUE, OPQ_BAR_ALPHA, OPQ_BORDER_ALPHA},
};

/* tagging */
static const char *tags[] = {"", "", "", "4", "5", "6", "7", "", "9", "0"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class instance  title 'tags mask' isfloating isterminal noswallow monitor
     */
    {"Gimp", NULL, NULL, 1 << 8, 1, 0, 0, -1},
    {"Pinentry-gtk-2", NULL, NULL, 0, 1, 0, 0, -1},
    {"Telegram", NULL, NULL, 1 << 7, 0, 0, 0, -1},
    {"SimpleScreenRecorder", NULL, NULL, 0, 1, 0, 0, -1},
    {"Emacs", NULL, NULL, 1 << 2, 0, 0, 0, -1},
    {"Kdenlive", NULL, NULL, 1 << 8, 0, 0, 0, -1},
    {"libreoffice", NULL, NULL, 1 << 3, 1, 0, 0, -1},
    {"Brave-browser", NULL, NULL, 1 << 1, 1, 0, 0, -1},
    {"St", NULL, NULL, 0, 0, 1, 0, -1},
    {NULL, NULL, "Event Tester", 0, 0, 0, 1, -1}, /* xev */
};

/* layout(s) */
static float mfact = 0.50f; /* factor of master area size [0.05..0.95] */
static int nmaster = 1;     /* number of clients in master area */
static int resizehints = 0; /* 1 means respect size hints in tiled resizals */
static int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol             arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
    {NULL, NULL},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

#define STACKKEYS(MOD, ACTION)                                                 \
  {MOD, XK_j, ACTION##stack, {.i = INC(+1)}},                                  \
      {MOD, XK_k, ACTION##stack, {.i = INC(-1)}},                              \
      {MOD, XK_grave, ACTION##stack, {.i = PREVSEL}},                          \
      {MOD, XK_q, ACTION##stack, {.i = 0}},                                    \
      {MOD, XK_a, ACTION##stack, {.i = 1}},                                    \
      {MOD, XK_z, ACTION##stack, {.i = 2}},                                    \
      {MOD, XK_x, ACTION##stack, {.i = -1}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-m",  dmenumon,    "-fn",
                                 dmenufont,   "-nb", normbgcolor, "-nf",
                                 normfgcolor, "-sb", selbgcolor,  "-sf",
                                 selfgcolor,  NULL};
static const char *termcmd[] = {"st", NULL};

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
    {"color5", STRING, &selbordercolor},
    {"color15", STRING, &normbordercolor},
    {"color0", STRING, &normbgcolor},
    {"color15", STRING, &normfgcolor},
    {"color3", STRING, &selbgcolor},
    {"color5", STRING, &selfgcolor},
    {"dmenufont", STRING, &dmenufont},
    {"borderpx", INTEGER, &borderpx},
    {"snap", INTEGER, &snap},
    {"showbar", INTEGER, &showbar},
    {"topbar", INTEGER, &topbar},
    {"gappih", INTEGER, &gappih},
    {"gappiv", INTEGER, &gappiv},
    {"gappoh", INTEGER, &gappoh},
    {"gappov", INTEGER, &gappov},
    {"nmaster", INTEGER, &nmaster},
    {"resizehints", INTEGER, &resizehints},
    {"mfact", FLOAT, &mfact},
};

#include "shiftview.c"
#include <X11/XF86keysym.h>

static Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_h, setmfact, {.f = -0.0005f}},
    {MODKEY, XK_l, setmfact, {.f = +0.0005f}},
    {MODKEY, XK_space, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY | ShiftMask, XK_m, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_Page_Up, shiftview, {.i = -1}},
    {MODKEY, XK_Page_Down, shiftview, {.i = +1}},
    {MODKEY | ControlMask, XK_period, cyclelayout, {.i = -1}},
    {MODKEY, XK_s, setlayout, {0}},
    {MODKEY, XK_Left, focusmon, {.i = -1}},
    {MODKEY, XK_Right, focusmon, {.i = +1}},
    {MODKEY, XK_f, togglefullscr, {0}},
    {MODKEY | ShiftMask, XK_q, killclient, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    STACKKEYS(MODKEY, focus) STACKKEYS(MODKEY | ShiftMask, push)
        TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
            TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
                TAGKEYS(XK_9, 8) TAGKEYS(XK_0, 9)};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument
     */
    {ClkStatusText, 0, Button1, sigstatusbar, {.i = 1}},
    {ClkStatusText, 0, Button2, sigstatusbar, {.i = 2}},
    {ClkStatusText, 0, Button3, sigstatusbar, {.i = 3}},
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[0]}},
    {ClkClientWin, MODKEY, Button1, resizemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, movemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};

