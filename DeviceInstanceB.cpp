// Class DeviceInstanceB class defines an instance
// of device to be used for sending messages to
// messaging system

#include <thread>
#include <iostream>

#include "Device.h"
#include "DeviceInstanceB.h" 
#include "MessageManager.h"

namespace DeviceInstanceB{

  void ReadMsgsOnDiffThread()
  {
    string deviceName("Device_B");
    Device deviceB(deviceName);
    while(1)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds{1000});
      MsgMgr* msgMgrPtr = MsgMgr::GetMsgMgr();
      msgMgrPtr->AddMsgToMsgMgr(deviceB.GetDeviceMsg());
      cout << "DEBUG: msg sent from " << deviceB.GetDeviceName() << endl; 
    }
  }

  void StartMessaging()
  {
    // Reading messages on a seperate thread so that DeviceInstanceB
    // main thread is free for any other processing
    std::thread t(ReadMsgsOnDiffThread);
    // use main thread for any processing here
    t.join();
  }
}
