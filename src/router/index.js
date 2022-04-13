import Vue from 'vue'
import VueRouter from 'vue-router'
import Ville from '../components/Ville.vue'
import Map from '../components/Map.vue'

Vue.use(VueRouter)

const routes = [
  {
    path: '/',
    name: 'Map',
    component: Map
  },
  {
    path: '/Ville',
    name: 'Ville',
    component: Ville
  }
]

const router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes
})

export default router
