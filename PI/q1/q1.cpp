#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Job {
    int id;
    int timeToDo;
};

struct Machine {
    int id;
    int timeQueue;
    vector<Job> jobs;
};

bool highestQueueTimeCompare(Job a, Job b){
    return b.timeToDo < a.timeToDo;
}

int getMinorQueue(vector<Machine> machineList) {
    int minQueueTime = machineList[0].timeQueue;
    int machineID = 0;
    for (int i = 0; i < machineList.size(); i++) {
        if (machineList[i].timeQueue < minQueueTime) {
            minQueueTime = machineList[i].timeQueue;
            machineID = i;
        }
    }
    return machineID;
}

int main() {
    int jobNum, maqNum, maxTimeQueue;

    vector<Job> jobList;
    vector<Machine> machineList;

    cin >> jobNum >> maqNum;

    // Reserva a memoria pra n jobs e m machines
    jobList.reserve(jobNum);
    machineList.reserve(maqNum);

    // Captura todos os jobs
    for(int i = 0; i < jobNum; i++) {
        Job newJob;
        newJob.id = i;
        cin >> newJob.timeToDo;
        jobList.push_back(newJob);
    }

    // Ordena os jobs com base no maior timeToDo
    sort(jobList.begin(), jobList.end(), highestQueueTimeCompare);

    // Inicia as maquinas
    for(int i = 0; i < maqNum; i++){
        Machine newMachine;
        vector<Job> mJobList;
        newMachine.id = i;
        newMachine.jobs = mJobList;
        newMachine.timeQueue = 0;
        machineList.push_back(newMachine);
    }

    for (auto& job: jobList) {
        int machineID = getMinorQueue(machineList);
        machineList[machineID].timeQueue += job.timeToDo;
        machineList[machineID].jobs.push_back(job);
    }

    maxTimeQueue = machineList[0].timeQueue;

    for (auto& machine: machineList) {
        if (machine.timeQueue > maxTimeQueue) {
            maxTimeQueue = machine.timeQueue;
        }
    }

    cout << maxTimeQueue << endl;

    return 0;
}