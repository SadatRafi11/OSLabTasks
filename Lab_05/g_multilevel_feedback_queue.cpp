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
    int waitTime;
    bool processedOnce;
    bool complete;
    int lastPreemption;
} processes[5], v[100];

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
        processes[i].waitTime = 0;
        processes[i].processedOnce = false;
        processes[i].complete = false;
        processes[i].lastPreemption = processes[i].arrivalTime;
    }
    return;
}

bool compare_arrival(struct process x, struct process y) {
    return (int)x.arrivalTime <= (int)y.arrivalTime;
}

bool compare_priority(process x, process y) {
    return x.priority < y.priority;
}

bool compare_serial(struct process x, struct process y) {
    return (int)x.serial <= (int)y.serial;
}

vector<string> order;
queue<string> priorityQueue4, priorityQueue8, fcfsQueue;

void multi_level_calculation() {
    int cnt = 0;
    bool flag = false;
    while (true) {
        int j;
        if (!priorityQueue4.empty()) {
            for (int i = 0; i < 5; i++) {
                if (priorityQueue4.front() == processes[i].name) {
                    j = i;
                }
            }
        } else if (!priorityQueue8.empty()) {
            flag = true;
            for (int i = 0; i < 5; i++) {
                if (priorityQueue8.front() == processes[i].name) {
                    j = i;
                }
            }
        } else break;

        if (!processes[j].processedOnce) {
            processes[j].startTime = cnt;
            processes[j].processedOnce = true;
        }

        processes[j].waitTime += cnt - processes[j].lastPreemption;

        if (!flag) {
            if (processes[j].burstTime <= 4) {
                cnt += processes[j].burstTime;
                processes[j].burstTime = 0;
                processes[j].finishTime = cnt;
                processes[j].complete = true;
            } else {
                processes[j].burstTime -= 4;
                cnt += 4;
                priorityQueue8.push(processes[j].name);
            }
            priorityQueue4.pop();
        } else {
            if (processes[j].burstTime <= 8) {
                cnt += processes[j].burstTime;
                processes[j].burstTime = 0;
                processes[j].finishTime = cnt;
                processes[j].complete = true;
            } else {
                processes[j].burstTime -= 8;
                cnt += 8;
                fcfsQueue.push(processes[j].name);
            }
            priorityQueue8.pop();
        }

        processes[j].lastPreemption = cnt;

        order.push_back(processes[j].name);
    }

    while(!fcfsQueue.empty()) {
        int j;
        for (int i = 0; i < 5; i++) {
            if (fcfsQueue.front() == processes[i].name) {
                j = i;
            }
        }
        processes[j].waitTime += cnt - processes[j].lastPreemption;
        cnt += processes[j].burstTime;
        processes[j].finishTime = cnt;
        processes[j].complete = true;
        processes[j].burstTime = 0;
        fcfsQueue.pop();
        order.push_back(processes[j].name);
    }
    return;
}

int main() {
    cout << "Multi-Level Feedback Queue: " << endl;
    assignValues();
    sort(processes, processes + 5, compare_arrival);

    for (int i = 0; i < 5; i++) {
        priorityQueue4.push(processes[i].name);
    }

    multi_level_calculation();

    int len = order.size();

    for (int i = 0; i < len - 1; i++) {
        cout << order[i] << " --> ";
    }
    cout << order[len - 1] << endl;

    sort(processes, processes + 5, compare_serial);
    float totalResponseTime = 0.0, totalWaitTime = 0.0;
    for (int i = 0; i < 5; i++) {
        cout << processes[i].name << ":" << endl;

        cout << "Start Time - " << processes[i].startTime << endl;
        cout << "Finish Time - " << processes[i].finishTime << endl;
        cout << "Response Time - " << processes[i].startTime - processes[i].arrivalTime << endl;
        cout << "Waiting Time - " << processes[i].waitTime << endl;
        totalResponseTime += processes[i].startTime - processes[i].arrivalTime;
        totalWaitTime += processes[i].waitTime;
    }

    cout << "Average Response Time - " << totalResponseTime/5.0 << endl;
    cout << "Average Waiting Time - " << totalWaitTime/5.0 << endl;

    return 0;
}


