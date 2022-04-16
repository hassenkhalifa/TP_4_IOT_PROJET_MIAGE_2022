 
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
    
  </l-map>
</template>

<script>
import { LMap, LTileLayer } from "vue2-leaflet";

import "leaflet/dist/leaflet.css";
export default {
  components: {
    LMap,
    LTileLayer,
  },
  data() {
    return {
      key: "9c0f6b0bd3e3abbcc0c9ad3bdee77677",
      url: "",
      layer: [
        { name: "clouds_new" },
        { name: "precipitation_new" },
        { name: "pressure_new" },
        { name: "wind_new" },
        { name: "temp_new" },
      ],
      center: [49.1193089, 6.1757156],
      zoom: 12,
    };
  },
  mounted() {
    this.setURL();
  },
  methods: {
    zoomUpdated(zoom) {
      this.zoom = zoom;
    },
    centerUpdated(center) {
      this.center = center;
    },
    setURL() {
      this.url = "https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png";


      //this.url = `https://tile.openweathermap.org/map/${this.layer[0].name}/{z}/{x}/{y}.png?appid=${this.key}`;
      // this.url=`http://maps.openweathermap.org/maps/2.0/weather/PA0/{z}/{x}/{y}appid=${this.key}`
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
