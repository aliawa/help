
// ---------------------------------------------------------
// 		Given username, password and realm this
// 		program calculates HA1
// 		HA1 = MD5(username:realm:password)
// ---------------------------------------------------------

#include <stdio.h>
#include "osip_md5.h"
#include <string.h>

#define HASHLEN 16
#define HASHHEXLEN 32
#define IN
#define OUT

typedef char Hash_t     [HASHLEN];
typedef char Hash_hex_t [HASHHEXLEN + 1];



void bin2Hex(char bin[16], char hex[32])
{
	char HexDigits[]="0123456789abcdef";
	int i=0, j=0;
	for (; i<16; ++i,j+=2)
	{ 
		hex[j+1] = HexDigits[(bin[i]     ) & 0xF];
		hex[j  ] = HexDigits[(bin[i] >> 4) & 0xF];
	}
}


void DigestCalcHA1 (
		IN const char *pszAlg,
		IN const char *pszUserName,
		IN const char *pszRealm,
		IN const char *pszPassword,
		IN const char *pszNonce,
		IN const char *pszCNonce, 
		OUT Hash_hex_t SessionKey
		)
{
	MD5_CTX Md5Ctx;
	Hash_t HA1;

	MD5Init (&Md5Ctx);
	MD5Update (&Md5Ctx, (unsigned char *) pszUserName, strlen (pszUserName));
	MD5Update (&Md5Ctx, (unsigned char *) ":", 1);
	MD5Update (&Md5Ctx, (unsigned char *) pszRealm, strlen (pszRealm));
	MD5Update (&Md5Ctx, (unsigned char *) ":", 1);
	MD5Update (&Md5Ctx, (unsigned char *) pszPassword, strlen (pszPassword));
	MD5Final ((unsigned char *) HA1, &Md5Ctx);
	if ((pszAlg != NULL) && strcasecmp (pszAlg, "md5-sess") == 0)
	{
		MD5Init (&Md5Ctx);
		MD5Update (&Md5Ctx, (unsigned char *) HA1, HASHLEN);
		MD5Update (&Md5Ctx, (unsigned char *) ":", 1);
		MD5Update (&Md5Ctx, (unsigned char *) pszNonce, strlen (pszNonce));
		MD5Update (&Md5Ctx, (unsigned char *) ":", 1);
		MD5Update (&Md5Ctx, (unsigned char *) pszCNonce, strlen (pszCNonce));
		MD5Final ((unsigned char *) HA1, &Md5Ctx);
	}
	bin2Hex (HA1, SessionKey);
}

int printUsage(const char* name)
{
	printf ("Usage:\n%s <username> <realm> <password>\n", name);
}

int main (int argc, char* argv[])
{
	if(argc < 4)
		printUsage(argv[0]);
	else
	{
		Hash_hex_t hash;
		DigestCalcHA1(
				"MD5", 		// algorithm
				argv[1], 	// username
				argv[2], 	// realm
				argv[3],	// password 
				NULL,		// nonce
				NULL,		// cnonce
				hash);

		printf ("\nusername=%s realm=%s password=%s \nMD5 Hash=%s\n\n", 
				argv[1], argv[2], argv[3], hash);
	}
} 
