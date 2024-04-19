#include <bits/stdc++.h>
using namespace std;
struct Process {
    int pid, waitingTime, burstTime, turnaroundTime;
};
int main() {
    int i, n, j, wait = 0;
    float avg = 0.0, totalTurnaroundTime = 0.0, waitAverage = 0.0;
    struct Process processes[10], temp;
    cout << "SJF Algorithm\n";
    cout << "Enter the total number of processes: ";
    cin >> n;
    for (i = 0; i < n; i++) {
        cout << "Enter Arrival Time and Burst Time for process id " << i + 1 << ":\n";
        cin >> processes[i].burstTime;
        processes[i].pid = i + 1;
    }
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (processes[j].burstTime > processes[j + 1].burstTime) {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < n; i++) {
        processes[i].waitingTime = wait;
        wait = wait + processes[i].burstTime;
        processes[i].turnaroundTime = wait;
    }
    wait = 0;
    cout << "PID\tBurst\tWait\tTurnaround\n";
    for (i = 0; i < n; i++) {
        cout << processes[i].pid << "\t" << processes[i].burstTime << "\t" << processes[i].waitingTime << "\t" << processes[i].turnaroundTime << "\n";
        totalTurnaroundTime += processes[i].turnaroundTime;
        wait += processes[i].waitingTime;
    }
    waitAverage = wait / (float)(n);
    avg = totalTurnaroundTime / (float)(n);
    cout << "Total Waiting Time: " << wait << "\n";
    cout << "Average Waiting Time: " << fixed << setprecision(3) << waitAverage << "\n";
    cout << "Total Turnaround Time: " << totalTurnaroundTime << "\n";
    cout << "Average Turnaround Time: " << fixed << setprecision(3) << avg << "\n";
    return 0;
}
