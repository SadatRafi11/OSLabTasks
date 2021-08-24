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

void preemptive_priority_calculation() {
    int cnt = 0;
    string prev_name = "";
    while (true) {
        bool flag = false;
        int k = 0;
        for (int i = 0; i < 5; i++) {
            if (processes[i].arrivalTime <= cnt && processes[i].burstTime > 0 && (!processes[i].complete)) {
                v[k++] = processes[i];
                flag = true;
            }
        }
        if (!flag) break;
        sort(v, v + k, compare_priority);

        int j;
        for (int i = 0; i < 5; i++) {
            if (v[0].name == processes[i].name) j = i;
        }
        processes[j].burstTime--;
        if (prev_name != processes[j].name) {
            order.push_back(prev_name);
            prev_name = processes[j].name;
        }

        if (!processes[j].processedOnce) {
            processes[j].startTime = cnt;
            processes[j].processedOnce = true;
        }

        if (processes[j].burstTime < 1 && (!processes[j].complete)) {
            processes[j].finishTime = cnt + 1;
            processes[j].complete = true;
        }

        for (int i = 0; i < 5; i++) {
            //cout << cnt << endl;
            if ( (!processes[i].complete) && (processes[i].arrivalTime <= cnt) && i != j) {
                processes[i].waitTime += 1;
                //cout << processes[i].name << ": " << processes[i].waitTime << endl;
            }
        }
        //cout << endl;

        cnt++;
    }
    order.push_back(prev_name);
}

int main() {
    cout << "preemptive priority: " << endl;
    assignValues();
    sort(processes, processes + 5, compare_arrival);

    preemptive_priority_calculation();

    int len = order.size();
    for (int i = 1; i < len - 1; i++) {
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

