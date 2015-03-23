#include <glog/logging.h>
#include <glog/raw_logging.h>
#include<vector>
using namespace std;

void ProcessSignal(const char* data, int size)
{
        LOG(ERROR) << __func__ << ":Error..." << std::string(data,size);
}



int main(int argc, char* argv[])
{
    FLAGS_log_dir = "/home/qsun/glog";
    google::InitGoogleLogging(argv[0]);
    google::InstallFailureSignalHandler();
    google::InstallFailureWriter(&ProcessSignal);

    int num_cookies = 5;
    LOG(INFO) << "Found " << num_cookies << " cookies";

    LOG(INFO) << "This is INFO";
    LOG(WARNING) << "This is WARNING";
    LOG(ERROR) << "This is Error";

    num_cookies = 100;
    LOG_IF(INFO, num_cookies > 10) << "Got lots of cookies";

    for(int i = 0; i < num_cookies; i++)
    {
        LOG_EVERY_N(INFO, 10) << "Got the " << google::COUNTER << "th cookie";
        LOG_IF_EVERY_N(WARNING, (i > 62), 10) << "Got the " << google::COUNTER << "th big cookie";
        LOG_FIRST_N(ERROR, 10) << "Got the " << google::COUNTER << "th cookie";
    }

    //  g++ -o  -D NDEBUG glogTest glogTest.o -I /home/qsun/tools/glog/include/ -L /home/qsun/tools/glog/lib/ -lglog
    DLOG(INFO) << "Debug mode: Found cookies";

    // Check Macros
    CHECK_LT(num_cookies, 101) << "Write failed!";

    CHECK_NE(1, 2) << ": The world must be ending!";

    // GLOG_v=2 ./glogTestVerbose
    VLOG(1) << "I'm printed when you run the program with --v=1 or higher";
    VLOG(2) << "I'm printed when you run the program with --v=2 or higher";
    VLOG_IF(1, (1025 > 1024))
         << "I'm printed when size is more than 1024 and when you run the "
                        "program with --v=1 or more";
    VLOG_EVERY_N(1, 10)
        << "I'm printed every 10th occurrence, and when you run the program "
        "with --v=1 or more. Present occurence is " << 1;
    VLOG_IF_EVERY_N(1, (1024 > 1024), 10)
        << "I'm printed on every 10th occurence of case when size is more "
        " than 1024, when you run the program with --v=1 or more. "
        "Present occurence is " << 1;

    // Test FailureSignalHandler
   // vector<int> a;
   // a[3]=4;

 
    return 0;
}
