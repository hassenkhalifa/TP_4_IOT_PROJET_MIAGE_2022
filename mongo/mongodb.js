var axios = require('axios');
var data = JSON.stringify({
    "collection": "Data",
    "filter": {
        "info.user":'dfdfddf11996'
    },
    "database": "DataMonitoring",
    "dataSource": "Cluster0",
    "projection": {
        "info": 1
    }
});

var config = {
    method: 'post',
    url: 'https://data.mongodb-api.com/app/data-grsmg/endpoint/data/beta/action/find',
    headers: {
        'Content-Type': 'application/json',
        'Access-Control-Request-Headers': '*',
        'api-key': 'pP3dYqzJQwzxhlj24CfIKPTHAy8LcAf4W2YdpRXbvmEXhh8LHLNOGSAabuO5QS7k'
    },
    data: data
};

axios(config)
    .then(function (response) {
        console.log(JSON.stringify(response.data.documents[0].info.user));
    })
    .catch(function (error) {
        console.log(error);
    });
