import http from 'node:http';

const PORT = 8080;
const ADDRESS = '127.0.0.1'; 

const BACKENDS: number[] = [8081, 8082, 8083];
let counter = 0; 

const proxy = http.createServer(async (req, res) => {
  const server = BACKENDS[counter % BACKENDS.length];
  counter++;
  
  let status: number;  
  let body: string; 
  let headers: Record<string, string>
  
  try { 
    const data = await fetch(`http://${ADDRESS}:${server}${req.url}`);

    status = data.status; 
    body = await data.text();
    headers = Object.fromEntries(data.headers.entries()); 

    res.writeHead(status, headers);
    res.end(body);
  } catch (err) {
    status = 502; 
    body = "Bad Gateway :("
    headers = {"Content-Type": "text/plain", "Content-Length": "14"};
    
    res.writeHead(status, headers);
    res.end(body);
  } 
});

proxy.listen(PORT);
