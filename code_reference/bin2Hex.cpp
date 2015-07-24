#include <iostream>

//
// Converting binary to Hexadecimal
// bin2Hex
//


using namespace std;


void arrayOut(char a[], int size)
{
	for (int i = size - 1; i >= 0; --i)
	{
		cout << a[i] << " ";
	} 
	cout << endl;
}



void bin2Hex(char bin[16], char hex[32])
{
	char HexDigits[] = "0123456789abcdef";
	for (int i=0, j=0; i<16; ++i,j+=2)
	{ 
		hex[j  ] = HexDigits[ (bin[i]     ) & 0xf ];
		hex[j+1] = HexDigits[ (bin[i] >> 4) & 0xf ];
	}
}



void getbin(char bin[16])
{
	for (int i = 0; i < 16; ++i)
	{
		bin[i] = i;
	}

	bin[0]=0xff;
	bin[1]=100;
	bin[2]=0xab;
}


int main ()
{
	char bin[16];
	getbin(bin);

	char hex[32];
	bin2Hex(bin, hex);

	arrayOut(hex, 32);
}

