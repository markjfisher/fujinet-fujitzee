#ifndef MISC_H
#define MISC_H
/* 
 * Include CC65 style Joystick defines for Adam - There is a probably a better way to do this.
 */

#ifdef _CMOC_VERSION_
#include "coco/joystick.h"
#else
#ifdef __ADAM__
#include "adam/joystick.h"
#else
#include <joystick.h>
#include <conio.h>
#endif /* __ADAM__ */
#endif /* _CMOC_VERSION_ */
#include "platform-specific/graphics.h"
#include "platform-specific/input.h"
#include <stdbool.h>
#include <stdint.h>

// FujiNet AppKey settings. These should not be changed
#define AK_LOBBY_CREATOR_ID 1     // FUJINET Lobby
#define AK_LOBBY_APP_ID 1         // Lobby Enabled Game
#define AK_LOBBY_KEY_USERNAME 0   // Lobby Username key
#define AK_LOBBY_KEY_SERVER 3     // Fujzee registered as Lobby appkey 3 at https://github.com/FujiNetWIFI/fujinet-firmware/wiki/SIO-Command-$DC-Open-App-Key

// Fujitzee
#define AK_CREATOR_ID 0xE41C      // Eric Carr's creator id
#define AK_APP_ID 3               // Fujzee App ID
#define AK_KEY_PREFS 0            // Preferences

#define PREF_HELP 0  // 1/2 - seen help screen no/yes
#define PREF_COLOR 1 // 1/2 - Color mode
#define PREF_LOCAL 2 // 1/8 - If appkey is manually set to 0xFF, use localhost instead of prod server

#define PLAYER_MAX 12

#define FUJITZEE_SCORE 14

typedef struct {
  char* table;
  char* name;
  char players[6];
} Table;

typedef struct {
  char* name;
  uint8_t alias;
  int16_t scores[16];
} Player;

typedef struct {
  char* move;
  char* name; 
} ValidMove;

typedef struct {

  // State received from server
  char* prompt;
  uint8_t round;
  uint8_t rollsLeft;
  int8_t activePlayer;
  uint8_t moveTime;
  uint8_t viewing;
  char* dice;
  char* keepRoll;
  Player players[PLAYER_MAX];
  int16_t validScores[15];
  char serverName[20];

  // Table info
  Table tables[10];
  uint8_t tableCount;

  // Internal game state
  uint8_t playerCount;
  uint8_t rollFrames;

  uint8_t prevRollsLeft;
  uint8_t prevPlayerCount;
  uint8_t prevRound;

  uint8_t apiCallWait;

  int8_t prevActivePlayer;
  
  bool playerMadeMove;
  bool promptChanged;
  bool countdownStarted;
  bool waitingOnEndGameContinue;
} GameState;

typedef struct {
  unsigned char key;
  bool trigger;
  int8_t dirX;
  int8_t dirY;
} InputStruct;


extern uint16_t rx_len, maxJifs;
extern bool forceReadyUpdates;
extern char tempBuffer[128];
extern char query[50];
extern char playerName[12];
extern char serverEndpoint[50];
extern char localServer[50];

extern GameState state;
extern InputStruct input;

// Common local scope temp variables
extern unsigned char h, i, j, k, x, y;
extern char prefs[10];

void pause(unsigned char frames);
void clearCommonInput();
void readCommonInput();
void loadPrefs();
void savePrefs();

void read_appkey(uint16_t creator_id, uint8_t app_id, uint8_t key_id, uint8_t* destination);
void write_appkey(uint16_t creator_id, uint8_t app_id, uint8_t key_id, uint8_t *inputString);

#endif /* MISC_H */