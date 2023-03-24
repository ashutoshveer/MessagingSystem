// Class DeviceInstanceA class defines an instance
// of device to be used for sending messages to
// messaging system

#include <thread>
#include <iostream>

#include "Device.h"
#include "DeviceInstanceA.h" 
#include "MessageManager.h"

namespace DeviceInstanceA{

  void ReadMsgsOnDiffThread()
  {
    string deviceName("Device_A");
    Device deviceA(deviceName);
    while(1)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds{500});
      MsgMgr* msgMgrPtr = MsgMgr::GetMsgMgr();
      msgMgrPtr->AddMsgToMsgMgr(deviceA.GetDeviceMsg());
      cout << "DEBUG: msg sent from " << deviceA.GetDeviceName() << endl; 
    }
  }

  void StartMessaging()
  {
    // Reading messages on a seperate thread so that DeviceInstanceA 
    // main thread is free for any other processing
    std::thread t(ReadMsgsOnDiffThread);
    // use main thread for any processing here
    t.join();
  }
}
