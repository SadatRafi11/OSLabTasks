#include<bits/stdc++.h>
using namespace std;

struct process {
    string name;
    int burstTime;
    int priority;
    int arrivalTime;
    int serial;
    int startTime;
    int finishTime;
} processes[5];

int burstTimeList[] = {13, 1, 2, 16, 7};
int priorityList[] = {3, 1, 3, 4, 2};
int arrivalTimeList[] = {2, 0, 1, 3, 5};

void assignValues() {
    processes[0].name = "p1";
    processes[1].name = "p2";
    processes[2].name = "p3";
    processes[3].name = "p4";
    processes[4].name = "p5";

    for (int i = 0; i < 5; i++) {
        processes[i].burstTime = burstTimeList[i];
        processes[i].arrivalTime = arrivalTimeList[i];
        processes[i].priority = priorityList[i];
        processes[i].serial = i;
    }
    return;
}

bool compare_arrival(process x, process y) {
    return x.arrivalTime <= y.arrivalTime;
}

bool compare_burst(process x, process y) {
    return x.burstTime <= y.burstTime;
}

bool compare_serial(process x, process y) {
    return x.serial <= y.serial;
}

void non_sjf_calculation() {
    processes[0].startTime = 0;
    processes[0].finishTime = processes[0].startTime + processes[0].burstTime;
    for (int i = 1, j = i; i < 5; i++) {
        while (processes[j].arrivalTime <= processes[i-1].finishTime && j < 5) j++;
        sort(processes + i, processes + j, compare_burst);
        processes[i].startTime = processes[i-1].finishTime;
        processes[i].finishTime = processes[i].startTime + processes[i].burstTime;
    }
    return;
}

int main() {
    cout << "non-preemptive SJF: " << endl;
    assignValues();
    sort(processes, processes + 5, compare_arrival);

    for (int i = 0; i < 4; i++) {
        cout << processes[i].name << " --> ";
    }
    cout << processes[4].name << endl;

    non_sjf_calculation();

    sort(processes, processes + 5, compare_serial);
    float totalResponseTime = 0.0;
    for (int i = 0; i < 5; i++) {
        cout << processes[i].name << ":" << endl;

        cout << "Start Time - " << processes[i].startTime << endl;
        cout << "Finish Time - " << processes[i].finishTime << endl;
        cout << "Response Time - " << processes[i].startTime - processes[i].arrivalTime << endl;
        cout << "Waiting Time - " << processes[i].startTime - processes[i].arrivalTime << endl;
        totalResponseTime += processes[i].startTime - processes[i].arrivalTime;
    }

    cout << "Average Response Time - " << totalResponseTime/5.0 << endl;
    cout << "Average Waiting Time - " << totalResponseTime/5.0 << endl;
    return 0;
}

