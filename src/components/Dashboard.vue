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
    </b-table>
  </section>
</template>


<script>
export default {
  data() {
    const data = [];

    return {
      data,
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
  created() {
    this.getUserEsp();
  },
  methods: {
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
    getUserEsp() {
      console.log(" init ? : " + this.init);
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
        "http://localhost:8080/app/data-grsmg/endpoint/data/beta/action/find",
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
          if (!this.init) {
            console.log("firt init !");
            for (let index = 0; index < json.documents.length; index++) {
              const obj = {
                id: json.documents[index].info.user,

                loc: json.documents[index].info.loc,
                user: json.documents[index].info.user,
              };

              this.data.push(obj);

              console.log("points : " + JSON.stringify(obj));
            }
          }
        });
    },
  },
};
</script>