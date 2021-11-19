#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class http_connection : public std::enable_shared_from_this<http_connection>
{
public:
  http_connection(tcp::socket socket)
    : socket_(std::move(socket)) {}

  void start(){
    do_read();
  }

private:
  void do_read(){
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/){
          if (!ec){
            do_write();
          }
        });
  }

  void do_write(){
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(success_status, strlen(success_status)),
        [this, self](boost::system::error_code ec, std::size_t /*length*/){
          if (!ec){
            while((pid = fork()) < 0) { usleep(1000);}
            if(pid == 0){ // child
              dup2(socket_.native_handle(), STDIN_FILENO);
              dup2(socket_.native_handle(), STDOUT_FILENO);
              dup2(socket_.native_handle(), STDERR_FILENO);
              self->socket_.close();

              int ret = execlp(exec_pannel, exec_pannel, NULL);
              if(ret < 0){ //TODO Handle Error
                // std::cout << "Content-type: text/html\r\n\r\n"
                //           << "<!DOCTYPE html>\n"
                //           << "<html lang=\"en\">\n"
                //           << "<h1> CGI not found </h1>\n"
                //           << "</html>\n";
              }
            }else{ // parent
              self->socket_.close();
            }
            do_read();
          }
        });
  }
  pid_t pid;
  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
  char exec_pannel[200] = "./panel.cgi";
  char success_status[200] = "HTTP/1.1 200 OK\r\n";
};

class http_server{
public:
  http_server(boost::asio::io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)){
    do_accept();
  }

private:
  void do_accept(){
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket){
          if (!ec){
            std::make_shared<http_connection>(std::move(socket))->start();
          }
          do_accept();
        });
  }

  tcp::acceptor acceptor_;
};

int main(int argc, char* argv[]){
  try{
    if (argc != 2){
      std::cerr << "Usage: http_server <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;
    http_server s(io_context, std::atoi(argv[1]));
    io_context.run();
  }catch (std::exception& e){
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
