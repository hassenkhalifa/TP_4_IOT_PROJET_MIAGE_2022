<template>
  <section>
    
    <b-tag type="is-info" size="is-large" >Ville : {{ selected }}</b-tag>
    <b-field label="Selectionné une ville">
      <b-autocomplete
        rounded
        v-model="name"
        :data="filteredDataArray"
        placeholder="e.g. jQuery"
        icon="magnify"
        clearable
        @select="(option) => (selected = option)"
      >
        <template #empty>No results found</template>
      </b-autocomplete>
    </b-field>
  </section>
</template>

<script>
export default {
  name: "Ville",
  props: ["Villes"],
  data() {
    return {
      data: this.Villes,
      name: "",
      selected: null,
    };
  },
  computed: {
    filteredDataArray() {
      return this.data.filter((option) => {
        return (
          option.toString().toLowerCase().indexOf(this.name.toLowerCase()) >= 0
        );
      });
    },
  },
  methods: {
    dataReplace: function () {
     
    },
  },
  
};
</script>


<style scoped>

</style>
