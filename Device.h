#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <string>
#include <memory>
#include <mutex>

using namespace std;

class MessageInstance;

class DeviceBase
{
  public:
    virtual string& GetDeviceName() = 0;
    virtual shared_ptr<MessageInstance> GetDeviceMsg() = 0;
};

class Device : public DeviceBase
{
  public:
  Device(string& deviceName);
  Device(string& deviceName, string& deviceDesc);
  
  void SetDeviceDescription(string desc)
  {
    mDeviceDesc.clear();
    mDeviceDesc.assign(desc);
  }
  
  string& GetDeviceDescription(void)
  {
    return mDeviceDesc;
  }
  
  virtual string& GetDeviceName()
  {
    return mDeviceName;
  }
  
  virtual shared_ptr<MessageInstance> GetDeviceMsg();
  
  ~Device() = default;
  
  private:
    std::mutex mMutex;
    string mDeviceName;
    string mDeviceDesc;
};

#endif
