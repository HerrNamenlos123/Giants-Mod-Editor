<script setup lang="ts">
import { onMounted } from "vue";
import BasicButton from "./components/Basic/BasicButton.vue";
import BasicText from "./components/Basic/BasicText.vue";
import TranslatedProperty from "./components/TranslatedProperty.vue";
import { useStore } from "./store";
import SimpleProperty from "./components/SimpleProperty.vue";
import SimpleAttribute from "./components/SimpleAttribute.vue";
import BasicTabSwitcher from "./components/Basic/BasicTabSwitcher.vue";

const store = useStore();

const tabs = ["General", "Data"];

onMounted(async () => {
  await store.loadDocs();
});
</script>

<template>
  <div class="flex flex-col h-full">
    <BasicText :text="'Chosen Folder: ' + store.modFolder" />
    <div class="flex h-full">
      <div class="flex-grow">
        <BasicTabSwitcher class="h-full" :options="tabs">
          <template #General>
            <SimpleProperty property="modDesc/author" title="Author" />
            <SimpleProperty property="modDesc/version" title="Version" />
            <TranslatedProperty property="modDesc/title" title="Title" />
            <TranslatedProperty
              property="modDesc/description"
              title="Description"
              multiline
            />
            <SimpleProperty
              property="modDesc/iconFilename"
              title="Icon Filename (.dds)"
            />
            <BasicText class="font-bold" text="Properties" />
            <SimpleAttribute
              attribute="supported"
              property="modDesc/multiplayer"
              title="Multiplayer supported"
              boolean
            />
            <SimpleAttribute
              attribute="descVersion"
              property="modDesc"
              title="Desc Version"
            />
            <SimpleAttribute
              attribute="xmlFilename"
              property="modDesc/storeItems/storeItem"
              title="Store Item"
            />
          </template>
          <template #Data>
            <SimpleProperty
              property="vehicle/annotation"
              title="Vehicle Annotation"
            />
          </template>
        </BasicTabSwitcher>
      </div>
      <div class="flex flex-col justify-end h-fit">
        <BasicButton text="Load from Disk" @clicked="store.loadDocs()" />
        <BasicButton text="Write to Disk" @clicked="store.saveDocs()" />
      </div>
    </div>
  </div>
</template>
