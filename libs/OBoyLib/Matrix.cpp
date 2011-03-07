#include <math.h>

using namespace oboylib;

bool isRowZero(const float matrix[16], unsigned int row)
{
	unsigned int column;

	for (column = 0; column < 4; column++)
	{
		if (matrix[column*4+row] != 0.0f)
			return false;
	}
	
	return true;
}
	
bool isColumnZero(const float matrix[16], unsigned int column)
{
	unsigned int row; 

	for (row = 0; row < 4; row++)
	{
		if (matrix[column*4+row] != 0.0f)
			return false;
	}
	
	return true;
}
	
void divideRowBy(float result[16], float matrix[16], unsigned int row, float value)
{
	unsigned int column;

	for (column = 0; column < 4; column++)
	{
		matrix[column*4+row] /= value;
		result[column*4+row] /= value;
	}
}
	
void swapRow(float result[16], float matrix[16], unsigned int rowOne, unsigned int rowTwo)
{
	unsigned int column;

	float temp;
	
	for (column = 0; column < 4; column++)
	{
		temp = matrix[column*4 + rowOne];
		matrix[column*4 + rowOne] = matrix[column*4 + rowTwo];
		matrix[column*4 + rowTwo] = temp;

		temp = result[column*4 + rowOne];
		result[column*4 + rowOne] = result[column*4 + rowTwo];
		result[column*4 + rowTwo] = temp;
	}	
}
	
void addRow(float result[16], float matrix[16], unsigned int rowOne, unsigned int rowTwo, float factor)
{
	unsigned int column;

	for (column = 0; column < 4; column++)
	{
		matrix[column*4+rowOne] += matrix[column*4+rowTwo]*factor;
		result[column*4+rowOne] += result[column*4+rowTwo]*factor;
	}
}

//

void loadIdentity(float matrix[16])
{
	matrix[0] = 1.0f;
	matrix[1] = 0.0f;
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;

	matrix[4] = 0.0f;
	matrix[5] = 1.0f;
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;

	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = 1.0f;
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;
}

void copyMatrix(float matrix[16], const float source[16])
{
	unsigned int i;

	for (i = 0; i < 16; i++)
	{
		matrix[i] = source[i];
	}
}

void multMatrix(float matrix[16], const float matrix0[16], const float matrix1[16])
{
	unsigned int i;
	unsigned int k; 

	float temp[16];

	for (i = 0; i < 16; i++)
	{
		temp[i] = 0.0f;
		
		for(k = 0; k < 4; k++)
		{
			//			  		row   column   		   row column
			temp[i] += matrix0[(i%4)+(k*4)] * matrix1[(k)+((i/4)*4)];
		}
	}
		
	for (i = 0; i < 16; i++)
	{
		matrix[i] = temp[i];
	}
}

bool inverseMatrix(float matrix[16], const float source[16])
{
	unsigned int i;

	unsigned int column;
	unsigned int row;

	float copy[16];

	loadIdentity(matrix);
	
	//
	// Copy the original matrix as we want to manipulate it
	//
	for (i = 0; i < 16; i++)
	{
		copy[i] = source[i];
	}
	
	//
	// Make triangle form
	//
	for (column = 0; column < 4; column++)
	{
		unsigned int row;

		for (row = column; row < 4; row++)
		{
			//
			// Is row all zero, then return false			
			//
			if (isRowZero(copy, row))
				return false;	

			//
			// Divide, if not zero, by copy[column*4+row]
			//
			if (copy[column*4+row] != 0.0f)
			{
				divideRowBy(matrix, copy, row, copy[column*4+row]);
			}
		}

		//
		// Is column all zero, then return false
		//		
		if (isColumnZero(copy, column))
			return false;
		
		//
		// Is pivot [column*4+column] = 0.0f
		//
		for (row = column+1; row < 4; row++)
		{
			if (copy[column*4+row] == 1.0f)
			{
				//
				// Swap with pivot row = column
				//
				swapRow(matrix, copy, column, row);
				
				break;
			}
		}
		
		for (row = column+1; row < 4; row++)
		{
			//
			// Subtract, [column*4+row] not zero, current row minus pivot row = column
			//
			if (copy[column*4+row] != 0.0f)
			{
				addRow(matrix, copy, row, column, -1.0f);
			}
		}
	}
	
	//
	// Make diagonal form
	//
	for (column = 3; column >= 0; column--)
	{
		for (row = column-1; row >= 0; row--)
		{
			//
			// Subtract, if [column*4+row] not zero, current row minus pivot row = column with factor [column*4+row]
			//
			if (copy[column*4+row] != 0.0f)
			{
				addRow(matrix, copy, row, column, -copy[column*4+row]);
			}
		}
	}

	return true;
}


