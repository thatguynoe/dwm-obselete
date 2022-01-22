/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10", "Joy Pixels:pixelsize=10:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

typedef struct {
    const char *name;
    const void *cmd;
} Sp;
const char *spcmd1[] = { TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = { TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
    /* name          cmd  */
    {"spterm",      spcmd1},
    {"spcalc",      spcmd2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class     instance  title                    tags mask   isfloating  isterminal  noswallow  monitor */
    { "Gimp",    NULL,     NULL,                    0,          1,          0,           0,        -1 },
    { "Firefox", NULL,     NULL,                    1 << 8,     0,          0,          -1,        -1 },
    { NULL,      NULL,     "Picture-in-Picture",    0,          1,          0,           0,        -1 },
    { TERMINAL,  NULL,     NULL,                    0,          0,          1,           0,        -1 },
    { NULL,      NULL,     "Event Tester",          0,          0,          0,           1,        -1 }, /* xev */
    { NULL,      "spterm", NULL,                    SPTAG(0),   1,          1,           0,        -1 },
    { NULL,      "spcalc", NULL,                    SPTAG(1),   1,          1,           0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1               /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "[D]",      deck },    /* master on the left, slaves stacked on the right */
    { "[M]",      monocle }, /* all windows on top of each other */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
    { MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
    { MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
    { MOD, XK_v,     ACTION##stack, {.i = 0 } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
    /* modifier                     key                         function        argument */
    STACKKEYS(MODKEY,                                           focus)
    STACKKEYS(MODKEY|ShiftMask,                                 push)
    { MODKEY,                       XK_grave,                   spawn,          SHCMD("dmenuunicode") },
    { MODKEY|ControlMask,           XK_grave,                   spawn,          SHCMD("dunstctl history-pop") },
    TAGKEYS(                        XK_1,                                       0)
    TAGKEYS(                        XK_2,                                       1)
    TAGKEYS(                        XK_3,                                       2)
    TAGKEYS(                        XK_4,                                       3)
    TAGKEYS(                        XK_5,                                       4)
    TAGKEYS(                        XK_6,                                       5)
    TAGKEYS(                        XK_7,                                       6)
    TAGKEYS(                        XK_8,                                       7)
    TAGKEYS(                        XK_9,                                       8)
    { MODKEY,                       XK_0,                       view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,                       tag,            {.ui = ~0 } },
    { MODKEY,                       XK_minus,                   spawn,          SHCMD("pamixer --allow-boost -d  5; kill -44 $(pidof dwmblocks)") },
    { MODKEY|ShiftMask,             XK_minus,                   spawn,          SHCMD("pamixer --allow-boost -d 20; kill -44 $(pidof dwmblocks)") },
    { MODKEY,                       XK_equal,                   spawn,          SHCMD("pamixer --allow-boost -i  5; kill -44 $(pidof dwmblocks)") },
    { MODKEY|ShiftMask,             XK_equal,                   spawn,          SHCMD("pamixer --allow-boost -i 20; kill -44 $(pidof dwmblocks)") },
    { MODKEY,                       XK_BackSpace,               spawn,          SHCMD("sysact") },
    { MODKEY|ShiftMask,             XK_BackSpace,               spawn,          SHCMD("sysact") },

    { MODKEY,                       XK_Tab,                     view,           {0} },
    { MODKEY,                       XK_q,                       killclient,     {0} },
    { MODKEY|ShiftMask,             XK_q,                       spawn,          SHCMD("sysact") },
    { MODKEY,                       XK_w,                       spawn,          SHCMD("$BROWSER") },
    { MODKEY|ShiftMask,             XK_w,                       spawn,          SHCMD(TERMINAL " -e nmtui") },
    { MODKEY,                       XK_e,                       spawn,          SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
    { MODKEY,                       XK_r,                       spawn,          SHCMD(TERMINAL " -e lf") },
    { MODKEY|ShiftMask,             XK_r,                       spawn,          SHCMD(TERMINAL " -e htop") },
    { MODKEY,                       XK_t,                       setlayout,      {.v = &layouts[0]} },    /* tile */
    { MODKEY,                       XK_u,                       setlayout,      {.v = &layouts[1]} },    /* deck */
    { MODKEY|ShiftMask,             XK_u,                       setlayout,      {.v = &layouts[2]} },    /* monocle */
    { MODKEY,                       XK_o,                       incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask,             XK_o,                       incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_p,                       spawn,          SHCMD("mpc toggle") },
    { MODKEY|ShiftMask,             XK_p,                       spawn,          SHCMD("mpc pause ; pauseallmpv") },
    { MODKEY,                       XK_bracketleft,             spawn,          SHCMD("mpc seek -10") },
    { MODKEY|ShiftMask,             XK_bracketleft,             spawn,          SHCMD("mpc seek -60") },
    { MODKEY,                       XK_bracketright,            spawn,          SHCMD("mpc seek +10") },
    { MODKEY|ShiftMask,             XK_bracketright,            spawn,          SHCMD("mpc seek +60") },

    { MODKEY,                       XK_a,                       togglegaps,     {0} },
    { MODKEY|ShiftMask,             XK_a,                       defaultgaps,    {0} },
    { MODKEY,                       XK_d,                       spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_d,                       spawn,          SHCMD("passmenu") },
    { MODKEY,                       XK_f,                       togglefullscr,  {0} },
    { MODKEY|ShiftMask,             XK_f,                       setlayout,      {.v = &layouts[3]} },    /* floating */
    { MODKEY,                       XK_h,                       setmfact,       {.f = -0.05} },
    { MODKEY|ShiftMask,             XK_h,                       focusmon,       {.i = -1} },
    { MODKEY,                       XK_l,                       setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_l,                       focusmon,       {.i = +1} },
    { MODKEY,                       XK_apostrophe,              togglescratch,  {.ui = 1} },
    { MODKEY,                       XK_backslash,               view,           {0} },
    { MODKEY,                       XK_Return,                  spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_Return,                  togglescratch,  {.ui = 0} },

    { MODKEY,                       XK_z,                       incrgaps,       {.i = +3 } },
    { MODKEY,                       XK_x,                       incrgaps,       {.i = -3 } },
    { MODKEY,                       XK_b,                       togglebar,      {0} },
    { MODKEY,                       XK_n,                       spawn,          SHCMD(TERMINAL " -e nvim") },
    { MODKEY,                       XK_m,                       spawn,          SHCMD(TERMINAL " -e ncmpcpp") },
    { MODKEY|ShiftMask,             XK_m,                       spawn,          SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
    { MODKEY,                       XK_comma,                   spawn,          SHCMD("mpc prev") },
    { MODKEY|ShiftMask,             XK_comma,                   spawn,          SHCMD("mpc seek 0%") },
    { MODKEY,                       XK_period,                  spawn,          SHCMD("mpc next") },
    { MODKEY|ShiftMask,             XK_period,                  spawn,          SHCMD("mpc repeat") },

    { MODKEY,                       XK_Left,                    focusmon,       {.i = -1} },
    { MODKEY|ShiftMask,             XK_Left,                    tagmon,         {.i = -1} },
    { MODKEY,                       XK_Right,                   focusmon,       {.i = +1} },
    { MODKEY|ShiftMask,             XK_Right,                   tagmon,         {.i = +1} },

    { MODKEY,                       XK_space,                   zoom,           {0} },
    { MODKEY|ShiftMask,             XK_space,                   togglefloating, {0} },
    { MODKEY|ControlMask,           XK_space,                   spawn,          SHCMD("dunstctl close") },

    { 0,                            XK_Print,                   spawn,          SHCMD("maim -u $HOME/Pictures/Screenshots/pic-full-$(date '+%y%m%d-%H%M-%S').png") },
    { ShiftMask,                    XK_Print,                   spawn,          SHCMD("maimpick") },
    { MODKEY,                       XK_Print,                   spawn,          SHCMD("dmenurecord") },
    { MODKEY|ShiftMask,             XK_Print,                   spawn,          SHCMD("dmenurecord kill") },
    { MODKEY,                       XK_Delete,                  spawn,          SHCMD("dmenurecord kill") },
    { MODKEY,                       XK_Scroll_Lock,             spawn,          SHCMD("killall screenkey || screenkey &") },

    { MODKEY,                       XK_F1,                      spawn,          SHCMD("groff -mom /usr/local/share/dwm/narbs.mom -Tpdf | zathura -") },
    { MODKEY,                       XK_F2,                      spawn,          SHCMD("xzoom") },
    { MODKEY,                       XK_F3,                      spawn,          SHCMD("displayselect") },
    { MODKEY,                       XK_F4,                      spawn,          SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)") },
    { MODKEY,                       XK_F5,                      spawn,          SHCMD("$BROWSER localhost:631/") },
    { MODKEY,                       XK_F6,                      spawn,          SHCMD("bluetoothcon; sleep 3; kill -44 $(pidof dwmblocks)") },
    { MODKEY,                       XK_F7,                      spawn,          SHCMD("bluetoothdis; kill -44 $(pidof dwmblocks)") },
    { MODKEY,                       XK_F8,                      spawn,          SHCMD("mw -Y; pkill -RTMIN+12 dwmblocks") },
    { MODKEY,                       XK_F9,                      spawn,          SHCMD("dmenumount") },
    { MODKEY,                       XK_F10,                     spawn,          SHCMD("dmenuumount") },
    { MODKEY,                       XK_F11,                     spawn,          SHCMD("mpv --no-cache --no-osc --no-input-default-bindings --profile=low-latency --untimed --vf=hflip --no-keepaspect-window --panscan=1 --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
    { MODKEY,                       XK_F12,                     spawn,          SHCMD("remaps & notify-send \"⌨️ Keyboard remapping...\" \"Re-running keyboard defaults for any newly plugged-in keyboards.\"") },

    { 0,                            XF86XK_Tools,               spawn,          SHCMD(TERMINAL " -e ncmpcpp") },
    { 0,                            XF86XK_AudioMute,           spawn,          SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
    { 0,                            XF86XK_AudioRaiseVolume,    spawn,          SHCMD("pamixer --allow-boost -i 1; kill -44 $(pidof dwmblocks)") },
    { 0,                            XF86XK_AudioLowerVolume,    spawn,          SHCMD("pamixer --allow-boost -d 1; kill -44 $(pidof dwmblocks)") },
    { 0,                            XF86XK_AudioPrev,           spawn,          SHCMD("mpc prev") },
    { 0,                            XF86XK_AudioNext,           spawn,          SHCMD("mpc next") },
    { 0,                            XF86XK_AudioPause,          spawn,          SHCMD("mpc pause") },
    { 0,                            XF86XK_AudioPlay,           spawn,          SHCMD("mpc play") },
    { 0,                            XF86XK_AudioStop,           spawn,          SHCMD("mpc stop") },
    { 0,                            XF86XK_AudioRewind,         spawn,          SHCMD("mpc seek -10") },
    { 0,                            XF86XK_AudioForward,        spawn,          SHCMD("mpc seek +10") },
    { 0,                            XF86XK_AudioMedia,          spawn,          SHCMD(TERMINAL " -e ncmpcpp") },
    { 0,                            XF86XK_AudioMicMute,        spawn,          SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
    { 0,                            XF86XK_PowerOff,            spawn,          SHCMD("loginctl poweroff") },
    { 0,                            XF86XK_Calculator,          togglescratch,  {.ui = 1} },
    { 0,                            XF86XK_Sleep,               spawn,          SHCMD("slock loginctl suspend") },
    { 0,                            XF86XK_WWW,                 spawn,          SHCMD("$BROWSER") },
    { 0,                            XF86XK_DOS,                 spawn,          SHCMD(TERMINAL) },
    { 0,                            XF86XK_ScreenSaver,         spawn,          SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
    { 0,                            XF86XK_TaskPane,            spawn,          SHCMD(TERMINAL " -e htop") },
    { 0,                            XF86XK_Mail,                spawn,          SHCMD(TERMINAL " -e neomutt; pkill -RTMIN+12 dwmblocks") },
    { 0,                            XF86XK_MyComputer,          spawn,          SHCMD(TERMINAL " -e lf /") },
    { 0,                            XF86XK_HomePage,            spawn,          SHCMD("$BROWSER") },
    { 0,                            XF86XK_Launch1,             spawn,          SHCMD("sleep 1 && xset dpms force off") },
    { 0,                            XF86XK_TouchpadToggle,      spawn,          SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
    { 0,                            XF86XK_TouchpadOff,         spawn,          SHCMD("synclient TouchpadOff=1") },
    { 0,                            XF86XK_TouchpadOn,          spawn,          SHCMD("synclient TouchpadOff=0") },
    { 0,                            XF86XK_MonBrightnessUp,     spawn,          SHCMD("xbacklight +1; pkill -RTMIN+19 dwmblocks") },
    { MODKEY,                       XF86XK_MonBrightnessUp,     spawn,          SHCMD("xbacklight +5; pkill -RTMIN+19 dwmblocks") },
    { MODKEY|ControlMask,           XF86XK_MonBrightnessUp,     spawn,          SHCMD("xbacklight +10; pkill -RTMIN+19 dwmblocks") },
    { 0,                            XF86XK_MonBrightnessDown,   spawn,          SHCMD("xbacklight -1; pkill -RTMIN+19 dwmblocks") },
    { MODKEY,                       XF86XK_MonBrightnessDown,   spawn,          SHCMD("xbacklight -5; pkill -RTMIN+19 dwmblocks") },
    { MODKEY|ControlMask,           XF86XK_MonBrightnessDown,   spawn,          SHCMD("xbacklight -10; pkill -RTMIN+19 dwmblocks") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
