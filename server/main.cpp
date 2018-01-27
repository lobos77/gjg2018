#include <boost/asio.hpp>
#include <boost/thread.hpp>

boost::asio::io_service io_service;

void NetworkHandler() {
    std::cout << "Thread Start\n";
    io_service.run();
    std::cout << "Thread Finish\n";
}

int main(int argc, char *argv[]) {
    boost::shared_ptr<boost::asio::io_service::work> work(
            new boost::asio::io_service::work( io_service )
    );


    boost::thread worker_thread( NetworkHandler );

    std::string input;
    bool prompt_alive = true;
    do {
        std::cout << "> ";
        std::cin >> input;
        if(input == "exit") {
            prompt_alive = false;
        } else {
            std::cout << "Unknown command." << std::endl;
        }

    } while (prompt_alive);

    io_service.stop();

    worker_thread.join();

    return 0;
}