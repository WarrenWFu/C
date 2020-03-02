const net = require('net');

const client = net.createConnection({
  port: 61001,
  host: '127.0.0.1',
  family: 4
}, () => {
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

client.on('error', err => {
  console.log(err.message);
});
