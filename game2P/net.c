
#include <serial.h>

#define RECEIVE_ACK 255

void netClearBuffer()
{
	unsigned char ch;
	while(ser_get(&ch)== SER_ERR_OK); //empty the buffer
}

void netClose(void)
{
	netClearBuffer();
}
/*
void netInit(void)
{
    struct ser_params params = {
        SER_BAUD_62500, 
        SER_BITS_8,     // only 8 data bits is supported
        SER_STOP_1,     // only 1 stop bit is supported
        SER_PAR_ODD,   // mark, space, even, odd is supported
        SER_HS_NONE     // only "none" is supported
    };
    ser_open(&params);
}
*/
void netSendData( char *data, char len)
{
	unsigned char	count;
	char		ch;

// transmit data
	for(count=0;count<len;count++)
	{
		while(ser_put(data[count]));
// wait end of transmission
		while (ser_get(&ch) != SER_ERR_OK);	
	}
// wait end of transmission
//	while (ser_get(&count) != SER_ERR_OK);	
// wait ACK
	while (ser_get(&ch) != SER_ERR_OK || ch!=RECEIVE_ACK);	
}

void netReceiveData( char *data, char len )
{
	unsigned char	count=0;
	char	ch;
// receive
	while(count<len)
	{
		while(ser_get(&ch) != SER_ERR_OK); 
		data[count++]=ch;
	}
// send ACK	
	while (ser_put(RECEIVE_ACK) != SER_ERR_OK);
// wait end of transmission
	while (ser_get(&count) != SER_ERR_OK);	
}

unsigned char netListen(void)
{
	unsigned char ch=0xff;

	if ( ser_get(&ch) == SER_ERR_OK )
	{
		if(ch==1)
		{
			return 1;
		}
		else 
			return 0;
	}

	return 0;
}

unsigned char netConnect(void)
{
	unsigned char ch=0xff;

	if ( ser_get(&ch) == SER_ERR_OK )
	{
		if(ch==0)
		{
			while (ser_put(1) != SER_ERR_OK);
			while (ser_get(&ch) != SER_ERR_OK);	
			return 1;
		}
		else 
			return 0;
	}
	
	while (ser_put(0) != SER_ERR_OK);
	while (ser_get(&ch) != SER_ERR_OK);	

	return 0;
}
