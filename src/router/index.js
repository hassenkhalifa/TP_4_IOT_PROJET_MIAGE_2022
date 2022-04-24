import Vue from 'vue'
import VueRouter from 'vue-router'
import Ville from '../components/Ville.vue'
import Map from '../components/Map.vue'
import Dashboard from '../components/Dashboard.vue'

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
  },
  {
    path: '/Dashboard',
    name: 'Dashboard',
    component: Dashboard
  }
]

const router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes
})

export default router
