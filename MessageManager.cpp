// Class MessageManager is used for processing of
// messages in the queue and saving details for
// the overall messaging system like number of messages

#include "MessageInstance.h"
#include "MessageManager.h"
#include <filesystem>
#include <fstream>

string MsgMgr::mOutputFileName("");
std::ofstream MsgMgr::mStream(nullptr);
shared_ptr<filebuf> MsgMgr::mFileBuffer(nullptr);
MsgMgr* MsgMgr::mMsgMgrObj(nullptr);

MsgMgr::MsgMgr(bool printStdOut): mPrintToStdOut(printStdOut)
{
  mMessageCountStr.assign("0");
  mProcessThread = unique_ptr<std::thread>(new std::thread(&MsgMgr::ConsumeMsg, this));
}

MsgMgr::~MsgMgr()
{
  mProcessThread->join();
  mStream.close();
}

void MsgMgr::SetOutputFileName(string& outputFileName)
{
    auto directoryToWriteTo = std::filesystem::current_path();
    std::filesystem::remove(directoryToWriteTo.string() + "/" + outputFileName);
    mStream.open(directoryToWriteTo.string() + "/" + outputFileName);
}

MsgMgr* MsgMgr::GetMsgMgr()
{
  if (mMsgMgrObj == nullptr)
  {
    mMsgMgrObj = new MsgMgr();
  }
  return mMsgMgrObj;
}

void MsgMgr::AddMsgToMsgMgr(shared_ptr<MessageInstance> msgInstPtr)
{
  std::unique_lock<std::mutex> lock(mMutex);
  mQueue.push(msgInstPtr);
  mCondVar.notify_one();
}

// function for incrementing the integer saved as a string
// in order to avoid the integer buffer overflow
void MsgMgr::IncrMessageCountStr()
{
  // carry kept as true in starting as it will result in the effect of incrementing by 1
  bool carry = true;
  for (auto iter = mMessageCountStr.rbegin(); iter != mMessageCountStr.rend(); iter++)
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
    mMessageCountStr = "1" + mMessageCountStr;
  }
}

void MsgMgr::ConsumeMsg()
{
  while(1)
  {
    shared_ptr<MessageInstance> msgInst;
    {
      std::unique_lock<std::mutex> lock(mMutex);
      while (mQueue.empty())
      {
        mCondVar.wait(lock);
      }
      
      msgInst = mQueue.front();
      mQueue.pop();
      IncrMessageCountStr();
      string msgStr;
      msgInst->CreateMsgString(msgStr);
      //cout << "DEBUG: Processed msg with string \'" << msgStr << "\'" << endl;
      if (mStream)
      {
        mStream << msgStr << endl << flush;
      }
      if (mPrintToStdOut)
      {
        cout << msgStr << flush;
      }
    }
  }
}
