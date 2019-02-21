<template>
  <v-container grid-list-lg>
    <v-layout
      wrap
      row
    >
      <v-flex xs12>
        <h2 class="headline">AQI</h2>
      </v-flex>
      <v-flex
        xs12
        sm6
        md6
        v-for="(item, index) in message.aqi"
        :key="index"
      >
        <v-card
          :color="aqiColor[item.level]"
          class="elevation-4"
          lighten-1
        >
          <v-card-title
            class="pt-3"
            :color="aqiColor[item.level]"
          >
            <span class="headline mr-3"> {{item.name.toUpperCase()}} </span>
          </v-card-title>

          <v-card-text>
            <p class="text-xs-right mr-3">
              <span class="display-4">{{item.val}}</span>
              <span class="font-weight-light font-italic ml-2 mt-5 mr-2"> μg/m<sup>3</sup></span>
            </p>

            <p class="text-xs-right mr-3"> {{aqiText[item.name][item.level]}}</p>
          </v-card-text>
          <v-card-text align="right">
            <span class="title">Base on </span>
            <span> {{item.base}}</span>
          </v-card-text>
        </v-card>
      </v-flex>

    </v-layout>

  </v-container>
</template>

<script>
export default {
  name: "Aqi",
  data: () => ({
    aqiText: {
      us: [
        "Good",
        "Moderate",
        "Unhealthy for Sensitive Groups",
        "Unhealthy",
        "Very Unhealthy",
        "Hazardous"
      ],
      cn: [
        "Exellent",
        "Good",
        "Lightly Polluted",
        "Moderately Polluted",
        "Heavily Polluted",
        "Severely Polluted"
      ]
    },
    aqiColor: ["#00e400", "#ffff00", "#ff7e00", "#ff0000", "#99004c", "#7e0023"]
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
