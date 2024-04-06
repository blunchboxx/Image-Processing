#pragma once
struct Pixel
{
	unsigned char _blueValue = 0;
	unsigned char _greenValue = 0;
	unsigned char _redValue = 0;

	float _blueValueNorm = 0;
	float _greenValueNorm = 0;
	float _redValueNorm = 0;

	bool operator==(const Pixel& rhs)
	{
		if (_blueValue != rhs._blueValue)
		{
			return false;
		}

		else if (_greenValue != rhs._greenValue)
		{
			return false;
		}

		else if (_redValue != rhs._redValue)
		{
			return false;
		}

		else
			return true;
	}

	void setNorm()
	{
		_blueValueNorm = (float)_blueValue / 255.0f;
		_redValueNorm = (float)_redValue / 255.0f;
		_greenValueNorm = (float)_greenValue / 255.0f;
	}

	void muliplyPixel(Pixel& topPixel, Pixel& backgroudPixel, Pixel& outputPixel, char channel)
	{
		if (channel == 'b')
		{
			outputPixel._blueValue = 0.5f + (2 * topPixel._blueValue * backgroudPixel._blueValue) / 255.0f;
		}
		else if (channel == 'g')
		{
			outputPixel._greenValue = 0.5f + (2 * (float)topPixel._greenValue * (float)backgroudPixel._greenValue / 255.0f);
		}
		else if (channel == 'r')
		{
			outputPixel._redValue = 0.5f + (2 * (float)topPixel._redValue * (float)backgroudPixel._redValue / 255.0f);
		}
		
		outputPixel.setNorm();
	}

	void screenPixel(Pixel& topPixel, Pixel& backgroudPixel, Pixel& outputPixel, char channel)
	{
		if (channel == 'b')
		{
			outputPixel._blueValue = 0.5f + 255.0 - ((2 * (255.0f - topPixel._blueValue) * (255.0f - backgroudPixel._blueValue)) / 255.0f);
		}
		else if (channel == 'g')
		{
			outputPixel._greenValue = 0.5f + 255.0 - ((2 * (255.0f - topPixel._greenValue) * (255.0f - backgroudPixel._greenValue)) / 255.0f);
		}
		else if (channel == 'r')
		{
			outputPixel._redValue = 0.5f + 255.0 - ((2 * (255.0f - topPixel._redValue) * (255.0f - backgroudPixel._redValue)) / 255.0f);
		}

		outputPixel.setNorm();
	}
};

