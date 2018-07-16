#include <packet.hpp>
#include <packetids.hpp>

using namespace osu;
using namespace packets;
using namespace std;

Packet::Packet(packets::PacketID ID) {
	this->ID = ID; }

Packet::Packet(packets::PacketID ID, Buffer Data) {
	this->ID = ID;
	this->Data = Data; }

Buffer Packet::toBuffer() {
	Buffer o;
	o.Write((uint16_t)this->ID);
	o.Write(false);
	o.Write((uint32_t)this->Data.Size());
	o.Write(this->Data);
	return o;
}