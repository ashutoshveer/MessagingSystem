#ifndef MESSAGE_MGR_H
#define MESSAGE_MGR_H

#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <queue>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//singleton
class MsgMgr
{
  public:
    static MsgMgr* GetMsgMgr();
    void AddMsgToMsgMgr(shared_ptr<MessageInstance> msgInstPtr);
    void ConsumeMsg();
    string GetMessageCount(){ return mMessageCountStr;}
    static void SetOutputFileName(string& outFileName);
    ~MsgMgr();

  private:
    MsgMgr(bool printStdOut = false);
    MsgMgr(const MsgMgr&) = delete;
    MsgMgr& operator=(const MsgMgr&) = delete;
    void IncrMessageCountStr();
    static MsgMgr* mMsgMgrObj;
    queue<shared_ptr<MessageInstance>> mQueue;
    bool mPrintToStdOut;
    string mMessageCountStr;

    std::mutex mMutex;
    unique_ptr<std::thread> mProcessThread;
    std::condition_variable mCondVar;
    
    static string mOutputFileName;
    static std::ofstream mStream;
    static shared_ptr<filebuf> mFileBuffer;
};

#endif
