<template>
  <l-marker :key="point.id" :lat-lng="point.coordinates">
    <l-icon ref="icon">
      <img class="ESP-icon" :src="point.imageUrl" />
    </l-icon>
    <l-popup>
      <pre>
GPS : lat {{ point.coordinates[0] }} lgn {{ point.coordinates[1] }}
      
localisation :  {{ point.loc }} 
      
utilisateur :  {{ point.user }} 
      
temperature : {{ point.temperature }}
      
Lumens: {{ point.lumens }}
      </pre>
    </l-popup>
  </l-marker>
</template>

<script>
import { LIcon, LMarker, LPopup } from "vue2-leaflet";
export default {
  components: { LIcon, LMarker, LPopup },
  props: {
    point: {
      type: Object,
      required: true,
    },
    LPopup,
  },
};
</script>

<style>
.ESP-icon {
  height: 50px;
  width: auto;
}
</style>