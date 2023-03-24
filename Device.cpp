// Class Device/ Class DeviceBase is used to
// implement basic Device functionality 
// to be derived by different devices

#include "MessageInstance.h"
#include "Device.h"

#define DELIMITER "-"

Device::Device(string& deviceName) : mDeviceName(deviceName){}

Device::Device(string& deviceName, string& deviceDesc) : mDeviceName(deviceName), mDeviceDesc(deviceDesc){}

static string GetNextMessageNumber()
{
  static string msgStr("0");
  bool carry = true;
  for (auto iter = msgStr.rbegin(); iter != msgStr.rend(); iter++)
  {
    if (carry == true)
    {
      if (*iter == '9')
      {
        *iter = '0';
        carry = true;
      }
      else
      {
        *iter += 1;
        carry = false;
      }
    }
    else
    {
      break;
    }
  }

  if (carry == true)
  {
    msgStr = "1" + msgStr;
  }
  return msgStr;
}

// Thread safe API for getting the device message instance 
// having the device message details
shared_ptr<MessageInstance> Device::GetDeviceMsg()
{
  std::unique_lock<std::mutex> lock(mMutex);
  string msg;
  msg += "message no";
  msg += DELIMITER;
  msg += GetNextMessageNumber();
  
  return make_shared<MessageInstance> (MsgType::MSG_INFO, GetDeviceName(), msg);
}
