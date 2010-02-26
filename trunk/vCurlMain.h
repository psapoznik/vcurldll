/*
 * vCurlMain.h
 * Copyright (C) Velneo S.A. 2010 <velneo@velneo.com>
 * 
 * vCurlDll is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * vCurlDll is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifdef WIN32
#define EXPORT __declspec(dllexport)
#include <curl/curl.h>
#else
#define EXPORT  
#include </usr/include/curl/curl.h>
#endif

/* imaginary struct */
typedef struct {
	char *memory;
	size_t size;
} MemoryStruct;


typedef struct {
	CURL* curl;
	MemoryStruct chunk;
} vCurlStruct;


// Declaración de funciones a exportar
EXPORT char* getVersion(void);
EXPORT long curlProcess(char* url, char* vars, int esPost, int timeout);
EXPORT char* easyPost(char* url, char* vars, int timeout);
EXPORT char* easyGet(char* url, int timeout);
EXPORT void easyFree(void);

EXPORT unsigned int init(char* url);
EXPORT void cleanup(vCurlStruct * vcurl);
EXPORT long setOpt(vCurlStruct *vcurl, long option, long parameter);
EXPORT long setOpt_s(vCurlStruct * vcurl, long option, void* parameter);
EXPORT long post(vCurlStruct * vcurl, char* vars);
EXPORT long get(vCurlStruct * vcurl);
EXPORT char* getResult(vCurlStruct *vcurl);
EXPORT void reset(vCurlStruct * vcurl);
EXPORT const char* strErr(long code);
EXPORT void cFree(char* ptr);
EXPORT char* escape(vCurlStruct * vcurl, char* url);
EXPORT char* unescape(vCurlStruct * vcurl, char* url);

