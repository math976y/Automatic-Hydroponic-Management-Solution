<script lang="ts">
	import { useTRPC } from '$lib/trpc/client.svelte';
	import type { ECVal, HumidifierVal, PhVal } from '$lib/trpc/router';
	import { onMount } from 'svelte';
	import NumberDisplay from '$lib/numberDisplay.svelte';
	import Slider from '$lib/slider.svelte';
	import Checkbox from '$lib/checkbox.svelte';

	let t = useTRPC();

	let phVal: PhVal | undefined = $state();
	let humidifierVal: HumidifierVal | undefined = $state();
	let ecVal: ECVal | undefined = $state();
	let pumpOn = $state(false);
	let humiditySetPoint = $state(60);
	onMount(() => {
		t.onPumpVal.subscribe(undefined, {
			onData: (val) => {
				pumpOn = val;
			}
		});
		t.onPhVal.subscribe(undefined, {
			onData: (val) => {
				phVal = val;
			}
		});
		t.onHumidifierVal.subscribe(undefined, {
			onData: (val) => {
				humidifierVal = val;
			}
		});
		t.onECVal.subscribe(undefined, {
			onData: (val) => {
				ecVal = val;
			}
		});
		t.onHumiditySetPoint.subscribe(undefined, {
			onData: (val) => {
				humiditySetPoint = val;
			}
		});
	});
</script>

<h1>Drivhus kontrolpanel</h1>

<NumberDisplay title="pH værdi" val={phVal?.pH} />
<NumberDisplay title="EC værdi" val={ecVal?.EC} />
<NumberDisplay title="Temperatur" val={humidifierVal?.temperature} />
<NumberDisplay title="Luftfugtighed" val={humidifierVal?.humidity} />

<Slider
	min={0}
	max={100}
	step={1}
	bind:value={humiditySetPoint}
	title="Enable humidifier at (%)"
	onchange={() => {
		t.setHumiditySetPoint.query(humiditySetPoint);
	}}
/>

<Checkbox
	title="Pump 1"
	bind:checked={pumpOn}
	onchange={() => {
		t.setPump.query(pumpOn);
	}}
/>
