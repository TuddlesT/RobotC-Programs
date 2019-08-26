#define GetBit(n, i) (((n) >> (i)) & 0x01)
#define SetBit(n, i) ((n) | (1 << (i)))
#define ClrBit(n, i) ((n) & ~(1 << (i)))
//void addSquareGrid1(int gridx, int gridy);

int speed = 400;


void moveLeft();
void moveRight();
bool canMoveLeft();
bool canMoveRight();
void selectSquare();
void selectLine();
void selectT();
void selectLRight();
void selectLLeft();
void selectZRight();
void selectZLeft();
void drawGrid1();
void moveDown();
bool floorCollision();
bool brickCollision();
void placeShape();
bool lineCompleteTest(int row);
void lineComplete(int row);
unsigned short gridMovement[20];
unsigned short gridPlacement[20];
unsigned short completedLine[1];
bool shapePlaced = true;
int currentShape;
bool hasMoved = false;
int rotationX;
int rotationY;
int currentRotation;
bool canRotate(int shape);
void rotate(int shape);
int direction = 0;

task main()
{
	while(true)
	{
		direction = 0;
		hasMoved = false;
		for (int i = 0; i < 10; ++i)
		{
			completedLine[0] = SetBit(completedLine[0], i);
		}
		if (shapePlaced == true)
		{
			currentRotation = 0;
			currentShape = abs(rand()%6);
			switch(currentShape)
			{
				case 0:
					selectSquare();
					break;
				case 1:
					selectLine();
					break;
				case 2:
					selectT();
					break;
				case 3:
					selectLRight();
					break;
				case 4:
					selectLLeft();
					break;
				case 5:
					selectZLeft();
					break;
				case 6:
					selectZRight();
					break;
			}
			shapePlaced = false;
		}
		drawRect(0,0,102,52);
		//if ((getButtonPress(buttonUp) == 1) && canMoveRight())
		//{
		//	moveLeft();
		//  direction = 1;
		//}
		//else if (getButtonPress(buttonDown) == 1 && canMoveLeft())
		//{
		//	moveRight();
		//  direction = -1;
		//}
		// else if (getButtonPress(buttonEnter) == 1 && canRotate())
		//{
		//	rotate(currentShape);
		//}
		if(nNxtButtonPressed == 2 && canMoveRight())
		{
			moveLeft();
		}
		else if(nNxtButtonPressed == 1 && canMoveLeft())
		{
			moveRight();
		}
		else if(nNxtButtonPressed == 3 && canRotate(currentShape))
		{
			rotate(currentShape);
		}
		drawGrid1();

		//if (getButtonPress(buttonRight) == 1)
		if (nNxtButtonPressed == 3)
		{
			sleep(speed);
		}
		else
		{
			sleep(speed);
		}
		rotationX = rotationX + direction;
		eraseDisplay();
		if ((floorCollision() == true) && (brickCollision() == true) && hasMoved == false)
		{
			moveDown();
		}
		else if ((floorCollision() == false) || (brickCollision() == false))
		{
			placeShape();
			shapePlaced = true;
		}
		for (int i = 0; i < 20; ++i)
		{
			if (lineCompleteTest(i) == true)
			{
				lineComplete(i);
			}
		}
	}
}

//void addSquareGrid1(int gridx, int gridy)
//{
//	fillRect(gridx*5, gridy*5, gridx*5+5, gridy*5+5);
//	gridMovement[gridy] = SetBit(gridMovement[gridy], gridx);
//}

bool canMoveLeft()
{
	for (int i = 0; i < 20; ++i)
	{
		if (GetBit(gridMovement[i], 0) == 1)
		{
			return false;
		}
	}
	return true;
}

bool canMoveRight()
{
	for (int i = 0; i < 20; ++i)
	{
		if (GetBit(gridMovement[i], 9) == 1)
		{
			return false;
		}
	}
	return true;
}

void moveLeft()
{
	for (int i =0; i < 20; ++i)
	{
		gridMovement[i] = gridMovement[i] << 1;
		eraseDisplay();
		drawGrid1();
		drawRect(0,0,102,52);
		hasMoved = true;
		direction = -1;
	}
}

void moveRight()
{
	for (int i =0; i < 20; ++i)
	{
		gridMovement[i] = gridMovement[i] >> 1;
		eraseDisplay();
		drawGrid1();
		drawRect(0,0,102,52);
		hasMoved = true;
		direction = 1;
	}
}

void selectSquare()
{
	gridMovement[0] = SetBit(gridMovement[0], 4);
	gridMovement[0] = SetBit(gridMovement[0], 5);
	gridMovement[1] = SetBit(gridMovement[1], 4);
	gridMovement[1] = SetBit(gridMovement[1], 5);
	rotationX = 4;
	rotationY = 0;
	currentRotation = 0;
}

