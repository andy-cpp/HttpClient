#include <iostream>
#include "Request.hpp"
#include "Response.hpp"
#include <thread>

int main()
{
    Request req;
    
    req.Go("https://ipinfo.io", [](Request& r, Response& res){
        std::cout << res.body << "\n";

        exit(0);
    });
    for(;;);
}
