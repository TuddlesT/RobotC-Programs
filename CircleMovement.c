task main()
{
	int x = 83; // Player's x coordinate
	int y = 63; // Player's y coordinate
	int radius = 16; // Radius of Player
	int fruit = 1; // Does the fruit exist
	int xf = abs(rand()%167); // Fruit's x coordinate
	int yf = abs(rand()%127); // Fruit's y coordinate
	while(true) {
		if (getButtonPress(buttonLeft) == 1)
		{
			x = x-1;
		}
		if(getButtonPress(buttonRight) == 1)
		{
			x = x+1;
		}
		if (getButtonPress(buttonUp) == 1)
		{
			y = y+1;
		}
		if(getButtonPress(buttonDown) == 1)
		{
			y = y-1;
		}
		if (fruit == 0)
		{
			xf = abs(rand()%167);
			yf = abs(rand()%127);
			fruit = 1;
		}
		if (x>xf-radius && x<xf+radius && y>yf-radius && y<yf+radius && fruit == 1)
		{
			radius = radius + 5;
			fruit = 0;
		}
		drawCircle (x, y, radius);
		drawCircle (xf, yf, 8);
		sleep(20);
		eraseDisplay();
	}
}
