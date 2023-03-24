// Class MessageInstance can be used to modify/add any new fields to the message
// without impacting in Device Instances

#include "MessageInstance.h"
#include <assert.h>

#define SPACE " "
#define OPENBRACE "["
#define CLOSEBRACE "]"

string MessageInstance::CreateMsgTypeToStr(MsgType& msgType)
{
  switch(msgType)
  {
    case MSG_INFO:               return "INFO :";
    case MSG_CRITICAL_WARNING:   return "CRITICAL_WARNING :";
    case MSG_WARNING:            return "WARNING :";
    case MSG_ERROR:              return "ERROR :";
    default:                     assert(0);
  }
  return ("");
}

// create Device specific string from message Instance
void MessageInstance::CreateMsgString(string& msgString)
{
  msgString.clear();
  msgString += CreateMsgTypeToStr(mSeverity);
  msgString += OPENBRACE;
  msgString += mDeviceName;
  msgString += CLOSEBRACE;
  msgString += SPACE;
  msgString += mMsgString;
}
