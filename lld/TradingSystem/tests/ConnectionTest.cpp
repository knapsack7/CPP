#include <gtest/gtest.h>
#include "Connection.h"
#include <boost/asio.hpp>

using namespace TradingSystem;

class ConnectionTest : public ::testing::Test {
protected:
    void SetUp() override {
        io_context = std::make_unique<boost::asio::io_context>();
        socket = std::make_unique<boost::asio::ip::tcp::socket>(*io_context);
    }

    void TearDown() override {
        socket->close();
        io_context->stop();
    }

    std::unique_ptr<boost::asio::io_context> io_context;
    std::unique_ptr<boost::asio::ip::tcp::socket> socket;
};

TEST_F(ConnectionTest, CreateConnection) {
    Connection conn(std::move(*socket));
    EXPECT_FALSE(conn.isActive());
}

TEST_F(ConnectionTest, StartStopConnection) {
    Connection conn(std::move(*socket));
    conn.start();
    EXPECT_TRUE(conn.isActive());
    conn.stop();
    EXPECT_FALSE(conn.isActive());
}

TEST_F(ConnectionTest, SetClientId) {
    Connection conn(std::move(*socket));
    conn.setClientId("test_client");
    EXPECT_EQ(conn.getClientId(), "test_client");
}

TEST_F(ConnectionTest, MessageCallback) {
    Connection conn(std::move(*socket));
    bool callback_called = false;
    std::vector<uint8_t> received_message;

    conn.setMessageCallback([&](const std::vector<uint8_t>& message) {
        callback_called = true;
        received_message = message;
    });

    std::vector<uint8_t> test_message = {1, 2, 3};
    conn.processMessage(test_message);

    EXPECT_TRUE(callback_called);
    EXPECT_EQ(received_message, test_message);
} 