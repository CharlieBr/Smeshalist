#ifndef  CONTROLLER_H
#define  CONTROLLER_H


#include <sstream>

class Controller{
    public:

        bool validPath(const char* path, const char* method){
            if(strcmp(path, "/") == 0 && strcmp("GET", method) == 0){
                return true;
            }
            return false;
        }

        void createResponse(struct MHD_Connection* connection, const char* url,
                        const char* method, const char* upload_data, size_t* upload_data_size, std::stringstream& response){

            time_t time_cur;
            time(&time_cur);
            struct tm* time_now = localtime(&time_cur);
            response << "<html><head><title>Hello World from cpp</title></head><body>Hello World at "
                << time_now->tm_hour << ":" << time_now->tm_min << ":" << time_now->tm_sec << "!</body></html>";
        }

        int handleRequest(struct MHD_Connection* connection, const char* url, const char* method, const char* upload_data, size_t* upload_data_size){

            std::stringstream response_string;
            createResponse(connection, url, method, upload_data, upload_data_size, response_string);

            struct MHD_Response * response = MHD_create_response_from_buffer(strlen(response_string.str().c_str()), (void*)response_string.str().c_str(), MHD_RESPMEM_MUST_COPY);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
            MHD_destroy_response(response);

            return ret;
        }
};

#endif //  CONTROLLER_H
