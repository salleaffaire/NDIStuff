#include <chrono>
#include <iostream>
#include <list>
#include <thread>

#include "Processing.NDI.Lib.h"

class NDISourceFinder {
 public:
  NDISourceFinder() {}
  ~NDISourceFinder() {}

  bool isRunning() { return mIsRunning; }

  void Start(int runForIterations = 10) {
    mIsRunning = true;
    mRunForIterations = runForIterations;
    mThread = std::thread(&NDISourceFinder::Run, this);
  }

  void Stop() {
    mIsRunning = false;
    mThread.join();
  }

  void Wait() { mThread.join(); }

 private:
  std::thread mThread;
  bool mIsRunning;
  int mRunForIterations;

  std::list<std::string> mNDIName;

  void Run() {
    // Not required, but "correct" (see the SDK documentation).
    if (!NDIlib_initialize()) {
      std::cout << "Cannot run NDIlib_initialize()" << std::endl;
      return;
    }
    // We are going to create an NDI finder that locates sources on the network.
    NDIlib_find_instance_t pNDI_find = NDIlib_find_create_v2();
    if (!pNDI_find) return;

    // Loop Iterator
    int mIterationNumber = 0;

    // While isRunning and time is less than 10 seconds
    while (isRunning() && mIterationNumber < mRunForIterations) {
      // Wait up till 5 seconds to check for new sources to be added or
      // removed
      if (!NDIlib_find_wait_for_sources(pNDI_find, 2000 /* milliseconds */)) {
        std::cout << "No change to the sources found." << std::endl;
        mIterationNumber++;
        continue;
      }

      // Get the updated list of sources
      uint32_t no_sources = 0;
      const NDIlib_source_t* p_sources =
          NDIlib_find_get_current_sources(pNDI_find, &no_sources);

      std::cout << "Number of sources: " << no_sources << std::endl;

      // Clear the name list
      mNDIName.clear();

      for (uint32_t i = 0; i < no_sources; i++)
        mNDIName.push_back(p_sources[i].p_ndi_name);

      mIterationNumber++;
    }
  }
};

int main(int argc, char* argv[]) {
  std::cout << "NDI Source Finder ..." << std::endl;

  NDISourceFinder ndiSourceFinder;
  ndiSourceFinder.Start(4);
  ndiSourceFinder.Wait();
  // std::this_thread::sleep_for(std::chrono::milliseconds(20000));
  return 1;
}