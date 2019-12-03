#include "Mono_LED_Matrix.h"
#include "Mono_LED_Matrix_font.h"

Mono_LED_Matrix::Mono_LED_Matrix(
  SPIHandler *spi,
  int matrixCount,
  int rotation,
  int intensity) :
  spi(spi),
  matrixCount(matrixCount),
  rotation(rotation),
  intensity(intensity),
  marqueeState(false),
  marqueeText(""),
  marqueePosition(0),
  marqueeDirection(1)
{
  buffer = (uint8_t *) calloc(8 * matrixCount, sizeof(uint8_t));

  animations = (uint8_t ***) calloc(matrixCount, sizeof(uint8_t **));
  animationFrames = (int *) calloc(matrixCount, sizeof(int));
  animationSizes = (size_t *) calloc(matrixCount, sizeof(size_t));
  animationStates = (bool *) calloc(matrixCount, sizeof(bool));

  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);
}

Mono_LED_Matrix::~Mono_LED_Matrix(void)
{
  for (int matrixN = 0; matrixN < matrixCount; matrixN++)
  {
    if (animations[matrixN] != nullptr)
    {
      for (size_t i = 0; i < animationSizes[matrixN]; i++)
      {
        free(animations[matrixN][i]);
        animations[matrixN][i] = nullptr;
      }
      free(animations[matrixN]);
      animations[matrixN] = nullptr;
    }
  }
  animations = nullptr;

  free(animationFrames);
  animationFrames = nullptr;

  free(animationSizes);
  animationSizes = nullptr;

  free(animationStates);
  animationStates = nullptr;
}

byte Mono_LED_Matrix::getId()
{
  return id;
}

void Mono_LED_Matrix::SendCmd(uint8_t opcode, uint8_t data)
{
  byte msg[] = { 1, opcode, data };

  if(spi != nullptr)
  {
    spi->SPITransfer(msg);
  }
}

void Mono_LED_Matrix::SendCmd(Opcode opcode, uint8_t data)
{
  SendCmd((uint8_t) opcode, data);
}

void Mono_LED_Matrix::Init(void)
{
  SendCmd(Opcode::DISPLAY_TEST, 0);
  SendCmd(Opcode::SCAN_LIMIT, 7);
  SendCmd(Opcode::DECODE_MODE, 0);
  ShutDown();
}

void Mono_LED_Matrix::ShutDown(void)
{
  SendCmd(Opcode::SHUTDOWN, 0);
}

void Mono_LED_Matrix::WakeUp(void)
{
  SendCmd(Opcode::SHUTDOWN, 1);
}

void Mono_LED_Matrix::SetIntensity(uint8_t intensity)
{
  SendCmd(Opcode::INTENSITY, intensity);
}

void Mono_LED_Matrix::Update(void)
{
  WakeUp();

  if (marqueeState)
  {
    // TODO:
    // Only matrix #0 for now
    int c_pos = (marqueePosition/7);

    uint8_t bmp[8];
    uint8_t *src1 = Mono_LED_Matrix_font[marqueeText[c_pos] - ' '];
    uint8_t *src2;
    if (c_pos >= strlen(marqueeText) - 1)
      src2 = Mono_LED_Matrix_font[marqueeText[0] - ' '];
    else
      src2 = Mono_LED_Matrix_font[marqueeText[c_pos + 1] - ' '];
    Mono_LED_Matrix::CombineBitmaps(bmp, marqueePosition%7, src1, src2);

    SetBitmap(0, bmp);

    if (marqueeDirection > 0)
    {
      if (marqueePosition >= strlen(marqueeText) * 7 - 1)
        marqueePosition = 0;
      else
        marqueePosition++;
    }
    else if (marqueeDirection < 0)
    {
      if (marqueePosition < 0)
        marqueePosition = strlen(marqueeText) * 7 - 1;
      else
        marqueePosition--;
    }
  }
  else
  {
    for (int i = 0; i < matrixCount; i++)
    {
      if (animationStates[i] == true && animations[i] != nullptr)
      {
        SetBitmap(i, animations[i][animationFrames[i]]);
        animationFrames[i]++;
        if (animationFrames[i] >= animationSizes[i])
          animationFrames[i] = 0;
      }
    }
  }

  for (int i = 0; i < matrixCount * 8; i+=8)
  {
    for (int j = 0; j < 8; j++)
      SendCmd(j+1, buffer[i+j]);
  }
}

void Mono_LED_Matrix::ClearDisplay(int matrixN)
{
  int offset = matrixN * 8;
  for (int i = 0; i < 8; i++)
    buffer[offset+i] = 0;
}

void Mono_LED_Matrix::SetPixel(int matrixN, int x, int y, int val)
{
  int offset = matrixN * 8;
  int x_ = 7 - x;
  int y_ = 7 - y;
  
  if (rotation == 0)
  {
    if (val)
      buffer[offset+y] |= 1 << x_;
    else
      buffer[offset+y] &= ~(1 << x_);
  }
  else if (rotation == 1)
  {
    if (val)
      buffer[offset+x_] |= 1 << y_;
    else
      buffer[offset+x_] &= ~(1 << y_);
  }
  else if (rotation == 2)
  {
    if (val)
      buffer[offset+y_] |= 1 << x;
    else
      buffer[offset+y_] &= ~(1 << x);
  }
  else
  {
    if (val)
      buffer[offset+x] |= 1 << y;
    else
      buffer[offset+x] &= ~(1 << y);
  }
}

