
#include "log.h"
#include <stddef.h>
#include <ctype.h>
#include <memory.h>
#include <malloc.h>

/*
 * 将字符转换为数值
 * */
int c2i(char ch)
{
    // 如果是数字，则用数字的ASCII码减去48, 如果ch = '2' ,则 '2' - 48 = 2
    if(isdigit(ch))
        return ch - 48;

    // 如果是字母，但不是A~F,a~f则返回
    if( ch < 'A' || (ch > 'F' && ch < 'a') || ch > 'z' )
        return -1;

    // 如果是大写字母，则用数字的ASCII码减去55, 如果ch = 'A' ,则 'A' - 55 = 10
    // 如果是小写字母，则用数字的ASCII码减去87, 如果ch = 'a' ,则 'a' - 87 = 10
    if(isalpha(ch))
        return isupper(ch) ? ch - 55 : ch - 87;

    return -1;
}

char *bufhex2str(const unsigned char *buffer, long len)
{
    static const char hexdig[] = "0123456789ABCDEF";
    char *tmp, *q;
    const unsigned char *p;
    int i;

    if (len == 0)
        return malloc(1);

    if ((tmp = malloc(len * 2)) == NULL) {
        LOGE("buf2hexstr malloc error.");
        return NULL;
    }
    q = tmp;
    for (i = 0, p = buffer; i < len; i++, p++) {
        *q++ = hexdig[(*p >> 4) & 0xf];
        *q++ = hexdig[*p & 0xf];
    }
    //q[-1] = 0;
#ifdef CHARSET_EBCDIC
    ebcdic2ascii(tmp, tmp, q - tmp - 1);
#endif

    return tmp;
}

unsigned char *hex2strbuf(const char *str, long *len)
{
    unsigned char *hexbuf, *q;
    unsigned char ch, cl;
    int chi, cli;
    const unsigned char *p;
    size_t s;

    s = strlen(str);
    if ((hexbuf = malloc(s >> 1)) == NULL) {
        LOGE("hexstr2buf malloc error.");
        return NULL;
    }
    for (p = (const unsigned char *)str, q = hexbuf; *p; ) {
        ch = *p++;
//        if (ch == ':')
//            continue;
        cl = *p++;
        if (!cl) {
            LOGE("hexstr2buf address null error.");
            free(hexbuf);
            return NULL;
        }
        cli = c2i(cl);
        chi = c2i(ch);
        if (cli < 0 || chi < 0) {
            LOGE("hexstr2buf calculate error.");
            free(hexbuf);
            return NULL;
        }
        *q++ = (unsigned char)((chi << 4) | cli);
    }

    if (len)
        *len = q - hexbuf;
    return hexbuf;
}

int hex2strEncode(const char *input, int input_len, unsigned char *hexStr)
{

    //const char HexCode[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

    unsigned char *hexStr1 = bufhex2str(input,input_len);

    memcpy(hexStr,hexStr1,input_len*2);

    LOGD("hexStr->%s",hexStr);
//
//    for (int i = 0; i <input_len ; ++i){
//        hexStr[2*i]=HexCode[input[i] / 16];
//        hexStr[2*i+1]=HexCode[input[i] % 16];
//    }
//
//    hexStr[input_len*2+1]='\0';

   // LOGE(" %s ",hexStr);

    return 0;
}

int hex2strDecode(unsigned char *hexStr,unsigned char *output){

    int binSize = 0;
    unsigned char *output1 = hex2strbuf(hexStr,&binSize);

    memcpy(output,output1,binSize);

    //LOGD("bufStr->%s",output);

    return binSize;
}
