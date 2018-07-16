#include <buffer.hpp>
#include <exceptions.hpp>
#include <sstream>

using namespace osu;
using namespace std;

void Buffer::allocate(size_t size) {
    for (size_t i = 0; i < size; ++i)
        this->raw_Buffer.push_back(0x00); }
void Buffer::seek(size_t pos){
	if (this->raw_Buffer.size() < pos)
		throw(POS_OUT_OF_RANGE);
	this->readpos = pos; }
size_t Buffer::Size() {
    return this->raw_Buffer.size(); }
string Buffer::toString() {
	stringstream out;
	for (size_t i = 0; i < this->raw_Buffer.size(); i++) {
		out << std::hex << this->raw_Buffer.at(i);
	}
	return out.str(); }

void Buffer::Write(const char* x) {
	this->allocate(strlen(x));
	for (size_t i = 0; i < strlen(x); ++i)
		this->raw_Buffer.at(this->pos++) = x[i]; }
void Buffer::Write(string x) {
	this->allocate(x.length());
	for (size_t i = 0; i < x.length(); ++i)
		this->raw_Buffer.at(this->pos++) = x[i]; }
void Buffer::Write(string x, bool o) {
	if (o) {
		if (x.length() <= 0) {
			this->Write((uint8_t)0x0B);
			this->allocate(1); // add an empty byte for (string Len = 0)
			return;
		}
		this->Write((uint8_t)0x0B);
		this->WriteULEB128(x.length());
		this->Write(x);
	} else
		this->Write(x);
}
void Buffer::Write(bool b) {
	this->Write((uint8_t)b); }
void Buffer::Write(int8_t i) {
	this->allocate(1);
	this->raw_Buffer.at(this->pos++) = (uint8_t) i; }
void Buffer::Write(uint8_t i) {
	this->allocate(1);
	this->raw_Buffer.at(this->pos++) = (uint8_t)i; }
void Buffer::Write(int16_t i) {
	Buffer by = Cast2Char(i);
	this->Write(by); }
void Buffer::Write(uint16_t i) {
	Buffer by = Cast2Char(i);
	this->Write(by); }
void Buffer::Write(int32_t i) {
	Buffer by = Cast2Char(i);
	this->Write(by); }
void Buffer::Write(uint32_t i) {
	Buffer by = Cast2Char(i);
	this->Write(by); }
void Buffer::Write(int64_t i) {
	Buffer by = Cast2Char(i);
	this->Write(by); }
void Buffer::Write(uint64_t i) {
	Buffer by = Cast2Char(i);
	this->Write(by); }
void Buffer::Write(float_t i) {
	Buffer by = Cast2Char(i);
	this->Write(by); }
void Buffer::Write(double_t i) {
	Buffer by = Cast2Char(i);
	this->Write(by); }
void Buffer::Write(Buffer b) {
	for (uint8_t &byte : b.raw_Buffer)
		this->Write(byte); }
void Buffer::WriteULEB128(uint64_t i) {
	Buffer out;
	do {
		uint8_t byte;
		byte = i & 0x7F;
		i >>= 0x07;
		if (i != 0)
			byte |= 0x80;
		out.Write(byte);
	} while (i > 0);
	this->Write(out);
}

string Buffer::Read(const size_t size) {
	if (this->readpos + size > this->raw_Buffer.size())
		throw(POS_OUT_OF_RANGE);

	stringstream out;
	size_t i = 0;
	while (i != size) {
		out << std::hex << this->raw_Buffer.at(this->readpos++);
		i++;
	}
	return out.str();
}
uint8_t Buffer::ReadByte() {
	return this->Read(1).c_str()[0]; }
string Buffer::ReadOsuString() {
	uint8_t byte = this->ReadByte();
	if (byte != 0x0B) {
		this->pos--;
		throw IS_NOT_STRING;
	}
	size_t StrLength = this->ReadULEB128();
	string bytes = this->Read(StrLength);
	return bytes;
}
int16_t Buffer::ReadSInt16() {
	uint8_t x[2]{ this->ReadByte(), this->ReadByte() };
	return (x[0] | x[1] << 8);
}
uint16_t Buffer::ReadUInt16() {
	uint8_t x[2]{ this->ReadByte(), this->ReadByte() };
	return (x[0] | x[1] << 8); }
int32_t Buffer::ReadSInt32() {
	uint8_t x[4];
	for (size_t i = 0; i < sizeof(int32_t); i++)
		x[i] = this->ReadByte();

	return (
		x[0] |
		x[1] << 8 |
		x[2]  << 16 |
		x[3] << 24
	);
}
uint32_t Buffer::ReadUInt32() {
	uint8_t x[4];
	for (size_t i = 0; i < sizeof(uint32_t); i++)
		x[i] = this->ReadByte();

	return (
		x[0] |
		x[1] << 8 |
		x[2] << 16 |
		x[3] << 24
	);
}
int64_t Buffer::ReadSInt64() {
	uint8_t x[8];
	for (size_t i = 0; i < sizeof(int64_t); i++)
		x[i] = this->ReadByte();

	return (
		x[0] |
		x[1] << 8 |
		x[2] << 16 |
		x[3] << 24 |
		x[4] << 32 |
		x[5] << 40 |
		x[6] << 48 |
		x[7] << 56
	);
}
uint64_t Buffer::ReadUInt64() {
	uint8_t x[8];
	for (size_t i = 0; i < sizeof(uint64_t); i++)
		x[i] = this->ReadByte();

	return (
		x[0] |
		x[1] << 8 |
		x[2] << 16 |
		x[3] << 24 |
		x[4] << 32 |
		x[5] << 40 |
		x[6] << 48 |
		x[7] << 56
	);
}
double_t Buffer::ReadDouble() {
	double_t a;
	memcpy(&a, this->Read(sizeof(double_t)).c_str(), sizeof(double_t));
	return a; }
float_t Buffer::ReadFloat() {
	float_t a;
	memcpy(&a, this->Read(sizeof(float_t)).c_str(), sizeof(float_t));
	return a; }
uint64_t Buffer::ReadULEB128() {
	uint64_t total = 0;
	uint64_t shift = 0;
	uint8_t byte = this->ReadByte();
	if ((byte & 0x80) == 0)
		total |= ((byte & 0x7F) << shift);
	else {
		bool end = false;
		do {
			if (shift)
				byte = this->ReadByte();
			total |= ((byte & 0x7F) << shift);
			if ((byte & 0x80) == 0) end = true;
			shift += 7;
		} while (!end);
	}
	return total; }

void Buffer::Print() {
	std::string s;
	s += "Byte{";
	for (auto &b : this->raw_Buffer) {
		s += to_string(b);
		s += ", ";
	}
	s.pop_back(); s.pop_back(); // Why trim it when here are 2 static characters ? xD
	s += "}\n";
	cout << s; }

bool Buffer::IsLittleEndian() {
	union {
		int i;
		uint8_t byte[4];
	} ile = { 0x0102 };
	
	return ile.byte[0] == 2; }