# DS_Assignment
Part A 
1) I have compiled the programs and understand what they do,how they function and operate.
   2) I have downloaded netserv.c and netclient.c from the link provided and after understanding the code I runned them in different terminals in ubuntu. When I run netserv.c it says "Server is alive and waiting for socket connection from client" and on another terminal when I run netclient.c it says "Client is alive and establishing socket connection" for a while and then say " Error establishing communications: connection refused" that means the connection between client and server couldn't be established (they couldn't connect). This is because of the ip address that is provided in netclient '132.161.33.175'
  
   3) The when I run ifconfig command it shows the ip address,mask,inet address,broadcast where I was working on my computer.
  
  4) After that if I gave my computer addres to the client then the server and the client found on the same host so they communicate quikly.

  
  
  5) After getting the copmuter ip address and replace the previous one by the computer ip (132.161.33.175 -> 127.0.0.1) when I recompile netclient.c and run both the server will be alive and creats a socket and will wait for socket connection and waits for a client to contact it.  if that is successful it will write for socket form 1 - 10 then exit similarly in the client side will receive 1-10 from socket finally will exit. Server and client have succesfully connected.The socket works as IPC
 
 6) When I run only the client it will first be alive and try to establish connection but since the server is not alive this connection will be refused.
  
