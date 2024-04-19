#include <bits/stdc++.h>
using namespace std;

struct Process {
	int id;
	int burstTime;
	int arrivalTime;
};

void calculateWaitingTime(Process processes[], int numProcesses, int waitingTimes[])
{
	int remainingTimes[numProcesses];

	for (int i = 0; i < numProcesses; i++)
		remainingTimes[i] = processes[i].burstTime;

	int completed = 0, currentTime = 0, shortestIndex = 0, finishTime;
	bool found = false;

	while (completed != numProcesses) {
		for (int j = 0; j < numProcesses; j++) {
			if ((processes[j].arrivalTime <= currentTime) &&
				(remainingTimes[j] < remainingTimes[shortestIndex]) &&
				remainingTimes[j] > 0) {
				shortestIndex = j;
				found = true;
			}
		}

		if (!found) {
			currentTime++;
			continue;
		}

		remainingTimes[shortestIndex]--;

		if (remainingTimes[shortestIndex] == 0) {
			completed++;
			found = false;

			finishTime = currentTime + 1;

			waitingTimes[shortestIndex] = finishTime -
										processes[shortestIndex].burstTime -
										processes[shortestIndex].arrivalTime;

			if (waitingTimes[shortestIndex] < 0)
				waitingTimes[shortestIndex] = 0;
		}
		currentTime++;
	}
}

void calculateTurnaroundTime(Process processes[], int numProcesses, int waitingTimes[], int turnaroundTimes[])
{
	for (int i = 0; i < numProcesses; i++)
		turnaroundTimes[i] = processes[i].burstTime + waitingTimes[i];
}

void calculateAverageTime(Process processes[], int numProcesses)
{
	int waitingTimes[numProcesses], turnaroundTimes[numProcesses], totalWaitingTime = 0, totalTurnaroundTime = 0;

	calculateWaitingTime(processes, numProcesses, waitingTimes);

	calculateTurnaroundTime(processes, numProcesses, waitingTimes, turnaroundTimes);

	cout << " P\t\t" << "BT\t\t" << "WT\t\t" << "TAT\t\t\n";

	for (int i = 0; i < numProcesses; i++) {
		totalWaitingTime += waitingTimes[i];
		totalTurnaroundTime += turnaroundTimes[i];
		cout << " " << processes[i].id << "\t\t"
			<< processes[i].burstTime << "\t\t " << waitingTimes[i]
			<< "\t\t " << turnaroundTimes[i] << endl;
	}

	cout << "\nAverage waiting time = " << (float)totalWaitingTime / (float)numProcesses << "\n";
	cout << "Average turnaround time = " << (float)totalTurnaroundTime / (float)numProcesses << "\n";
}

int main()
{
	Process processes[] = { { 1, 7, 3 }, { 2, 4, 2 },
					{ 3, 1, 5 }, { 4, 4, 0}, {5, 5, 4} };
	int numProcesses = sizeof(processes) / sizeof(processes[0]);

	calculateAverageTime(processes, numProcesses);
	return 0;
}
