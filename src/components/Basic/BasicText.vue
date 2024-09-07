<script setup lang="ts">
const props = defineProps<{ text: string }>();
</script>

<template>
    <div class="mx-1">{{ props.text }}</div>
</template>