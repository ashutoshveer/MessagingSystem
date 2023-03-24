// Class DeviceInstanceD class defines an instance
// of device to be used for sending messages to
// messaging system

#include <thread>
#include <iostream>

#include "Device.h"
#include "DeviceInstanceD.h" 
#include "MessageManager.h"

namespace DeviceInstanceD{

  void ReadMsgsOnDiffThread()
  {
    string deviceName("Device_D");
    Device deviceD(deviceName);
    while(1)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds{2000});
      MsgMgr* msgMgrPtr = MsgMgr::GetMsgMgr();
      msgMgrPtr->AddMsgToMsgMgr(deviceD.GetDeviceMsg());
      cout << "DEBUG: msg sent from " << deviceD.GetDeviceName() << endl; 
    }
  }

  void StartMessaging()
  {
    // Reading messages on a seperate thread so that DeviceInstanceD
    // main thread is free for any other processing
    std::thread t(ReadMsgsOnDiffThread);
    // use main thread for any processing here
    t.join();
  }
}
