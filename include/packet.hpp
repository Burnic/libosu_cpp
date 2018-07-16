#ifndef LIBOSU_INCLUDE_PACKET_HPP
#define LIBOSU_INCLUDE_PACKET_HPP

#include <buffer.hpp>
#include <packetids.hpp>

namespace osu {
	namespace packets {
		class Packet {
		public:
			Packet(osu::packets::PacketID ID);
			Packet(osu::packets::PacketID ID, osu::Buffer Data);

			osu::Buffer toBuffer();
		private:
			osu::packets::PacketID ID;
			osu::Buffer Data;
		};
	}
}

#endif