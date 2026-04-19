<script lang="ts">
	let { title, checked = $bindable(false), onchange = () => {} } = $props();
</script>

<div class="container">
	<div class="title">{title}:</div>
	<input type="checkbox" bind:checked onchange={() => onchange()} />
</div>

<style>
	.container {
		display: flex;
		flex-direction: row;
	}
</style>
