<script setup lang="ts">
import { computed } from "vue";

const selectedText = defineModel<string>();
const selectedIndex = defineModel<number>("index");

const props = defineProps<{
  options: string[];
}>();

const modelValueProxy = computed({
  get() {
    if (selectedIndex.value !== undefined) {
      return props.options[selectedIndex.value];
    } else if (selectedText.value !== undefined) {
      return props.options.find((o) => o === selectedText.value) || "";
    }
    return "";
  },
  set(value: string) {
    if (selectedIndex.value !== undefined) {
      selectedIndex.value = props.options.indexOf(value);
    }
    if (selectedText.value !== undefined) {
      selectedText.value = value;
    }
  },
});
</script>

<template>
  <div class="">
    <select
      v-model="modelValueProxy"
      class="flex px-1 py-1 bg-button border-text border-opacity-30 rounded-sm"
    >
      <option
        v-for="option in props.options"
        :key="option"
        class="p-2"
        :value="option"
      >
        {{ option }}
      </option>
    </select>
  </div>
</template>
