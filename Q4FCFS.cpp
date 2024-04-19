#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Process {
    int id, arrivalTime, burstTime, turnaroundTime;
};

int main() {
    int n;
    float avgTurnaroundTime = 0.0, totalTurnaroundTime = 0.0;
    vector<Process> processes;

    cout << "Enter the total number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Process p;
        cout << "Enter Arrival Time and Burst Time for process id " << i + 1 << ":\n";
        cin >> p.arrivalTime >> p.burstTime;
        p.id = i + 1;
        processes.push_back(p);
    }

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrivalTime < b.arrivalTime;
    });

    for (int i = 0; i < n; i++) {
        totalTurnaroundTime += processes[i].burstTime;
        processes[i].turnaroundTime = totalTurnaroundTime;
    }

    cout << "PID\tArrival\tBurst\tTurnaround\n";

    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t" << processes[i].arrivalTime << "\t" << processes[i].burstTime << "\t" << processes[i].turnaroundTime << endl;
    }

    avgTurnaroundTime = totalTurnaroundTime / static_cast<float>(n);
    cout << "Total Turnaround Time: " << totalTurnaroundTime << endl;
    cout << "Average Turnaround Time : " << avgTurnaroundTime << endl;

    return 0;
}
