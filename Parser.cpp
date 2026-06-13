#include"Parser.h"
#include<fstream>
#include<sstream>
#include<iostream>

vector<Task>Parser::readTasks(string filename){
    vector<Task>tasks; // إنشاء قائمة لتخزين جميع المهام
    ifstream file(filename); // فتح ملف الإدخال
    if(!file){ // التحقق من وجود الملف
        cout<<"File not found!"<<endl;
        return tasks;
    }
    string line;
    // قراءة الملف سطرًا سطرًا
    while(getline(file,line)){
        if(line.empty()){ // تجاهل الأسطر الفارغة
         continue;
        } 
       // تحويل السطر إلى stream لسهولة القراءة
        stringstream ss(line);
        // قراءة أول كلمة من السطر
        string firstWord;
        ss>>firstWord;
        // تجاهل أي سطر لا يبدأ بكلمة TASK
        if(firstWord!="TASK"){
        continue;
        }
        string keyword;
        // إنشاء مهمة جديدة
        Task t;
        // متغير لتحديد صلاحية المهمة
        bool valid = true;
        // قراءة رقم المهمة
        ss>>t.id;
        // قراءة مدة المهمة
        ss>>keyword;     // DURATION مدة المهمة
        ss>>t.duration;
        // التحقق من أن المدة أكبر من صفر
        if(t.duration<=0){
         cout<<"Error: Invalid Duration in Task "<<t.id<<endl;
         valid=false;
        }
        // قراءة عدد الموارد المطلوبة
        ss>>keyword;     // RESOURCE الموارد
        ss >> t.resource_demand;
        // التحقق من أن عدد الموارد أكبر من صفر
        if(t.resource_demand <= 0){
         cout<<"Error: Invalid Resource in Task "<<t.id<<endl;
         valid=false;
        }
        // قراءة المهام المعتمدة عليها
        ss>>keyword;  // DEPENDS المهام الي تعتمد عليها كل مهمة
        int dep;
        while(ss>>dep){
            t.dependencies.push_back(dep);
        }
        // إضافة المهمة فقط إذا كانت صحيحة
        if(valid){
         tasks.push_back(t);
        }
    }
    // التحقق من عدم تكرار IDs المهام
    for(int i=0;i<tasks.size();i++){
          for(int j=i+1;j<tasks.size();j++){
              if(tasks[i].id==tasks[j].id){
                 cout<<"Error: Duplicate Task ID "<<tasks[i].id<<endl;
        }
    }
}
// التحقق من وجود جميع الـ Dependencies
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
        // طباعة خطأ إذا كانت المهمة المعتمدة غير موجودة
        if(!found){
          cout<<"Error: Task "<<tasks[i].id<<" depends on non-existing Task "<<depId<<endl;
        }
    }
}
    // إرجاع جميع المهام الصحيحة
    return tasks;
}