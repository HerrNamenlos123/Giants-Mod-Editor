<script setup lang="ts">
const value = defineModel<string>({ default: "" });
const props = defineProps<{
    placeholder: string;
}>();
</script>

<template>
    <div class="p-1 bg-red-500">
        <input type="text" class="" v-model="value" :placeholder="placeholder">
    </div>
    <div class="bg-green-500 w-16 h-16 border"/>
</template>