import VueNativeSock from 'vue-native-websocket';
import '@babel/polyfill';
import Vue from 'vue';
import './plugins/vuetify';
import App from './App';
import router from './router';
import store from './store';

Vue.config.productionTip = false;
let hname = process.env.NODE_ENV === 'production' ? location.host : 'pms5003st.local';

Vue.use(VueNativeSock, 'ws://' + hname + '/ws', {
	store: store,
	reconnection: true,
	reconnectionAttempts: 5,
	reconnectionDelay: 3000,
	format: 'json',
	passToStoreHandler: function(eventName, event) {
		if (!eventName.startsWith('SOCKET_')) {
			return;
		}
		let method = 'commit';
		let target = eventName.toUpperCase();
		let msg = event;

		if (this.format === 'json' && msg.data) {
			msg = JSON.parse(msg.data);

			if (msg.mutation) {
				target = [msg.namespace || '', msg.mutation].filter(e => !!e).join('/');
			} else if (msg.action) {
				method = 'dispatch';
				target = [msg.namespace || '', msg.action].filter(e => !!e).join('/');
			}
		} else {
			msg = msg.data;
		}

		this.store[method](target, msg);
	}
});

/* eslint-disable no-new */
new Vue({
	el: '#app',
	router,
	store,
	render: h => h(App)
});
