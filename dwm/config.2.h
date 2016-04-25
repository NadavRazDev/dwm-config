/* See LICENSE file for copyright and license details. */

/* appearance 
static const char font[] = "-*-stlarch-medium-r-*-*-12-*-*-*-*-*-*-*" ","
                           "-*-ohsnap.icons-medium-r-*-*-12-*-*-*-*-*-*-*";
*/
static const char font[] = "-*-ohsnap.icons-medium-r-*-*-14-*-*-*-*-*-*-*";
#define NUMCOLORS 12
static const char colors[NUMCOLORS][ColLast][9] = {
  // border foreground background
  { "#282a2e", "#eeeeee", "#1d1f21" }, // 1 = normal (grey on black)
  { "#72c6fa", "#c5c8c6", "#1d1f21" }, // 2 = selected (white on black)
  { "#dc322f", "#1d1f21", "#2cF6fa" }, // 3 = urgent (black on yellow)
  { "#282a2e", "#282a2e", "#1d1f21" }, // 4 = darkgrey on black (for glyphs)
  { "#282a2e", "#1d1f21", "#282a2e" }, // 5 = black on darkgrey (for glyphs)
  { "#282a2e", "#cc6666", "#1d1f21" }, // 6 = red on black
  { "#282a2e", "#b5bd68", "#1d1f21" }, // 7 = green on black
  { "#282a2e", "#de935f", "#282a2e" }, // 8 = orange on black
  { "#282a2e", "#f0c674", "#1d1f21" }, // 9 = yellow on darkgrey
  { "#282a2e", "#81a2be", "#1d1f21" }, // A = blue on darkgrey
  { "#282a2e", "#b28adf", "#282a2e" }, // B = magenta on darkgrey
  { "#282a2e", "#8abeb7", "#282a2e" }, // C = cyan on darkgrey
};

static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 8;        /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool extrabar					= False;
/* tagging */
static const char *tags[] = { "½","©", "¨", "Ñ", "Ç" };

static const Rule rules[] = {
  /* class                      instance     title  tags mask isfloating  iscentred   monitor */
  { "feh",                      NULL,        NULL,  0,        True,       True,       -1 },
  { "Xfd",                      NULL,        NULL,  0,        True,       True,       -1 },
  { "Firefox",                  NULL,        NULL,  1 << 0,   False,      True,       -1 },
  { "Gvim",                     NULL,        NULL,  1 << 1,   False,      False,      -1 },
  { "mpv",                      NULL,        NULL,  1 << 3,   False,      False,      -1 },
  { "Transmission",             NULL,        NULL,  1 << 3,   True,       True,       -1 },
  { "Wireshark",                NULL,        NULL,  1 << 4,   True,       True,       -1 },
};

/* layout(s) */
static const float mfact      = 0.65;  /* factor of master area size [0.05..0.95] */
static const int nmaster      = 2;     /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

