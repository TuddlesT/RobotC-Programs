#define GetBit(n, i) (((n) >> (i)) & 0x01)
#define SetBit(n, i) ((n) | (1 << (i)))
#define ClrBit(n, i) ((n) & ~(1 << (i)))
//void addSquareGrid1(int gridx, int gridy);
void moveLeft();
void moveRight();
bool canMoveLeft();
bool canMoveRight();
void selectSquare();
void drawGrid1();
void moveDown();
bool floorCollision();
bool brickCollision();
void placeShape();
	word gridMovement[20];
	word gridPlacement[20];
	bool shapePlaced = true;
task main()
{
	while(true)
	{
		if (shapePlaced == true)
		{
			selectSquare();
			shapePlaced = false;
		}
		drawRect(0,0,102,52);
							//if ((getButtonPress(buttonLeft) == 1) && canMoveLeft())
							//{
							//	moveLeft();
							//}
							//else if (getButtonPress(buttonRight) == 1 && canMoveRight())
							//{
							//	moveRight();
							//}
		if(nNxtButtonPressed == 2 && canMoveRight())
		{
			moveLeft();
		}
		else if(nNxtButtonPressed == 1 && canMoveLeft())
		{
			moveRight();
		}
		drawGrid1();
		sleep(500);
		eraseDisplay();
		if ((floorCollision() == true) && (brickCollision() == true))
		{
			moveDown();
		}
		else if ((floorCollision() == false) || (brickCollision() == false))
		{
			placeShape();
			shapePlaced = true;
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
	}
}

void moveRight()
{
	for (int i =0; i < 20; ++i)
	{
		gridMovement[i] = gridMovement[i] >> 1;
	}
}

void selectSquare()
{
	gridMovement[0] = SetBit(gridMovement[0], 4);
	gridMovement[0] = SetBit(gridMovement[0], 5);
	gridMovement[1] = SetBit(gridMovement[1], 4);
	gridMovement[1] = SetBit(gridMovement[1], 5);
}

void drawGrid1()
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (GetBit(gridMovement[i], j) == 1)
			{
				fillRect(i*5+1, j*5+1, i*5+6, j*5+6);
			}
			if (GetBit(gridPlacement[i], j) == 1)
			{
				fillRect(i*5+1, j*5+1, i*5+6, j*5+6);
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
