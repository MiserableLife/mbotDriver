#include "MBotPacket.h"
#include <memory.h>
MBotPacket::MBotPacket(unsigned char* buf, unsigned int len) : buf_(buf), num_fragment_(0), cnt_(0)
{
	unsigned int len_payload  = LEN_PAYLOAD;
	num_fragment_ = len/len_payload;
}
MBotPacket::MBotPacket() : buf_(nullptr), num_fragment_(0), cnt_(0)
{
}

bool 
MBotPacket::assemble()
{
	if(num_fragment_ > cnt_)
		return false;
	return true;

}
void 
MBotPacket::fragment(int i, int len, unsigned char* buf/*out */)
{
	buf[sizeof(FRAGMENT_HEADER)-1] = i;
	if(i== num_fragment_)
		memcpy(buf+sizeof(FRAGMENT_HEADER), buf_ + i*LEN_PAYLOAD, len%(LEN_PAYLOAD+1));
	else
		memcpy(buf + sizeof(FRAGMENT_HEADER), buf_+i*LEN_PAYLOAD, LEN_PAYLOAD);

}
MBotPacket& 
MBotPacket::add(FRAGMENT *fr, unsigned int len)
{
	if(!buf_) //if not initialized
	{
		buf_ = new unsigned char[fr->len];
		unsigned int len_payload  = LEN_PAYLOAD;
		num_fragment_ = fr->len / len_payload;
	}
	memcpy(buf_+fr->seq*LEN_PAYLOAD, fr->payload, len-sizeof(FRAGMENT_HEADER));

	cnt_++;
	return *this;
}



