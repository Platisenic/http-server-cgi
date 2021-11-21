#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <functional>
#include <iostream>
#include <string>
#include <fstream>

using boost::asio::ip::tcp;

class client_connection : public std::enable_shared_from_this<client_connection>
{
public:
  client_connection(boost::asio::io_context& io_context, std::string input_file)
    : resolver_(io_context),
      socket_(io_context),
      file_ifs_(input_file.c_str())
      {}
  
  void start_resolve(std::string host , std::string port){
    auto self(shared_from_this());
    resolver_.async_resolve(host, port,
    [this, self](boost::system::error_code ec, tcp::resolver::iterator endpoint_iterator){
      if(!ec){
        endpoint_iterator_ = endpoint_iterator;
        start_connect();
      }
    });
  }

  void start_connect(){
    auto self(shared_from_this());
    socket_.async_connect(*endpoint_iterator_,
    [this, self](boost::system::error_code ec){
      if(!ec){
        do_read();
      }
    });
  }

  void do_read(){
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(read_buf_, max_length),
    [this, self](boost::system::error_code ec, std::size_t length){
      if (!ec){
        std::string data(read_buf_, read_buf_+length);
        std::cout << data;
        std::cout.flush();
        size_t found = data.find("% ");
        if(found != std::string::npos){
          do_write();
        }else{
          do_read();
        }
      }
    });
  }

  void do_write(){
    auto self(shared_from_this());
    std::string input_line;
    std::getline(file_ifs_, input_line);
    input_line += "\n";
    std::cout << input_line;
    std::cout.flush();
    strcpy(write_buf_, input_line.c_str());
    socket_.async_write_some(boost::asio::buffer(write_buf_, strlen(write_buf_)),
    [this, self](boost::system::error_code ec, std::size_t /*length*/){
      if(!ec){
        do_read();
      }
    });
  }
private:
  enum { max_length = 4096 };
  char read_buf_[max_length];
  char write_buf_[max_length];
  tcp::resolver resolver_;
  tcp::resolver::iterator endpoint_iterator_;
  tcp::socket socket_;
  std::ifstream file_ifs_;
};

int main(int argc, char* argv[])
{
  try
  {
    boost::asio::io_context io_context;
    
    std::string host = "localhost";
    std::string port = "5556";
    std::string fileinput = "test_case/t2.txt";
    std::make_shared<client_connection>(io_context, fileinput)->start_resolve(host, port);
    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}