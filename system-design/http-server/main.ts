import net from "node:net"; 


const PORT = 8080;
const CRLF = '\r\n';

function split_request(buf: Buffer, empty_line: number): [string[], Map<string, string>] { 
  /* split buffer into method, headers */
  
  let l = buf.indexOf(CRLF);
  
  const request_line = buf.subarray(0, l).toString(); 
  const headers = new Map<string, string>();
  
  l += 2; 
  while (l < empty_line) {
    const r = buf.indexOf(CRLF, l); 
    
    if (r === -1) break; 
    
    const header = buf.subarray(l, r).toString();
    const colon = header.indexOf(":");
     
    const key = header.slice(0, colon);
    const value = header.slice(colon+1).trim();
    
    headers.set(key, value);
    l = r + 2;         
  }
  return [request_line.split(" "), headers];
}


const server = net.createServer((c: net.Socket) => { 
  console.log("connected!");
  let buf = Buffer.alloc(0);
  const pages = new Set<string>(["/hello"]);
  
  c.on('data', (data) => {
    if (typeof data === "object") {
      buf = Buffer.concat([buf, data]);
      let i = buf.indexOf(CRLF + CRLF); 
      
      
      if (i === -1) return;
      
      const [request_line, headers] = split_request(buf, i); 
      
      if (request_line.length < 3) { 
        console.log(request_line);
        c.write(`HTTP/1.1 400\r\nContent-Type: text/plain\r\nContent-Length: 11\r\n\r\nBad Request`);
        return;
      }     
      const [method, resource, protocol] = request_line;
      
      if (!pages.has(resource)) {
         c.write(`HTTP/1.1 404\r\nContent-Type: text/plain\r\nContent-Length: 9\r\n\r\nNot Found`);
      } 
      
      let body = ""
      const content_length = headers.get('Content-Length');
      if (content_length !== undefined) { 
        const j = i+4 // 2 CRLF's = 4 bytes 
        const n = j + parseInt(content_length);
        
        if (n > buf.length) return;  
      
        body = buf.subarray(j, n).toString();
      }

      console.log(body)
    }
  });

});

server.listen(PORT, () => {
  console.log('listening...');
});


