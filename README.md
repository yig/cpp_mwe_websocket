This repos contains a minimal working example of a C++ WebSocket server. It is based on the easiest-to-use C++ WebSocket server (and client) I could find ([libdatachannel](https://github.com/paullouisageneau/libdatachannel)). It uses CMake's `FetchContent` to pull in the dependency.

## Compile

```
cmake -B build
cmake --build build -j 4
```

## Run

```
./build/echo
```

## Test

Open a blank browser page. Open the Develop Tools console. Type:

```javascript
s = new WebSocket("ws://localhost:{}");
s.onmessage = (event) => console.log(event.data);
s.send("Hi");
```
