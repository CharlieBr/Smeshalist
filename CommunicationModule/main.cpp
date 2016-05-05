#include <iostream>
#include <json/json.h>

using namespace std;

#include "httpServer.h"
#include <time.h>

int main()
{
    Json::Value val;
    val["smeshalist"] = "Smeshalist is the best!!!";
    cout << val << endl;


    Controller myPage;

    httpServer server(8080);
    server.addController(&myPage);
    server.start();


    return 0;
}
