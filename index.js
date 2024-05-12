import addon from "./addon.cjs";

async function osDelay(cb) {
  await new Promise((resolve) => setTimeout(resolve, 20));
  cb();
}

const mouse = {
  click(mouseButton) {
    return osDelay(() => addon.mouseClick(mouseButton));
  },
  press(mouseButton) {
    return osDelay(() => addon.mousePress(mouseButton));
  },
  release(mouseButton) {
    return osDelay(() => addon.mouseRelease(mouseButton));
  },
  setPosition(x, y) {
    addon.setMousePosition(x, y);
  },
  getPosition() {
    return addon.getMousePosition();
  },
  clickOnPosition(x, y, mouseButton) {
    this.setPosition(x, y);
    this.click(mouseButton);
  },
};

export default mouse;