#include "bstack.c"
#include "gaplessgrid.c"
static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[ ú ]",    NULL },    /* first entry is default */
  { "[ þ ]",    tile },    /* no layout function means floating behavior */
  { "[ õ ]",    bstack },
  { "[ ö ]",    gaplessgrid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[]      = { "dmenu_extended_run", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG], "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *termcmd[]       = { "urxvtc", "-color13", "'#B294BB'", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "urxvtc", "-name", scratchpadname, "-geometry", "100x25", NULL };
static const char *volupcmd[]      = { "amixer", "sset", "Master", "3dB+", NULL };
static const char *voldncmd[]      = { "amixer", "sset", "Master", "3dB-", NULL };
static const char *mpctog[]        = { "mpc", "-q", "toggle", NULL };
static const char *mpcprev[]       = { "mpc", "-q", "prev", NULL };
static const char *mpcnext[]       = { "mpc", "-q", "next", NULL };
static const char *gvim[]          = { "gvim", NULL };
static const char *ranger[]        = { "urxvtc", "-color13", "'#B294BB'", "-e", "ranger", NULL };
static const char *firefox[]       = { "firefox", NULL} ;
static const char *htop[]          = { "urxvtc", "-geometry", "80x7", "-color13", "'#B294BB'", "-e", "htop", NULL };
static const char *music[]         = { "urxvtc", "-color13", "'#B294BB'", "-e", "ncmpcpp", NULL };
static const char *vb[]            = { "VirtualBox", NULL };
static const char *sysshut[]       = { "shutdown", "-h", "now", NULL };
static const char *sysreb[]        = { "reboot", NULL };
static const char *slock[]         = { "slock", NULL };
static const char *panel[]         = { "lxpanel", NULL };
static const char *trans[]         = { "transmission-gtk", NULL };
#include "push.c"
static Key keys[] = {
  /* modifier               key               function        argument */
  { MODKEY,                 XK_p,             spawn,          {.v = dmenucmd } },
  { MODKEY,					        XK_Return,        spawn,          {.v = termcmd } },
  { MODKEY,                 XK_s,             togglescratch,  {.v = scratchpadcmd} },
  { 0,                      0x1008ff13,       spawn,          {.v = volupcmd } },
  { 0,                      0x1008ff11,       spawn,          {.v = voldncmd } },
  { 0,                      0x1008ff15,       spawn,          {.v = mpctog } },
  { 0,                      0x1008ff16,       spawn,          {.v = mpcprev } },
  { 0,                      0x1008ff17,       spawn,          {.v = mpcnext } },
  { 0,                      0x1008ff54,       spawn,          {.v = termcmd } },
  { 0,                      0x1008ff8E,       spawn,          {.v = gvim } },
  { 0,                      0x1008ff41,       spawn,          {.v = htop } },
  { 0,                      0x1008ff42,       spawn,          {.v = trans} },
  { MODKEY,                 XK_f,			       	spawn,          {.v = firefox } },
  { MODKEY,                 XK_g,			       	spawn,          {.v = gvim   } },
  { MODKEY,                 XK_r,			       	spawn,          {.v = ranger  } },
  { MODKEY,                 XK_n,				      spawn,          {.v = music   } },
  { MODKEY,                 XK_h,       			spawn,          {.v = htop    } },
  { MODKEY,                 XK_v,             spawn,          {.v = vb } },
  { MODKEY|ControlMask,     XK_s,             spawn,          {.v = sysshut } },
  { MODKEY|ControlMask,     XK_r,             spawn,          {.v = sysreb } },
  { MODKEY|ControlMask,     XK_l,             spawn,          {.v = slock } },
  { MODKEY,                 XK_x,             spawn,          {.v = panel } },
  { MODKEY,                 XK_b,             togglebar,      {0} },
  { MODKEY,                 XK_j,             focusstack,     {.i = +1 } },
  { MODKEY,                 XK_k,             focusstack,     {.i = -1 } },
  { MODKEY|ShiftMask,       XK_j,             pushdown,       {0} },
  { MODKEY|ShiftMask,       XK_k,             pushup,         {0} },
  { MODKEY,                 XK_i,             incnmaster,     {.i = +1 } },
  { MODKEY,                 XK_d,             incnmaster,     {.i = -1 } },
  { MODKEY,                 XK_h,             setmfact,       {.f = -0.05} },
  { MODKEY,                 XK_l,             setmfact,       {.f = +0.05} },
  { MODKEY|ShiftMask,       XK_Return,        zoom,           {0} },
  { MODKEY,                 XK_Tab,           view,           {0} },
  { MODKEY|ShiftMask,       XK_c,             killclient,     {0} },
  { MODKEY|ControlMask,     XK_n,             setlayout,      {.v = &layouts[0]} },
  { MODKEY|ControlMask,     XK_t,             setlayout,      {.v = &layouts[1]} },
  { MODKEY|ControlMask,     XK_b,             setlayout,      {.v = &layouts[2]} },
  { MODKEY|ControlMask,     XK_g,             setlayout,      {.v = &layouts[3]} },
  { MODKEY,                 XK_space,         setlayout,      {0} },
  { MODKEY|ShiftMask,       XK_space,         togglefloating, {0} },
  { MODKEY,                 XK_0,             view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,       XK_0,             tag,            {.ui = ~0 } },
  { MODKEY,                 XK_comma,         focusmon,       {.i = -1 } },
  { MODKEY,                 XK_period,        focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,       XK_comma,         tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,       XK_period,        tagmon,         {.i = +1 } },
  TAGKEYS(                  XK_1,                             0)
    TAGKEYS(                  XK_2,                             1)
    TAGKEYS(                  XK_3,                             2)
    TAGKEYS(                  XK_4,                             3)
    TAGKEYS(                  XK_5,                             4)
    TAGKEYS(                  XK_6,                             5)
    TAGKEYS(                  XK_7,                             6)
    TAGKEYS(                  XK_8,                             7)
    TAGKEYS(                  XK_9,                             8)
    { MODKEY|ShiftMask,       XK_q,             quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        toggleview,     {0} },
  { ClkTagBar,            0,              Button3,        view,           {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
