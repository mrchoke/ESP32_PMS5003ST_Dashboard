<template>
  <v-container grid-list-lg>
    <v-layout
      wrap
      row
    >
      <v-flex xs12>
        <h2 class="headline">PM (CF1)</h2>
      </v-flex>
      <v-flex
        xs12
        sm6
        md4
        v-for="(item, index) in message.cf1"
        :key="index"
      >
        <v-card
          color="green lighten-1"
          class="white--text"
          elevation-4
        >
          <v-card-title>
            <span class="headline mr-3"> {{item.name.toUpperCase()}} </span>
          </v-card-title>
          <v-card-text>
            <p class="text-xs-right mr-3">
              <span class="display-4">{{item.val}}</span>
              <span class="font-weight-light font-italic ml-2 mt-5 mr-2"> μg/m<sup>3</sup></span>
            </p>
          </v-card-text>
        </v-card>
      </v-flex>

    </v-layout>

  </v-container>
</template>

<script>
export default {
  name: "Pm25cf1",
  data: () => ({
    //
  }),
  created() {
    //
  },
  computed: {
    message() {
      return this.$store.state.socket.message;
    }
  },
  methods: {
    //
  }
};
</script>

<style>
</style>
