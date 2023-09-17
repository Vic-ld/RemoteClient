#ifndef PACKET_H
#define PACKET_H
#include <iostream>
#include <Windows.h>
#include <qDebug>

using std::string;
#pragma pack(push)
#pragma pack(1)
class Packet
{
public:
    Packet() :sHead(0), nLength(0), sCmd(0), sSum(0) {}
    Packet(WORD nCmd, const BYTE* pData, size_t nSize) {
        sHead = 0xFEFF;
        nLength = nSize + 4;
        sCmd = nCmd;
        if (nSize > 0) {
            strData.resize(nSize);
            memcpy((void*)strData.c_str(), pData, nSize);
        }
        else {
            strData.clear();
        }
        sSum = 0;
        for (size_t j = 0; j < strData.size(); j++)
        {
            sSum += BYTE(strData[j]) & 0xFF;
        }
    }
    Packet(const Packet& pack) {
        sHead = pack.sHead;
        nLength = pack.nLength;
        sCmd = pack.sCmd;
        strData = pack.strData;
        sSum = pack.sSum;
    }
    void Dump(BYTE* pData, size_t nSize)
    {
        string strOut;
        for (size_t i = 0; i < nSize; i++)
        {
            char buf[8] = "";
            if (i > 0 && (i % 16 == 0)) strOut += "\n";
            snprintf(buf, sizeof(buf), "%02X ", pData[i] & 0xFF);
            strOut += buf;
        }
        strOut += "\n";
        OutputDebugStringA(strOut.c_str());
    }
    Packet(const BYTE* pData, size_t& nSize) {
        size_t i = 0;
        for (; i < nSize; i++) {
            if (*(WORD*)(pData + i) == 0xFEFF) {
                sHead = *(WORD*)(pData + i);
                i += 2;
                break;
            }
        }
        if (i + 4 + 2 + 2 > nSize) {//包数据可能不全，或者包头未能全部接收到
            nSize = 0;
            return;
        }
        nLength = *(DWORD*)(pData + i); i += 4;
        //if (nLength + i > nSize) {//包未完全接收到，就返回，解析失败
        if (nLength  > nSize) {//包未完全接收到，就返回，解析失败
           nSize = 0;
           return;
        }
        sCmd = *(WORD*)(pData + i); i += 2;
        if (nLength > 4) {
            strData.resize(nLength - 2 - 2);
            memcpy((void*)strData.c_str(), pData + i, nLength - 4);
            //qDebug()<< "%s\r\n"<< strData.c_str() + 12;
            i += nLength - 4;
        }
        sSum = *(WORD*)(pData + i); i += 2;
        WORD sum = 0;
        for (size_t j = 0; j < strData.size(); j++)
        {
            sum += BYTE(strData[j]) & 0xFF;
        }
        if (sum == sSum) {
            qDebug()<< i;
            nSize = i;//head2 length4 data...
            return;
        }
        nSize = 0;
    }
    ~Packet() {}
    Packet& operator=(const Packet& pack) {
        if (this != &pack) {
            sHead = pack.sHead;
            nLength = pack.nLength;
            sCmd = pack.sCmd;
            strData = pack.strData;
            sSum = pack.sSum;
        }
        return *this;
    }
    int Size() {//包数据的大小
        return nLength + 6;
    }
    const char* Data(std::string& strOut) const {
        strOut.resize(nLength + 6);
        BYTE* pData = (BYTE*)strOut.c_str();
        *(WORD*)pData = sHead; pData += 2;
        *(DWORD*)(pData) = nLength; pData += 4;
        *(WORD*)pData = sCmd; pData += 2;
        memcpy(pData, strData.c_str(), strData.size()); pData += strData.size();
        *(WORD*)pData = sSum;
        return strOut.c_str();
    }

public:
    WORD sHead;//固定位 0xFEFF
    DWORD nLength;//包长度（从控制命令开始，到和校验结束）
    WORD sCmd;//控制命令
    std::string strData;//包数据
    WORD sSum;//和校验
};
#pragma pack(pop)

typedef struct MouseEvent {
    MouseEvent() {
        nAction = 0;
        nButton = -1;
        x = 0;
        y = 0;
    }
    WORD nAction;//点击、移动、双击
    WORD nButton;//左键、右键、中键
    WORD    x;
    WORD    y;
}MOUSEEV, * PMOUSEEV;

typedef struct file_info
{
    file_info()
    {
        IsInvalid = FALSE;
        IsDirectory = -1;
        HasNext = TRUE;
        memset(szFileName, 0, sizeof(szFileName));

    }
    bool IsInvalid;
    bool IsDirectory;
    bool HasNext;
    char szFileName[256];
}FILEINFO, * PFILEINFO;

#endif // PACKET_H
