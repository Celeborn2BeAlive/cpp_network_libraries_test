#include <iostream>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

// Implements https://github.com/Microsoft/cpprestsdk/wiki/Getting-Started-Tutorial
void gettingStartedTutorial()
{
    auto fileStream = std::make_shared<ostream>();
    auto requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
    {
        *fileStream = outFile;

        http_client client(U("http://www.bing.com/"));

        uri_builder builder(U("/search"));
        builder.append_query(U("q"), U("cpprestsdk github"));
        return client.request(methods::GET, builder.to_string());
    }).then([=](http_response response)
    {
        std::cout << "Received response status code: " << response.status_code() << std::endl;
        return response.body().read_to_end(fileStream->streambuf());
    }).then([=](size_t)
    {
        return fileStream->close();
    });

    try
    {
        requestTask.wait();
    }
    catch (const std::exception & e)
    {
        std::cerr << "Error exception: " << e.what() << std::endl;
    }
}

int main()
{
    gettingStartedTutorial();
    return 0;
}