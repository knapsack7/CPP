#include "Connection.h"
#include <iostream>

namespace TradingSystem {

Connection::Connection(boost::asio::ip::tcp::socket socket)
    : socket_(std::move(socket))
    , active_(false) {
}

Connection::~Connection() {
    stop();
}

void Connection::start() {
    if (!active_) {
        active_ = true;
        startReading();
    }
}

void Connection::stop() {
    if (active_) {
        active_ = false;
        boost::system::error_code ec;
        socket_.close(ec);
    }
}

void Connection::startReading() {
    if (!active_) {
        return;
    }

    read_buffer_.resize(sizeof(uint32_t));
    socket_.async_read_some(
        boost::asio::buffer(read_buffer_),
        [this](const boost::system::error_code& error, size_t bytes_transferred) {
            handleRead(error, bytes_transferred);
        }
    );
}

void Connection::handleRead(const boost::system::error_code& error, size_t bytes_transferred) {
    if (!active_) {
        return;
    }

    if (!error) {
        if (bytes_transferred == sizeof(uint32_t)) {
            // Read message size
            uint32_t message_size;
            std::memcpy(&message_size, read_buffer_.data(), sizeof(message_size));
            read_buffer_.resize(message_size);

            // Read message body
            socket_.async_read_some(
                boost::asio::buffer(read_buffer_),
                [this](const boost::system::error_code& error, size_t bytes_transferred) {
                    if (!error && bytes_transferred == read_buffer_.size()) {
                        processMessage(read_buffer_);
                        startReading();
                    } else {
                        stop();
                    }
                }
            );
        } else {
            stop();
        }
    } else {
        stop();
    }
}

void Connection::handleWrite(const boost::system::error_code& error, size_t bytes_transferred) {
    if (!active_) {
        return;
    }

    if (!error) {
        std::lock_guard<std::mutex> lock(write_queue_mutex_);
        write_queue_.pop();
        if (!write_queue_.empty()) {
            const auto& data = write_queue_.front();
            boost::asio::async_write(
                socket_,
                boost::asio::buffer(data),
                [this](const boost::system::error_code& error, size_t bytes_transferred) {
                    handleWrite(error, bytes_transferred);
                }
            );
        }
    } else {
        stop();
    }
}

void Connection::send(const std::vector<uint8_t>& data) {
    if (!active_) {
        return;
    }

    std::lock_guard<std::mutex> lock(write_queue_mutex_);
    write_queue_.push(data);
    if (write_queue_.size() == 1) {
        const auto& front_data = write_queue_.front();
        boost::asio::async_write(
            socket_,
            boost::asio::buffer(front_data),
            [this](const boost::system::error_code& error, size_t bytes_transferred) {
                handleWrite(error, bytes_transferred);
            }
        );
    }
}

void Connection::processMessage(const std::vector<uint8_t>& message) {
    if (message_callback_) {
        message_callback_(message);
    }
}

} // namespace TradingSystem 