import http from 'node:http'; 

const [ID, PORT] = process.argv.slice(2);

const server = http.createServer((req, res) => {
  res.end(`hello, i'm server ${ID}`);
});

server.listen(PORT, () => {
  console.log(`listening on port ${PORT}`);
});
