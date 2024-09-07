<script setup lang="ts">
import BasicIcon from "./BasicIcon.vue";

const props = withDefaults(
  defineProps<{
    text?: string;
    icon?: string;
    iconAlignment?: "left" | "right";
  }>(),
  {
    iconAlignment: "left",
    icon: undefined,
    text: undefined,
  },
);

const emit = defineEmits<{
  clicked: [];
}>();

const clicked = () => {
  emit("clicked");
};
</script>

<template>
  <div
    class="flex items-center border rounded-sm px-1 m-1 py-0 border-text border-opacity-30 bg-button cursor-pointer active:bg-accent hover:bg"
    :tabindex="0"
    @click="clicked"
    @keypress.enter="clicked"
    @keypress.space="clicked"
  >
    <BasicIcon v-if="iconAlignment === 'left' && icon" :icon="icon" />
    <div v-if="text">
      {{ props.text }}
    </div>
    <BasicIcon v-if="iconAlignment === 'right' && icon" :icon="icon" />
  </div>
</template>
