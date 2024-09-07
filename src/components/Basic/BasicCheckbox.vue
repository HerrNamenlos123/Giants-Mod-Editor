<script setup lang="ts">
import { PhCheck } from "@phosphor-icons/vue";

const isChecked = defineModel<boolean>({ default: false });
const props = defineProps<{
  text?: string;
}>();

const emit = defineEmits<{
  input: [boolean];
}>();

const toggle = () => {
  isChecked.value = !isChecked.value;
  emit("input", isChecked.value);
};
</script>

<template>
  <div id="preventParentFromAlteringPaddingInOutline">
    <div
      class="flex items-center select-none cursor-pointer"
      tabindex="0"
      @click.stop.prevent="toggle"
      @keypress.enter="toggle"
      @keypress.space="toggle"
    >
      <div
        class="flex items-center justify-center h-[1em] border rounded-sm aspect-square cursor-pointer overflow-hidden"
        :class="{ 'bg-primary border-white': isChecked }"
      >
        <div
          v-if="isChecked"
          class="text-white flex items-center justify-center"
        >
          <PhCheck size="100%" weight="bold" />
        </div>
      </div>
      <div v-if="text" class="ml-1">
        {{ text }}
      </div>
    </div>
  </div>
</template>
