#ifdef WIN32
#include <memory.h>
#else
#include <string.h>
#endif
#include "basedef.h"
#include "protocol.h"

/*
**	创建集中器发送帧.
**	@buf:	发送缓冲区
**	@bufSize:	发送缓冲区长度
**	@pProto:	发送帧额外信息
*/
static uint8 createFrame(U8 *buf, U16 *bufSize, gateway_protocol_ptr pProto)
{
    U8 *pTemp = buf;

    if (NULL == buf || NULL == bufSize || NULL == pProto)
        return ERR_1;

    memcpy(pTemp, &(pProto->head_str.prefix), sizeof(protocol_head_str));//head
    pTemp += sizeof(protocol_head_str);

    memcpy(pTemp, pProto->pMsgBody, pProto->head_str.bodyLen);//body
    pTemp += pProto->head_str.bodyLen;
    *pTemp++ = pProto->bodyChk;//body check
    memset(pTemp, GATEWAY_SUFIX, GATEWAY_SUFIX_CNT);//suffix
    *bufSize = sizeof(protocol_head_str) + pProto->head_str.bodyLen + GATEWAY_EC_LEN + GATEWAY_SUFIX_CNT;
}

