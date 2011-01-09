#pragma once

#include "oboylib/CrtDbgInc.h"

namespace oboy
{
	void aesEncrypt(const unsigned char *key, 
		const char *inData, int inDataSize, 
		char **outData, int *outDataSize);

	void aesDecrypt(const unsigned char *key, 
		const char *inData, int inDataSize, 
		char **outData, int *outDataSize);

	bool loadDecrypt(const unsigned char *key, 
		const char *filename, 
		char **outData, int *outDataSize);

}
