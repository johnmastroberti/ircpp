#include <iostream>
#include <asio.hpp>
#include <string>

int main() {


  // Connect to server
  asio::io_context io;
  asio::ip::tcp::resolver resolver(io);
  auto endpoints = resolver.resolve("127.0.0.1", "4040");

  asio::ip::tcp::socket socket(io);
  asio::async_connect(socket, endpoints, [&](std::error_code ec, asio::ip::tcp::endpoint /*ep*/) {
      if (!ec) {
        std::cout << "connected\n";
        std::string line;
        while (!std::cin.eof()) {
          std::getline(std::cin, line);
          asio::write(socket, asio::buffer(line));
        }
      }
      else std::cout << "could not connect\n";
      });

  io.run();
  // Asynchronously receive new messasges to write to standard out

  // Poll for messages to send


  return 0;
}
