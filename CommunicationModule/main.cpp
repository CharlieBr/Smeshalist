#include <iostream>
#include <json/json.h>

using namespace std;

int main()
{
    Json::Value val;
    val["smeshalist"] = "Smeshalist is the best!!!";
    cout << val << endl;
    return 0;
}
