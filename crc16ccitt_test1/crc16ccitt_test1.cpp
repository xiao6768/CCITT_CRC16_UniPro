// crc16ccitt_test1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

typedef unsigned short uint16_t;

typedef unsigned char uint8_t;

typedef unsigned __int16    INT16U;
typedef unsigned char BYTE;


unsigned short calc_crc16_ccitt(unsigned int *p, int size_in_dword, unsigned int seed, unsigned char calc_width_int_bits)
{
	if (calc_width_int_bits >= 32)
		return 0;
	unsigned int bitn_data = 0x1 << (calc_width_int_bits- 1);
	unsigned int temp = seed;

	unsigned int data = *p++;

	while (size_in_dword--)
	{

		for (int i = bitn_data; i != 0; i = i >> 1)
		{
			temp <<= 1;
			if ((temp & 0x10000) != 0)
			{
				temp = temp ^ 0x11021;
			}
			if ((data & i) != 0)
			{
				temp ^= (0x10000 ^ 0x11021);
			}
		}

		data = *p++;
	}

	return (~temp) & 0xFFFF;
}


int main()
{
	

	unsigned int dw_data[] = { 0x10107, 0x8284
		,0x3132, 0x3334, 0x3536, 0x3738, 0x3941, 0x4243, 0x1012A
	};

	unsigned short crc4 = calc_crc16_ccitt(&dw_data[0], sizeof(dw_data) / sizeof(unsigned int), 0xFFFF, 17);
	printf("crc4 = 0x%X\r\n", crc4);

    return 0;
}