void transpose(float matrix[16])
{
	unsigned int column; 
	unsigned int row; 

	float temp[16];

	copyMatrix(temp, matrix);

	for (column = 0; column < 4; column++)
	{
		for (row = 0; row < 4; row++)
		{
			matrix[row*4+column] = temp[column*4+row];
		}
	}
}


void translate(float matrix[16], float x, float y, float z)
{
	float temp[16];

	loadIdentity(temp);

	temp[12] = x;
	temp[13] = y;
	temp[14] = z;
	
	multMatrix(matrix, matrix, temp);
}

void rotate(float matrix[16], float angle, float x, float y, float z)
{
	float temp[16];

	float s = sinf(2.0f*PIf*angle/360.0f);
	float c = cosf(2.0f*PIf*angle/360.0f);

	loadIdentity(temp);

	temp[0] = x*x*(1 - c) + c;
	temp[1] = x*y*(1 - c) + z*s;
	temp[2] = x*z*(1 - c) - y*s;

	temp[4] = x*y*(1 - c) - z*s;
	temp[5] = y*y*(1 - c) + c;
	temp[6] = y*z*(1 - c) + x*s;

	temp[8] = x*z*(1 - c) + y*s;
	temp[9] = y*z*(1 - c) - x*s;
	temp[10] = z*z*(1 - c) + c;

	multMatrix(matrix, matrix, temp);
}

void rotateRzRyRx(float matrix[16], float anglex, float angley, float anglez)
{
	float temp[16];

	float rx = 2.0f*PIf*anglex/360.0f;
	float ry = 2.0f*PIf*angley/360.0f;
	float rz = 2.0f*PIf*anglez/360.0f;
	float sx = sinf(rx);
	float cx = cosf(rx);
	float sy = sinf(ry);
	float cy = cosf(ry);
	float sz = sinf(rz);
	float cz = cosf(rz);
	
	loadIdentity(temp);

	temp[0] = cy*cz;
	temp[1] = cy*sz;
	temp[2] = -sy;

	temp[4] = cz*sx*sy-cx*sz;
	temp[5] = cx*cz+sx*sy*sz;
	temp[6] = cy*sx;

	temp[8] = cx*cz*sy+sx*sz;
	temp[9] = -cz*sx+cx*sy*sz;
	temp[10] = cx*cy;

	multMatrix(matrix, matrix, temp);
}

void scale(float matrix[16], float x, float y, float z)
{
	float temp[16];

	loadIdentity(temp);

	temp[0] = x;
	temp[5] = y;
	temp[10] = z;
	
	multMatrix(matrix, matrix, temp);
}

void multVector(float result[3], const float matrix[16], const float vector[3])
{
	unsigned int i;

	float temp[3];

	for (i = 0; i < 3; i++)
		temp[i] = matrix[i]*vector[0] + matrix[4+i]*vector[1] + matrix[8+i]*vector[2];
	
	for (i = 0; i < 3; i++)	
    	result[i] = temp[i];
}

void multPoint(float result[4], const float matrix[16], const float vector[4])
{
	unsigned int i;

	float temp[4];

	for (i = 0; i < 4; i++)
		temp[i] = matrix[i]*vector[0] + matrix[4+i]*vector[1] + matrix[8+i]*vector[2] + matrix[12+i]*vector[3];
	
	for (i = 0; i < 3; i++)	
    	result[i] = temp[i];
        
    if (temp[3] != 0.0f)
    {
		for (i = 0; i < 3; i++)	
    		result[i] /= temp[3];
    }
}
