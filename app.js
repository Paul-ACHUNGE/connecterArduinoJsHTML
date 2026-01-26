var http = require('http');
var fs = require('fs');
var index = fs.readFileSync( 'index.html');

const {SerialPort}=require('serialport');
const {ReadlineParser}=require('@serialport/parser-readline');
const port=new SerialPort({path: 'COM7',
    baudRate:9600
})
const parser=port.pipe(new ReadlineParser({delimiter:'\r\n'}));

var app = http.createServer(function(req, res) {
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.end(index);
});

var io = require('socket.io').listen(app);

io.on('connection', function(socket) {
    
    socket.on('lights',function(data){
        
        console.log( data );
        
        port.write( data.status.toString());
    
    });
    
});

app.listen(3000);
