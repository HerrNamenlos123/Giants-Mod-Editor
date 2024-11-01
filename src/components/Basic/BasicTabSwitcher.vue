<script setup lang="ts">
import { watch } from "vue";

const selectedItem = defineModel<string>({
  default: undefined,
});

const props = withDefaults(
  defineProps<{
    options: string[];
    fillHorizontalSpace?: boolean;
  }>(),
  {
    fillHorizontalSpace: false,
  },
);

watch(
  selectedItem,
  () => {
    if (!selectedItem.value) {
      selectedItem.value = props.options[0];
    }
  },
  { immediate: true },
);

const emit = defineEmits<{
  selected: [value: string];
}>();

const select = (option: string) => {
  emit("selected", option);
  selectedItem.value = option;
};
</script>

<template>
  <div class="w-full flex flex-col overflow-hidden">
    <div class="w-full flex select-none border-b border-gray-300">
      <div
        v-for="(tabItem, index) in options"
        :key="index"
        class="px-5 border-r border-t border-gray-300 cursor-pointer"
        :class="{
          'border-b-accent border-b-2 font-bold': selectedItem === tabItem,
          'border-l': index === 0,
          'w-full': fillHorizontalSpace,
        }"
        @click="select(tabItem)"
      >
        <div class="h-full flex justify-center items-center pb-2 pt-3 px-10">
          <span>{{ tabItem }}</span>
        </div>
      </div>
    </div>
    <div class="relative w-full h-full flex flex-col pt-1 overflow-auto">
      <div class="absolute w-full h-full p-1 flex flex-col">
        <slot :name="selectedItem" />
        <div class="p-1" />
      </div>
    </div>
  </div>
</template>
