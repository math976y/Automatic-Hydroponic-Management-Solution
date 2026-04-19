<script lang="ts">
	let { title, val } = $props();
</script>

<div class="container">
	<div class="title">{title}:</div>
	<div class="value">
		{#if typeof val === 'number'}
			{val}
		{:else}
			Loading...
		{/if}
	</div>
</div>

<style>
	.container {
		display: flex;
		flex-direction: row;
	}
</style>
