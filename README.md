
USAGE

TCP_Client.cpp:

```cpp
{
    ./client 127.0.0.1 64500
    >> Merhaba
    Server: Your message has been received!
    >> Hi
    Server: Your message has been received!
    >> Laba Diena
    Server: Your message has been received!
    >> exit

    Connection has been closed!
}
```
TCP_Server.cpp:

```cpp
{
    /server 64500
    Client: Merhaba
    Client: Hi
    Client: Laba diena

    Client has quit the session
    Connection has been closed!
}
```