<script lang="ts">
    let { min = 0, max = 10, value = $bindable(5), step = 0, title = $bindable(""), onchange = () => {} } = $props();

    let id = "slider" + Math.random();
</script>

<div class="container">
    {#if title}
        <label class="title" for={id}>{title}:</label>
    {/if}
    <input class="slider" {id} type="range" {min} {max} bind:value step={step === 0 ? 'any' : step} onchange={() => onchange()} />
    <input type="number" class="value" bind:value={value} />
</div>

<style>
    .container {
        display: flex;
        flex-direction: row;
        align-items: center;
    }
    .slider {
        margin: 0px 5px 0px 10px;
    }
    .value {
        margin: 0px;
        width: 8ch;
    }
</style>