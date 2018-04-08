# include <iostream>
# include <memory>
# include "lib/Terminal.h"
# include "lib/PassportService.h"
# include "lib/PassportManager.h"
# include "lib/BankService.h"

template<Id ID>
class SimpleTerminal : public ITerminal
{
public:
    SimpleTerminal() = default;
    SimpleTerminal(const SimpleTerminal&) = default;
    ~SimpleTerminal() = default;
    virtual std::shared_ptr<Card> getCard() override
    {
        return std::shared_ptr<Card>(new Card(ID));
    }
};

static PassportManager pm;
static BankService bs;

inline void passportTest()
{
    std::shared_ptr<ITerminal> term(new SimpleTerminal<0>);
    std::shared_ptr<Card> card = term->getCard();
    EXPECT_EQ(card->getId(), 0);
    std::shared_ptr<Passport> passp = pm.getPassport(card);
    EXPECT_EQ(passp->getFullName(), "Utushkin Maxim Alexandrovich");
    EXPECT_EQ(passp->getDateBirth(), Date(1999, 06, 07));
    EXPECT_EQ(passp->getNumber(), "1234123456");    
}

TEST(PassportTest, ValidCardTest)
{
    passportTest();
}

TEST(PassportTest, CacheTest)
{
    passportTest();
}

TEST(PassportTest, InvalidCardTest)
{
    std::shared_ptr<ITerminal> term(new SimpleTerminal<100>);
    std::shared_ptr<Card> card = term->getCard();
    std::shared_ptr<Passport> passp = pm.getPassport(card);
    EXPECT_EQ(passp, nullptr);
}

TEST(BankTest, ValidCardTest)
{
    std::shared_ptr<ITerminal> term(new SimpleTerminal<0>);
    std::shared_ptr<Card> card = term->getCard();
    std::shared_ptr<Money> money = bs.getMoney(card);
    EXPECT_EQ(*money, 1000000);
}

TEST(BankTest, InvalidCardTest)
{
    std::shared_ptr<ITerminal> term(new SimpleTerminal<25>);
    std::shared_ptr<Card> card = term->getCard();
    std::shared_ptr<Money> money = bs.getMoney(card);
    EXPECT_EQ(money, nullptr);
    std::shared_ptr<Money> money_from_nullptr = bs.getMoney(nullptr);
    EXPECT_EQ(money_from_nullptr, nullptr);
}

TEST(BankTest, ValidOperationTest)
{
    std::shared_ptr<ITerminal> term0(new SimpleTerminal<0>);
    std::shared_ptr<ITerminal> term1(new SimpleTerminal<1>);
    std::shared_ptr<Card> card0 = term0->getCard();
    std::shared_ptr<Card> card1 = term1->getCard();
    bool op = bs.transferMoney(card0, card1, 500000);
    EXPECT_EQ(op, true);
    EXPECT_EQ(*bs.getMoney(card0), 500000);
    EXPECT_EQ(*bs.getMoney(card1), 500010);
    op = bs.transferMoney(card1, card0, 500000);
    EXPECT_EQ(op, true);
    EXPECT_EQ(*bs.getMoney(card0), 1000000);
    EXPECT_EQ(*bs.getMoney(card1), 10);
}

TEST(BankTest, InvalidOperationTest)
{
    std::shared_ptr<ITerminal> term0(new SimpleTerminal<0>);
    std::shared_ptr<ITerminal> term1(new SimpleTerminal<42>);
    std::shared_ptr<Card> card0 = term0->getCard();
    std::shared_ptr<Card> card1 = term1->getCard();
    bool op = bs.transferMoney(card0, card1, 500000);
    EXPECT_EQ(op, false);
    EXPECT_EQ(*bs.getMoney(card0), 1000000);
    EXPECT_EQ(bs.getMoney(card1), nullptr);
}