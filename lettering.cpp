
#include "lettering.h"

vector<string> letterM = {
    "    ...     ..      ..    ",
    "  x*8888x.:*8888: -\"888:  ",
    " X   48888X `8888H  8888  ",
    "X8x.  8888X  8888X  !888> ",
    "X8888 X8888  88888  \"*8%- ",
    "'*888!X8888> X8888  xH8>  ",
    "  `?8 `8888  X888X X888>  ",
    "  -^  '888\"  X888  8888>  ",
    "   dx '88~x. !88~  8888>  ",
    " .8888Xf.888x:!    X888X.:",
    ":\"\"888\":~\"888\"     `888*\" ",
    "    \"~'    \"~        \"\"   " };

vector<string> letterA = {
    "      u    ",
    "   us888u. ",
    ".@88 \"8888\"",
    "9888  9888 ",
    "9888  9888 ",
    "9888  9888 ",
    "9888  9888 ",
    "\"888*\"\"888\"",
    " ^Y\"   ^Y' " };

vector<string> letterN = {
    "   u.    u.  ",
    " x@88k u@88c.",
    "^\"8888\"\"8888\"",
    "  8888  888R ",
    "  8888  888R ",
    "  8888  888R ",
    "  8888  888R ",
    " \"*88*\" 8888\"",
    "   \"\"   'Y\"  " };

vector<string> letterO = {
    "       u.  ",
    " ...ue888b ",
    " 088R Y8a8r",
    " 888b I888>",
    " b880 I888>",
    " 8a8R I888>",
    "u8888cJ888 ",
    " \"*8a8*P\"  ",
    "   'Y\"     " };

vector<string> letterR = {
    "   .u    .  ",
    " .d88B :@8c ",
    "=\"8888f8888r",
    "  4888>'88\" ",
    "  4888> '   ",
    "  4888>     ",
    " .d888L .+  ",
    " ^\"8888*\"   ",
    "    \"Y\"     " };

vector<string> wordMANOR = {
    letterM[0] + string(51, ' '),
    letterM[1] + string(51, ' '),
    letterM[2] + string(51, ' '),
    letterM[3] + " " + letterA[0] + " " + letterN[0] + " " + letterO[0] + " " + letterR[0],
    letterM[4] + " " + letterA[1] + " " + letterN[1] + " " + letterO[1] + " " + letterR[1],
    letterM[5] + " " + letterA[2] + " " + letterN[2] + " " + letterO[2] + " " + letterR[2],
    letterM[6] + " " + letterA[3] + " " + letterN[3] + " " + letterO[3] + " " + letterR[3],
    letterM[7] + " " + letterA[4] + " " + letterN[4] + " " + letterO[4] + " " + letterR[4],
    letterM[8] + " " + letterA[5] + " " + letterN[5] + " " + letterO[5] + " " + letterR[5],
    letterM[9] + " " + letterA[6] + " " + letterN[6] + " " + letterO[6] + " " + letterR[6],
    letterM[10] + " " + letterA[7] + " " + letterN[7] + " " + letterO[7] + " " + letterR[7],
    letterM[11] + " " + letterA[8] + " " + letterN[8] + " " + letterO[8] + " " + letterR[8]
};

vector<string> wordTHE = {
    "~~~888~~~ 888               ",
    "   888    888-~88e  e88~~8e ",
    "   888    888  888 d888  88b",
    "   888    888  888 8888__888",
    "   888    888  888 Y888    ,",
    "   888    888  888  \"88___/ " };

vector < string> letterH = {
    "         .xHL        ",
    "      .-`a888hxxx~   ",
    "   .H8X  `%888*\"     ",
    "   ?a8X     ..x..    ",
    "  %>888k .x8888888%  ",
    "   ?8888X    \"88a88X ",
    "    ?8888X    %88888>",
    " H8H %8888     `8888>",
    "'888> 8a8\"      8888 ",
    " \"8` .8\" ..     88*  ",
    "    `  x8888h. d*\"   ",
    "       \"\"*8a8%~      "
};

vector < string> letterU = {
    "   x.    .    ",
    " .@a8k  z88u  ",
    "~\"8888 ^8a88  ",
    "  8888  888R  ",
    "  R888  8880  ",
    "  88a8  888b  ",
    "  R888 ,888B .",
    " \"8888Y 8888\" ",
    "  `Y\"   'YP   "
};

vector < string> letterS {
    "     .   <k",
    "   .@8Ned8\"",
    " .@^%8888\" ",
    "x88:  `)8b.",
    "8888N=*88a8",
    " %8\"    R88",
    "  @8Wou 9% ", 
    ".8a8888P`  ",
    "`   ^\"F    "
};

vector < string> letterE = {
    "     .u   ",
    "  ud8a88. ",
    ":888'8888.",
    "d888 '88%\"",
    "8888.+\"   ",
    "88a8L     ",
    "'8888c. .+",
    " \"888a8%  ",
    "   \"YP'   "
};

vector<string> wordHOUSE = {
    letterH[0] + string(50, ' '),
    letterH[1] + string(50, ' '),
    letterH[2] + string(50, ' '),
    letterH[3] + " " + letterO[0] + " " + letterU[0] + letterS[0] + "  " + letterE[0],
    letterH[4] + " " + letterO[1] + " " + letterU[1] + letterS[1] + "  " + letterE[1],
    letterH[5] + " " + letterO[2] + " " + letterU[2] + letterS[2] + "  " + letterE[2],
    letterH[6] + " " + letterO[3] + " " + letterU[3] + letterS[3] + "  " + letterE[3],
    letterH[7] + " " + letterO[4] + " " + letterU[4] + letterS[4] + "  " + letterE[4],
    letterH[8] + " " + letterO[5] + " " + letterU[5] + letterS[5] + "  " + letterE[5],
    letterH[9] + " " + letterO[6] + " " + letterU[6] + letterS[6] + "  " + letterE[6],
    letterH[10] + " " + letterO[7] + " " + letterU[7] + letterS[7] + "  " + letterE[7],
    letterH[11] + " " + letterO[8] + " " + letterU[8] + letterS[8] + "  " + letterE[8]
};

vector<string> tag_box = {
    "\x1B[38;2;238;130;238m+\x1B[38;2;255;215;0m" + string(20, '-') +"\x1B[38;2;238;130;238m+",
    "\x1B[38;2;255;215;0m|      \x1B[38;2;130;150;160mMADE BY -     \x1B[38;2;255;215;0m|",
    "\x1B[38;2;255;215;0m|" + string(20, ' ') + "|",
    "\x1B[38;2;255;215;0m| \x1B[38;2;255;190;160mHER LADYSHIP GAMES \x1B[38;2;255;215;0m|",
    "\x1B[38;2;238;130;238m+\x1B[38;2;255;215;0m" + string(20, '-') + "\x1B[38;2;238;130;238m+"
};