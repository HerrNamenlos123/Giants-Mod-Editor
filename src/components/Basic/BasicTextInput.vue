<script setup lang="ts">
const value = defineModel<string>({ default: "" });
const props = withDefaults(
  defineProps<{
    placeholder?: string;
    multiline?: boolean;
  }>(),
  {
    placeholder: "Value",
    multiline: false,
  },
);
</script>

<template>
  <div class="m-[1px] w-fit">
    <input
      v-if="!props.multiline"
      v-model="value"
      class="border rounded-sm pl-1 border-text border-opacity-30 w-full bg-button"
      type="text"
      :placeholder="placeholder"
    />
    <textarea
      v-else
      v-model="value"
      class="border rounded-sm pl-1 border-text border-opacity-30 w-full resize bg-button"
      :placeholder="placeholder"
    />
  </div>
</template>
