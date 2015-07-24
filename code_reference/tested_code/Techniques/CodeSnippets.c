/*
 * bit-sized declarations.
 */
typedef unsigned char       u8_t;
typedef unsigned short int  u16_t;
typedef unsigned long int   u32_t;



// -------------------------------------------------------------------------------------


/*
 * Convert a hex string like "3A" into a binary number
 */


// hex to number
unsigned char hton(char hexChar)
{
	// is it from 0 to 9
	if (hexChar >47 && hexChar < 58)
		return hexChar - 48;

	// is it from A to F
	else if (hexChar >64 && hexChar < 71)
		return hexChar - 55;

    // is it from a to f
	else if (hexChar >96 && hexChar < 123)
		return hexChar - 87;

	// this was not a hex char
	else
		return 0;

}

// hex to byte
unsigned char htob(char* pHexString)
{
	// put the first character in the higher nible
	// and the second in the lower nibble
	return hton(pHexString[0]) << 4 | hton(pHexString[1]);
}


// hex to integer (32 bit)
unsigned int htoi(char* pHexString)
{
	return
		hton(pHexString[0])<<28 |
		hton(pHexString[1])<<24	|
		hton(pHexString[2])<<20 |
		hton(pHexString[3])<<16 |
		hton(pHexString[4])<<12 |
		hton(pHexString[5])<<8	|
		hton(pHexString[6])<<4	|
		hton(pHexString[7])	;
}

int main(int argc, char** argv)
{
	unsigned char x;
	unsigned int  y;

	// example usage
	x = htob("A1");  // decimal 161
	x = htob("10");  // decimal 16
	x = htob("12");  // decimal 18
	x = htob("FF");  // decimal 255
	y = htoi("ABCD1234");
}


// -------------------------------------------------------------------------------------


//
//  Convert a dotted decimal IP address to u32.
//    Takes an IP address in the form a.b.c.d and return a
//    32 bit representation of this address.
//
u32_t ipAddressStrToU32(char *strIPAddress)
{
   u8_t  u8Value     = 0;
   u8_t  u8BytePos   = 32;
   u32_t u32Result   = 0;
   char ch;


   do{
       ch = *strIPAddress;

       if (ch < 57 && ch > 47) // also if (ch != '.' && ch != 0)
           u8Value = (u8Value * 10) + ch - '0';
       else
       {
           u8BytePos-=8;
           u32Result |= (u8Value << u8BytePos);
           u8Value=0;
       }
       strIPAddress++;
   }
   while (ch && u8BytePos );

   return u32Result;
}



// -------------------------------------------------------------------------------------


//
//  Fast Mod for powers of 2
//
int main(int argc, char* argv[])
{

    int n=64;

    for (int i=0; i<1000; ++i)
    {
        // normal modulus
        if ((i % n) == 0)
            printf ("mod %d\n", i);

        // this modulus does not involve division
        // but works for powers of 2 only
        // eg. 2, 4, 8, 16, 32, 64 ...
        if ((i & (n-1))== 0)
            printf ("fast mod %d \n", i);
    }

    return 0;
}


// -------------------------------------------------------------------------------------

//
//      calculate the nearest boundry to a given number
//      works only for powers of two.
//      2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, ...
//
int main(int argc, char* argv[])
{

    int number              = 55;
    int nextHigherBoundary  = 0;
    int boundry             = 16;


    // find the next higher "boundary" bit boundary to "number"
    nextHigherBoundary = (number + boundry -1) & ~(boundry-1);

    return 0;
}




// -------------------------------------------------------------------------------------


//
// DEMONSTRATES:
// 1. file status using _stat(),
// 2. reading binary data using fread()
// DESCRIPTION:
// Reads upto "nMaxDataSize" bytes from the file "strFileName"
// and copies data into a buffer pointed to by "pData"
// RETERNS:
// return the size of the buffer pointed to by pData
// NOTE:
// it is the responsibility of the caller to free the buffer.
// HEADERS REQURED:
// <sys/stat.h>
//
u32_t GetCodedData(const char* strFileName, u8_t* pData, int nMaxDataSize)
{
   struct _stat statusInfo  ={0};// buffer to collect status information of the file
   int nDataSize            =0;  // How many bytes to read from file
   int nDataRead            =0;  // bytes actually read
   FILE* pSamplesFile       =NULL;

   // make sure we don't read more than nMaxDataSize bytes
   if( _stat( strFileName, &statusInfo ) == 0 )
   {
       nDataSize = statusInfo.st_size;
       if (nDataSize > nMaxDataSize)
           nDataSize = nMaxDataSize;
   }

   if( nDataSize) // if the file size is greater than 0
   {
       pData = (u8_t*) malloc(nDataSize);

       // open file in read-only and binary mode
       pSamplesFile = fopen(strFileName,"rb");

       // read data if file successfully opened
       if (pSamplesFile)
       {
           nDataRead = fread( pData, sizeof( u8_t ), nDataSize, pSamplesFile );
           fclose(pSamplesFile);

       }
   }
   return nDataRead;
}
