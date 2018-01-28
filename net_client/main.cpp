#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>

boost::mutex global_stream_lock;

unsigned long getThreadId(){
    std::string threadId = boost::lexical_cast<std::string>(boost::this_thread::get_id());
    unsigned long threadNumber = 0;
    sscanf(threadId.c_str(), "%lx", &threadNumber);
    return threadNumber;
}

void WorkerThread(boost::shared_ptr<boost::asio::io_service> &io_service) {
    global_stream_lock.lock();
    std::cout << "[" << getThreadId() << "] Thread Start" << std::endl;
    global_stream_lock.unlock();

    while (true) {
        try {
            boost::system::error_code ec;
            io_service->run(ec);
            if (ec) {
                global_stream_lock.lock();
                std::cout << "[" << getThreadId() << "] Error: " << ec << std::endl;
                global_stream_lock.unlock();
            }
            break;
        }
        catch (std::exception &ex) {
            global_stream_lock.lock();
            std::cout << "[" << getThreadId() << "] Exception: " << ex.what() << std::endl;
            global_stream_lock.unlock();
        }
    }

    global_stream_lock.lock();
    std::cout << "[" << getThreadId() << "] Thread Finish" << std::endl;
    global_stream_lock.unlock();
}

void OnConnect( const boost::system::error_code & ec, boost::shared_ptr< boost::asio::ip::tcp::socket > &sock)
{
    if( ec )
    {
        global_stream_lock.lock();
        std::cout << "[" << getThreadId() << "] Error: " << ec << std::endl;
        global_stream_lock.unlock();
    }
    else
    {
        global_stream_lock.lock();
        std::cout << "[" << getThreadId() << "] Connected!" << std::endl;
        global_stream_lock.unlock();
    }
}

int main(int argc, char *argv[]) {
    boost::shared_ptr<boost::asio::io_service> io_service(
            new boost::asio::io_service
    );
    boost::shared_ptr<boost::asio::io_service::work> work(
            new boost::asio::io_service::work(*io_service)
    );
    boost::shared_ptr<boost::asio::io_service::strand> strand(
            new boost::asio::io_service::strand(*io_service)
    );

    int thread_id = 0;

    global_stream_lock.lock();
    std::cout << "[" << getThreadId() << "] Press [return] to exit." << std::endl;
    global_stream_lock.unlock();

    boost::thread_group worker_threads;
    for (int x = 0; x < 1; ++x) {
        worker_threads.create_thread(boost::bind(&WorkerThread, io_service));
    }

    boost::shared_ptr< boost::asio::ip::tcp::socket > sock(
            new boost::asio::ip::tcp::socket( *io_service )
    );

    try {
        boost::asio::ip::tcp::resolver resolver( *io_service );
        boost::asio::ip::tcp::resolver::query query(
                "192.168.0.2",
                boost::lexical_cast< std::string >( 7777 )
        );
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve( query );
        boost::asio::connect( *sock, endpoint_iterator );

        for (;;)
        {
            boost::array<char, 128> buf;
            boost::system::error_code error;

            size_t len = (*sock).read_some(boost::asio::buffer(buf), error);
            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            std::string myData = buf.data();
            std::cout << myData << std::endl;
        }

        global_stream_lock.lock();
        std::cout << "Listening on: " << endpoint << std::endl;
        global_stream_lock.unlock();
    }
    catch (std::exception &ex) {
        global_stream_lock.lock();
        std::cout << "[" << thread_id << "] Exception: " << ex.what() << std::endl;
        global_stream_lock.unlock();
    }

    std::cin.get();

    boost::system::error_code ec;
    sock->shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
    sock->close(ec);

    io_service->stop();

    worker_threads.join_all();

    return 0;
}