void selectLine()
{
	gridMovement[0] = SetBit(gridMovement[0], 3);
	gridMovement[0] = SetBit(gridMovement[0], 4);
	gridMovement[0] = SetBit(gridMovement[0], 5);
	gridMovement[0] = SetBit(gridMovement[0], 6);
	rotationX = 5;
	rotationY = 0;
	currentRotation = 0;
}

void selectT()
{
	gridMovement[0] = SetBit(gridMovement[0], 4);
	gridMovement[1] = SetBit(gridMovement[1], 3);
	gridMovement[1] = SetBit(gridMovement[1], 4);
	gridMovement[1] = SetBit(gridMovement[1], 5);
	rotationX = 4;
	rotationY = 1;
	currentRotation = 0;
}

void selectLRight()
{
	gridMovement[1] = SetBit(gridMovement[1], 3);
	gridMovement[0] = SetBit(gridMovement[0], 3);
	gridMovement[0] = SetBit(gridMovement[0], 4);
	gridMovement[0] = SetBit(gridMovement[0], 5);
	rotationX = 4;
	rotationY = 0;
	currentRotation = 0;
}

void selectLLeft()
{
	gridMovement[1] = SetBit(gridMovement[1], 5);
	gridMovement[0] = SetBit(gridMovement[0], 3);
	gridMovement[0] = SetBit(gridMovement[0], 4);
	gridMovement[0] = SetBit(gridMovement[0], 5);
	rotationX = 4;
	rotationY = 0;
	currentRotation = 0;
}

void selectZLeft()
{
	gridMovement[0] = SetBit(gridMovement[0], 3);
	gridMovement[0] = SetBit(gridMovement[0], 4);
	gridMovement[1] = SetBit(gridMovement[1], 4);
	gridMovement[1] = SetBit(gridMovement[1], 5);
	rotationX = 4;
	rotationY = 0;
	currentRotation = 0;
}

void selectZRight()
{
	gridMovement[0] = SetBit(gridMovement[0], 5);
	gridMovement[0] = SetBit(gridMovement[0], 4);
	gridMovement[1] = SetBit(gridMovement[1], 4);
	gridMovement[1] = SetBit(gridMovement[1], 3);
	rotationX = 4;
	rotationY = 1;
	currentRotation = 0;
}

void drawGrid1()
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (GetBit(gridMovement[i], j) == 1)
			{
				fillRect(i*5+1, j*5+1, i*5+5, j*5+5);
			}
			if (GetBit(gridPlacement[i], j) == 1)
			{
				fillRect(i*5+1, j*5+1, i*5+5, j*5+5);
			}
		}
	}
}

void moveDown()
{
	for (int i = 18; i > -1; --i)
	{
		gridMovement[i+1] = gridMovement[i];
	}
	gridMovement[0] = 0;
	rotationY = rotationY + 1;
}

bool floorCollision()
{
	for (int i = 0; i < 10; i++)
	{
		if (GetBit(gridMovement[19], i) == 1)
		{
			return false;
		}
	}
	return true;
}

void placeShape()
{
	for (int column = 0; column < 10; column++)
	{
		for (int row = 0; row < 20; row++)
		{
			if (GetBit(gridMovement[row], column) == 1)
			{
				gridPlacement[row] = SetBit(gridPlacement[row], column);
			}
			gridMovement[row] = ClrBit(gridMovement[row], column);
		}
	}
}

