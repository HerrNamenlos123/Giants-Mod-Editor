<script setup lang="ts">
import BasicText from "./Basic/BasicText.vue";
import TextInputXMLTag from "./TextInputXMLTag.vue";

const props = defineProps<{
  property: string;
  title: string;
  multiline?: boolean;
}>();
</script>

<template>
  <div class="m-1 flex flex-col mb-4">
    <BasicText class="font-bold" :text="props.title" />
    <div class="flex pl-2 items-center h-fit">
      <TextInputXMLTag :multiline="multiline" :property="props.property" />
    </div>
  </div>
</template>
