<script setup lang="ts">
import BasicButton from "./components/Basic/BasicButton.vue";
import ModEditor from "./ModEditor.vue";
import { useStore } from "./store";
const store = useStore();
</script>

<template>
  <div class="flex flex-col bg-background h-screen w-screen text-text">
    <BasicButton text="Choose Mod Folder" @clicked="store.chooseModFolder()" />
    <ModEditor v-if="store.modFolder !== null" />
  </div>
</template>
