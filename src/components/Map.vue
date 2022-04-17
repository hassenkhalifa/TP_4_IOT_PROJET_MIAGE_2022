 
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
    point
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
    };
  },
  methods: {
    zoomUpdated(zoom) {
      this.zoom = zoom;
    },
    centerUpdated(center) {
      this.center = center;
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
