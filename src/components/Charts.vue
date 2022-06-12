<template>
  <section>
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
      chartData: {
        labels: [],
        datasets: [
          {
            label: "Temperatures",
            backgroundColor: "#f87979",
            data: [],
          },
          {
            label: "Lumens",
            backgroundColor: "#000000",
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
    this.getDataFromUser(this.user.user);
    console.log("user chart :", this.user);
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
        filter: { "info.user": user },
        projection: {
          status: 1,
          info: 1,
        },
      });

      fetch(
        "https://thingproxy.freeboard.io/fetch/https://data.mongodb-api.com/app/data-grsmg/endpoint/data/beta/action/find",
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
          console.log("userselect  :", json);
          for (let index = 0; index < json.documents.length; index++) {
            this.chartData.labels.push(json.documents[index].info.time);

            this.chartData.datasets[0].data.push(
              parseFloat(json.documents[index].status.temperature)
            );

            this.chartData.datasets[1].data.push(
              parseInt(json.documents[index].status.light)
            );
          }
          let valBegin = this.chartData.datasets[1].data.length - 10;
          if (valBegin <= 0) {
            valBegin = 0;
          }
          this.chartData.datasets[1].data =
            this.chartData.datasets[1].data.slice(
              valBegin,
              this.chartData.datasets[1].data.length
            );
          valBegin = this.chartData.datasets[0].data.length - 10;
          if (valBegin <= 0) {
            valBegin = 0;
          }
          this.chartData.datasets[0].data =
            this.chartData.datasets[0].data.slice(
              valBegin,
              this.chartData.datasets[0].data.length
            );
          valBegin = this.chartData.labels.length - 10;
          if (valBegin <= 0) {
            valBegin = 0;
          }
          this.chartData.labels = this.chartData.labels.slice(
            valBegin,
            this.chartData.labels.length
          );

          console.log("labels :", this.chartData.labels);
          console.log("dataset data :", this.chartData.datasets[0].data);
          this.isFinish = true;
        });
    },
  },
};
</script>
