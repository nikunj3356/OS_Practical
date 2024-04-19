#include <iostream>
using namespace std;

int main()
{
    int burstTimes[20], processes[20], waitingTimes[20], turnaroundTimes[20], priorities[20], temp, total = 0, pos, avgWaitingTime, avgTurnaroundTime, numProcesses;
    
    cout << "Enter the total number of processes: ";
    cin >> numProcesses;

    cout << "Enter Burst Time and Priority for each process:\n";
    for (int i = 0; i < numProcesses; i++)
    {
        cout << "\nP[" << i + 1 << "]\n";
        cout << "Burst Time: ";
        cin >> burstTimes[i];
        cout << "Priority: ";
        cin >> priorities[i];
        processes[i] = i + 1;
    }

    for (int i = 0; i < numProcesses; i++)
    {
        pos = i;
        for (int j = i + 1; j < numProcesses; j++)
        {
            if (priorities[j] < priorities[pos])
                pos = j;
        }
        temp = priorities[i];
        priorities[i] = priorities[pos];
        priorities[pos] = temp;
        temp = burstTimes[i];
        burstTimes[i] = burstTimes[pos];
        burstTimes[pos] = temp;
        temp = processes[i];
        processes[i] = processes[pos];
        processes[pos] = temp;
    }

    waitingTimes[0] = 0;
    for (int i = 1; i < numProcesses; i++)
    {
        waitingTimes[i] = 0;
        for (int j = 0; j < i; j++)
            waitingTimes[i] += burstTimes[j];
        total += waitingTimes[i];
    }

    avgWaitingTime = total / numProcesses;
    total = 0;

    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < numProcesses; i++)
    {
        turnaroundTimes[i] = burstTimes[i] + waitingTimes[i];
        total += turnaroundTimes[i];
        cout << "P[" << processes[i] << "]\t\t" << burstTimes[i] << "\t\t" << waitingTimes[i] << "\t\t" << turnaroundTimes[i] << endl;
    }

    avgTurnaroundTime = total / numProcesses;

    cout << "\nAverage Waiting Time = " << avgWaitingTime;
    cout << "\nAverage Turnaround Time = " << avgTurnaroundTime;

    return 0;
}
