#include "Mono_LED_Matrix.h"

Mono_LED_Matrix::Mono_LED_Matrix(
  SPIHandler *spi,
  int matrixCount,
  int rotation,
  int intensity) :
  spi(spi),
  matrixCount(matrixCount),
  rotation(rotation),
  intensity(intensity)
{
  buffer = (uint8_t *) calloc(8 * matrixCount, sizeof(uint8_t));

  animations = (animation_t *) calloc(matrixCount, sizeof(animation_t));
  animationFrames = (int *) calloc(matrixCount, sizeof(int));
  animationSizes = (size_t *) calloc(matrixCount, sizeof(size_t));
  animationStates = (bool *) calloc(matrixCount, sizeof(bool));
  
}

byte Mono_LED_Matrix::getId(){
  return(id);
}
void Mono_LED_Matrix::SendCmd(uint8_t opcode, uint8_t data)
{
  byte msg[] = {1,opcode,data};
  spi->SPITransfer(msg);
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
  
  if (val)
    buffer[offset+y] |= 1 << x_;
  else
    buffer[offset+y] &= ~(1 << x_);
}

void Mono_LED_Matrix::SetBitmap(int matrixN, uint8_t bmp[8])
{
  int offset = matrixN * 8;

  for (int i = 0; i < 8; i++)
    buffer[offset+i] = bmp[i];
}

void Mono_LED_Matrix::Invert(int matrixN)
{
  int offset = matrixN * 8;

  for (int i = 0; i < 8; i++)
    buffer[offset+i] = ~buffer[offset+i];
}

void Mono_LED_Matrix::SetAnimation(int matrixN, uint8_t (*animation)[8], size_t size)
{
  animations[matrixN] = animation;
  animationSizes[matrixN] = size;
  animationFrames[matrixN] = 0;
  animationStates[matrixN] = false;
}

void Mono_LED_Matrix::PlayAnimation(int matrixN)
{
  animationStates[matrixN] = true;
}

void Mono_LED_Matrix::StopAnimation(int matrixN)
{
  animationStates[matrixN] = false;
}
