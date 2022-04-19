 
<template>
  <l-map
    :center="center"
    :zoom="zoom"
    class="map"
    ref="map"
    @update:zoom="zoomUpdated"
    @update:center="centerUpdated"
  >
    <l-tile-layer :url="url"> </l-tile-layer>
    <point v-for="point in points" :key="point.id" :point="point"> </point>
  </l-map>
</template>

<script>
import { LMap, LTileLayer } from "vue2-leaflet";
import point from "./Marker";
import "leaflet/dist/leaflet.css";
export default {
  components: {
    LMap,
    LTileLayer,
    point,
  },
  data() {
    return {
      key: "9c0f6b0bd3e3abbcc0c9ad3bdee77677",
      url: "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png",
      center: [49.1193089, 6.1757156],
      zoom: 12,
      points: [
        {
          id: 1,
          imageUrl: "https://cdn-icons-png.flaticon.com/512/2540/2540201.png",
          coordinates: [49.11491, 6.17881],
        },
      ],
      users: {},
    };
  },

  created() {
    this.getUserEsp();
    console.log();
  },
  methods: {
    zoomUpdated(zoom) {
      this.zoom = zoom;
    },
    centerUpdated(center) {
      this.center = center;
    },
    getUserEsp() {
      var data = JSON.stringify({
        collection: "Data",
        filter: {
          "info.user": "dfdfddf11996",
        },
        database: "DataMonitoring",
        dataSource: "Cluster0",
        projection: {
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
          console.log(json)
          this.users=json;
          console.log('users : '+JSON.stringify(this.users))
        });
    },
  },
};
</script>

<style>
.map {
  position: absolute;
  width: 100%;
  height: 100%;
  overflow: hidden;
}
</style>
