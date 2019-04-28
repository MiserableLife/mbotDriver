#ifndef _MBOTPACKET_H_
#define _MBOTPACKET_H_

#include <limits>

//#define FRAGMENT_SIZE std::numeric_limits<unsigned short>::max()-1
#define FRAGMENT_SIZE 64000
#define LEN_PAYLOAD FRAGMENT_SIZE-sizeof(FRAGMENT_HEADER)
#define HEADER_CONTENTS   \
	unsigned short id; 			\
	unsigned int len; 			\
	unsigned char seq;
	/* id for packet
		 packet length
		 sequence of fragment
		*/


typedef struct
{
	HEADER_CONTENTS
} FRAGMENT_HEADER;

typedef struct
{
	HEADER_CONTENTS
	unsigned char payload[1];//paylaod
} FRAGMENT;

class MBotPacket
{
private:
	unsigned char cnt_;
	unsigned char num_fragment_;
	unsigned char* buf_;
public:
	MBotPacket(unsigned char* buf, unsigned int len);
	MBotPacket();

	bool assemble();

	void fragment(int i, int len, unsigned char* buf/*out */);
	
	MBotPacket& add(FRAGMENT *fr, unsigned int len);



};


#endif
