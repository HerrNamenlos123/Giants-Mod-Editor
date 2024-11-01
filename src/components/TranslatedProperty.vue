<script setup lang="ts">
import { computed, onUnmounted, ref, watch } from "vue";
import BasicText from "./Basic/BasicText.vue";
import BasicTextInput from "./Basic/BasicTextInput.vue";
import { useStore } from "@/store";
import TextInputXMLTag from "./TextInputXMLTag.vue";
import BasicButton from "./Basic/BasicButton.vue";
import SectionHeader from "./SectionHeader.vue";

const store = useStore();

const props = defineProps<{
  property: string;
  title: string;
  multiline?: boolean;
}>();

const doc = computed(() => store.docs?.modDesc);

const languages = ref([] as string[]);
watch(
  [() => doc.value],
  () => {
    if (doc.value) {
      languages.value =
        doc.value.getPropertyChildren(props.property.split("@")[1]) ?? [];
    }
  },
  { immediate: true, deep: true },
);

const isNewLanguagePopupOpen = ref(false);
const newLanguage = ref("");
const handleClickOutside = (event: MouseEvent) => {
  if (event.target?.closest(".relative") === null) {
    closePopup();
  }
};
const openPopup = () => {
  isNewLanguagePopupOpen.value = true;
  newLanguage.value = "";
  document.removeEventListener("click", handleClickOutside);
  document.addEventListener("click", handleClickOutside);
};

const closePopup = () => {
  isNewLanguagePopupOpen.value = false;
  document.removeEventListener("click", handleClickOutside);
};
const addLanguage = () => {
  if (newLanguage.value) {
    doc.value?.setProperty(props.property + "/" + newLanguage.value, "");
  }
  closePopup();
};

onUnmounted(() => {
  document.removeEventListener("click", handleClickOutside);
});
</script>

<template>
  <div class="m-1 flex flex-col mb-4">
    <SectionHeader :title="props.title" />
    <div v-for="l in languages" :key="l" class="flex flex-col">
      <div class="flex pl-2 items-center h-fit">
        <BasicButton
          class="h-full py-1"
          icon="PhTrash"
          @clicked="doc?.removeProperty(props.property, l)"
        />
        <BasicText class="w-12" :text="l + ':'" />
        <TextInputXMLTag
          :multiline="multiline"
          :property="props.property + '/' + l"
        />
      </div>
    </div>
    <div class="relative flex flex-col">
      <BasicButton
        class="w-fit"
        icon="PhPlus"
        text="Add Language"
        @clicked="openPopup"
      />
      <div
        v-if="isNewLanguagePopupOpen"
        class="absolute top-full left-0 w-48 bg-white border shadow-xl border-gray-400 flex flex-col p-1"
      >
        <BasicTextInput v-model="newLanguage" class="m-1" />
        <div class="flex">
          <BasicButton text="Cancel" @clicked="closePopup" />
          <div class="w-full" />
          <BasicButton text="Add" @clicked="addLanguage" />
        </div>
      </div>
    </div>
  </div>
</template>
