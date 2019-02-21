<template>
  <v-container grid-list-lg>
    <v-layout
      wrap
      row
    >
      <v-flex xs12>
        <v-toolbar
          color="green"
          dark
        >
          <v-toolbar-title>PM (CF1)</v-toolbar-title>
        </v-toolbar>

      </v-flex>
      <v-flex
        xs12
        sm6
        md4
        v-for="(item, index) in message.cf1"
        :key="index"
      >
        <v-card
          class="elevation-3"
          color="light-green"
        >
          <v-card-title>
            <span class="headline mr-3"> {{item.name.toUpperCase()}} </span>
          </v-card-title>
          <v-card-text>

            <p class="text-xs-right"> <span class="display-1 mr-5">{{item.val}}</span></p>
          </v-card-text>
        </v-card>
      </v-flex>

    </v-layout>
    <v-layout
      wrap
      row
    >
      <v-flex xs12>
        <v-toolbar
          color="green"
          dark
        >
          <v-toolbar-title>PM (ATO)</v-toolbar-title>
        </v-toolbar>
      </v-flex>
      <v-flex
        xs12
        sm6
        md4
        v-for="(item, index) in message.ato"
        :key="index"
      >
        <v-card
          class="elevation-3"
          color="light-green"
        >
          <v-card-title>
            <span class="headline mr-3"> {{item.name.toUpperCase()}} </span>
          </v-card-title>
          <v-card-text>

            <p class="text-xs-right"> <span class="display-1 mr-5">{{item.val}}</span></p>
          </v-card-text>
        </v-card>
      </v-flex>

    </v-layout>
    <v-layout
      wrap
      row
    >
      <v-flex xs12>
        <v-toolbar
          color="green"
          dark
        >
          <v-toolbar-title>PCS</v-toolbar-title>
        </v-toolbar>

      </v-flex>
      <v-flex
        xs12
        sm6
        md4
        v-for="(item, index) in message.pcs"
        :key="index"
      >
        <v-card
          class="elevation-3"
          color="light-green"
        >
          <v-card-title>
            <span class="headline mr-3"> {{item.name.toUpperCase()}} </span>
          </v-card-title>
          <v-card-text>

            <p class="text-xs-right"> <span class="display-1 mr-5">{{item.val}}</span></p>
          </v-card-text>
        </v-card>
      </v-flex>

    </v-layout>
    <v-layout
      wrap
      row
    >
      <v-flex xs12>
        <v-toolbar
          color="green"
          dark
        >
          <v-toolbar-title>Environment</v-toolbar-title>
        </v-toolbar>

      </v-flex>
      <v-flex
        xs12
        sm6
        md4
        v-for="(item, index) in message.env"
        :key="index"
      >
        <v-card
          class="elevation-3"
          color="light-green"
        >
          <v-card-title>
            <span class="headline mr-3"> {{item.name.toUpperCase()}} </span>
          </v-card-title>
          <v-card-text>

            <p class="text-xs-right"> <span class="display-1 mr-5">{{item.val}}</span></p>
          </v-card-text>
        </v-card>
      </v-flex>

    </v-layout>
    <v-layout
      wrap
      row
    >
      <v-flex xs12>
        <v-toolbar
          color="green"
          dark
        >
          <v-toolbar-title>Network</v-toolbar-title>
        </v-toolbar>
      </v-flex>
      <v-flex
        xs12
        sm6
        md4
        v-for="(item, index) in message.network"
        :key="index"
      >
        <v-card
          class="elevation-3"
          color="light-green"
        >
          <v-card-title>
            <span class="headline mr-3"> {{item.name.toUpperCase()}} </span>
          </v-card-title>
          <v-card-text>

            <p class="text-xs-right"> <span class="display-1 mr-5">{{item.val}}</span></p>
          </v-card-text>
        </v-card>
      </v-flex>

    </v-layout>

    <v-layout
      wrap
      row
    >
      <v-flex xs12>
        <v-toolbar
          color="green"
          dark
        >
          <v-toolbar-title>System</v-toolbar-title>
        </v-toolbar>
      </v-flex>
      <v-flex
        xs12
        sm6
        md4
        v-for="(item, index) in message.system"
        :key="index"
      >
        <v-card
          class="elevation-3"
          color="light-green"
        >
          <v-card-title>
            <span class="headline mr-3"> {{item.name.toUpperCase()}} </span>
          </v-card-title>
          <v-card-text>

            <p class="text-xs-right"> <span class="display-1 mr-5">{{item.val}}</span></p>
          </v-card-text>
        </v-card>
      </v-flex>

    </v-layout>

  </v-container>
</template>

<script>
export default {
  name: "Home",
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
