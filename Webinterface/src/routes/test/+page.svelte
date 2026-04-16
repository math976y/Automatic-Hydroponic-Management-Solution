<script lang="ts">
	import { useTRPC } from '$lib/trpc/client.svelte.js';

	const trpc = useTRPC();
	let greeting = $state('')

	// Runs on server and client
	trpc.greeting.query().then((data) => {
	   greeting = data;
	});

	let val = $state(await trpc.rand.query());
</script>

<h1>{greeting}</h1>

<button onclick={async () => val = await trpc.rand.query()}>{val}</button>