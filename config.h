/*                          ___                  __           */ 
/*                        /'___\ __             /\ \          */
/*    ___    ___     ___ /\ \__//\_\     __     \ \ \___      */
/*   /'___\ / __`\ /' _ `\ \ ,__\/\ \  /'_ `\    \ \  _ `\    */
/*  /\ \__//\ \L\ \/\ \/\ \ \ \_/\ \ \/\ \L\ \  __\ \ \ \ \   */
/*  \ \____\ \____/\ \_\ \_\ \_\  \ \_\ \____ \/\_\\ \_\ \_\  */
/*   \/____/\/___/  \/_/\/_/\/_/   \/_/\/___L\ \/_/ \/_/\/_/  */
/*                                       /\____/              */
/*                                       \_/__/               */

/* See LICENSE file for copyright and license details. */

#define BROWSER "brave"
#define JUPYTER "jupyter-lab"
#define MAIL "claws-mail"
#define RUNMENU "runmenu.sh"
#define NUMCOLORS 4

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 4;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 4;       /* vert inner gap between windows */
static const unsigned int gappoh    = 4;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 4;       /* vert outer gap between windows and screen edge */
static int smartgaps                = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char termcol0[]  = "#282828"; /* black   */
static char termcol1[]  = "#cc241d"; /* red     */
static char termcol2[]  = "#98971a"; /* green   */
static char termcol3[]  = "#d79921"; /* yellow  */
static char termcol4[]  = "#458588"; /* blue    */
static char termcol5[]  = "#b16286"; /* magenta */
static char termcol6[]  = "#689d6a"; /* cyan    */
static char termcol7[]  = "#a89984"; /* white   */
static char termcol8[]  = "#928374"; /* black   */
static char termcol9[]  = "#fb4934"; /* red     */
static char termcol10[] = "#b8bb26"; /* green   */
static char termcol11[] = "#fabd2f"; /* yellow  */
static char termcol12[] = "#83a598"; /* blue    */
static char termcol13[] = "#d3869b"; /* magenta */
static char termcol14[] = "#8ec07c"; /* cyan    */
static char termcol15[] = "#ebdbb2"; /* white   */
static char termcol16[] = "#005577"; /* dwmblue */
static char *termcolor[] = {
  termcol0,
  termcol1,
  termcol2,
  termcol3,
  termcol4,
  termcol5,
  termcol6,
  termcol7,
  termcol8,
  termcol9,
  termcol10,
  termcol11,
  termcol12,
  termcol13,
  termcol14,
  termcol15,
  termcol16,
};
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "st",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int attachdirection = 4;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include "movestack.c"
#include <X11/XF86keysym.h>

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define ALTMOD Mod1Mask
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
    { ALTMOD,                       KEY,      focusnthmon,    {.i  = TAG } }, \
    { ALTMOD|ShiftMask,             KEY,      tagnthmon,      {.i  = TAG } },


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run_i", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *tabterm[]  = { "tabbed", "-r", "2", "st", "-w", "''", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *surfbrowser[] = { "tabbed", "surf", "-e", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
    /* software */
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_Return, spawn,          {.v = tabterm } },
	{ MODKEY,                       XK_s,      togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY,                       XK_r,      spawn,          {.v = surfbrowser } },
	{ MODKEY,                       XK_y,      spawn,          {.v = (const char*[]){ JUPYTER, NULL } } },
	{ MODKEY,                       XK_m,      spawn,          {.v = (const char*[]){ MAIL, NULL } } },
	{ MODKEY,                       XK_Menu,   spawn,          {.v = (const char*[]){ RUNMENU, NULL } } },
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	
    /* windows */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	
    /* gaps */
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_0,      defaultgaps,    {0} },
/*  { MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } }, */
/*  { MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } }, */
/*  { MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } }, */
/*  { MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } }, */
/*  { MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } }, */
/*  { MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } }, */
/*  { MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } }, */
/*  { MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } }, */
/*  { MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } }, */
/*  { MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } }, */
/*  { MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } }, */
/*  { MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } }, */
/*  { MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } }, */
/*  { MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } }, */
	
    /* tags & monitors */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
    { MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[11]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ControlMask,		    XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

    /* special buttons */
    { 0, XF86XK_AudioMicMute,                  spawn,          SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,              spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ false ; pactl set-sink-volume @DEFAULT_SINK@ -5%; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioMute,                     spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,              spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ false ; pactl set-sink-volume @DEFAULT_SINK@ +5%; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_MonBrightnessUp,               spawn,          SHCMD("xbacklight -inc 5; kill -45 $(pidof dwmblocks)") },
	{ 0, XF86XK_MonBrightnessDown,             spawn,          SHCMD("xbacklight -dec 5; kill -45 $(pidof dwmblocks)") },
	{ 0, XF86XK_ScreenSaver,                   spawn,          SHCMD("slock") },
	{ 0, XF86XK_WebCam,                        spawn,          SHCMD("sudo rfkill toggle bluetooth") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,		    MODKEY,		    Button4,	    incrgaps,	    {.i = +1} },
	{ ClkClientWin,		    MODKEY,		    Button5,	    incrgaps,	    {.i = -1} },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

