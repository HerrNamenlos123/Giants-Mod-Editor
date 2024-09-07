<script setup lang="ts">
import BasicIcon from './BasicIcon.vue';

const props = withDefaults(defineProps<{
    text: string
    icon?: string;
    iconAlignment?: 'left' | 'right';
}>(), {
    iconAlignment: 'left'
});

const emit = defineEmits<{
    clicked: [];
}>();

const clicked = () => {
    emit('clicked');
}
</script>

<template>
    <div class="flex items-center border rounded-sm px-1 m-1 py-0 border-gray-400" 
    @click="clicked">
        <BasicIcon :icon="icon" v-if="iconAlignment === 'left' && icon"/>
        <div class="">{{ props.text }}</div>
        <BasicIcon :icon="icon" v-if="iconAlignment === 'right' && icon"/>
    </div>
</template>