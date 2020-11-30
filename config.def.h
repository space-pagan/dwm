#include <X11/XF86keysym.h>

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 30;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 30;       /* vert inner gap between windows */
static const unsigned int gappoh    = 30;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { 
                                        "RobotoMono-Regular:size=14",
                                        "'Noto Mono Nerd Font Complete Mono':size=17"
                                      };
static const char dmenufont[]       = "monospace:size=14";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_1[]           = "#252a35";
static const char col_2[]           = "#ffbaff";
static const char col_3[]           = "#606087";
static const char col_4[]           = "#ff87d7";
static const char col_5[]           = "#765abf";
static const char col_6[]           = "#bd93f9";
static const char col_bg[]          = "#453570";
static const unsigned int baralpha  = 0xc0; /* 75% */
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
    /*               fg         bg          border  */
    [SchemeNorm] = { col_gray4, col_bg,      col_3 },
    [SchemeSel]  = { col_2,     col_bg,      col_6 },
};

static const unsigned int alphas[][3] = {
    /*               fg         bg          border  */
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
    [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
// static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
    /* xprop(1):
     *    WM_CLASS(STRING) = instance, class
     *    WM_NAME(STRING) = title
     */
    /* class        instance    title           tags mask   isfloating  isterminal  noswallow   monitor */
    { "Gimp",       NULL,       NULL,           0,          1,          0,          0,          -1 },
    { "Firefox",    NULL,       NULL,           1 << 8,     0,          0,          -1,         -1 },
    { "Alacritty",  NULL,       NULL,           0,          0,          1,          0,          -1 },
    { "colortest",  NULL,       NULL,           0,          1,          0,          1,          -1 }, /* colortest */
    { NULL,         NULL,       "Event Tester", 0,          0,          0,          1,          -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol   arrange function */
    { "侀",     tile },    /* first entry is default */
    { "יּ",      deck },
    { "",      monocle },
    { "頻",     centeredmaster },
    { "恵",     centeredfloatingmaster },
    { "",      NULL },    /* no layout function means floating behavior */
};

enum { TILE, DECK, MONOCLE, CENTERED, CENTFLOAT, FLOATING };

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define TERMINAL "alacritty"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_5, "-nf", col_2, "-sb", col_6, "-sf", col_gray4, NULL };
static const char *termcmd[]    = { "/home/zoya/.scripts/spawn-term-cwd",   NULL };

static Key keys[] = {
    /* modifier                     key         function        argument */
    
/* NUM Row */
    // { MODKEY,                       XK_Escape,  spawn,          SHCMD("") },
    { MODKEY,                       XK_grave,   spawn,          SHCMD("unicodedmenu") },
    TAGKEYS(                        XK_1,                       0)
    TAGKEYS(                        XK_2,                       1)
    TAGKEYS(                        XK_3,                       2)
    TAGKEYS(                        XK_4,                       3)
    TAGKEYS(                        XK_5,                       4)
    TAGKEYS(                        XK_6,                       5)
    TAGKEYS(                        XK_7,                       6)
    TAGKEYS(                        XK_8,                       7)
    TAGKEYS(                        XK_9,                       8)
    { MODKEY,                       XK_0,       view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,       tag,            {.ui = ~0 } },
    // { MODKEY,                       XK_minux,   spawn,          SHCMD("") },
    { MODKEY,                       XK_equal,   setmfact,       {.f = 1.5} },



/* QWERTY Row */
    { MODKEY,                       XK_Tab,     view,           {0} },
    { MODKEY,                       XK_q,       killclient,     {0} },
    { MODKEY|ShiftMask,             XK_q,       quit,           {0} },
    { MODKEY,                       XK_w,       spawn,          SHCMD("$BROWSER") },
    { MODKEY|ShiftMask,             XK_w,       spawn,          SHCMD("networkmanager_dmenu") },
    { MODKEY,                       XK_e,       spawn,          SHCMD(TERMINAL " -e vifm") },
    { MODKEY|ShiftMask,             XK_r,       quit,           {1} },
    { MODKEY,                       XK_t,       setlayout,      {.v = &layouts[TILE]} },
    // { MODKEY,                       XK_y,       setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_u,       setlayout,      {.v = &layouts[DECK]} },
    { MODKEY|ShiftMask,             XK_u,       setlayout,      {.v = &layouts[MONOCLE]} },
    { MODKEY,                       XK_i,       setlayout,      {.v = &layouts[CENTERED]} },
    { MODKEY|ShiftMask,             XK_i,       setlayout,      {.v = &layouts[CENTFLOAT]} },
    { MODKEY,                       XK_o,       incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask,             XK_o,       incnmaster,     {.i = -1 } },
    // { MODKEY,                       XK_p,       spawn,          SHCMD("") },
    // { MODKEY,               XK_bracketleft,     spawn,          SHCMD("") },
    // { MODKEY,               XK_bracketright,    spawn,          SHCMD("") },
    // { MODKEY,               XK_backslash,       spawn,          SHCMD("") },
  


/* ASDFGH Row */
    // { MODKEY,                       XK_a,       spawn,          SHCMD("") },
    // { MODKEY,                       XK_s,       spawn,          SHCMD("") },
    // { MODKEY,                       XK_d,       spawn,          SHCMD("") },
    { MODKEY,                       XK_f,       setlayout,      {.v = &layouts[FLOATING]} },
    // { MODKEY,                       XK_g,       spawn,          SHCMD("") },
    { MODKEY,                       XK_h,       setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_j,       focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,       focusstack,     {.i = -1 } },
    { MODKEY,                       XK_l,       setmfact,       {.f = +0.05} },
    // { MODKEY,               XK_semicolon,       spawn,          SHCMD("") },
    // { MODKEY,               XK_apostrophe,      spawn,          SHCMD("") },
    { MODKEY|ShiftMask,             XK_Return,  spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return,  spawn,          {.v = termcmd } },



/* ZXCVBN Row */
    { MODKEY,                       XK_z,       focusstack,     {.i = 0 } },
    // { MODKEY,                       XK_x,       spawn,          SHCMD("") },
    // { MODKEY,                       XK_c,       spawn,          SHCMD("") },
    { MODKEY,                       XK_v,       spawn,          SHCMD(TERMINAL " -e vim") },
    // { MODKEY,                       XK_b,       spawn,          SHCMD("") },
    // { MODKEY,                       XK_n,       spawn,          SHCMD("") },
    // { MODKEY,                       XK_m,       spawn,          SHCMD("") },
    // { MODKEY,                       XK_comma,   spawn,          SHCMD("") },
    // { MODKEY,                       XK_period,  spawn,          SHCMD("") },
    
  
  
/* Other Keys */
    { MODKEY,                       XK_space,   zoom,           {0} },
    { MODKEY|ShiftMask,             XK_space,   togglefloating, {0} },
    { MODKEY,                       XK_Left,    focusmon,       {.i = -1 } },
    { MODKEY|ShiftMask,             XK_Left,    tagmon,         {.i = -1 } },
    { MODKEY,                       XK_Right,   focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_Right,   tagmon,         {.i = +1 } },
    // { MODKEY,                   XK_Page_Up,     shiftview,      {.i = -1 } },
    // { MODKEY|ShiftMask,         XK_Page_Up,     shifttag,       {.i = -1 } },
    // { MODKEY,                   XK_Page_Down,   shiftview,      { .i = +1 } },
    // { MODKEY|ShiftMask,         XK_Page_Down,   shifttag,       { .i = +1 } },
    { 0,              XF86XK_AudioLowerVolume,  spawn,          SHCMD("volctl -5%") },
    { 0,                     XF86XK_AudioMute,  spawn,          SHCMD("volctl toggle") },
    { 0,              XF86XK_AudioRaiseVolume,  spawn,          SHCMD("volctl +5%") },
    { 0,                            XK_Print,   spawn,          SHCMD("maim -s --format png /dev/stdout | xclip -selection clipboard -t image/png") },
    { ControlMask,                  XK_Print,   spawn,          SHCMD("screenshot") },
    { 0,               XF86XK_MonBrightnessUp,  spawn,          SHCMD("monctl +10%") },
    { 0,             XF86XK_MonBrightnessDown,  spawn,          SHCMD("monctl 10%-") },
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

