#include <string.h>
#include <stdio.h>

static const char s_FileName[] = "boxconfig.txt";


/*  Function  : getINIValue
 *
 *  parameters:
 *         iniFile		  : ini file to read
 *		   pParameterName : The name of the parameter to search
 *		   buff			  : buffer that will contain the value
 *						  : IMPORTANT make sure the buffer is large enough for the 
 *						  : value
 */
void getINIValue(FILE* iniFile, const char* pParameterName, char* buff)
{
	char line[255];
	char* pPos;

	buff[0] = '\0';

	// Reposition the file pointer to the beginning of file
	rewind(iniFile);

	// continue reading lines until end of file or other error
	while (fgets(line, 255, iniFile) != NULL) 
	{
		// is it a comment
		if (line[0] == '#')
			continue;

		// Is the first part of line the parameter name then process further
		if (strncmp(pParameterName, line, strlen(pParameterName)) == 0)
		{
			// search for '=' in the text
			if ((pPos =strchr(line, '=')) != NULL)
			{
				// immediately after '=' is the value
				strcpy(buff, ++pPos);
				return;
			}
		}
	}
}



int main(int argc, char** argv)
{
	// variables
	FILE* inputFileHandle;
	char buff[10];


	// Open for read (will fail if file  does not exist)
   if( (inputFileHandle  = fopen( s_FileName, "r" )) == NULL )
      printf( "The file %s was not opened\n", s_FileName );

   getINIValue(inputFileHandle, "IPAddress", buff);
}
