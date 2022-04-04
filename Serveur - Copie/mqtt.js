const mqtt = require('mqtt')
var MongoClient = require('mongodb').MongoClient;
var url = "mongodb+srv://hassen:kO0IgBWVGgzWmaRZ@cluster0.1blp0.mongodb.net/Datamonitoring?retryWrites=true&w=majority";

const host = 'o66b0ca7-internet-facing-d84cedade336f3f6.elb.eu-central-1.amazonaws.com'
const port = '1883'
const clientId = `mqtt_${Math.random().toString(16).slice(3)}`

const connectUrl = `mqtt://${host}:${port}`
const client = mqtt.connect(connectUrl, {
  clientId,
  clean: true,
  connectTimeout: 4000,
  username: 'HassenTest',
  password: '12345678',
  reconnectPeriod: 1000,
})

const topic = 'esp32/test'
client.on('connect', () => {
  console.log('Connected')
  client.subscribe([topic], () => {
    console.log(`Subscribe to topic '${topic}'`)
  })
})
client.on('message', (topic, payload) => {
  console.log('Received Message:', topic, payload.toString());
  
  json_check(payload);
})

function json_check(data) {
  try {
      JSON.parse(data);
  } catch (e) {
      return false;
  }
  console.log("ca marche pour l'instant")
  Mongo_insert(JSON.parse(data))
}

//insert data in mongodb
function Mongo_insert(data) {
  MongoClient.connect(url, function (err, db) {
      if (err) throw err;
      var dbo = db.db("DataMonitoring");
      dbo.collection("Data").insertOne(data, function (err, res) {
          if (err) throw err;
          db.close();
      });
  });
}