#include <packetlist.hpp>

using namespace osu;
using namespace packets;

PacketList* PacketList::operator+=(Packet packets[]) { this->append(packets); return this; }
PacketList* PacketList::operator+=(Packet packet) { this->append(packet); return this; }

void PacketList::append(Packet packets[]) {
	for (size_t i = 0; i < (sizeof(*packets)); i++)
		this->packets.push_back(packets[i]); }
void PacketList::append(Packet packet) {
	this->packets.push_back(packet); }

Buffer PacketList::toBuffer() {
	Buffer outBuffer;
	for (auto& packet : this->packets)
		outBuffer.Write(packet.toBuffer());
	return outBuffer;
}