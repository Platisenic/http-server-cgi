# HTTP Server & CGI

Implement a simple HTTP server and a CGI program using Boost.Asio library.

## Prerequisite

- Install Boost library

```shell
sudo apt-get install libboost-all-dev
```

## How to use

1. Build from source

```shell
cd httpserver_cgi
make
```

2. Start the HTTP Server

```shell
./http_server [port]
```

3. Visit the website (http://[host]:[port]/panel.cgi)

## Implementation detail

### HTTP Server

1. The URI of HTTP requests will always be in the form of `/${cgi_name}.cgi` (e.g., `/panel.cgi`, `/console.cgi`, `/printenv.cgi`), and only support for the HTTP GET method.
2. HTTP Server parse the HTTP headers and folllow the CGI procedure (fork, set environment variables, dup, exec) to execute the specificied CGI program.
3. The following environment variables are required to set:
   - REQUEST_METHOD
   - REQUEST_URI
   - QUERY_STRING
   - SERVE_RPROTOCOL
   - HTTP_HOST
   - SERVER_ADDR
   - SERVER_PORT
   - REMOTE_ADDR
   - REMOTE_PORT
4. HTTP Header Example

```shell
GET /console.cgi?h0=nplinux1.cs.nctu.edu.tw&p0= ... (too long, ignored)
Host: nplinux8.cs.nctu.edu.tw:7779
User-Agent: Mozilla/5.0Accept: text/html,application/xhtml+xml,applica ... (too long, ignored)
Accept-Language: en-US,en;q=0.8,zh-TW;q=0.5,zh; ... (too long, ignored)
Accept-Encoding: gzip, deflate
DNT: 1
Connection: keep-alive
Upgrade-Insecure-Requests: 1
```

### console.cgi

1. The console.cgi should parse the connection information (e.g., host, port, file) from the environment variable QUERY STRING, which is set by HTTP server.
2. The remote servers that `console.cgi` connects to are Remote Working Ground Servers with shell prompt ”% ”, and the files (e.g., t1.txt) contain the commands for the remote shells. 

### panel.cgi

1. This CGI program generates the form in the web page. It detects all files in the directory test case/ and display them in the selection menu.

## ScreenShots

1. panel.cgi
<img width="686" alt="image" src="https://user-images.githubusercontent.com/69299037/192147027-adc80684-5305-478a-8df8-80d3e88310f5.png">
2. console.cgi
<img alt="image" src="https://user-images.githubusercontent.com/69299037/192147315-60a0b692-fb93-47f4-88bb-956a130f2465.png">


