#include "FadeManager.h"
#include "DxLib.h"

FadeManager::FadeManager()
{
    state = FadeState::None;
    alpha = 0;
}

void FadeManager::Start()
{
    state = FadeState::FadeOut;
    alpha = 0;
}

void FadeManager::Update()
{
    switch (state)
    {
    case FadeState::None:
        break;

    case FadeState::FadeOut:
        alpha += FadeSpeed;

        if (alpha >= 255)
        {
            alpha = 255;
            state = FadeState::FadeIn;
        }
        break;

    case FadeState::FadeIn:
        alpha -= FadeSpeed;

        if (alpha <= 0)
        {
            alpha = 0;
            state = FadeState::None;
        }
        break;
    }
}

void FadeManager::Draw()
{
    if (alpha <= 0)
    {
        return;
    }

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

    DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool FadeManager::IsFadeOutFinished() const
{
    return state == FadeState::FadeIn;
}

bool FadeManager::IsFinished() const
{
    return state == FadeState::None;
}
