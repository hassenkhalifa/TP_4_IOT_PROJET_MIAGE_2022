<template>
  <section>
    <div>
      <b-button
        type="is-info"
        icon-left="refresh"
        @click="this.getDataFromUser(this.user.id)"
      ></b-button>
    </div>
    <div v-if="isFinish">
      <LineChartGenerator
        :chart-options="chartOptions"
        :chart-data="chartData"
        :chart-id="chartId"
        :dataset-id-key="datasetIdKey"
        :plugins="plugins"
        :css-classes="cssClasses"
        :styles="styles"
        :width="width"
        :height="height"
      />
    </div>
  </section>
</template>

<script>
import { Line as LineChartGenerator } from "vue-chartjs/legacy";

import {
  Chart as ChartJS,
  Title,
  Tooltip,
  Legend,
  LineElement,
  LinearScale,
  CategoryScale,
  PointElement,
} from "chart.js";

ChartJS.register(
  Title,
  Tooltip,
  Legend,
  LineElement,
  LinearScale,
  CategoryScale,
  PointElement
);

export default {
  name: "LineChart",
  components: {
    LineChartGenerator,
  },
  props: {
    user: Object,
    chartId: {
      type: String,
      default: "line-chart",
    },
    datasetIdKey: {
      type: String,
      default: "label",
    },
    width: {
      type: Number,
      default: 200,
    },
    height: {
      type: Number,
      default: 400,
    },
    cssClasses: {
      default: "",
      type: String,
    },
    styles: {
      type: Object,
      default: () => {},
    },
    plugins: {
      type: Array,
      default: () => [],
    },
  },
  data() {
    return {
      isFinish: false,
      results: [],
      chartData: {
        labels: [],
        datasets: [
          {
            label: "Data One",
            backgroundColor: "#f87979",
            data: [],
          },
        ],
      },
      chartOptions: {
        responsive: true,
        maintainAspectRatio: false,
      },
    };
  },
  created() {
    setTimeout(() => {
      this.getDataFromUser(this.user.id);
    }, 5000);
  },
  methods: {
    getDataFromUser(user) {
      console.log(" user ? : " + user);
      let selectUser = user.toString();
      console.log("selectUser : " + selectUser);
      var data = JSON.stringify({
        collection: "Data",
        database: "DataMonitoring",
        dataSource: "Cluster0",
        filter:{'info.user':3753},
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
          this.results = json;
          console.log("userselect  :", JSON.stringify(this.results));
        });
      if (this.results) {
        for (let index = 0; index < this.results.length; index++) {
          if (this.user.user === this.results.documents[index].info.user) {
            this.chartData.datasets[0].data.push(
              parseFloat(this.results.documents[index].status.temperature)
            );
            this.chartData.labels.push("19:48:53");
          }
        }
        console.log(
          "labels",
          this.chartData.labels,
          "data",
          this.chartData.datasets[0].data
        );

        this.isFinish = true;
      }
    },
  },
};
</script>
