 
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
      users: {},
      uniqueId: [],
    };
  },

  created() {
    this.getUserEsp();
    console.log();
    console.log("iduser  map : ", this.idUser);
    setTimeout(() => {
      this.getUniqueID();
    }, 2000);
    
  },
  methods: {
    getUniqueID() {
      this.idUser.forEach((c) => {
        if (!this.uniqueId.includes(c)) {
          this.uniqueId.push(c);
        }
      });
      console.log("uniqueid : " + this.uniqueId);
    },

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
          const obj = {
            id: json.documents[0].info.user,
            imageUrl: "https://cdn-icons-png.flaticon.com/512/2540/2540201.png",
            coordinates: [
              parseFloat(json.documents[0].status.lat),
              parseFloat(json.documents[0].status.lgn),
            ],
            temperature: json.documents[0].status.temperature,
            lumens: json.documents[0].status.light,
            loc: json.documents[0].info.loc,
            user: json.documents[0].info.user,
          };
          this.points.push(obj);
          console.log("points : " + JSON.stringify(obj));
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
  overflow: hidden;
}
</style>
