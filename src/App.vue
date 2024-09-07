<script setup lang="ts">
import { PhFactory } from "@phosphor-icons/vue";
import { ref } from "vue";
import BasicTextInput from "./components/Basic/BasicTextInput.vue";
import Greet from "./components/Greet.vue";
import BasicButton from "./components/Basic/BasicButton.vue";
import { dialog } from '@tauri-apps/api';
import BasicText from "./components/Basic/BasicText.vue";

const selectedFolder = ref<string | null>(null);

const chooseFolder = async () => {
  selectedFolder.value = await dialog.open({
    directory: true, // Set to true to open folder chooser
    multiple: false, // Choose whether to allow selecting multiple folders
  }) as string | null;
};
</script>

<template>
  <div class="flex flex-col p-1">
    <BasicButton text="Choose Mod Folder" />
    <BasicText text="Chosen Folder: " />
  </div>
</template>