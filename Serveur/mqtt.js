var mqtt = require('mqtt')
var MongoClient = require('mongodb').MongoClient;
var url = "mongodb+srv://hassen:kO0IgBWVGgzWmaRZ@cluster0.1blp0.mongodb.net/Datamonitoring?retryWrites=true&w=majority";

const mqtt_url = 'http://test.mosquitto.org:1883'
var options = {
    clientId: "deathstar",
    username: "darkvador",
    password: "6poD2R2",
    clean: true
};
var client = mqtt.connect(mqtt_url, options);







// on mqtt conect subscribe on tobic test 
client.on('connect', function () {
    client.subscribe('iot/M1Miage2022', function (err) {
        if (err)
            console.log(err)
        if (!err)
            console.log("cava pour l'instant")
    })
})

//when recive message 
client.on('message', function (topic, message) {
    //json_check(message)
    console.log("json_check = " +JSON.stringify(message) );
    json_check(message)
})

//check if data json or not
function json_check(data) {
    try {
        JSON.parse(data);
    } catch (e) {
        return false;
    }
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