#include <iostream>
#include <stdlib.h>
#include <string>


int main(){
    std::cout << "Content-type: text/html\r\n\r\n";
    std::cout << "<!DOCTYPE html>\n"
              << "<html lang=\"en\">\n"
              <<    "<head>\n"
              <<        "<meta charset=\"UTF-8\" />\n"
              <<        "<title>NP Project 3 Sample Console</title>\n"
              <<        "<link\n"
              <<        "rel=\"stylesheet\"\n"
              <<        "href=\"https://cdn.jsdelivr.net/npm/bootstrap@4.5.3/dist/css/bootstrap.min.css\"\n"
              <<        "integrity=\"sha384-TX8t27EcRE3e/ihU7zmQxVncDAy5uIKz4rEkgIXeMed4M0jlfIDPvg6uqKI2xXr2\"\n"
              <<        "crossorigin=\"anonymous\"\n"
              <<        "/>\n"
              <<        "<link\n"
              <<        "href=\"https://fonts.googleapis.com/css?family=Source+Code+Pro\"\n"
              <<        "rel=\"stylesheet\"\n"
              <<        "/>\n"
              <<        "<link\n"
              <<        "rel=\"icon\"\n"
              <<        "type=\"image/png\"\n"
              <<        "href=\"https://cdn0.iconfinder.com/data/icons/small-n-flat/24/678068-terminal-512.png\"\n"
              <<        "/>\n"
              <<        "<style>\n"
              <<        "* {\n"
              <<        "    font-family: 'Source Code Pro', monospace;\n"
              <<        "    font-size: 1rem !important;\n"
              <<        "}\n"
              <<        "body {\n"
              <<        "    background-color: #212529;\n"
              <<        "}\n"
              <<        "pre {\n"
              <<        "    color: #cccccc;\n"
              <<        "}\n"
              <<        "b {\n"
              <<        "    color: #01b468;\n"
              <<        "}\n"
              <<        "</style>\n"
              <<    "</head>\n"
              <<    "<body>\n"
              <<        "<table class=\"table table-dark table-bordered\">\n"
              <<        "<thead>\n"
              <<            "<tr>\n"
              <<            "<th scope=\"col\">nplinux1.cs.nctu.edu.tw:1234</th>\n"
              <<            "<th scope=\"col\">nplinux2.cs.nctu.edu.tw:5678</th>\n"
              <<            "</tr>\n"
              <<        "</thead>\n"
              <<        "<tbody>\n"
              <<            "<tr>\n"
              <<            "<td><pre id=\"s0\" class=\"mb-0\"></pre></td>\n"
              <<            "<td><pre id=\"s1\" class=\"mb-0\"></pre></td>\n"
              <<            "</tr>\n"
              <<        "</tbody>\n"
              <<        "</table>\n"
              <<    "</body>\n"
              <<"</html>\n";
    // std::string query_string(getenv("QUERY_STRING"));
    // std::cout << "<h1>" << query_string << "</h1>" << std::endl;

    return 0;
}