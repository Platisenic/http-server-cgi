#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "htmlmsg.hpp"

using boost::asio::ip::tcp;

class tcp_connection : public std::enable_shared_from_this<tcp_connection>
{
public:
  tcp_connection(boost::asio::io_context& io_context, int session, std::string input_file)
    : session(session),
      resolver_(io_context),
      socket_(io_context),
      file_ifs_(input_file.c_str())
      {}

  void start(std::string host , std::string port){
    do_resolve(host, port);
  }
  
  void do_resolve(std::string host , std::string port){
    auto self(shared_from_this());
    resolver_.async_resolve(host, port,
    [this, self](boost::system::error_code ec, tcp::resolver::iterator endpoint_iterator){
      if(!ec){
        endpoint_iterator_ = endpoint_iterator;
        do_connect();
      }
    });
  }

  void do_connect(){
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
    boost::asio::async_read_until(socket_, boost::asio::dynamic_buffer(read_buf_), "% ",
    [this, self](boost::system::error_code ec, std::size_t length){
      if(!ec){
        std::string data(read_buf_.substr(0, length));
        read_buf_.erase(0, length);
        printShell(session, data);
        do_write();
      }
    });
  }

  void do_write(){
    auto self(shared_from_this());
    write_buf_.clear();
    std::getline(file_ifs_, write_buf_);
    write_buf_ += "\n";
    printCMD(session, write_buf_);
    boost::asio::async_write(socket_, boost::asio::dynamic_buffer(write_buf_),
    [this, self](boost::system::error_code ec, std::size_t /*length*/){
      if(!ec){
        do_read();
      }
    });
  }
private:
  int session;
  std::string read_buf_;
  std::string write_buf_;
  tcp::resolver resolver_;
  tcp::resolver::iterator endpoint_iterator_;
  tcp::socket socket_;
  std::ifstream file_ifs_;
};

struct connection_info{
  connection_info() {}
  void insert_element(char hpf, std::string value){
      value.erase(0, 1);
    if(hpf == 'h'){
      host = value;
    }else if(hpf == 'p'){
      port = value;
    }else if(hpf == 'f'){
      filename = "test_case/" + value;
    }
  }
  bool is_valid(){
    return !host.empty() && !port.empty() && !filename.empty();
  }
  std::string host;
  std::string port;
  std::string filename;
};

int main(){
  try{
    boost::asio::io_context io_context;
    std::string query_string(getenv("QUERY_STRING"));
    std::stringstream ss(query_string);
    std::string parsed_string;
    connection_info conn_infos[5];
    while(std::getline(ss, parsed_string, '&')){
      conn_infos[parsed_string[1]-'0'].insert_element(parsed_string[0], parsed_string.substr(2));
    }

    printHtmltemplate();

    for(int i=0 ; i<5; i++){
      if(conn_infos[i].is_valid()){
        printTableTitle(i, conn_infos[i].host, conn_infos[i].port);
        std::make_shared<tcp_connection>(io_context, i, conn_infos[i].filename)
          ->start(conn_infos[i].host, conn_infos[i].port);
      }
    }

    io_context.run();
  }catch (std::exception& e){
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}