bool brickCollision()
{
	for (int row = 0; row < 19; row++)
	{
		for (int column = 0; column < 10; column++)
		{
			if (GetBit(gridMovement[row], column) == 1)
			{
				if (GetBit(gridPlacement[row+1], column) == 1)
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool lineCompleteTest(int row)
{
	if (gridPlacement[row] == completedLine[0])
	{
		return true;
	}
	return false;
}

void lineComplete(int row)
{
	for (int i = row; i > 0; --i)
	{
		for (int column = 0; column < 10; ++column)
		{
			gridPlacement[i] = ClrBit(gridPlacement[i], column);
		}
		gridPlacement[i] = gridPlacement[i - 1];
	}
}

bool canRotate(int shape)
{
	if (shape == 1) // Line
	{
		if (currentRotation == 0)
		{
			if ((GetBit(gridPlacement[rotationY - 1], (rotationX)) == 1) || (GetBit(gridPlacement[rotationY - 2], (rotationX)) == 1) || (GetBit(gridPlacement[rotationY + 1], (rotationX)) == 1))
			{
				return false;
			}
		}
		if (currentRotation == 1)
		{
			if ((GetBit(gridPlacement[rotationY], (rotationX + 1)) == 1) || (GetBit(gridPlacement[rotationY], (rotationX - 1)) == 1) || (GetBit(gridPlacement[rotationY], (rotationX - 2)) == 1))
			{
				return false;
			}
		}
	}
	if (shape == 2) // T-Shape
	{
		if (currentRotation == 0)
		{
			if ((GetBit(gridPlacement[rotationY + 1], (rotationX)) == 1))
			{
				return false;
			}
		}
		if (currentRotation == 1)
		{
			if ((GetBit(gridPlacement[rotationY], (rotationX + 1)) == 1))
			{
				return false;
			}
		}
		if (currentRotation == 2)
		{
			if ((GetBit(gridPlacement[rotationY + 1], (rotationX)) == 1))
			{
				return false;
			}
		}
		if (currentRotation == 3)
		{
			if ((GetBit(gridPlacement[rotationY], (rotationX - 1)) == 1))
			{
				return false;
			}
		}
		if (currentShape == 3) // Right-Facing L Shape
		{
			if (currentRotation == 0)
			{
				if ((GetBit(gridPlacement[rotationY - 1], (rotationX)) == 1) || (GetBit(gridPlacement[rotationY + 1], (rotationX)) == 1) || (GetBit(gridPlacement[rotationY - 1], (rotationX + 1)) == 1))
				{
					return false;
				}
			}
			if (currentRotation == 1)
			{
				if ((GetBit(gridPlacement[rotationY], (rotationX - 1)) == 1) || (GetBit(gridPlacement[rotationY], (rotationX + 1)) == 1) || (GetBit(gridPlacement[rotationY - 1], (rotationX + 1)) == 1))
				{
					return false;
				}
			}
			if (currentRotation == 2)
			{
				if ((GetBit(gridPlacement[rotationY + 1], (rotationX)) == 1) || (GetBit(gridPlacement[rotationY - 1], (rotationX)) == 1) || (GetBit(gridPlacement[rotationY - 1], (rotationX - 1)) == 1))
				{
					return false;
				}
			}
			if (currentRotation == 3)
			{
				if ((GetBit(gridPlacement[rotationY], (rotationX + 1)) == 1) || (GetBit(gridPlacement[rotationY], (rotationX - 1)) == 1) || (GetBit(gridPlacement[rotationY + 1], (rotationX - 1)) == 1))
				{
					return false;
				}
			}
		}
		if (currentShape == 4) // Left-Facing L Shape
		{
			if (currentRotation == 0)
			{
				if ((GetBit(gridPlacement[rotationY + 1], (rotationX)) == 1) || (GetBit(gridPlacement[rotationY - 1], (rotationX)) == 1) || (GetBit(gridPlacement[rotationY - 1], (rotationX + 1)) == 1))
				{
					return false;
				}
			}
			if (currentRotation == 1)
			{
				if ((GetBit(gridPlacement[rotationY], (rotationX + 1)) == 1) || (GetBit(gridPlacement[rotationY], (rotationX - 1)) == 1) || (GetBit(gridPlacement[rotationY - 1], (rotationX - 1)) == 1))
				{
					return false;
				}
			}
			if (currentRotation == 2)
			{
				if ((GetBit(gridPlacement[rotationY - 1], (rotationX)) == 1) || (GetBit(gridPlacement[rotationY + 1], (rotationX)) == 1) || (GetBit(gridPlacement[rotationY + 1], (rotationX - 1)) == 1))
				{
					return false;
				}
			}
			if (currentRotation == 3)
			{
				if ((GetBit(gridPlacement[rotationY], (rotationX - 1)) == 1) || (GetBit(gridPlacement[rotationY], (rotationX + 1)) == 1) || (GetBit(gridPlacement[rotationY + 1], (rotationX + 1)) == 1))
				{
					return false;
				}
			}
		}
		if (currentShape == 5)
		{
			if (currentRotation == 0)
			{
				if ((GetBit(gridPlacement[rotationY], (rotationX + 1)) == 1) || (GetBit(gridPlacement[rotationY - 1], (rotationX + 1)) == 1))
				{
					return false;
				}
			}
			if (currentRotation == 1)
			{
				if ((GetBit(gridPlacement[rotationY - 1], (rotationX)) == 1) || (GetBit(gridPlacement[rotationY - 1], (rotationX - 1)) == 1))
				{
					return false;
				}
			}
			if (currentRotation == 2)
			{
				if ((GetBit(gridPlacement[rotationY], (rotationX - 1)) == 1) || (GetBit(gridPlacement[rotationY + 1], (rotationX - 1)) == 1))
				{
					return false;
				}
			}
			if (currentRotation == 3)
			{
				if ((GetBit(gridPlacement[rotationY + 1], (rotationX)) == 1) || (GetBit(gridPlacement[rotationY + 1], (rotationX + 1)) == 1))
				{
					return false;
				}
			}
		}
		if (currentShape == 6)
		{
			if (currentRotation == 0)
			{
				if ((GetBit(gridPlacement[rotationY + 1], (rotationX)) == 1) || (GetBit(gridPlacement[rotationY - 1], (rotationX - 1)) == 1))
				{
					return false;
				}
			}
			if (currentRotation == 1)
			{
				if ((GetBit(gridPlacement[rotationY], (rotationX + 1)) == 1) || (GetBit(gridPlacement[rotationY + 1], (rotationX - 1)) == 1))
				{
					return false;
				}
			}
			if (currentRotation == 2)
			{
				if ((GetBit(gridPlacement[rotationY - 1], (rotationX)) == 1) || (GetBit(gridPlacement[rotationY + 1], (rotationX + 1)) == 1))
				{
					return false;
				}
			}
			if (currentRotation == 3)
			{
				if ((GetBit(gridPlacement[rotationY], (rotationX - 1)) == 1) || (GetBit(gridPlacement[rotationY - 1], (rotationX + 1)) == 1))
				{
					return false;
				}
			}
		}
	}
	return true;
}


void rotate(int shape)
{
	hasMoved = true;
	for (int row = 0; row < 20; ++row)
	{
		for (int column = 0; column < 10; ++column)
		{
			gridMovement[row] = ClrBit(gridMovement[row], column);
		}
	}
	if (shape == 0)
	{
		gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
		gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX + 1));
		gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX));
		gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX + 1));
	}
	if (shape == 1) // Line
	{
		if (currentRotation == 0)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX));
			gridMovement[rotationY - 2] = SetBit(gridMovement[rotationY - 2], (rotationX));
			gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX));
			currentRotation = 1;
		}
		else if (currentRotation == 1)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX + 1));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX - 1));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX - 2));
			currentRotation = 0;
		}
	}
	if (shape == 2) // T-Shape
	{
		if (currentRotation == 0)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX - 1));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX));
			currentRotation = 1;
		}
		else if (currentRotation == 1)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX + 1));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX - 1));
			gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX));
			currentRotation = 2;
		}
		else if (currentRotation == 2)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX + 1));
			currentRotation = 3;
		}
		else if (currentRotation == 3)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX - 1));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX + 1));
			currentRotation = 0;
		}
	}
	if (currentShape == 3) // Right-Facing L Shape
	{
		if (currentRotation == 0)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY - 1] = SetBit(gridMovement[(rotationY - 1)], (rotationX));
			gridMovement[rotationY + 1] = SetBit(gridMovement[(rotationY + 1)], (rotationX));
			gridMovement[rotationY - 1] = SetBit(gridMovement[(rotationY - 1)], (rotationX + 1));
			currentRotation = 1;
		}
		else if (currentRotation == 1)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX - 1));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX + 1));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX + 1));
			currentRotation = 2;
		}
		else if (currentRotation == 2)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX - 1));
			currentRotation = 3;
		}
		else if (currentRotation == 3)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX + 1));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX - 1));
			gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX - 1));
			currentRotation = 0;
		}
	}
	if (currentShape == 4) // Left-Facing L Shape
	{
		if (currentRotation == 0)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX + 1));
			currentRotation = 1;
		}
		else if (currentRotation == 1)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX + 1));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX - 1));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX - 1));
			currentRotation = 2;
		}
		else if (currentRotation == 2)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX));
			gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX));
			gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX - 1));
			currentRotation = 3;
		}
		else if (currentRotation == 3)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX - 1));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX + 1));
			gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX + 1));
			currentRotation = 0;
		}
	}
	if (currentShape == 5)
	{
		if (currentRotation == 0)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX + 1));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX + 1));
			currentRotation = 1;
		}
		else if (currentRotation == 1)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX + 1));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX - 1));
			currentRotation = 2;
		}
		else if (currentRotation == 2)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX - 1));
			gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX - 1));
			currentRotation = 3;
		}
		else if (currentRotation == 3)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX - 1));
			gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX));
			gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX + 1));
			currentRotation = 0;
		}
	}
	if (currentShape == 6)
	{
		if (currentRotation == 0)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX - 1));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX - 1));
			currentRotation = 1;
		}
		else if (currentRotation == 1)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX + 1));
			gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX));
			gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX - 1));
			currentRotation = 2;
		}
		else if (currentRotation == 2)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX + 1));
			gridMovement[rotationY + 1] = SetBit(gridMovement[rotationY + 1], (rotationX + 1));
			currentRotation = 3;
		}
		else if (currentRotation == 3)
		{
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX));
			gridMovement[rotationY] = SetBit(gridMovement[rotationY], (rotationX - 1));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX));
			gridMovement[rotationY - 1] = SetBit(gridMovement[rotationY - 1], (rotationX + 1));
			currentRotation = 0;
		}
	}
}
