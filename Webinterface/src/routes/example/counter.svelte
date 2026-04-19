<script lang="ts">
    // Definer variablen med $state funktionen, for at
    // fortælle Svelte, at variablen skal være reaktiv
    let val = $state(0);
</script>

<h1>Værdi: {val}</h1>

<button onclick={() => val++}>Forøg værdi</button>
<button onclick={() => val--}>Formindsk værdi</button>