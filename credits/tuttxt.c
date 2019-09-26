const char * tuttxt[16]=
{
"4Ttde is a tic-tac-toe variant played/on a 4x4x4 cubical array of cells./Players take turns placing their/markers in blank cells in the array.",
"The first player to achieve four of/their own markers in a row wins./The winning row can be horizontal,/vertical, or diagonal on a single/board as in regular tic-tac-toe,/or vertically in a column, or a/diagonal line through four boards.",
"When it is your turn move on the board/with the directional pad and place/your move with the A key, then wait/for the move of the opponent.",
"Making 4 in a row is not simlle,/because there are only 72 possible/winning lines, and if two players/place at least one mark on one of/this position, it can not be used/anymore to win the game.",
"The first defence strategy to/learn in this game is to block your/opponent in making a row.",
"To master the game you will have/to learn develop a board situation/where placing a mark on the board you/create several (two or more)/opportunities to make 4 in a row at the/next move, so that the opponent/can block only one.",
"4TTude can be played agaist the/Lynx CPU or versus another player,/playing on the same Lynx alternating/the moves, or with two Lynx/connected with a comlynx cable.",
"RANKED GAME/In ranked games the ranks of the two/players can change on the result of/the game./4Ttude has 3 saveslots, every/saveslot can be used to track the/progresses of a player.",
"Selecting for the first time an unused/saveslot, the player rank starts from/0, but can rise up to 10 winning/against stronger players.",
"When you play agaist the CPU, the CPU/rank is its strength level. By default/the CPU strength is set to your rank 1/(or at 10 if it's your rank, since 10/is the max rank), but you can change/it before starting the game.",
"Start learning the game with a CPU/with a low level, because it is very/hard to beat it when its strength/raises.",
"UNRANKED GAME/Unranked games are useful to train/your skill against the CPU or against/another player.",
"In unranked games the result of the/game is not saved in the savslots,/but you can use two training tools/when you play against the CPU/you can undo moves and you can/ask for hints to the CPU.",
"During your turn press B to use one/of these tools. Beware that asking an/hint to CPU, you will have it according/to the selected CPU strength, so do/not expect anything useful from a/CPU playing at strength 0." ,
"GAME CONTROLS  1/DIR KEYS: Navigate menus or move/A KEY: select options or place a mark/B KEY: access training tools/PAUSE: pause - unpause the game",
"GAME CONTROLS  2/OPT1: change board visualization/OPT2: rotate, mute, unmute musics/PAUSE + OPT1: Back to game menu/PAUSE + OPT2: Rotate the screen/OPT1 + OPT2: clears saves (only/while the game is paused)"
};
/*

GAME OPTIONS

From the menu screen you can open the option menu decide your favourite configuration for the game.

You can have at startup:
- Music ON or OFF
- Alternate views of the board (side wiews, slices and diafonals) ON or OFF
- A mark on the last played move of your opponent ON or OFF

Exiting the Options menu the configuration is saved on the internal EEPROM of the cart.

During the game you can change the configuration using Opt 1 to switch ON / OFF the aternate wiew and the mark on the last opponet move. With Opt 2 you can rotate game musics or mute it.

This changes at the game options are not saved in the internale eeprom, but if you access again the Options menu, the current state of the options is displayed, and exiting the menu it's saved on the EEPROM. 

GAME CONTROLS

DIRECTIONS KEYS: Navigate menus or move on the game board
A KEY: select an option on the menus or place you move during the game
B KEY: access training tools during an unranked game vs the CPU
PAUSE: pause / unpause the game
OPT1: rotate board visualization options (only during a game)
OPT2: rotate musics (during game) and mute unmute it
PAUSE OPT1: Back to game menu
PAUSE OPT2: Rotate the screen
OPT1 OPT2: clears the internal EEPROM (only when the game is paused)
*/
