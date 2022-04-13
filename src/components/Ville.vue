<template>
  <section>
        <p class="content"><b>Ville :</b> {{ selected }}</p>
        <b-field label="Selectionné une ville">
            <b-autocomplete
                rounded
                v-model="name"
                :data="filteredDataArray"
                placeholder="e.g. jQuery"
                icon="magnify"
                clearable
                @select="option => selected = option">
                <template #empty>No results found</template>
            </b-autocomplete>
        </b-field>
    </section>
</template>

<script>
export default {
  name: 'Ville',
  // props: {
  //   msg: String
  // }
  data() {
            return {
                data: [
                    'Grasse',
                    'Nice'
                ],
                name: '',
                selected: null
            }
        },
        computed: {
            filteredDataArray() {
                return this.data.filter((option) => {
                    return option
                        .toString()
                        .toLowerCase()
                        .indexOf(this.name.toLowerCase()) >= 0
                })
            }
        }
}

</script>


<style scoped>

</style>
