import Vue from 'vue';
import Router from 'vue-router';
import Home from '@/components/Home';
import Pm25cf1 from '@/components/Pm25cf1';
import Pm25ato from '@/components/Pm25ato';
import Aqi from '@/components/Aqi';
import Pcs from '@/components/Pcs';
import Env from '@/components/Env';

Vue.use(Router);

export default new Router({
	mode: 'history',
	routes: [
		{
			path: '/all',
			name: 'Home',
			component: Home
		},
		{
			path: '/',
			name: 'Aqi',
			component: Aqi
		},
		{
			path: '/pm25cf1',
			name: 'Pm25cf1',
			component: Pm25cf1
		},
		{
			path: '/pm25ato',
			name: 'Pm25ato',
			component: Pm25ato
		},
		{
			path: '/pcs',
			name: 'Pcs',
			component: Pcs
		},
		{
			path: '/env',
			name: 'Env',
			component: Env
		}
	]
});
