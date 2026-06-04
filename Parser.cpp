#include"Parser.h"
#include<fstream>
#include<sstream>
#include<iostream>

vector<Task>Parser::readTasks(string filename){
    vector<Task>tasks;
    ifstream file(filename);
    if(!file){
        cout<<"File not found!"<<endl;
        return tasks;
    }
    string line;
    while(getline(file,line)){
        stringstream ss(line);
        string word;
        Task t;
        ss>>word;   // TASK المهمة
        ss>>t.id;

        ss>>word;     // DURATION مدة المهمة
        ss>>t.duration;
        if(t.duration<=0){
        cout<<"Error: Invalid Duration in Task "<<t.id<<endl;
}

        ss>>word;     // RESOURCE الموارد
        ss>>t.resource;
        if(t.resource<=0){
        cout<<"Error: Invalid Resource in Task "<<t.id<<endl;
        }

        ss>>word;  // DEPENDS المهام الي تعتمد عليها كل مهمة
        int dep;
        while(ss>>dep){
            t.dependencies.push_back(dep);
        }
        tasks.push_back(t);
    }
    for(int i=0;i<tasks.size();i++){
          for(int j=i+1;j<tasks.size();j++){
              if(tasks[i].id==tasks[j].id){
                 cout<<"Error: Duplicate Task ID "<<tasks[i].id<<endl;
        }
    }
}
for(int i=0;i<tasks.size();i++){
    for(int j=0;j<tasks[i].dependencies.size();j++){
        int depId=tasks[i].dependencies[j];
        bool found=false;
        for(int k=0;k<tasks.size();k++){
            if(tasks[k].id==depId){
                found=true;
                break;
            }
        }
        if(!found){
          cout<<"Error: Task"<<tasks[i].id<<"depends on non existing Task"<<depId<<endl;
        }
    }
}
    return tasks;
}