#pragma once

namespace OBoyLib
{
  bool isRowZero(const float matrix[16], unsigned int row);
  bool isColumnZero(const float matrix[16], unsigned int column);	
  void divideRowBy(float result[16], float matrix[16], unsigned int row, float value);
  void swapRow(float result[16], float matrix[16], unsigned int rowOne, unsigned int rowTwo);
  void addRow(float result[16], float matrix[16], unsigned int rowOne, unsigned int rowTwo, float factor);
  void loadIdentity(float matrix[16]);
  void copyMatrix(float matrix[16], const float source[16]);
  void multMatrix(float matrix[16], const float matrix0[16], const float matrix1[16]);
  bool inverseMatrix(float matrix[16], const float source[16]);
  void transpose(float matrix[16]);
  void translate(float matrix[16], float x, float y, float z);
  void rotate(float matrix[16], float angle, float x, float y, float z);
  void rotateRzRyRx(float matrix[16], float anglex, float angley, float anglez);
  void scale(float matrix[16], float x, float y, float z);
  void multVector(float result[3], const float matrix[16], const float vector[3]):
  void multPoint(float result[4], const float matrix[16], const float vector[4]);
}