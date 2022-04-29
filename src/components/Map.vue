 
<template>
  <l-map
    :center="center"
    :zoom="zoom"
    class="map"
    ref="map"
    @update:zoom="zoomUpdated"
    @update:center="centerUpdated"
  >
    <b-button
      type="is-primary"
      class="position"
      icon-left="refresh"
      @click="getUserEsp()"
    >
      Actualiser</b-button
    >
    <l-tile-layer :url="url"> </l-tile-layer>
    <point v-for="p in points" :key="p.id" :point="p"> </point>
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

  props: {
    idUser: Array,
  },
  data() {
    return {
      key: "9c0f6b0bd3e3abbcc0c9ad3bdee77677",
      url: "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png",
      center: [49.1193089, 6.1757156],
      zoom: 5,
      points: [],
      pointsinit: [],
      init: false,
    };
  },

  created() {
    this.getUserEsp(this.idUser);
    console.log();
    console.log("iduser  map : ", this.idUser);
  },
  methods: {
    zoomUpdated(zoom) {
      this.zoom = zoom;
    },
    centerUpdated(center) {
      this.center = center;
    },
    getUserEsp(user) {
      console.log(" init ? : " + this.init);
      var data = JSON.stringify({
        collection: "Data",
        database: "DataMonitoring",
        dataSource: "Cluster0",
        filter: { "info.user": user[0] },
        projection: {
          status: 1,
          info: 1,
        },
      });

      fetch(
        "http://localhost:8080/app/data-grsmg/endpoint/data/beta/action/findOne",
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
            const obj = {
              id: json.documents.info.user,
              imageUrl:
                "https://cdn-icons-png.flaticon.com/512/2540/2540201.png",
              coordinates: [
                parseFloat(json.documents.status.lat),
                parseFloat(json.documents.status.lgn),
              ],
              temperature: json.documents.status.temperature,
              lumens: json.documents.status.light,
              loc: json.documents.info.loc,
              user: json.documents.info.user,
            };

            this.points.push(obj);

            console.log("points : " + JSON.stringify(obj));
          }
          if (!this.init) {
            console.log("second init !");
            this.pointsinit = [];

            const obj = {
              id: json.documents.info.user,
              imageUrl:
                "https://cdn-icons-png.flaticon.com/512/2540/2540201.png",
              coordinates: [
                parseFloat(json.documents.status.lat),
                parseFloat(json.documents.status.lgn),
              ],
              temperature: json.documents.status.temperature,
              lumens: json.documents.status.light,
              loc: json.documents.info.loc,
              user: json.documents.info.user,
            };

            this.pointsinit.push(obj);

            console.log("points : " + JSON.stringify(obj));

            this.points = this.pointsinit;
          }
          this.init = true;
        });
    },
    getPoints() {
      const obj = {
        id: this.users.documents[0].info.user,
        imageUrl: "https://cdn-icons-png.flaticon.com/512/2540/2540201.png",
        coordinates: [
          parseFloat(this.users.documents[0].status.lat),
          parseFloat(this.users.documents[0].status.lgn),
        ],
        loc: this.users.documents[0].info.loc,
      };
      this.points = obj;
      console.log("points : " + JSON.stringify(obj));
    },
  },
};
</script>

<style>
.map {
  position: absolute;
  width: 100%;
  height: 100%;
  z-index: 0;
}
.position {
  position: absolute;
  top: 20px;
  right: 20px;
  padding: 10px;
  z-index: 500;
}
</style>
