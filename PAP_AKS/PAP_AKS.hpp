struct PAP
{
	byte coil [5];
  	byte TIME, z = 4;
	unsigned short c;
	short i, j;
  	void direction (bool *clockwize)
  	{
		if (*clockwize)
		{
			j++;
			if (j > 3)
				j = 0;
		}
		else
		{
			j--;
			if (j < 0)
				j = 3;
		}
  	}
  	void light (int *limit, bool clockwize)
	{
		j = 0;
		for (i = 0; i < *limit; i++)
		{
			for (c = 0; c < z; c++)
				j == c ? digitalWrite(coil[c], HIGH) : digitalWrite(coil[c], LOW);
			delay(TIME);
			direction(&clockwize);
		}
	}
	void hard (int *limit, bool clockwize)
	{
		j = 0;
		for (i = 0; i < *limit; i++)
		{
			for (c = 0; c < z; c++)
			{
				if ((c == j || c == j + 1) || (c == 0 && j == 3))
					digitalWrite(coil[c], HIGH);
				else
					digitalWrite(coil[c], LOW);
			}
			delay(TIME);
			direction(&clockwize);
		}
	}
	void precision (int *limit, bool clockwize)
	{
		j = 0;
		for (i = 0; i < *limit; i++)
		{
			for (byte l = 0; l < 2; l++)
			{
				for (c = 0; c < z; c++)
				{
					if (c == j || (clockwize == true && l == 1 && (c == j + 1 || (c == 0 && j == 3))) || (clockwize == false && l == 1 && (c == j - 1 || (c == 3 && j == 0))))
						digitalWrite(coil[c], HIGH);
					else
						digitalWrite(coil[c], LOW);
				}
				delay(TIME);
				if (l == 1)
					direction(&clockwize);
			}
		}
	}
	void rotate (float grade, char mode)
	{
		int d = grade * 2048 / 360;
		bool dir = d > 0 ? true : false;
		if (d < 0)
			d = -d;
		switch (mode)
		{
			case 'n':
				light(&d, dir);
				break;
			case 'h':
				hard(&d, dir);
				break;
			case 'p':
				precision(&d, dir);
				break;
		}
		for (c = 0; c < z; c++)
			digitalWrite(coil[c], LOW);
	}
	void SetMotor (byte a, byte b, byte c, byte d)
	{
		coil[0] = a;
		coil[1] = b;
		coil[2] = c;
		coil[3] = d;
		coil[4] = a;
		for (c = 0; c < z; c++)
			pinMode(coil[c], OUTPUT);
	}
	void SetTime (byte a)
	{
		TIME = a;
	}
};

