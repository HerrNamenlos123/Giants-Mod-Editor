<script setup lang="ts">
const value = defineModel<string>({ default: "" });
const props = defineProps<{
  placeholder: string;
}>();
</script>

<template>
  <div class="m-1">
    <input
      v-model="value"
      class="border rounded-sm pl-1 border-gray-400"
      type="text"
      :placeholder="placeholder"
    />
  </div>
</template>
