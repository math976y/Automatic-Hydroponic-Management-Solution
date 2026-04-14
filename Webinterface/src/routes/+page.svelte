<script lang="ts">
	import Slider from "$lib/slider.svelte";

    let val = $state(3);
    let val2 = $state(3);
    let val3 = $state(3);
    let val4 = $state(3);
</script>

<h1>Drivhus kontrolpanel</h1>
<Slider bind:value={val} step={.1} title="Værdi"/>
<Slider bind:value={val2} step={.1} title="Værdi 2"/>
<Slider bind:value={val3} step={.1} title="Værdi 3"/>
<Slider bind:value={val4} step={.1} title="Værdi 4"/>

<p>Slider val is {val}</p>