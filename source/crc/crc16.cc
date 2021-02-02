
#include "crc16.h"

uint16_t crc16_table[256]={
  0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7, //   8
  0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF, //  16 
  0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6, //  24
  0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE, //  32
  0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485, //  40
  0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D, //  48
  0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4, //  56
  0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC, //  64
  0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823, //  72
  0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B, //  80
  0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12, //  88
  0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A, //  96
  0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41, // 104
  0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49, // 112
  0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70, // 120
  0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78, // 128
  0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F, // 136
  0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067, // 144
  0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E, // 152
  0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256, // 160
  0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D, // 168
  0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405, // 176
  0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C, // 184
  0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634, // 192
  0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB, // 200
  0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3, // 208
  0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A, // 216
  0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92, // 224
  0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9, // 232
  0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1, // 240
  0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8, // 248
  0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0};// 256

uint16_t CalculateCRC16 (void *pData, uint32_t uiDataLen)
{
//var
    unsigned char *ptr = nullptr;
    uint16_t c = 0,
             a = 0,
             b = 0;
    uint32_t n = 0;

//code
    ptr = (unsigned char*) pData;
    c   = 0xffff;

    for (n = 0; n < uiDataLen; n++)
    {
        a = c>>8;
        b = (c<<8)&0xffff;
        c = crc16_table [ *ptr ^ a ] ^ b;
        ptr++;
    }
    return (c ^ 0xffff);
}

/*
{
	unsigned char *ptr = (unsigned char *)pData;
	unsigned int c = 0xffff,a,b;
	int n;
	for (n = 0; n < dataLen; n++)
	{
		a=c>>8;
		b=(c<<8)&0xffff;
		c = crc16_table[ *ptr++ ^ a ] ^ b;
	}
	return c ^ 0xffff;
}
*/

uint16_t RoutineCRC16Char2ui16 (uint8_t uiCh)
{
    switch (uiCh)
    {
        case '0' : return 0x0000;
        case '1' : return 0x0001;
        case '2' : return 0x0002;
        case '3' : return 0x0003;
        case '4' : return 0x0004;
        case '5' : return 0x0005;
        case '6' : return 0x0006;
        case '7' : return 0x0007;
        case '8' : return 0x0008;
        case '9' : return 0x0009;
        case 'a' : 
        case 'A' : return 0x000A;
        case 'b' : 
        case 'B' : return 0x000B;
        case 'c' : 
        case 'C' : return 0x000C;
        case 'd' : 
        case 'D' : return 0x000D;
        case 'e' : 
        case 'E' : return 0x000E;
        case 'f' : 
        case 'F' : return 0x000F;
    }
    return 0xFFFF;
}

uint8_t RoutineCRC16ui162Char (uint16_t ui)
{
    switch (ui)
    {
        case 0      : return '0';
        case 1      : return '1';
        case 2      : return '2';
        case 3      : return '3';
        case 4      : return '4';
        case 5      : return '5';
        case 6      : return '6';
        case 7      : return '7';
        case 8      : return '8';
        case 9      : return '9';
        case 0x000A : return 'A';
        case 0x000B : return 'B';
        case 0x000C : return 'C';
        case 0x000D : return 'D';
        case 0x000E : return 'E';
        case 0x000F : return 'F';
    }
    return '*';
}
