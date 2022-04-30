<template>
  <section>
    <div class="position">
      <b-field label="Selectionner une ville" class="search-box">
        <b-input v-model="nom"></b-input>
      </b-field>

      <b-button @click="Datafetch">lancer la recherche</b-button>
    </div>
    <div v-if="notEmpty">
      <div class="location-box">
        <div class="location">
          {{ temps.name }}, {{ temps.sys.country || null }}
        </div>

        <div class="weather-box">
          <div class="temp">{{ Math.round(temps.main.temp) }} C°</div>
          <div class="weather">{{ temps.weather[0].main }}</div>
        </div>
      </div>
    </div>
  </section>
</template>

<script>
export default {
  data() {
    return {
      nom: "",
      key: "9c0f6b0bd3e3abbcc0c9ad3bdee77677",
      url: "https://thingproxy.freeboard.io/fetch/http://api.openweathermap.org/data/2.5/",
      temps: {},
      notEmpty: false,
    };
  },
  computed: {
    filteredDataArray() {
      return this.data.filter((option) => {
        return (
          option.toString().toLowerCase().indexOf(this.nom.toLowerCase()) >= 0
        );
      });
    },
  },

  methods: {
    Datafetch() {
      fetch(`${this.url}weather?q=${this.nom}&units=metric&APPID=${this.key}`)
        .then((response) => {
          return response.json();
        })
        .then(this.tempsResultat);
    },
    tempsResultat(result) {
      this.temps = result;
      this.notEmpty = true;
    },
  },
};
</script>


<style scoped>
.position {
  position: absolute;
  left: 25%;
  display: block;
}
.search-box {
  width: 50%;
  margin-bottom: 30px;
  align-items: center;
}

.location-box .location {
  color: rgb(0, 0, 0);
  font-size: 32px;
  font-weight: 500;
  text-align: center;
  margin-top: 125px;
}

.weather-box {
  text-align: center;
}
.weather-box .temp {
  display: inline-block;
  padding: 10px 25px;
  color: rgb(0, 0, 0);
  font-size: 102px;
  font-weight: 900;
  background-color: rgba(255, 255, 255, 0.25);
  border-radius: 16px;
  margin: 30px 0px;
}
.weather-box .weather {
  color: rgb(0, 0, 0);
  font-size: 48px;
  font-weight: 700;
  font-style: italic;
}
</style>
