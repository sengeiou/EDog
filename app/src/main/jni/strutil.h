﻿#include <stdlib.h>#include <stdio.h>#include <string.h>#include <locale.h>#include <android/log.h>//#include <iconv.h>//#include <wctype.h>//#include <CHAR.h>#ifndef LOG_TAG#define LOG_TAG "androiddll"#endif#define LOGI(...) ((int)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))#if 1size_t get_CHAR_size(const char *str){   size_t len = strlen(str);   size_t size=0;   size_t i;   for(i=0; i < len; i++)   {      if( str[size] >= 0 && str[size] <= 127 ) //不是全角字符      size+=sizeof(char);      else //是全角字符，是中文      {        size+=sizeof(char);        i+=2;      }   }  return size;}/*char *_w2c(const char *pw){   if(!pw)   return NULL;   size_t size= (strlen(pw))*sizeof(char);   char *pc;   if(!(pc = (char*)malloc(size)))   {	 LOGI("malloc fail");     return NULL;   }   wcstombs(pc,pw,size);   return pc;}*//*string w2c(const string pw){   if(!pw)   return NULL;   size_t size= strlen(pw)*sizeof(char);   char *pc;   if(!(pc = (char*)malloc(size)))   {     printf("malloc fail");     return NULL;   }   wcstombs(pc,pw,size);   return pc;}*/char *c2w(const char *pc){   if(!pc)   return NULL;   size_t size_of_ch = strlen(pc)*sizeof(char);   size_t size_of_wc = get_CHAR_size(pc);   char *pw;   if(!(pw = (char*)malloc(size_of_wc)))   {      printf("malloc fail");      return NULL;   }   mbstowcs(pw,pc,size_of_wc);   return pw;}/*int gbk2utf8(char *dst, int outlen,char *src,int inlen){     static iconv_t  its_conv;     char *p1;     its_conv = iconv_open("UTF-8","GBK");     const char*  p = src;     p1 = dst;     iconv(its_conv, &p, &inlen, &p1, &outlen);     //printf("%s\n",out);     iconv_close(its_conv);     return 0;}*/#endif//取得char字符串长度int _wlen(const char* strString){	int i=0;	while(strString[i] != 0)	{		i++;	}	return i;	/*int i=0;    while (1) {        if (strString[i] == 0) {            break;        }else{            i++;        }    }    return i;*/}char *W2C(const char *pw , char *pc){//      *pc++ = *pw >> 8 ;//      *pc = *pw ;	//*pc = *pw >> 8 ;	*pc = *pw & 0xff ;      return 0 ;}/*char *W2C--3(const char *pw , char *pc){//      *pc++ = *pw >> 8 ;//      *pc = *pw ;	//*pc = *pw >> 8 ;	*pc = *pw & 0xff ;      return pc;}*///转换字符串char *wstr2cstr(const char *pwstr, char *pcstr, size_t len) {    char *ptemp = pcstr;    if (pwstr != NULL && pcstr != NULL) {        size_t wstr_len = _wlen(pwstr);        len = (len > wstr_len) ? wstr_len : len;        while (len-- > 0) {            W2C(pwstr, pcstr);            pwstr++;            pcstr += 1;        }        *pcstr = '\0';        return ptemp;    }    return 0;}