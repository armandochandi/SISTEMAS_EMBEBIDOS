const int windowSize = 10;
int circularBuffer[windowSize];
int* circularBufferAccessor = circularBuffer;
 
float values[] = {  0.20, 2.10, 0.20, 0.80, 0.20, 0.20, 0.80, 0.80, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 2.10, 0.80, 0.20, 0.20, 1.50, 0.20, 1.50, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 2.10, 0.20, 0.80, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.80, 1.50, 0.80, 2.10, 0.20, 0.20, 1.50, 1.50, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 2.10, 0.80, 0.80, 0.20, 0.20, 0.20, 2.10, 0.80, 0.20, 0.20, 0.20, 2.10, 0.20, 0.20, 0.20, 0.20, 2.10, 0.80, 2.10, 2.10, 0.80, 0.20, 0.20, 0.80, 0.20, 2.10, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 1.50, 2.10, 0.20, 1.50, 0.20, 2.10, 2.10, 0.20, 2.10, 0.80, 0.20, 0.80, 0.20, 0.20, 0.20, 0.20, 0.80, 1.50, 0.80, 0.20, 0.20, 2.10, 2.10, 1.50, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 2.10, 1.50, 2.10, 0.20, 0.20, 0.20, 1.50, 0.80, 0.20, 0.20, 0.80, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 2.10, 0.20, 2.10, 2.10, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 0.20, 2.10, 2.10, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 0.20, 0.20, 2.10, 3.40, 2.10, 2.10, 2.10, 2.10, 2.10, 0.20, 2.10, 0.80, 0.20, 2.10, 0.20, 2.10, 0.20, 2.10, 0.20, 0.20, 0.20, 0.20, 2.10, 24.90, 0.20, 0.20, 2.10, 2.80, 0.20, 0.20, 2.10, 2.10, 2.10, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 0.80, 0.20, 2.10, 2.10, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 0.20, 0.20, 25.50, 2.10, 0.20, 2.10, 0.20, 2.10, 0.20, 0.20, 0.20, 2.10, 14.50, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 2.10, 2.10, 2.10, 2.10, 0.20, 0.20, 0.20, 8.60, 10.60, 0.20, 0.20, 2.10, 2.10, 0.20, 0.20, 2.10, 2.10, 2.10, 0.20, 2.10, 0.20, 2.10, 10.60, 0.20, 2.10, 2.10, 0.80, 18.40, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 0.20, 0.80, 2.10, 2.10, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 0.20, 2.10, 2.10, 0.20, 0.20, 0.20, 0.20, 2.10, 0.20, 0.20, 0.20, 0.20, 2.10, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 2.10, 2.10, 2.10, 2.10, 2.10, 0.20, 0.20, 3.40, 2.10, 0.20, 2.10, 0.80, 10.60, 0.80, 0.20, 2.10, 2.10, 2.10, 0.20, 0.20, 0.20, 2.10, 21.00, 0.20, 2.10, 2.10, 2.10, 2.10, 0.20, 0.20, 0.20, 0.20, 2.10, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 0.20, 2.10, 2.10, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 0.20, 2.10, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 0.20, 0.20, 2.10, 24.90, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 2.10, 0.20, 0.20, 0.20, 0.20, 2.10, 0.20, 2.10, 0.20, 0.20, 0.20, 2.10, 1.50, 1.50, 0.20, 0.20, 2.10, 2.10, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 2.10, 2.10, 0.80, 4.70, 0.20, 2.10, 2.10, 2.10, 2.10, 0.20, 0.20, 2.10, 9.90, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 1.50, 0.20, 0.20, 2.10, 0.20, 0.20, 0.20, 2.10, 2.10, 0.20, 0.20, 0.20, 2.10, 2.10};
int valuesLength = sizeof(values) / sizeof(int);
int getMeasure()
{
  int static index = 0;
  index++;
  return values[index - 1];
}
 
int appendToBuffer(int value)
{
  *circularBufferAccessor = value;
  circularBufferAccessor++;
  if (circularBufferAccessor >= circularBuffer + windowSize) 
    circularBufferAccessor = circularBuffer;
}
 
long sum;
int elementCount;
float mean;
float AddValue(int value)
{
  sum -= *circularBufferAccessor;
  sum += value;
  appendToBuffer(value);
 
  if (elementCount < windowSize)
    ++elementCount;
  return (float) sum / elementCount;
}
 
void setup()
{
  Serial.begin(115200);
 
  for (int iCount = 0; iCount < valuesLength; iCount++)
  {
    float med = AddValue(getMeasure());
    Serial.print(values[iCount]);
    Serial.print(",\t");
    Serial.println(med);
  }
}
 
void loop()
{
}
