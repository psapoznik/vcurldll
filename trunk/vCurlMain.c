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

#include <malloc.h>
#include "vCurlMain.h"
#include "string.h"


MemoryStruct easychunk;

static char *myrealloc(void *ptr, size_t size)
{
  if(ptr)
    return (char *)realloc(ptr, size);
  else
    return (char *)malloc(size);
}

static size_t responseCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
  size_t realsize = size * nmemb;
  MemoryStruct *mem = (MemoryStruct *)data;

  mem->memory = myrealloc(mem->memory, mem->size + realsize + 1);
  if (mem->memory) {
    memcpy(&(mem->memory[mem->size]), ptr, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
  }
  return realsize;
}


EXPORT char* getVersion(void)
{
	return "0.3";
}

EXPORT void easyFree(void)
{
	easychunk.memory=NULL; 
	easychunk.size = 0;
}

EXPORT long curlProcess(char* url, char* vars, int esPost, int timeout)
{
	CURL *curl; 
	CURLcode res; 
	MemoryStruct chunk;

	chunk.memory=NULL; 
	chunk.size = 0;

//	OutputDebugStringA("Entramos en curlProcess");
	curl = curl_easy_init(); 
	if(curl) { 
		curl_easy_setopt(curl, CURLOPT_URL, url); 
		if (esPost)
			curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, responseCallback);
		if (timeout) {
			curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout+1);
			curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, timeout);
		} else {
			curl_easy_setopt(curl, CURLOPT_TIMEOUT, 6);
			curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, 5);
		}
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		if (strlen(vars))
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, vars);
		res = curl_easy_perform(curl); 
		
		curl_easy_cleanup(curl); 
	} 
	return (unsigned long)chunk.memory;
}

EXPORT char* easyPost(char* url, char* vars, int timeout)
{
	CURL *curl; 
	CURLcode res; 

	easychunk.memory=NULL; 
	easychunk.size = 0;

//	OutputDebugStringA("Entramos en curlProcess");
	curl = curl_easy_init(); 
	if(curl) { 
		curl_easy_setopt(curl, CURLOPT_URL, url); 
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, responseCallback);
		if (timeout) {
			curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout+1);
			curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, timeout);
		} else {
			curl_easy_setopt(curl, CURLOPT_TIMEOUT, 6);
			curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, 5);
		}
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&easychunk);
		if (strlen(vars))
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, vars);
		res = curl_easy_perform(curl); 
		
		curl_easy_cleanup(curl); 
	} 
	return easychunk.memory;
}

EXPORT char* easyGet(char* url, int timeout)
{
	CURL *curl; 
	CURLcode res;

	easychunk.memory=NULL; 
	easychunk.size = 0;

//	OutputDebugStringA("Entramos en curlProcess");
	curl = curl_easy_init(); 
	if(curl) { 
		curl_easy_setopt(curl, CURLOPT_URL, url); 
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, responseCallback);
		if (timeout) {
			curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout+1);
			curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, timeout);
		} else {
			curl_easy_setopt(curl, CURLOPT_TIMEOUT, 6);
			curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, 5);
		}
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&easychunk);
		res = curl_easy_perform(curl); 
		
		curl_easy_cleanup(curl); 
	} 
	return easychunk.memory;
}

EXPORT unsigned int init(char* url)
{	
	vCurlStruct* vcurl=(vCurlStruct *)malloc(sizeof(vCurlStruct));

	vcurl->curl=curl_easy_init();
	if (strlen(url)) curl_easy_setopt(vcurl->curl, CURLOPT_URL, url);
	vcurl->chunk.memory=NULL; 
	vcurl->chunk.size = 0;
	return (unsigned int)vcurl;
}

EXPORT void cleanup(vCurlStruct *vcurl)
{	
	curl_easy_cleanup(vcurl->curl);
	if (vcurl->chunk.size>0)
		free(vcurl->chunk.memory);
	free(vcurl);
}

EXPORT long setOpt(vCurlStruct *vcurl, long option, long parameter)
{
	return curl_easy_setopt(vcurl->curl, (CURLoption)option, parameter);
}

EXPORT long setOpt_s(vCurlStruct *vcurl, long option, void* parameter)
{
	return curl_easy_setopt(vcurl->curl, (CURLoption)option, parameter);
}

EXPORT long post(vCurlStruct *vcurl, char* vars)
{
	long res;
	
	if(vcurl) { 
		curl_easy_setopt(vcurl->curl, CURLOPT_WRITEFUNCTION, responseCallback);
		curl_easy_setopt(vcurl->curl, CURLOPT_POST, 1);
		curl_easy_setopt(vcurl->curl, CURLOPT_POSTFIELDS, vars);
		curl_easy_setopt(vcurl->curl, CURLOPT_WRITEDATA, (void *)&vcurl->chunk);
		res = curl_easy_perform(vcurl->curl); 
	} 
	return res;
}

EXPORT long get(vCurlStruct *vcurl)
{
	long res;

	if(vcurl) { 
		curl_easy_setopt(vcurl->curl, CURLOPT_WRITEFUNCTION, responseCallback);
		curl_easy_setopt(vcurl->curl, CURLOPT_WRITEDATA, (void *)&vcurl->chunk);
		res = curl_easy_perform(vcurl->curl); 
	} 
	return res;
}

EXPORT char* getResult(vCurlStruct *vcurl)
{
	return vcurl->chunk.memory;
}

EXPORT void reset(vCurlStruct *vcurl)
{
	curl_easy_reset(vcurl->curl);
}

EXPORT void cFree(char* ptr)
{
	curl_free(ptr);
}


EXPORT const char* strErr(long code)
{
	return curl_easy_strerror((CURLcode)code);
}

EXPORT char* escape(vCurlStruct *vcurl, char* url)
{
	return curl_easy_escape(vcurl->curl, url, 0);
}

EXPORT char* unescape(vCurlStruct *vcurl, char* url)
{
	return curl_easy_unescape(vcurl->curl, url, 0, NULL);
}
