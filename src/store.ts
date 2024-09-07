import { useLocalStorage } from "@vueuse/core";
import { defineStore } from "pinia";
import { dialog } from "@tauri-apps/api";
import { invoke } from "@tauri-apps/api/tauri";
import { XmlDoc } from "./utils";

export const useStore = defineStore("store", {
  state: () => ({
    modFolder: useLocalStorage("modFolder", null as string | null),
    docs: null as null | {
      modDesc: XmlDoc;
      storeItem: XmlDoc;
    },
  }),
  actions: {
    async loadDocs() {
      if (!this.modFolder) {
        return;
      }
      const modDescDocument = new DOMParser().parseFromString(await loadFile(this.getModDescPath()), "text/xml");
      this.docs = {
        modDesc: new XmlDoc(modDescDocument),
        storeItem: new XmlDoc(),
      };
      const storeItemPath = this.getStoreItemPath();
      if (storeItemPath) {
        this.docs.storeItem = new XmlDoc(new DOMParser().parseFromString(await loadFile(storeItemPath), "text/xml"));
      }
    },
    async saveDocs() {
      if (!this.modFolder) {
        return;
      }
      if (!this.docs) {
        return;
      }
      if (this.docs.modDesc.document) {
        await saveFile(this.getModDescPath(), new XMLSerializer().serializeToString(this.docs.modDesc.document));
      }
      if (this.docs.storeItem.document) {
        await saveFile(this.getStoreItemPath()!, new XMLSerializer().serializeToString(this.docs.storeItem.document));
      }
      await this.loadDocs();
    },
    async chooseModFolder() {
      this.modFolder = (await dialog.open({
        directory: true, // Set to true to open folder chooser
        multiple: false, // Choose whether to allow selecting multiple folders
      })) as string | null;
    },
    getModDescPath() {
      return this.modFolder + "/modDesc.xml";
    },
    getStoreItemPath() {
      const filename = this.docs?.modDesc.getPropertyAttribute("modDesc/storeItems/storeItem", "xmlFilename");
      if (filename) {
        return this.modFolder + "/" + filename;
      }
    },
  },
});

export const loadFile = async (path: string) => {
  const content = await invoke("load_file", { path });
  return content as string;
};

export const saveFile = async (path: string, content: string) => {
  await invoke("save_file", { path, content });
};
