/// \file Net.h
/// \author Paolo Mazzon
/// \brief General netcode stuff that doesn't belong to the client
#pragma once
#include "Nym/Structs.h"
#include "Nym/Packet.h"

/// \brief Handles a few different packet types (connection, initial, lobby, and message packets)
void nymNetHandlePacket(NymGame game, NymPacketServerMaster *packet);