#include<iostream>
#include<fstream>
#include<sstream>
#include"task.h"
using namespace std;

int main(){
   ifstream file("input.txt");
if(!file){
    cout<<"File not found!"<<endl;
    return 1;
}
string line;
vector<Task> tasks;
while(getline(file,line)){
    stringstream ss(line);
    string word;
    Task t;
    ss>>word;      // TASK المهمة
    ss>>t.id;

    ss>>word;      // DURATION مدة المهمة
    ss>>t.duration;

    ss>>word;      // RESOURCE الموارد
    ss>>t.resource;

    ss>>word;      // DEPENDS المهام الي تعتمد عليها كل مهمة
    int dep;
    while(ss>>dep){
        t.dependencies.push_back(dep);
    }
    tasks.push_back(t);
}
    cout<<"Number of Tasks = "<<tasks.size()<<endl; 

      for(int i=0;i<tasks.size();i++){
          cout<<"ID = "<<tasks[i].id<<endl;
          cout<<"Duration = "<<tasks[i].duration<<endl;
          cout<<"Resource = "<<tasks[i].resource<<endl;
          cout<<"Dependencies: ";
              for(int j=0;j<tasks[i].dependencies.size();j++){
                  cout<<tasks[i].dependencies[j]<<" ";
    }
    cout<<endl;
}

}