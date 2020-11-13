#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>

std::mutex mtx;
std::vector<std::string>::iterator it;

void ChangeNames(std::vector<std::string> names, std::string name, std::string source, int time){
    mtx.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    it = std::find(names.begin(),names.end(),name); //find the position of "name" in the vector
    names[it - names.begin()] = names[0]; //replace the string in the vector that matches "name" with the first string in the vector
    names[0] = name; //replace the first string in the vector with "name"
    for(int i = 0; i < names.size(); ++i){
        std::cout << names[i];
    }
    std::cout << " from " << source << "\n";
    mtx.unlock();
}

void CallCN(){
    std::vector<std::string> names = {"Steve ","Jane ","Bill ", "Bob "};

    for(int i = 0; i < names.size(); ++i){
        ChangeNames(names, names[i], "t1", 1000);
    }
}

int main()
{
    std::vector<std::string> names = {"Steve ","Jane ","Bill ", "Bob "};
    std::thread t1(CallCN);


    for(int i = 0; i < names.size(); ++i){
        ChangeNames(names, names[i],"main", 500);
    }
    t1.join();

    return 0;
}
