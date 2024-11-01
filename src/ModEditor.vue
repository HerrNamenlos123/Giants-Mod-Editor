<script setup lang="ts">
import { onMounted } from "vue";
import BasicButton from "./components/Basic/BasicButton.vue";
import BasicText from "./components/Basic/BasicText.vue";
import TranslatedProperty from "./components/TranslatedProperty.vue";
import { useStore } from "./store";
import SimpleProperty from "./components/SimpleProperty.vue";
import SimpleAttribute from "./components/SimpleAttribute.vue";
import BasicTabSwitcher from "./components/Basic/BasicTabSwitcher.vue";
import SectionHeader from "./components/SectionHeader.vue";
import SubSectionHeader from "./components/SubSectionHeader.vue";
import SoundModifiers from "./components/SoundModifiers.vue";

const store = useStore();

const tabs = ["General", "Data", "Sounds"];

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
            <SimpleProperty property="modDesc@modDesc/author" title="Author" />
            <SimpleProperty
              property="modDesc@modDesc/version"
              title="Version"
            />
            <TranslatedProperty
              property="modDesc@modDesc/title"
              title="Title"
            />
            <TranslatedProperty
              property="modDesc@modDesc/description"
              title="Description"
              multiline
            />
            <SimpleProperty
              property="modDesc@modDesc/iconFilename"
              title="Icon Filename (.dds)"
            />
            <SectionHeader title="Properties" />
            <SimpleAttribute
              attribute="supported"
              property="modDesc@modDesc/multiplayer"
              title="Multiplayer supported"
              boolean
            />
            <SimpleAttribute
              attribute="descVersion"
              property="modDesc@modDesc"
              title="Desc Version"
            />
            <SimpleAttribute
              attribute="xmlFilename"
              property="modDesc@modDesc/storeItems/storeItem"
              title="Store Item"
            />
          </template>
          <template #Data>
            <SimpleProperty
              property="storeItem@vehicle/annotation"
              title="Vehicle Annotation"
              multiline
            />
            <SectionHeader title="StoreData" />
            <SimpleProperty
              property="storeItem@vehicle/storeData/name"
              title="Name"
            />
            <SubSectionHeader title="Specs">
              <SimpleProperty
                property="storeItem@vehicle/storeData/specs/power"
                title="Power"
              />
              <SimpleProperty
                property="storeItem@vehicle/storeData/specs/maxSpeed"
                title="Max Speed"
              />
            </SubSectionHeader>
            <SubSectionHeader title="Functions">
              <SimpleProperty
                property="storeItem@vehicle/storeData/functions/function"
                title="Function"
              />
            </SubSectionHeader>
            <SimpleProperty
              property="storeItem@vehicle/storeData/image"
              title="Image"
            />
            <SimpleProperty
              property="storeItem@vehicle/storeData/price"
              title="Price"
            />
            <SimpleProperty
              property="storeItem@vehicle/storeData/lifetime"
              title="Lifetime"
            />
            <SimpleProperty
              property="storeItem@vehicle/storeData/rotation"
              title="Rotation"
            />
            <SimpleProperty
              property="storeItem@vehicle/storeData/brand"
              title="Brand"
            />
            <SimpleProperty
              property="storeItem@vehicle/storeData/category"
              title="Category"
            />
            <SubSectionHeader title="Base">
              <SimpleProperty
                property="storeItem@vehicle/base/filename"
                title="Base Filename"
              />
              <SimpleAttribute
                attribute="width"
                property="storeItem@vehicle/base/size"
                title="Base Size (Width)"
              />
              <SimpleAttribute
                attribute="length"
                property="storeItem@vehicle/base/size"
                title="Base Size (Length)"
              />
              <SimpleAttribute
                attribute="filename"
                property="storeItem@vehicle/base/sounds"
                title="Sounds Filename"
              />
            </SubSectionHeader>
          </template>
          <template #Sounds>
            <SectionHeader title="Motorized Sounds" />
            <SubSectionHeader title="Motor Start">
              <SimpleAttribute
                attribute="template"
                property="soundFile@sounds/motorized/sounds/motorStart"
                title="Template"
              />
              <SimpleAttribute
                attribute="file"
                property="soundFile@sounds/motorized/sounds/motorStart"
                title="Filename"
              />
              <SoundModifiers />
            </SubSectionHeader>
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
