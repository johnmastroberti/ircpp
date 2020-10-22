#include <iostream>
#include <asio.hpp>
#include <string>
#include <cstring>

int main() {


  // Connect to server
  asio::io_context io;
  asio::ip::tcp::resolver resolver(io);
  auto endpoints = resolver.resolve("127.0.0.1", "4040");

  asio::ip::tcp::socket socket(io);
  asio::async_connect(socket, endpoints, [&](std::error_code ec, asio::ip::tcp::endpoint /*ep*/) {
      if (!ec) {
  const char* message = "test test test";
  auto len = strlen(message);
        std::cout << "connected\n";
        asio::async_write(socket, asio::buffer(message, len));
      }
      else std::cout << "could not connect\n";
      });

  io.run();
  // Asynchronously receive new messasges to write to standard out

  // Poll for messages to send


  return 0;
}
