#include <mutex>
#include <thread>
#include <iostream>
#include "MessageInstance.h"
#include "MessageManager.h"
#include "Device.h"
#include "DeviceInstanceA.h"
#include "DeviceInstanceB.h"
#include "DeviceInstanceC.h"
#include "DeviceInstanceD.h"
#include <csignal>

void signal_handler(int sigNum)
{
  MsgMgr* msgMgrPtr = MsgMgr::GetMsgMgr();
  cout << "DEBUG: Interrupt signal [" << sigNum << "] received" << endl;
  cout << "DEBUG: Main Application thread. ********** FINAL MESSAGE COUNT = " << msgMgrPtr->GetMessageCount() << "**********" << endl;
  exit(sigNum);
}

void DoSomethingElse()
{
  std::this_thread::sleep_for(std::chrono::milliseconds{500});
  MsgMgr* msgMgrPtr = MsgMgr::GetMsgMgr();
  cout << "DEBUG: Main Application thread. **** Message Count = " << msgMgrPtr->GetMessageCount() << "****" << endl;
}

int main()
{
  signal(SIGABRT, signal_handler);
  signal(SIGINT, signal_handler);
  signal(SIGABRT, signal_handler);
  MsgMgr* msgMgrPtr = MsgMgr::GetMsgMgr();
  string logFileName("DevicesMsg.log");
  MsgMgr::SetOutputFileName(logFileName);
  std::thread threadA(&DeviceInstanceA::StartMessaging);
  std::thread threadB(&DeviceInstanceB::StartMessaging);
  std::thread threadC(&DeviceInstanceC::StartMessaging);
  std::thread threadD(&DeviceInstanceD::StartMessaging);
  while (1)
  {
    DoSomethingElse();
  }
  threadA.join();
  threadB.join();
  threadC.join();
  threadD.join();
}
