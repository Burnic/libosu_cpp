#ifndef LIBOSU_INCLUDE_PACKETLIST_HPP
#define LIBOSU_INCLUDE_PACKETLIST_HPP

#include <packet.hpp>

namespace osu {
	namespace packets {
		class PacketList {
		public:
			PacketList(osu::packets::Packet packets[]) { this->append(packets); }
			PacketList(osu::packets::Packet packet) { this->append(packet); }
			PacketList() : packets() {}

			osu::packets::PacketList* operator+=(osu::packets::Packet packets[]);
			osu::packets::PacketList* operator+=(osu::packets::Packet packet);

			void append(osu::packets::Packet packets[]);
			void append(osu::packets::Packet packet);

			osu::Buffer toBuffer();
		private:
			std::vector<osu::packets::Packet> packets;
		};
	}
}

#endif