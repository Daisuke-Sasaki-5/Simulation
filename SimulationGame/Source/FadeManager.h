#pragma once

enum class FadeState
{
	None,
	FadeOut,
	FadeIn
};

class FadeManager
{
public:
	FadeManager();

	void Start();
	void Update();
	void Draw();

	bool IsFadeOutFinished() const;
	bool IsFinished() const;

private:
	FadeState state;

	int alpha;

	const int FadeSpeed = 5;
};