#ifndef Mono_LED_Matrix_H
#define Mono_LED_Matrix_H

#include <stdlib.h>

#include "Arduino.h"
#include "SPIHandler.h"

typedef uint8_t (*animation_t)[8];

class Mono_LED_Matrix
{
  public:
    enum class Opcode : uint8_t {
      NOOP = 0x00,
      DIGIT0 = 0x01,
      DIGIT1 = 0x02,
      DIGIT2 = 0x03,
      DIGIT3 = 0x04,
      DIGIT4 = 0x05,
      DIGIT5 = 0x06,
      DIGIT6 = 0x07,
      DIGIT7 = 0x08,
      DECODE_MODE = 0x09,
      INTENSITY = 0x0A,
      SCAN_LIMIT = 0x0B,
      SHUTDOWN = 0x0C,
      DISPLAY_TEST = 0x0F
    };

    Mono_LED_Matrix(
      SPIHandler *spi,
      int matrixCount=1,
      int rotation=0,
      int intensity=8);
    ~Mono_LED_Matrix(void);
    void Init(void);
    void SetRotation(int rotation);
    void SetIntensity(uint8_t intensity);

    void ClearDisplay(int matrixN);
    void Update(void);

    void SetPixel(int matrixN, int x, int y, int val);
    void SetBitmap(int matrixN, uint8_t *bmp);
    void SetChar(int matrixN, char c);
    void Invert(int matrixN);

    // animation: 2-dim array
    void SetAnimation(int matrixN, uint8_t (*animation)[8], size_t size);

    // animation: flattened 1-dim array
    // returns number of frames
    size_t SetAnimation(int matrixN, uint8_t *animation, size_t size);

    void PlayAnimation(int matrixN);
    void StopAnimation(int matrixN);

    size_t StartMarquee(char *text, int direction=1);
    void StopMarquee(void);

    byte getId();

  private:
    SPIHandler *spi;
    int cs;
    int matrixCount;
    int rotation;
    int intensity;
    uint8_t *buffer;
    byte id;

    uint8_t ***animations;
    size_t *animationSizes;
    int *animationFrames;
    bool *animationStates;

    bool marqueeState;
    char *marqueeText;
    int marqueePosition;
    int marqueeDirection;

    void SendCmd(Opcode opcode, uint8_t data);
    void SendCmd(uint8_t opcode, uint8_t data);
    void ShutDown(void);
    void WakeUp(void);
    static uint8_t reverseBitOrder(uint8_t b);
    static void CombineBitmaps(
      uint8_t *dst, uint8_t pos, uint8_t *src1, uint8_t *src2);
};

#endif
