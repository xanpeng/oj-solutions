// zoj: judge_client/client/util.cc

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
using namespace std;

// Documentation/filesystems/proc.txt, Table 1-4 "Contents of the stat files"
// cat /proc/<PID>/stat
int read_time_consumption(pid_t pid) {
    char buffer[64];
    sprintf(buffer, "/proc/%d/stat", pid);
    FILE* fp = fopen(buffer, "r");
    if (fp == NULL) {
        return -1;
    }

    int utime, stime; // jiffies
    while (fgetc(fp) != ')');
    fgetc(fp);
    // http://stackoverflow.com/questions/2155518/what-is-scanfs-and-scanfd-format-identifiers
    // "*": read but ignored
    if (fscanf(fp, "%*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %d %d", &utime, &stime) < 2) {
        fclose(fp);
        return -1;
    }
    fclose(fp);
    
    static int clock_tick = 0;
    if (clock_tick == 0) {
        // man sysconf, grep _SC_CLK_TCK
        clock_tick = sysconf(_SC_CLK_TCK);
    }
    return int((utime + stime + 0.0) / clock_tick * 1000); // milliseconds
}

// Documentation/filesystems/proc.txt, Table 1-2 "Contents of the status files"
// cat /proc/<PID>/status
int read_memory_consumption(pid_t pid, bool is_peak_memory = false) {
    char buffer[64];
    sprintf(buffer, "/proc/%d/status", pid);
    FILE* fp = fopen(buffer, "r");
    if (fp == NULL) {
        return -1;
    }

    int vmPeak = 0, vmSize = 0, vmExe = 0, vmLib = 0, vmStack = 0;
    while (fgets(buffer, 32, fp)) {
        if (!strncmp(buffer, "VmPeak:", 7)) { // peak virtual memory size
            sscanf(buffer + 7, "%d", &vmPeak);
        } else if (!strncmp(buffer, "VmSize:", 7)) { // total program size
            sscanf(buffer + 7, "%d", &vmSize);
        } else if (!strncmp(buffer, "VmExe:", 6)) { // size of text segment
            sscanf(buffer + 6, "%d", &vmExe);
        } else if (!strncmp(buffer, "VmLib:", 6)) { // size of shared library code
            sscanf(buffer + 6, "%d", &vmLib);
        } else if (!strncmp(buffer, "VmStk:", 6)) { // size of data, stack, and text segments
            sscanf(buffer + 6, "%d", &vmStack);
        }
    }
    fclose(fp);
    if (vmPeak && is_peak_memory) {
        vmSize = vmPeak;
    }
    // Q1: vmExe and vmStack overlaps?
    // A1: 
    // Q2: better to use stack memory?
    // A2: 简单测试发现不是这样，当然官方ZOJ可能有改动
    return vmSize - vmExe - vmLib - vmStack; // KB
}

int main() {
    cout << "target pid: " << getppid() << endl;
    cout << read_time_consumption(getppid()) << " ms" << endl;
    cout << read_memory_consumption(getppid()) << " KB" << endl;

    return 0;
}
