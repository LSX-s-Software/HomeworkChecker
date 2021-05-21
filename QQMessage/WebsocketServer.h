#define ASIO_STANDALONE
#define _WEBSOCKETPP_CPP11_RANDOM_DEVICE_
#define _WEBSOCKETPP_CPP11_TYPE_TRAITS_
#pragma once
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;
using websocketpp::endpoint;
using websocketpp::connection;
typedef websocketpp::server<websocketpp::config::asio> server;
typedef server::message_ptr message_ptr;


class connection_metadata_server
{
public:
    typedef websocketpp::lib::shared_ptr<connection_metadata_server> ptr;
    connection_metadata_server(websocketpp::connection_hdl hdl, std::string strRemote) :
        m_hdl(hdl), strRemote(strRemote)
    {}
    void sethdl(websocketpp::connection_hdl hdl)
    {
        m_hdl = hdl;
    }
    websocketpp::connection_hdl gethdl()
    {
        return m_hdl;
    }
    void setRemote(std::string strRemote)
    {
        this->strRemote = strRemote;
    }

    std::string getRemote() const
    {
        return strRemote;
    }
private:
    std::string strRemote;
    websocketpp::connection_hdl m_hdl;
};

class WebsocketServer
{
public:
    WebsocketServer();
    ~WebsocketServer();
    /// <summary>
    /// 连接
    /// </summary>
    static void OnOpen(server* s, WebsocketServer* pWebSocket, websocketpp::connection_hdl hdl);
    /// <summary>
    /// 断开
    /// </summary>
    static void OnClose(server* s, WebsocketServer* pWebSocket, websocketpp::connection_hdl hdl);
    /// <summary>
    /// 通信
    /// </summary>
    static void OnMessage(server* s, WebsocketServer* pWebSocket, websocketpp::connection_hdl hdl, message_ptr msg);


    void start(int port);
private:
    typedef std::map<std::string, connection_metadata_server::ptr> con_list;

    server echo_server;
    con_list m_connection_list;
    websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_thread;
};