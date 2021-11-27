/// \file Structs.h
/// \author Paolo Mazzon
/// \brief Forward declares all structs and important types
#pragma once
#include <stdint.h>

/********************** Typedefs **********************/

typedef int32_t NymPlayerID;

/********************** Forward-Declare Structs **********************/

typedef struct NymGame *NymGame;
typedef struct NymSave *NymSave;
typedef struct NymUIButton NymUIButton;
typedef struct NymClient *NymClient;
typedef struct NymUIMessage NymUIMessage;
typedef struct NymPlayer *NymPlayer;
typedef struct NymPlayerControls NymPlayerControls;
typedef struct NymPlayerState NymPlayerState;
typedef struct NymUITextbox NymUITextbox;
typedef struct NymPacketClientPlayerUpdate NymPacketClientPlayerUpdate;
typedef struct NymPacketClientMessage NymPacketClientMessage;
typedef struct NymPacketClientLobby NymPacketClientLobby;
typedef struct NymPacketClientMaster NymPacketClientMaster;
typedef struct NymPacketServerPlayerUpdates NymPacketServerPlayerUpdates;
typedef struct NymPacketServerMessage NymPacketServerMessage;
typedef struct NymPacketServerLobby NymPacketServerLobby;
typedef struct NymPacketServerMaster NymPacketServerMaster;
typedef struct NymUIChatbox NymUIChatbox;
typedef struct NymPacketServerConnection NymPacketServerConnection;
typedef struct NymPacketServerInitial NymPacketServerInitial;

/********************** Enums **********************/

/// \brief Log levels for the logging function
typedef enum {
	NYM_LOG_LEVEL_MESSAGE = 0,  ///< Just a message
	NYM_LOG_LEVEL_WARNING = 1,  ///< Warning something has gone wrong
	NYM_LOG_LEVEL_ERROR = 2,    ///< Recoverable error
	NYM_LOG_LEVEL_CRITICAL = 3, ///< Fatal error that will crash now the game
} NymLogLevel;

/// \brief All the levels in the game -- must be sequential
typedef enum {
	NYM_LEVEL_SPLASH_SCREEN = 0,    ///< Opening splash screen
	NYM_LEVEL_MENU = 1,             ///< Menu
	NYM_LEVEL_TESTINGARENA = 2,     ///< Testing arena
	NYM_LEVEL_CONNECTIONSCREEN = 3, ///< Connect to server screen
	NYM_LEVEL_LOBBY = 4,            ///< Lobby screen before games
	NYM_LEVEL_GAMEWORLD = 5,        ///< Actual game world where game takes place
	NYM_LEVEL_MAX = 6,              ///< Total number of levels
	NYM_LEVEL_QUIT = 500,           ///< Quit the game
} NymLevel;

/// \brief The type of packet structs
typedef enum {
	NYM_PACKET_TYPE_NONE = 0,                 ///< There is no packet here
	NYM_PACKET_TYPE_CLIENT_PLAYERUPDATE = 1,  ///< Information on this player's movements
	NYM_PACKET_TYPE_CLIENT_MESSAGE = 2,       ///< Client sent a chat message
	NYM_PACKET_TYPE_CLIENT_LOBBY = 3,         ///< Client chose some lobby information
	NYM_PACKET_TYPE_SERVER_PLAYERUPDATES = 4, ///< Server telling the clients other player's information
	NYM_PACKET_TYPE_SERVER_MESSAGE = 5,       ///< Server providing new chat message
	NYM_PACKET_TYPE_SERVER_LOBBY = 6,         ///< Server's lobby choices from other players
	NYM_PACKET_TYPE_SERVER_INITIAL = 7,       ///< Initial information the server sends on connecting
	NYM_PACKET_TYPE_MAX = 8,                  ///< Max number of packet types
} NymPacketType;

/// \brief Status of the client
typedef enum {
	NYM_CLIENT_STATUS_OK = 0,           ///< Business as usual
	NYM_CLIENT_STATUS_DISCONNECTED = 1, ///< Disconnected from server
	NYM_CLIENT_STATUS_TIMEOUT = 2,      ///< Server timed out
	NYM_CLIENT_STATUS_KICKED = 3,       ///< Server kicked this client
	NYM_CLIENT_STATUS_ERROR = 4,        ///< An error occurred
	NYM_CLIENT_STATUS_KILL = 5,         ///< Kill the client thread and shutdown (internal use)
	NYM_CLIENT_STATUS_MAX = 6,          ///< Max number of status codes
} NymClientStatus;

/// \brief Whether this is a new connection or a disconnect for connection packets
typedef enum {
	NYM_CONNECT_NEWCONNECTION = 0,        ///< A new player has connected
	NYM_CONNECT_DISCONNECTED_TIMEOUT = 1, ///< Player disconnected due to timeout
	NYM_CONNECT_DISCONNECTED_NORMAL = 2,  ///< Player disconnected of their own will
	NYM_CONNECT_DISCONNECTED_KICK = 3,    ///< Player was kicked from the game
	NYM_CONNECT_MAX = 4,                  ///< Max number of connection types
} NymConnectType;