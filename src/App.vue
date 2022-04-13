<template>
  <div>
  <nav class="navbar" role="navigation" aria-label="main navigation">
  <div class="navbar-brand">
    <a class="navbar-item" >
      <img src="./assets/globe.png" width="28" height="30">
    </a>
  </div>
  <div id="navbarBasicExample" class="navbar-menu">
    <div class="navbar-start">
      <router-link class="navbar-item" to="/">World Map</router-link> 
      <router-link class="navbar-item" to="/Ville">Ville</router-link>
    </div>

     
  </div>
</nav>
<router-view/>
  </div>
</template>

<script>
// import HelloWorld from './components/HelloWorld.vue'

export default {
  name: 'App',
  components: {
    // HelloWorld
  }
}
</script>

<style>

</style>
