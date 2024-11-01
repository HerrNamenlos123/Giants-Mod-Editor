<script setup lang="ts">
import BasicText from "./Basic/BasicText.vue";

const props = defineProps<{ title: string }>();
</script>

<template>
  <BasicText class="font-bold mb-1 mt-1" :text="title" />
</template>
