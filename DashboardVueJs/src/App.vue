<template>
  <v-app>
    <v-navigation-drawer
      :mini-variant="miniVariant"
      :clipped="clipped"
      v-model="drawer"
      enable-resize-watcher
      app
    >
      <v-list dense>
        <v-list-tile
          @click.stop="drawer = !drawer"
          ripple
        >
          <v-list-tile-action>
            X
          </v-list-tile-action>
        </v-list-tile>

        <v-list-tile
          @click.stop="miniVariant = !miniVariant"
          ripple
        >
          <v-list-tile-action>
            <span class="font-weight-black"> {{ miniVariant ? '&gt;' : '&lt;'}}</span>
          </v-list-tile-action>
          <v-list-tile-content>
            <v-list-tile-title></v-list-tile-title>
          </v-list-tile-content>
        </v-list-tile>

        <v-list-tile
          value="true"
          v-for="(item, i) in items"
          :key="i"
          :to="item.link"
          ripple
        >
          <v-list-tile-action>
            <v-avatar
              color="teal"
              size="28"
            >
              <span class="white--text headline">{{item.text}}</span>
            </v-avatar>

          </v-list-tile-action>
          <v-list-tile-content>
            <v-list-tile-title v-text="item.title"></v-list-tile-title>
          </v-list-tile-content>
        </v-list-tile>
      </v-list>
    </v-navigation-drawer>

    <v-toolbar
      app
      color="green"
    >
      <v-toolbar-title class="headline text-uppercase">
        <span
          @click.stop="drawer = !drawer"
          ripple
        ><svg
            xmlns="http://www.w3.org/2000/svg"
            width="24"
            height="24"
            viewBox="0 0 24 24"
          >
            <path
              d="M0 0h24v24H0z"
              fill="none"
            />
            <path d="M3 13h8V3H3v10zm0 8h8v-6H3v6zm10 0h8V11h-8v10zm0-18v6h8V3h-8z" /></svg></span>
        <span class="font-weight-light">PMS5003ST</span>
      </v-toolbar-title>
      <v-spacer></v-spacer>

      <span class="mr-2">ESP32</span>

    </v-toolbar>

    <v-content>

      <router-view v-if="this.$store.state.socket.message.aqi" />

      <v-container v-else>
        <v-layout
          row
          wrap
          align-center
        >
          <v-flex
            class="text-xs-center"
            xs12
            mt-5
          >
            <v-progress-circular
              :size="150"
              :width="6"
              color="green"
              indeterminate
            ></v-progress-circular>
            <v-flex
              xs12
              mt-5
            >
              Loading.....
            </v-flex>
          </v-flex>
        </v-layout>
      </v-container>

    </v-content>
    <v-footer>
      <v-flex xs12>
        <p class="text-xs-center mt-2">#NoobMaker</p>
      </v-flex>
    </v-footer>
  </v-app>
</template>

<script>
export default {
  name: "App",
  data() {
    return {
      clipped: true,
      drawer: false,
      fixed: false,
      miniVariant: true,
      right: true,
      rightDrawer: false,
      items: [
        {
          text: "H",
          title: "Home",
          link: { name: "Home" }
        },
        {
          text: "A",
          title: "AQI",
          link: { name: "Aqi" }
        },
        {
          text: "C",
          title: "PM (CF1)",
          link: { name: "Pm25cf1" }
        },
        {
          text: "A",
          title: "PM (ATO)",
          link: { name: "Pm25ato" }
        },
        {
          text: "N",
          title: "PCS",
          link: { name: "Pcs" }
        },
        {
          text: "E",
          title: "Env",
          link: { name: "Env" }
        }
      ]
    };
  },
  created() {
    //
  },
  methods: {}
};
</script>
<style scoped>
.v-list__tile--active {
  background-color: lightgray;
}
</style>
