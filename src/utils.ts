export class XmlDoc {
  document?: Document;
  proxies: Map<string, this> = new Map();
  setUpdateCounter: number = 0;

  constructor(document?: Document) {
    this.document = document;
  }

  getProperty(path: string): string | undefined {
    return this.document?.evaluate(path, this.document, null, XPathResult.STRING_TYPE).stringValue;
  }

  createNode(path: string) {
    if (!this.document) {
      return;
    }
    const parts = path.split("/");
    let node = this.document as Document | Element;
    for (const part of parts) {
      const tags = node.getElementsByTagName(part);
      if (tags.length === 0) {
        node.appendChild(this.document.createElement(part));
      }
      node = tags[0];
    }
  }

  setProperty(path: string, value: string) {
    if (!this.document) {
      return;
    }
    const node = this.document.evaluate(path, this.document, null, XPathResult.FIRST_ORDERED_NODE_TYPE).singleNodeValue;
    if (node) {
      node.textContent = value;
      this.setUpdateCounter++;
    } else {
      this.createNode(path);
      this.setProperty(path, value);
    }
  }

  getPropertyAttribute(path: string, name: string) {
    if (!this.document) {
      return;
    }
    const node = this.document.evaluate(path, this.document, null, XPathResult.FIRST_ORDERED_NODE_TYPE).singleNodeValue;
    if (node) {
      return (node as Element).getAttribute(name) || undefined;
    }
  }

  setPropertyAttribute(path: string, name: string, value: string) {
    if (!this.document) {
      return;
    }
    const node = this.document.evaluate(path, this.document, null, XPathResult.FIRST_ORDERED_NODE_TYPE).singleNodeValue;
    if (node) {
      (node as Element).setAttribute(name, value);
      this.setUpdateCounter++;
    } else {
      this.createNode(path);
      this.setPropertyAttribute(path, name, value);
    }
  }

  getPropertyChildren(path: string) {
    if (!this.document) {
      return;
    }
    const node = this.document.evaluate(path, this.document, null, XPathResult.FIRST_ORDERED_NODE_TYPE).singleNodeValue;
    if (node) {
      return Array.from((node as Element).children).map((child) => child.tagName);
    }
  }

  getPropertyProxy(path: string) {
    if (this.proxies.has(path)) {
      return this.proxies.get(path)!;
    }
    const proxy = new Proxy(this, {
      get(target, prop) {
        return target.getProperty(path);
      },
      set(target, prop, value) {
        target.setProperty(path, value);
        return true;
      },
    });
    this.proxies.set(path, proxy);
    return proxy;
  }

  removeProperty(path: string, child: string) {
    if (!this.document) {
      return;
    }
    const node = this.document.evaluate(path, this.document, null, XPathResult.FIRST_ORDERED_NODE_TYPE).singleNodeValue;
    if (node) {
      const childNodes = (node as Element).getElementsByTagName(child);
      // Convert HTMLCollection to an array to safely modify the DOM while iterating
      Array.from(childNodes).forEach((childNode) => {
        node.removeChild(childNode);
      });
      this.setUpdateCounter++;
    }
  }
}
