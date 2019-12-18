const net = require('net');

const client = net.createConnection({port: 52481}, () => {
  console.log('connect to server');
  client.write('world!\n');
});

client.on('data', (data) => {
  console.log(data.toString());
  client.end();
});

client.on('end', () => {
  console.log('disconnected from server');
});
