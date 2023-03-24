#ifndef MESSAGE_INSTANCE_H
#define MESSAGE_INSTANCE_H

#include <iostream>
#include <string>

using namespace std;

enum MsgType {
  MSG_INFO = 0,
  MSG_CRITICAL_WARNING,
  MSG_WARNING,
  MSG_ERROR
};

class MessageInstance
{
  public:
    MessageInstance(MsgType type, string& deviceName, string& msgString):
      mSeverity(type), mDeviceName(deviceName), mMsgString(msgString){};
    void CreateMsgString(string& msgStr);
    string CreateMsgTypeToStr(MsgType& msgType);

  private:
    MsgType mSeverity;
    string mDeviceName;
    string mMsgString;
};

#endif
