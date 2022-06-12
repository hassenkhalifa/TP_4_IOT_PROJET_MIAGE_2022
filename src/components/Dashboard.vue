<template>
  <section>
    <b-table
      :data="data"
      :paginated="isPaginated"
      :per-page="perPage"
      :current-page.sync="currentPage"
      :pagination-simple="isPaginationSimple"
      :pagination-position="paginationPosition"
      :default-sort-direction="defaultSortDirection"
      :pagination-rounded="isPaginationRounded"
      :sort-icon="sortIcon"
      :sort-icon-size="sortIconSize"
      default-sort="user.first_name"
      aria-next-label="Next page"
      aria-previous-label="Previous page"
      aria-page-label="Page"
      aria-current-label="Current page"
      :page-input="hasInput"
      :pagination-order="paginationOrder"
      :page-input-position="inputPosition"
      :debounce-page-input="inputDebounce"
      :selected.sync="selected"
      focusable
    >
      <b-table-column
        field="id"
        label="ID"
        width="40"
        sortable
        numeric
        v-slot="props"
      >
        {{ props.row.id }}
      </b-table-column>

      <b-table-column
        field="id"
        label="Localisation"
        width="40"
        sortable
        numeric
        v-slot="props"
      >
        {{ props.row.loc }}
      </b-table-column>
      <b-table-column
        field="id"
        label="Utilisateur"
        width="40"
        sortable
        numeric
        v-slot="props"
      >
        {{ props.row.user }}
      </b-table-column>
      <b-table-column
        field="id"
        label="Dernière mise a jour"
        width="40"
        sortable
        numeric
        v-slot="props"
      >
        {{ props.row.time }}
      </b-table-column>
      <b-table-column
        field="id"
        label="Status Coller"
        width="40"
        sortable
        numeric
        v-slot="props"
      >
        {{ props.row.CoolerStatus }}
      </b-table-column>
      <b-table-column
        field="id"
        label="Status Heater"
        width="40"
        sortable
        numeric
        v-slot="props"
      >
        {{ props.row.HeaterStatus }}
      </b-table-column>
      <b-table-column
        field="id"
        label="Latitude"
        width="40"
        sortable
        numeric
        v-slot="props"
      >
        {{ props.row.lat }}
      </b-table-column>
      <b-table-column
        field="id"
        label="Longitude"
        width="40"
        sortable
        numeric
        v-slot="props"
      >
        {{ props.row.lgn }}
      </b-table-column>
    </b-table>
    <div v-if="selected">
      <Chart :user="selected" :key="selected"></Chart>
    </div>
  </section>
</template>


<script>
import Chart from "./Charts";
export default {
  props: {
    idUser: Array,
  },
  data() {
    const data = [];

    return {
      data,
      selected: data[1],
      isPaginated: true,
      isPaginationSimple: false,
      isPaginationRounded: false,
      paginationPosition: "bottom",
      defaultSortDirection: "asc",
      sortIcon: "arrow-up",
      sortIconSize: "is-small",
      currentPage: 1,
      perPage: 5,
      hasInput: false,
      paginationOrder: "",
      inputPosition: "",
      inputDebounce: "",
    };
  },
  components: {
    Chart,
  },
  created() {
    let requests = this.idUser.map((user) => this.getUserEsp(user));
    Promise.all(requests);
    this.getUserEsp();
  },
  methods: {
    setUser(user) {
      console.log("user utiliser : " + user);
    },
    dateThAttrs(column) {
      return column.label === "Date"
        ? {
            title: 'This title is sponsored by "th-attrs" prop',
            class: "has-text-success",
          }
        : null;
    },
    columnTdAttrs(row, column) {
      if (row.id === "Total") {
        if (column.label === "ID") {
          return {
            colspan: 4,
            class: "has-text-weight-bold",
            style: {
              "text-align": "left !important",
            },
          };
        } else if (column.label === "Gender") {
          return {
            class: "has-text-weight-semibold",
          };
        } else {
          return {
            style: { display: "none" },
          };
        }
      }
      return null;
    },
    getUserEsp(user) {
      console.log(" init ? : " + this.init);
      var data = JSON.stringify({
        collection: "Data",
        database: "DataMonitoring",
        dataSource: "Cluster0",
        filter: { "info.user": user },
        projection: {
          status: 1,
          info: 1,
        },
      });

      fetch(
        "https://api.codetabs.com/v1/proxy?quest=https://data.mongodb-api.com/app/data-grsmg/endpoint/data/beta/action/findOne",
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
          console.log(json);

          console.log("firt init !");

          const obj = {
            id: json.document._id,
            loc: json.document.info.loc,
            user: json.document.info.user,
            time: json.document.info.time,
            CoolerStatus: json.document.status.ledCooler,
            HeaterStatus: json.document.status.ledHeater,
            lat: json.document.status.lat,
            lgn: json.document.status.lgn,
          };

          this.data.push(obj);

          console.log("points : " + JSON.stringify(obj));
        });
    },
  },
};
</script>

<style scoped>
.samples {
  font-family: sans-serif;
  max-width: 800px;
  margin: 20px auto;
}
</style>