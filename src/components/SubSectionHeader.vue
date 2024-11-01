<script setup lang="ts">
import BasicText from "./Basic/BasicText.vue";

const props = defineProps<{ title: string }>();
</script>

<template>
  <BasicText class="m-1 pl-2" :text="title" />
  <div class="flex flex-col pl-6 pb-2">
    <slot />
  </div>
</template>
