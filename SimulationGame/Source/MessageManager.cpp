#include "MessageManager.h"
#include "DxLib.h"

MessageManager::MessageManager()
{
    message = normalMessage[0];
    isDoublePrice = false;
}

void MessageManager::NextDay()
{
    // 20%‚Å‚‰¿”ƒæ
    isDoublePrice = (GetRand(99) < 20);

    if (isDoublePrice)
    {
        message = "–{“ú‚Í‘Sì•¨‚‰¿”ƒæ!";
    }
    else
    {
        int index = GetRand(MessageCounut - 1);
        message = normalMessage[index];
    }
}

const char* MessageManager::GetCurrentMessage() const
{
    return message;
}

bool MessageManager::IsDoublePriceDay() const
{
    return isDoublePrice;
}
