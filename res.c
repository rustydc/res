#include <ApplicationServices/ApplicationServices.h>

int main(int argc, char **argv) {
  CGDirectDisplayID mainDisplay = CGMainDisplayID();
  CFArrayRef array = CGDisplayCopyAllDisplayModes(mainDisplay, NULL);
  if (argc == 1) {
    // List the available modes.
    CGSize curSize = CGDisplayBounds(kCGDirectMainDisplay).size;
    size_t curX = curSize.width;
    size_t curY = curSize.height;
    bool foundCurrent = false;
    for (int i = 0; i < CFArrayGetCount(array); i++) {
      CGDisplayModeRef modeRef = (CGDisplayModeRef) CFArrayGetValueAtIndex(array, i);
      size_t modeX = CGDisplayModeGetWidth(modeRef);
      size_t modeY = CGDisplayModeGetHeight(modeRef);
      char isActive = (curX == modeX && curY == modeY) ? '*' : ' ';
      if (isActive) {
        foundCurrent = true;
      }
      printf("%c%2d: %4zu x %4zu\n", isActive, i, modeX, modeY);
    }

    // List the current mode, if not already displayed.
    if (!foundCurrent) {
      fprintf(stderr, "Current: %zu, %zu\n", curX, curY);
    }
    return 0;
  } else if (argc == 2) {
    // Set the mode to one of the above.
    int modeNumber = strtol(argv[1], NULL, 10 /* base */);
    if (errno != EINVAL && modeNumber >= 0 && modeNumber < CFArrayGetCount(array)) {
      CGDisplayModeRef modeRef = (CGDisplayModeRef) CFArrayGetValueAtIndex(array, modeNumber);
      CGDisplayConfigRef displayConfig;
      CGBeginDisplayConfiguration(&displayConfig);
      CGConfigureDisplayWithDisplayMode(displayConfig, mainDisplay, modeRef, NULL);
      CGCompleteDisplayConfiguration(displayConfig, kCGConfigurePermanently);
      return 0;
    }
    fprintf(stderr, "Invalid mode '%s'.\n", argv[1]);
  }
  fprintf(stderr, "Usage: %s [MODE_NUMBER]\n", argv[0]);
  return -1;
}
