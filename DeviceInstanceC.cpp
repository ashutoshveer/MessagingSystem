// Class DeviceInstanceC class defines an instance
// of device to be used for sending messages to
// messaging system

#include <thread>
#include <iostream>

#include "Device.h"
#include "DeviceInstanceC.h" 
#include "MessageManager.h"

namespace DeviceInstanceC{

  void ReadMsgsOnDiffThread()
  {
    while(1)
    {
      string deviceName("Device_C");
      Device deviceC(deviceName);
      std::this_thread::sleep_for(std::chrono::milliseconds{1500});
      MsgMgr* msgMgrPtr = MsgMgr::GetMsgMgr();
      msgMgrPtr->AddMsgToMsgMgr(deviceC.GetDeviceMsg());
      cout << "DEBUG: msg sent from " << deviceC.GetDeviceName() << endl; 
    }
  }

  void StartMessaging()
  {
    // Reading messages on a seperate thread so that DeviceInstanceC
    // main thread is free for any other processing
    std::thread t(ReadMsgsOnDiffThread);
    // use main thread for any processing here
    t.join();
  }
}
