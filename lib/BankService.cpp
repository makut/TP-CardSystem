# include "BankService.h"

std::map<Id, Money> BankService::accounts_ = {{0, 1000000}, {1, 10}, {2, 12000},
                                              {3, 100}, {4, 25000}, {5, 125000}};

std::shared_ptr<Money> BankService::getMoney(const std::shared_ptr<Card> &card)
{
    if (card == nullptr)
        return nullptr;
    if (accounts_.find(card->getId()) != accounts_.end())
        return std::shared_ptr<Money>(new Money(accounts_[card->getId()]));
    return nullptr;
}

bool BankService::transferMoney(const std::shared_ptr<Card> &from, Id to, Money amount)
{
    if (from == nullptr || accounts_.find(from->getId()) == accounts_.end() || accounts_.find(to) == accounts_.end())
        return false;
    if (accounts_[from->getId()] < amount)
        return false;
    accounts_[from->getId()] -= amount;
    accounts_[to] += amount;
    return true;
}

bool BankService::transferMoney(const std::shared_ptr<Card> &from, const std::shared_ptr<Card> &to, Money amount)
{
    if (to == nullptr)
        return false;
    return transferMoney(from, to->getId(), amount);
}
