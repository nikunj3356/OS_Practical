#include <iostream>
using namespace std;

void calculateWaitingTime(int processes[], int numProcesses, int burstTimes[], int waitingTimes[], int quantum)
{
	int remainingBurstTimes[numProcesses];
	for (int i = 0; i < numProcesses; i++)
		remainingBurstTimes[i] = burstTimes[i];

	int currentTime = 0;

	while (true)
	{
		bool allDone = true;

		for (int i = 0; i < numProcesses; i++)
		{
			if (remainingBurstTimes[i] > 0)
			{
				allDone = false;

				if (remainingBurstTimes[i] > quantum)
				{
					currentTime += quantum;
					remainingBurstTimes[i] -= quantum;
				}
				else
				{
					currentTime += remainingBurstTimes[i];
					waitingTimes[i] = currentTime - burstTimes[i];
					remainingBurstTimes[i] = 0;
				}
			}
		}

		if (allDone)
			break;
	}
}

void calculateTurnaroundTime(int processes[], int numProcesses, int burstTimes[], int waitingTimes[], int turnaroundTimes[])
{
	for (int i = 0; i < numProcesses; i++)
		turnaroundTimes[i] = burstTimes[i] + waitingTimes[i];
}

void calculateAverageTime(int processes[], int numProcesses, int burstTimes[], int quantum)
{
	int waitingTimes[numProcesses], turnaroundTimes[numProcesses], totalWaitingTime = 0, totalTurnaroundTime = 0;

	calculateWaitingTime(processes, numProcesses, burstTimes, waitingTimes, quantum);

	calculateTurnaroundTime(processes, numProcesses, burstTimes, waitingTimes, turnaroundTimes);

	cout << "Processes\tBurst time\tWaiting time\tTurnaround time\n";

	for (int i = 0; i < numProcesses; i++)
	{
		totalWaitingTime += waitingTimes[i];
		totalTurnaroundTime += turnaroundTimes[i];
		cout << " " << processes[i] << "\t\t" << burstTimes[i] << "\t\t " << waitingTimes[i] << "\t\t" << turnaroundTimes[i] << endl;
	}

	cout << "\nAverage waiting time = " << (float)totalWaitingTime / (float)numProcesses;
	cout << "\nAverage turnaround time = " << (float)totalTurnaroundTime / (float)numProcesses;
}

int main()
{
	int processes[] = { 1, 2, 3 };
	int numProcesses = sizeof processes / sizeof processes[0];

	int burstTimes[] = { 5, 10, 3 };

	int quantum = 2;

	calculateAverageTime(processes, numProcesses, burstTimes, quantum);

	return 0;
}
