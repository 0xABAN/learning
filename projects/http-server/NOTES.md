- tcp only guarantees bytes are delivered in order
- we need a way for sockets to read bytes and understand certain boundaries 

- \r\n\r\n tells it it's the end of the headers
- Content-Length header tells it how long the request body is 
  - Content-Length: 5 (bytes)


anatomy of a request: 

GET /resource HTTP/1.1 (or any request)

- Request Headers 
- \r\n\r\n 
- Request Body 

anatomy of a response: 

HTTP/1.1 200 OK \r\n
...Headers \r\n
Content-Type: text/plain \r\n
Content-Length: 13 \r\n
\r\n
Hello, world!


task: GET /hello returns 200 OK with body "Hello, world!" 

this is 13 bytes. 

scope: 

must accept TCP connections, then worry about HTTP parsing 


now, everything before i is the http request + headers, everything after i is the request body
