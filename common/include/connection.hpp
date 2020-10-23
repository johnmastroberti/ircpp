#pragma once
#include <string>
#include <asio.hpp>

#include "tsqueue.hpp"


template<typename T>
class connection {
  protected:
    asio::io_context* m_io;
    std::string m_address, m_port;
    asio::ip::tcp::socket m_socket;
    tsqueue<T> m_outq, m_inq;

  public:
    connection(asio::io_context* io, const std::string& address,
        const std::string& port)
      : m_io(io), m_address(address), m_port(port), m_socket(*io)
    {
      // Try to resolve the address and port
      asio::ip::tcp::resolver resolver(m_io);
      auto endpoints = resolver.resolve(m_address, m_port);

      // Make the connection
      asio::async_connect(m_socket, endpoints);
    }

    connection(const connection&) = delete;
    connection<T>& operator=(const connection&) = delete;
    connection(connection&&) = default;
    connection<T>& operator=(connection&&) = default;
    ~connection() {}
};



