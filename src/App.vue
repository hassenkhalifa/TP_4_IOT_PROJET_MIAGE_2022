<template>
  <div>
    <nav class="navbar" role="navigation" aria-label="main navigation">
      <div class="navbar-brand">
        <a class="navbar-item">
          <img src="./assets/globe.png" width="28" height="30" />
        </a>
      </div>
      <div id="navbarBasicExample" class="navbar-menu">
        <div class="navbar-start">
          <router-link class="navbar-item" to="/">World Map</router-link>
          <router-link class="navbar-item" to="/Ville">Ville</router-link>
          <router-link class="navbar-item" to="/Dashboard">Dashboard</router-link>
        </div>
      </div>
    </nav>
    <router-view :idUser="idUser" />
  </div>
</template>

<script>
export default {
  name: "App",
  data: function () {
    return {
      idUser: [],
      uniqueId: [],
    };
  },
  created() {
    setTimeout(() => {
      this.getID();
    }, 1000);
  },
  methods: {
    getID() {
      var data = JSON.stringify({
        collection: "Data",
        database: "DataMonitoring",
        dataSource: "Cluster0",
        projection: {
          status: 1,
          info: 1,
        },
      });

      fetch(
        "https://api.codetabs.com/v1/proxy?quest=https://data.mongodb-api.com/app/data-grsmg/endpoint/data/beta/action/find",
        {
          method: "POST",
          body: data,
          headers: {
            "Content-Type": "application/json",
            "Access-Control-Request-Headers": "*",
            "api-key":
              "pP3dYqzJQwzxhlj24CfIKPTHAy8LcAf4W2YdpRXbvmEXhh8LHLNOGSAabuO5QS7k",
          },
        }
      )
        .then((response) => response.json())
        .then((json) => {
          console.log("json legth : ", json.documents.length);
          for (let index = 0; index < json.documents.length; index++) {
            if (!this.idUser.includes(json.documents[index].info.user)) {
              this.idUser.push(json.documents[index].info.user);
            }
          }

          console.log("idusers : " + this.idUser);
        });
    },
  },
};
</script>

<style>
</style>
