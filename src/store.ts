import { set, useLocalStorage } from "@vueuse/core";
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
      soundFile: XmlDoc;
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
        soundFile: new XmlDoc(),
      };
      const storeItemPath = this.getStoreItemPath();
      if (storeItemPath) {
        this.docs.storeItem = new XmlDoc(new DOMParser().parseFromString(await loadFile(storeItemPath), "text/xml"));
      }
      const soundFilePath = this.getSoundFilePath();
      if (soundFilePath) {
        this.docs.soundFile = new XmlDoc(new DOMParser().parseFromString(await loadFile(soundFilePath), "text/xml"));
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
      if (this.docs.soundFile.document) {
        await saveFile(this.getSoundFilePath()!, new XMLSerializer().serializeToString(this.docs.soundFile.document));
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
    getSoundFilePath() {
      const filename = this.docs?.storeItem.getPropertyAttribute("vehicle/base/sounds", "filename");
      if (filename) {
        return this.modFolder + "/" + filename;
      }
    },
    getProperty(propertyPath: string) {
      const document = propertyPath.split("@")[0];
      const property = propertyPath.split("@")[1];
      if (!document || !property) {
        throw new Error("Invalid propertyPath: " + propertyPath);
      }
      switch (document) {
        case "modDesc":
          return this.docs?.modDesc.getProperty(property) || "";
        case "storeItem":
          return this.docs?.storeItem.getProperty(property) || "";
        case "soundFile":
          return this.docs?.soundFile.getProperty(property) || "";
        default:
          throw new Error("Unknown document type in propertyPath: " + document);
      }
    },
    setProperty(propertyPath: string, value: string) {
      const document = propertyPath.split("@")[0];
      const property = propertyPath.split("@")[1];
      if (!document || !property) {
        throw new Error("Invalid propertyPath: " + propertyPath);
      }
      switch (document) {
        case "modDesc":
          this.docs?.modDesc.setProperty(property, value);
          break;
        case "storeItem":
          this.docs?.storeItem.setProperty(property, value);
          break;
        case "soundFile":
          this.docs?.soundFile.setProperty(property, value);
          break;
        default:
          throw new Error("Unknown document type in propertyPath: " + document);
      }
    },
    getPropertyAttribute(propertyPath: string, name: string) {
      const document = propertyPath.split("@")[0];
      const property = propertyPath.split("@")[1];
      if (!document || !property) {
        throw new Error("Invalid propertyPath: " + propertyPath);
      }
      switch (document) {
        case "modDesc":
          return this.docs?.modDesc.getPropertyAttribute(property, name) || "";
        case "storeItem":
          return this.docs?.storeItem.getPropertyAttribute(property, name) || "";
        case "soundFile":
          return this.docs?.soundFile.getPropertyAttribute(property, name) || "";
        default:
          throw new Error("Unknown document type in propertyPath: " + document);
      }
    },
    setPropertyAttribute(propertyPath: string, name: string, value: string) {
      const document = propertyPath.split("@")[0];
      const property = propertyPath.split("@")[1];
      if (!document || !property) {
        throw new Error("Invalid propertyPath: " + propertyPath);
      }
      switch (document) {
        case "modDesc":
          this.docs?.modDesc.setPropertyAttribute(property, name, value);
          break;
        case "storeItem":
          this.docs?.storeItem.setPropertyAttribute(property, name, value);
          break;
        case "soundFile":
          this.docs?.soundFile.setPropertyAttribute(property, name, value);
          break;
        default:
          throw new Error("Unknown document type in propertyPath: " + document);
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
