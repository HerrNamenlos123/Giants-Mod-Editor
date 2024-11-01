<script setup lang="ts">
import { computed } from "vue";
import BasicTextInput from "./Basic/BasicTextInput.vue";
import { useStore } from "@/store";

const store = useStore();
const props = defineProps<{
  property: string;
  multiline?: boolean;
}>();

const proxy = computed({
  get() {
    return store.getProperty(props.property);
  },
  set(value: string) {
    return store.setProperty(props.property, value);
  },
});
</script>

<template>
  <BasicTextInput v-model="proxy" :multiline="multiline" />
</template>