void Mono_LED_Matrix::SetBitmap(int matrixN, uint8_t *bmp)
{
  if (bmp == nullptr)
  {
    #ifdef DEBUG_MODE
      Serial.println("Mono_LED_Matrix::SetBitmap: bmp is null");
      this->StartMarquee("NULL");
    #endif

    return;
  }

  int offset = matrixN * 8;

  if (rotation == 0)
  {
    for (int i = 0; i < 8; i++)
      buffer[offset+i] = bmp[i];
  }
  // Possible area to refactor until the end of this method
  else if (rotation == 1)
  {
    for (int i = 0; i < 8; i++)
    {
      uint8_t b = 0;
      for (int j = 0; j < 8; j++)
        b |= ((uint8_t) !!(bmp[j] & (1 << i))) << j;
      buffer[offset + i] = Mono_LED_Matrix::reverseBitOrder(b);
    }
  }
  else if (rotation == 2)
  {
    for (int i = 0; i < 8; i++)
      buffer[offset + i] = Mono_LED_Matrix::reverseBitOrder(bmp[7-i]);
  }
  else
  {
    for (int i = 0; i < 8; i++)
    {
      uint8_t b = 0;
      for (int j = 0; j < 8; j++)
        b |= ((uint8_t) !!(bmp[j] & (1 << i))) << j;
      buffer[offset + 7 - i] = b;
    }
  }
}

void Mono_LED_Matrix::Invert(int matrixN)
{
  int offset = matrixN * 8;

  for (int i = 0; i < 8; i++)
    buffer[offset+i] = ~buffer[offset+i];
}

void Mono_LED_Matrix::SetAnimation(int matrixN, uint8_t (*animation)[8], size_t size)
{
  if (animation == nullptr)
  {
    #ifdef DEBUG_MODE
      Serial.println("Mono_LED_Matrix::SetAnimation: animation is null");
      this->StartMarquee("NULL");
    #endif

    return;
  }

  // Free an existing animation if any
  if (animations[matrixN] != nullptr)
  {
    for (size_t i = 0; i < animationSizes[matrixN]; i++)
    {
      // Free frame #i
      free(animations[matrixN][i]);
    }

    free(animations[matrixN]);
  }

  animations[matrixN] = (uint8_t **) calloc(size, sizeof(uint8_t *));

  for (size_t frame_idx = 0; frame_idx < size; frame_idx++)
  {
    animations[matrixN][frame_idx] = (uint8_t *) calloc(8, sizeof(uint8_t));
    for (int i = 0; i < 8; i++)
    {
      animations[matrixN][frame_idx][i] = animation[frame_idx][i];
    }
  }

  animationSizes[matrixN] = size;
  animationFrames[matrixN] = 0;
  animationStates[matrixN] = false;
}

size_t Mono_LED_Matrix::SetAnimation(int matrixN, uint8_t *animation, size_t size)
{
  if (animation == nullptr || size == 0)
  {
    #ifdef DEBUG_MODE
      Serial.println("Mono_LED_Matrix::SetAnimation: animation is null");
      this->StartMarquee("NULL");
    #endif

    return 0;
  }

  size_t frameCount = size / 8;
  if (frameCount == 0)
  {
    #ifdef DEBUG_MODE
      Serial.println(
        "Mono_LED_Matrix::SetAnimation: event though animation is not null, "
        "the animation frame count is less than 0"
      );
    #endif

    return 0;
  }

  // Free an existing animation if any
  if (animations[matrixN] != nullptr)
  {
    for (size_t i = 0; i < animationSizes[matrixN]; i++)
    {
      // Free frame #i
      free(animations[matrixN][i]);
    }

    free(animations[matrixN]);
  }

  animations[matrixN] = (uint8_t **) calloc(frameCount, sizeof(uint8_t *));

  // Copy the animation to 2-dim array frame by frame, line by line
  for (size_t frame_idx = 0; frame_idx < frameCount; frame_idx++)
  {
    animations[matrixN][frame_idx] = (uint8_t *) calloc(8, sizeof(uint8_t));

    for (int i = 0; i < 8; i++)
    {
      animations[matrixN][frame_idx][i] = animation[frame_idx*8 + i];
    }
  }

  animationSizes[matrixN] = frameCount;
  animationFrames[matrixN] = 0;
  animationStates[matrixN] = false;

  return frameCount;
}

void Mono_LED_Matrix::PlayAnimation(int matrixN)
{
  animationStates[matrixN] = true;
}

void Mono_LED_Matrix::StopAnimation(int matrixN)
{
  animationStates[matrixN] = false;
}

void Mono_LED_Matrix::SetRotation(int rotation)
{
  this->rotation = rotation;
}

uint8_t Mono_LED_Matrix::reverseBitOrder(uint8_t b)
{
  uint8_t o = b;
  o = (o & 0xf0) >> 4 | (o & 0x0f) << 4;
  o = (o & 0xcc) >> 2 | (o & 0x33) << 2;
  o = (o & 0xaa) >> 1 | (o & 0x55) << 1;
  return o;
}

size_t Mono_LED_Matrix::StartMarquee(char *text, int direction)
{
  if (strcmp("", text) == 0)
    return 0;

  marqueeText = text;
  marqueePosition = 0;
  marqueeState = true;
  marqueeDirection = direction;

  return strlen(text) * 7;
}

void Mono_LED_Matrix::StopMarquee(void)
{
  marqueeState = false;
}

void Mono_LED_Matrix::CombineBitmaps(
  uint8_t *dst, uint8_t pos, uint8_t *src1, uint8_t *src2)
{
  for (int i = 0; i < 8; i++)
  {
    dst[i] = 0;
    dst[i] |= src1[i] << pos;
    dst[i] |= src2[i] >> (7-pos);
  }
}

void Mono_LED_Matrix::SetChar(int matrixN, char c)
{
  SetBitmap(matrixN, Mono_LED_Matrix_font[c - ' ']);
}
