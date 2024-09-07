<script setup lang="ts">
const props = defineProps<{ text: string }>();
</script>

<template>
  <div class="">{{ props.text }}</div>
</template>
