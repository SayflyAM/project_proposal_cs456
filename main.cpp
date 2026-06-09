#include<iostream>
#include "Parser.h"

using namespace std;
int main(){
    Parser parser;
    vector<Task>tasks=parser.readTasks("Testing/valid_input.txt");
    cout<<"Number of Tasks = "<<tasks.size()<<endl;
}