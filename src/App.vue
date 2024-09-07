<script setup lang="ts">
import { PhFactory } from "@phosphor-icons/vue";
import Greet from "./components/Greet.vue";
import BasicTextInput from "./components/Basic/BasicTextInput.vue";
import { ref } from "vue";

const s = ref("hello");
</script>

<template>
  <div class="container">
    <h1>Welcome to Tauri!</h1>

    <div class="row">
      <a href="https://vitejs.dev" target="_blank">
        <img src="/vite.svg" class="logo vite" alt="Vite logo" />
      </a>
      <a href="https://tauri.app" target="_blank">
        <img src="/tauri.svg" class="logo tauri" alt="Tauri logo" />
      </a>
      <a href="https://vuejs.org/" target="_blank">
        <img src="./assets/vue.svg" class="logo vue" alt="Vue logo" />
      </a>
    </div>

    <p>Click on the Tauri, Vite, and Vue logos to learn more.</p>
    <PhFactory />

    <BasicTextInput placeholder="Enter a name..." v-model="s"/>
    <BasicTextInput placeholder="Enter a name..." v-model="s"/>

    <Greet />
  </div>
</template>