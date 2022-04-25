import Vue from 'vue'
import App from './App.vue'
import Buefy from 'buefy'
import 'buefy/dist/buefy.css'
import router from './router'
import 'leaflet/dist/leaflet.css';
import VueFusionCharts from 'vue-fusioncharts';
import FusionCharts from 'fusioncharts';

Vue.use(Buefy, VueFusionCharts, FusionCharts)

Vue.config.productionTip = false

new Vue({
  router,
  render: h => h(App)
}).$mount('#app')
