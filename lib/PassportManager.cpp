# include "PassportManager.h"

std::shared_ptr<Passport> PassportManager::getPassport(const std::shared_ptr<Card> &card) const
{
    if (cache_.find(card) != cache_.end())
        return cache_[card];
    std::shared_ptr<Passport> answer = ps_.getPassport(card);
    cache_[card] = answer != nullptr ? std::make_shared<Passport>(*answer) : nullptr;
    if (answer != nullptr)
        passports_.insert(std::make_shared<Passport>(*answer));
    return answer;
}

bool PassportManager::passportValidation(const std::shared_ptr<Passport> &pass) const
{
    if (passports_.find(pass) != passports_.end())
        return true;
    return ps_.passportValidation(pass);
}