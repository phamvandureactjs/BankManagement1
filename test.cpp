#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

int main(){
    std::ifstream ifs("test.json");
    json j = json::parse(ifs);
    vector<int> vt;
    for(int i = 0; i < j.size(); i++){
        vt.push_back(j[i]["Balance"]);
    }
    for(int i = 0; i < vt.size(); i++){
        cout << vt[i] << " ";
    }
    return 0;
}
 // json result = json::array();
    // for (int i = 0; i < 10; i++)
    // {
    //     json j = {
    //         {"id", i},
    //         {"qty", i},
    //         {"price", i}};
    //     result.push_back(j);
    // }

    // {
    //     std::ofstream f("test.json");
    //     f << result;
    // }