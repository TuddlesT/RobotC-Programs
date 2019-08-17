void ThrowDice();

task main()
{ eraseDisplay();
	displayCenteredBigTextLine(1, "Hello World");
	// playSoundFile();
	while(true)
	{
		eraseDisplay();
		displayCenteredBigTextLine(5,"Play ?");
		displayCenteredBigTextLine(10, "NO      YES");

		if(getButtonPress(buttonLeft) == 1)
		{
			eraseDisplay();
			displayCenteredBigTextLine(1, "Bye Bye");
			playSound(soundException);
			sleep(2000);
			break;
		}
		if(getButtonPress(buttonRight) == 1)
		{
			eraseDisplay();
			playSound(soundBlip);
			ThrowDice();
		}
	}
}
 void ThrowDice()
{	int x;
	eraseDisplay();
	displayCenteredBigTextLine(1,"Throwing dice");
	x= abs(rand()%6)+1;
	if(x==1)playSoundFile("One");
	if(x==2)playSoundFile("Two");
	if(x==3)playSoundFile("Three");
	if(x==4)playSoundFile("Four");
	if(x==5)playSoundFile("Five");
	if(x==6)playSoundFile("Six");
	displayCenteredBigTextLine(10,"%d",x);
	sleep(2000);


}
