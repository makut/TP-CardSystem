# pragma once
# include <map>
# include "Card.h"
# include "Terminal.h"

using Money = size_t;

/**
 * @brief Service for managing of the bank system
 * @details Let transfer money between accounts, withdraw money.
 */
class BankService
{
public:
    BankService() = default;
    BankService(const BankService&) = default;
    ~BankService() = default;

    /**
     * @brief Getter the amount of money using Card
     * @param  shared_ptr to Card
     * @return shared_ptr to Money. It is nullptr, if the card is invalid or no data in the system returns nullptr
     */
    std::shared_ptr<Money> getMoney(const std::shared_ptr<Card>&);

    /**
     * @brief Transfer money between two accounts.
     * @details If one of the accounts is invalid or not enough money no operation occurs.
     * 
     * @param from shared_ptr to Card, which you want to withdraw money from.
     * @param to Id of the Card, which you want to withdraw money to.
     * @param amount Amount of money you want to transfer
     * 
     * @return true, if operation succeeded, or false, if id didn't.
     */
    bool transferMoney(const std::shared_ptr<Card> &from, Id to, Money amount);

    /**
     * @brief Transfer money between two accounts.
     * @details If one of the accounts is invalid or not enough money no operation occurs.
     * 
     * @param from shared_ptr to Card, which you want to withdraw money from.
     * @param to shared_ptr to the Card, which you want to withdraw money to.
     * @param amount Amount of money you want to transfer
     * 
     * @return true, if operation succeeded, or false, if id didn't.
     */
    bool transferMoney(const std::shared_ptr<Card> &from, const std::shared_ptr<Card> &to, Money amount);
private:
    static std::map<Id, Money> accounts_;
};
