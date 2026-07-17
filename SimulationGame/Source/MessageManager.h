#pragma once

class MessageManager
{
public:
	MessageManager();

	void NextDay();

	const char* GetCurrentMessage() const;
	bool IsDoublePriceDay() const;

private:
	const char* message;

	bool isDoublePrice;

	static const int MessageCounut = 6;

	const char* normalMessage[MessageCounut] =
	{
		"今日はいい天気です",
		"水やりを忘れないように",
		"作物の残り水量で\n売値が変わるらしい",
		"お金の利用は計画的に",
		"売値が2倍になる日が\nあるらしい",
		"作物は元気かな？"
	};
};