<script setup lang="ts">
import { useStore } from "@/store";
import BasicText from "./Basic/BasicText.vue";
import { computed, onUpdated, ref } from "vue";
import BasicTextInput from "./Basic/BasicTextInput.vue";
import BasicDropdown from "./Basic/BasicDropdown.vue";
import BasicCheckbox from "./Basic/BasicCheckbox.vue";

const store = useStore();
const props = defineProps<{
  property: string;
  attribute: string;
  title: string;
  multiline?: boolean;
  options?: string[];
  boolean?: boolean;
}>();

const proxy = computed({
  get() {
    const attribute = store.docs?.modDesc.getPropertyAttribute(
      props.property,
      props.attribute,
    );
    return attribute || "";
  },
  set(value: string) {
    store.docs?.modDesc.setPropertyAttribute(
      props.property,
      props.attribute,
      value,
    );
  },
});

const s = ref(false);
const booleanProxy = computed({
  get() {
    const attribute = store.docs?.modDesc.getPropertyAttribute(
      props.property,
      props.attribute,
    );
    s.value = attribute === "true";
    return s.value;
  },
  set(value: boolean) {
    s.value = value;
    store.docs?.modDesc.setPropertyAttribute(
      props.property,
      props.attribute,
      s.value.valueOf().toString(),
    );
  },
});
</script>

<template>
  <div class="m-1 flex pl-2 items-center">
    <BasicText class="mr-2 w-48" :text="props.title + ':'" />
    <BasicDropdown
      v-if="options !== undefined"
      v-model="proxy"
      :options="options"
    />
    <BasicCheckbox v-else-if="boolean" v-model="booleanProxy" />
    <BasicTextInput v-else v-model="proxy" :multiline="multiline" />
  </div>
</template>
