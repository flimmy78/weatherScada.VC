#ifdef WIN32
#include <memory.h>
#else
#include <string.h>
#endif
#include "basedef.h"
#include "protocol.h"

/*
**	��������������֡.
**	@buf:	���ͻ�����
**	@bufSize:	���ͻ���������
**	@pProto:	����֡������Ϣ
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

