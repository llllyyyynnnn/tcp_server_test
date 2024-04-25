# C++ TCP Server test

A small project with basic TCP functionality where unlike UDP, it does the bare minimum to verify that the data is being acknowledged. 

Start the server before the client, as the client application will exit as soon as there's nothing being transmitted. 
The client is able to send a message until the server acknowledges it and decides to send a message back.

All of the code is commented out so that anyone can look at it and understand why and how things work.

* Both the server and client only support 1 connection at the moment. Fixing it is as simple as making an array with the active connections and handling them at the same time through the server.

> This project was created for learning purposes and should not be used in serious projects.
