<template>
  <section>
    <b-field label="Name">
      <b-input v-model="nom"></b-input>
    </b-field>
    <section>
      <b-button @click="Datafetch">Click Me</b-button>
    </section>
    <div v-if="notEmpty">
      <b-tag rounded type="is-info" size="is-large"
        >Ville : {{ temps.name }}</b-tag
      >
      <b-tag rounded type="is-info" size="is-large"
        >Pays : {{ temps.sys.country || null }}</b-tag
      >
      <b-tag rounded type="is-info" size="is-large"
        >Temps : {{ temps.weather[0].main }}</b-tag
      >
      <b-tag rounded type="is-info" size="is-large"
        >Temperature : {{ Math.round(temps.main.temp) }}</b-tag
      >
    </div>
  </section>
</template>

<script>
export default {
  data() {
    return {
      nom: "",
      key: "9c0f6b0bd3e3abbcc0c9ad3bdee77677",
      url: "http://api.openweathermap.org/data/2.5/",
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
</style>
