import addon from "./addon.cjs";

async function osDelay(cb) {
  await new Promise((resolve) => setTimeout(resolve, 20));
  cb();
}

const mouse = {
  click() {
    return osDelay(addon.mouseClick);
  },
  press() {
    return osDelay(addon.mousePress);
  },
  release() {
    return osDelay(addon.mouseRelease);
  },
  click() {
    return osDelay(addon.mouseClick);
  },
  setPosition(x, y) {
    addon.setMousePosition(x, y);
  },
  getPosition() {
    return addon.getMousePosition();
  },
  clickOnPosition(x, y) {
    this.setPosition(x, y);
    this.click();
  },
};

export default mouse;
