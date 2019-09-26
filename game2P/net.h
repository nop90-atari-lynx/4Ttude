

void netClearBuffer(void);
void netClose(void);
void netInit(void);
void netSendData( char *data, char len);
void netReceiveData( char *data, char len );
unsigned char netListen(void);
unsigned char netConnect(void);
