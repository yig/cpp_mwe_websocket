#include "rtc/rtc.hpp"
// References I used:
// server onClient: <https://github.com/paullouisageneau/libdatachannel/blob/v0.21.2/include/rtc/websocketserver.hpp>
// server configuration: <https://github.com/paullouisageneau/libdatachannel/blob/v0.21.2/include/rtc/configuration.hpp>
// client send: <https://github.com/paullouisageneau/libdatachannel/blob/v0.21.2/include/rtc/websocket.hpp>
// client onMessage: <https://github.com/paullouisageneau/libdatachannel/blob/v0.21.2/include/rtc/channel.hpp> 
// string and binary data types: <https://github.com/paullouisageneau/libdatachannel/blob/v0.21.2/include/rtc/common.hpp>

#include <iostream>
#include <string>
#include <format>

#include <chrono>
#include <thread>

int main( int argc, char* argv[] ) {
    using namespace rtc;
    
    // Get the port as an optional command line argument.
    int port = 8080;
    if( argc == 3 && argv[1] == std::string("--port") ) port = std::stoi( argv[2] );
    
    // Make a WebSocket server.
    WebSocketServer server( WebSocketServerConfiguration{ .port = static_cast<uint16_t>( port ) } );
    
    // Announce it on the command line.
    std::cout << std::format( "Listening on ws://localhost:{}", port ) << std::endl;
    std::cout << std::format( R"(Try:
    s = new WebSocket("ws://localhost:{}"); s.onmessage = (event) => console.log(event.data);
    s.send("Hi");)", port ) << std::endl;
    
    // Listen for clients.
    server.onClient( []( auto client ) {
        std::cout << "Client connected!" << std::endl;
        
        client->onMessage(
            // Capture the client by value, since it's a shared_ptr.
            [=]( auto binary ) {
                std::cout << std::format( "<Received {}-byte binary message.>", binary.size() ) << std::endl;
            },
            [=]( auto text ) {
                // Print the text.
                std::cout << text << std::endl;
                
                // Echo it back.
                client->send( text );
            }
        );
    } );
    
    // Sleep forever
    while( true ) { std::this_thread::sleep_for(std::chrono::hours(100000)); }
    
    return 0;
}
